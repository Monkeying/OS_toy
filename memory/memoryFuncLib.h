/*
所有的函数包含
 */
#include<stdio.h>
#include "MACRO.H"
//#include "basic_data_struct.h"
#include "../sys_global.h"
#include "../error/systemError.c"
//===========================================================================<PART 1>======================================================================
void Initialize(void);									//初始化模拟内存和磁盘的文件

void BitMapToBuffer();	//把文件中的位图拷入到真正的内存数组中，使读取速度增快

void BufferToBitMap();	//把数组中的数据拷入到文件中的位图中，使得下次打开有正确的页表位图

int FindFreeBufferMem();					//查找内存中的第一个空闲页表位图

int FindFreeBufferDisk();				//查找硬盘中的第一个空闲位图

int FindTotalFreeBufferMem();				//查找内存中所有空闲位图的数目总数

void MaskBuffer(char *buffer, int numOfBit);				//置特定位图的值为1

void ClearBuffer(char *buffer, int numOfBit);			//置特定位图的值为0
//===========================================================================<PART 2>======================================================================
int _write(unsigned int virAddr, unsigned int size, unsigned int count, void *buffer);//写入字节

void *_read(unsigned int virAddr, unsigned int size, unsigned int count);//读出字节

int _mallocSegment(int sizeInByte);//申请一段地址，返回逻辑段首页逻辑页号

unsigned int _freeSegment(unsigned int firstLinnerPage_num, int sizeInpage);//释放逻辑地址中的一段地址

int _malloc(unsigned char processName, int sizeInByte);//一个程序段内的分配没有回收。

unsigned int _free(unsigned int virAddr);

int VirAddr2LinnerAddr(unsigned int virAddr);			//虚地址和实地址的转换

int GetPhyAddr(unsigned char processName, int linnerAddr);		//由线性地址计算得到内存或磁盘中的物理地址

int PageSwap(unsigned int pageInDisk, unsigned int pageInMem, unsigned int linnerPage_num);			//页的换入/换出

unsigned int PageSwapStratgy(unsigned char processName);//得到该段中可以换出的页表下标，FIFO
//===========================================================================<PART 3>======================================================================
int CreateProcess(unsigned char processName, int sizeInByte);		//创建一个进程内存

void DelProcess(unsigned char processName);						//注销进程内存