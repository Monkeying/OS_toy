/*
整个系统的全局变量
 */
#include"memory/MACRO.h"
#include<stdio.h>

struct GLOBAL{
	FILE *mem;
	FILE *disk;
	char diskBuffer[DISK_SIZE/PAGE_SIZE];
	char memBuffer[MEM_SIZE/PAGE_SIZE];
}global;