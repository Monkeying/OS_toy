/*
进程内存页表入口表项
内存使用记录项
 */

#include"MACRO.h"
#include<time.h>

//进程内存页表入口表项
struct processEntry{
	char processName[24];
	unsigned int size;//所需字节B的数量
	unsigned int FirstPage;//所在第一页的逻辑页表下标，(DISK_SIZE+MEM_SIZE)/PAGE_SIZE
	unsigned int byte2malloc;
	struct processEntry * nextProcess;
};

//内存物理页使用记录项
struct memPageRecord{
	unsigned int page_num;//逻辑页号
	unsigned int phyAddrInDisk;
	time_t timeStamp;
	int isModified;
	int isReadable;
};

//逻辑页分配纪录
struct linnerPageRecord{
	struct linnerPageRecord *preLinnerPage;
	struct linnerPageRecord *nextLinnerPage;
	unsigned int firstLinnerPage_num;
	unsigned int size;
};