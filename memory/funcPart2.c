/*
内存虚拟内存实现
在本次试验中，虚拟地址包含段地址，但不处理段项。直接程序首地址等于段地址
逻辑地址=段地址+段内偏移地址。unsigned int
线性偏移地址=程序起始地址+段内偏移地址。int
物理地址=页地址+页内偏移地址

页表统一编号，页表从内存开始编号一直到磁盘。
 */
#include "funcPart1.c"

int _write(char *processName, unsigned int virAddr, char ByteContent)//写入字符
{
	int i = 0;
	int linnerAddr = VirAddr2LinnerAddr(processName, virAddr);//获取线性地址,在非分页结构下，等同于物理地址
	printf("linnerAddr: %d \n",linnerAddr);
	if (linnerAddr >= 0)
	{
		int phyAddr = GetPhyAddr(processName, linnerAddr);//获取物理地址
		printf("phyAddr %d\n",phyAddr);
		if (phyAddr >= 0)
		{
			unsigned int page_num = phyAddr / PAGE_SIZE;
			printf("page_num %d\n", page_num);
			for (i = 0; i < MEM_SIZE/PAGE_SIZE; i++)
			{
				if (global.MMU[i] != NULL && global.MMU[i]->page_num == page_num)
				{
					global.MMU[i]->isModified = 1;
					fseek(global.mem, phyAddr, 0);					
					fputc(ByteContent, global.mem);
				
					return 1;
				}
			}			
		}
	}
}

char _read(char *processName, unsigned int virAddr)//读出字符
{
	int i = 0;
	int linnerAddr = VirAddr2LinnerAddr(processName, virAddr);//获取线性地址,在非分页结构下，等同于物理地址
	printf("linnerAddr: %d \n",linnerAddr);
	if (linnerAddr >= 0)
	{
		int phyAddr = GetPhyAddr(processName, linnerAddr);//获取物理地址
		printf("phyAddr %d\n",phyAddr);
		if (phyAddr >= 0)
		{
			unsigned int page_num = phyAddr / PAGE_SIZE;
			printf("page_num %d\n", page_num);
			for (i = 0; i < MEM_SIZE/PAGE_SIZE; i++)
			{
				if (global.MMU[i] != NULL && global.MMU[i]->page_num == page_num)
				{
					fseek(global.mem, phyAddr, 0);	
					char result = fgetc(global.mem);
					return result;
				}
			}			
		}
	}
}

int VirAddr2LinnerAddr(char *processName, unsigned int virAddr)			//虚地址和实地址的转换
{
	unsigned int segment_num = virAddr & 0xff000000;//获取前8位段项,这里的段项和processEntry有啥关系不？

	unsigned int segment_offset = virAddr & 0x00ffffff;//获取末24位段内偏移地址，4M

	int i = 0;
	int linnerAddr = 0;
	struct processEntry *tempPtr = global.processEntryList;
	while (tempPtr != NULL)
	{
		if (*(tempPtr->processName) == *processName)
		{
			if (segment_offset <= tempPtr->size)
			{
				linnerAddr = tempPtr->FirstPage * PAGE_SIZE + segment_offset;//段地址*页大小 + 段内偏移地址 = 线性地址
				return linnerAddr;
			}
			else
			{
				return -1;//虚拟地址给出来的超出了内存分配给他的地址
			}
		}
		tempPtr = tempPtr->nextProcess;
	}
	return -2;//该进程不存在于进程列表中
}

int GetPhyAddr(char *processName, int linnerAddr)		//由线性地址计算得到内存或磁盘中的物理地址
{
	int i = 0;
	unsigned int page_num = linnerAddr / PAGE_SIZE;//逻辑页
	unsigned int page_offset = linnerAddr % PAGE_SIZE;
	printf("%d       %d\n",page_num,page_offset);
	for (i = 0; i < MEM_SIZE/PAGE_SIZE && global.MMU[i] != NULL; i++)
	{
		if (global.MMU[i]->page_num == page_num)//该逻辑页在内存中
		{
			return i*PAGE_SIZE + page_offset;//返回该物理页（内存中）地址+页内偏移
		}
	}
	printf("here\n");
	//该逻辑页在磁盘中
	unsigned int swapOutPage = PageSwapStratgy(processName);
	PageSwap(page_num, swapOutPage);//将该逻辑页换到内存中
	return swapOutPage*PAGE_SIZE + page_offset;
}
int PageSwap(unsigned int pageInDisk, unsigned int pageInMem)			//页的换入/换出
{
	printf("inDisk:%d inMem:%d\n",pageInDisk,pageInMem);
	char temp;
	int i = 0;
	if (global.MMU[pageInMem] == NULL)//相当于直接从磁盘读入内存
	{
		global.MMU[pageInMem] = malloc(sizeof(struct memPageRecord));
		global.MMU[pageInMem]->isModified = 0;//剩下的初始化在后面完成
	}
	if (global.MMU[pageInMem]->isModified)//当存在改动的时候需要将其写回(新分配的时候需要将其都置为0)
	{
		fseek(global.disk, global.MMU[pageInMem]->phyAddrInDisk, 0);
		fseek(global.mem,  pageInMem * PAGE_SIZE, 0);
		
		for (i = 0; i < PAGE_SIZE; i++)
		{
			temp = fgetc(global.mem);
			fputc(temp, global.disk);
		}
	}

	fseek(global.disk, pageInDisk * PAGE_SIZE - MEM_SIZE, 0);
	//逻辑页在磁盘中的物理地址是pageInDisk * PAGE_SIZE - MEM_SIZE
	fseek(global.mem,  pageInMem * PAGE_SIZE, 0);
	for (i = 0; i < PAGE_SIZE; i++)
	{
		temp = fgetc(global.disk);
		fputc(temp, global.mem);
	}
	global.MMU[pageInMem]->page_num = pageInDisk;
	time( &global.MMU[pageInMem]->timeStamp );//纪录换入时间
	global.MMU[pageInMem]->isModified = 0;
	global.MMU[pageInMem]->isReadable = 1;
	global.MMU[pageInMem]->phyAddrInDisk = pageInDisk * PAGE_SIZE - MEM_SIZE;

	return 1;
}

unsigned int PageSwapStratgy(char *processName)//得到该段中可以换出的页表下标，FIFO
{
	int i = 0;
	int freePage = GetFreePageAddr();
	if (freePage != -1)
	{
		return freePage;//内存中第一个空页表
	}
	else
	{
		struct processEntry *tempPtr = global.processEntryList;
		while (tempPtr != NULL)
		{
			if (*tempPtr->processName == *processName)
			{
				int page_count = tempPtr->size/PAGE_SIZE;
				if (tempPtr->size % PAGE_SIZE != 0)
				{
					page_count += 1;
				}
				int j = 0;
				for (i = 0, j = 0; i < page_count; i++)
				{					
					unsigned int fisrtInPage = 0;
					time_t tempTimeStamp = 0xffffffff;
					for (j = 0; j < MEM_SIZE/PAGE_SIZE; j++)
					{
						if (global.MMU[j] != NULL && global.MMU[j]->page_num == tempPtr->FirstPage + i)
						{
							if (global.MMU[j]->timeStamp < tempTimeStamp)
								fisrtInPage = j;
						}
					}
				}
				return j;//该程序段中最早进来的一页
			}
			tempPtr = tempPtr->nextProcess;
		}
	}
}

int GetFreePageAddr()									//在内存未满的情况下发生缺页异常，返回内存中的空闲页地址
{
	return  FindFreeBufferMem();
}

main()
{
	Initialize();
	printf("%d\n",_write("baseProcess",0x00000110,0x55));
	printf("%x\n",_read("baseProcess",0x00000110) );
}