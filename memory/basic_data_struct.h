/*
进程内存页表入口表项
内存使用记录项
 */



//进程内存页表入口表项
typeof struct{
	char processName[24];
	unsigned int size;
	unsigned int FirstPage;
}processEntry;

//内存使用记录项
typeof struct{
	operCodeT operation;
	char procName[24];
	unsigned int sizeORaddr;
	unsigned char data;
}InstructionT;