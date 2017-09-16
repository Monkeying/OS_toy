/*
进程内存页表入口表项
内存使用记录项
 */

#include"MACRO.h"
#include<time.h>

//进程内存页表入口表项
struct processEntry{
	char *processName;
	unsigned int size;//所需字节B的数量
	unsigned int FirstPage;//所在第一页的逻辑页表下标，(DISK_SIZE+MEM_SIZE)/PAGE_SIZE
	struct processEntry * nextProcess;
};

//内存使用记录项
struct memPageRecord{
	unsigned int page_num;
	unsigned int phyAddrInDisk;
	time_t timeStamp;
	int isModified;
	int isReadable;
};
