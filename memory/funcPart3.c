/*
进程内存分配
 */
#include "funcPart2.c"

int CreateProcess(char *processName, int sizeInByte)		//创建一个进程
{
	struct processEntry *tempPtr = global.processEntryList;
	if (tempPtr != NULL)
	{
		while (tempPtr->nextProcess != NULL)
		{
			if (strcmp(tempPtr->processName, processName) == 0)
			{
				return -1;//该进程名称已存在
			}
			tempPtr = tempPtr->nextProcess;
		}	
		if (strcmp(tempPtr->processName,processName) == 0)
		{
			printf("%s %s\n",tempPtr->processName,processName);
			return -1;//该进程名称已存在
		}
	}

	int firstLinnerPage_num = _mallocSegment(sizeInByte);
	if (firstLinnerPage_num >= 0)
	{
		tempPtr->nextProcess = malloc(sizeof(struct processEntry));
		strcpy(tempPtr->nextProcess->processName, processName);
		tempPtr->nextProcess->size = sizeInByte;
		tempPtr->nextProcess->FirstPage = firstLinnerPage_num;//纪录该进程的虚拟段地址开始
		tempPtr->nextProcess->byte2malloc = 0;//该进程的段内地址从0开始分配
		tempPtr->nextProcess->nextProcess = NULL;

		return firstLinnerPage_num*PAGE_SIZE;//返回逻辑页地址
	}
	else//虚存地址不足
	{
		return -2;//虚存地址不足
	}
}

void DelProcess(char *processName)						//注销进程
{
	;
}

void AllocFirstPage(FILE *men, int addr, int size, int *memBuffer, int *diskBuffer);	//分配进程的一级页表

void AllocSecondPage(FILE *mem, FILE *disk, int addr, int size, int MorD, int *memBuffer, int *diskBuffer);	//对指定的二级页表进行分配

void AllocPageFrame(FILE *mem, int addr);				//分配进程的页

void DelProcess(char *processName);						//删除特定名字的进程

void DelFirstPage(FILE *mem, int addr, int size, int *memBuffer, int *diskBuffer);	//删除进程的一级页表

void DelSecondPage(FILE *mem, FILE *disk, int addr, int size, int MorD, int *memBuffer, int *diskBuffer);	//删除进程的二级页表

int FindFreeProcessEntry(FILE *mem);					//查找空闲进程表项

int FindProcssEntry(FILE *mem, char *processName);		//查找特定名字的进程的进程表项首地址

char Read(char *processName, unsigned int virAddr);		//读进程

main()
{
	Initialize();
	if (CreateProcess("testProcess",4*PAGE_SIZE+100) >= 0 )
	{
		unsigned int i = _malloc("testProcess",4);
		_write("testProcess", i, "four");
		printf("read result :%s\n", _read("testProcess", i, 4));
	}

	fclose(global.mem);
	fclose(global.disk);
}