/*
重载运算符的封装
 */
#include "funcPart3.c"

class _int//返回段内地址，进程名称默认为main. -1内存已满，-2程序不存在
{
public:
	int addr;

	_int()
	{
		this->addr = -1;
	}
	_int(unsigned char processName)
	{
		this->addr = _malloc(processName, sizeof(int));
		if (this < 0)
		{
			printf("申请失败\n");
			this->~_int();
		}
	}
	~_int()
	{
		_free(this->addr);
	}
	bool setAddr(unsigned int addr)
	{
		this->addr = addr;
		return  1;
	}
	int operator +()
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		return *temp;
	}
	_int * operator &()
	{
		//return this->addr;
		return this;
	}	
	void operator =(int num)//注意和申请语句分开，这个只有赋值功能
	{
		_write(this->addr,sizeof(int), 1, &num);
	}
	void operator =(_int copy)
	{
		this->addr = copy.addr;
	}
	int operator +(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = *temp + num;
		return *temp;
	}
	int operator -(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = *temp - num;
		return *temp;
	}
	int operator *(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = (*temp) * num;
		return *temp;
	}
	int operator /(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = *temp / num;
		return *temp;
	}
	int operator %(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = *temp % num;
		return *temp;
	}
	int operator ++(int)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = *temp + 1;
		_write(this->addr,sizeof(int), 1, temp);
		temp = (int *)_read(this->addr,sizeof(int), 1);
		return *temp;
	}
	void operator +=(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		*temp = *temp + num;
		_write(this->addr,sizeof(int), 1, temp);
		temp = (int *)_read(this->addr,sizeof(int), 1);
	}
	bool operator <(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		if (*temp < num)
		{
			return 1;
		}
		return 0;
	}
	bool operator >(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		if (*temp > num)
		{
			return 1;
		}
		return 0;
	}
	bool operator ==(int num)
	{
		int *temp = (int *)_read(this->addr,sizeof(int), 1);
		if (*temp == num)
		{
			return 1;
		}
		return 0;
	}
};
class _char
{
public:
	int addr;

	_char()
	{
		this->addr = -1;
	}
	_char(unsigned char processName)
	{
		this->addr = _malloc(processName, sizeof(char));
		if (this < 0)
		{
			printf("申请失败\n");
			this->~_char();
		}
	}
	~_char()
	{
		_free(this->addr);
	}
	int operator *()
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		return *temp;
	}
	_char * operator &()
	{
		//return this->addr;
		return this;
	}
	void operator =(char character)//注意和申请语句分开，这个只有赋值功能
	{		
		_write(this->addr,sizeof(char), 1, &character);
	}
	int operator +(int num)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		*temp = *temp + num;
		return *temp;
	}
	int operator -(int num)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		*temp = *temp - num;
		return *temp;
	}
	bool operator <(int num)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		if (*temp < num)
		{
			return 1;
		}
		return 0;
	}
	bool operator >(int num)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		if (*temp > num)
		{
			return 1;
		}
		return 0;
	}
	bool operator ==(int num)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		if (*temp == num)
		{
			return 1;
		}
		return 0;
	}
	bool operator ==(char character)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		if (*temp == character)
		{
			return 1;
		}
		return 0;
	}
	bool operator >(char character)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		if (*temp > character)
		{
			return 1;
		}
		return 0;
	}
	bool operator <(char character)
	{
		char *temp = (char *)_read(this->addr,sizeof(char), 1);
		if (*temp < character)
		{
			return 1;
		}
		return 0;
	}
};
class int_ARRAY
{
public:
	int addr;
	unsigned int count;

	int_ARRAY(unsigned char processName, unsigned int count)
	{
		this->addr = _malloc(processName, sizeof(int)*count);
		this->count = count;
		if (this->addr < 0)
		{
			printf("申请失败\n");
			this->~int_ARRAY();
		}
	}
	~int_ARRAY()
	{
		_free(this->addr);
	}
	int_ARRAY * operator &()
	{
		//int *temp = (int *)_read(this->addr,sizeof(int), this->count);
		//return temp;
		return this;
	}
	unsigned int getAddr()
	{
		return this->addr;
	}
	int operator [](unsigned int i)//仅仅能够读取，不能赋值
	{
		int *temp = (int *)_read(this->addr + i * sizeof(int), sizeof(int), 1);
		return *temp;
	}
	bool assignment(unsigned int i, int value)
	{
		if (_write(this->addr + i * sizeof(int), sizeof(int), 1, &value))
		{
			int *temp = (int *)_read(this->addr + i * sizeof(int),sizeof(int), 1);
			return 1;
		}	
		else
		{
			return 0;
		}	
	}
};

class int_ARRAY_ARRAY
{
public:
	int_ARRAY *addr;
	unsigned int lines;
	unsigned int columns;

	int_ARRAY_ARRAY()
	{
		this->addr = NULL;
	}
	int_ARRAY_ARRAY(unsigned char processName, unsigned int lines, unsigned int columns)
	{
		int i = 0;
		this->addr = (int_ARRAY *)malloc(sizeof(int_ARRAY *)*lines);
		for (i = 0; i < lines; i++)
		{
			this->addr[i] = int_ARRAY(processName, columns);			
		}
		this->columns = columns;
		this->lines = lines;
		if (this->addr < 0)
		{
			printf("申请失败\n");
			this->~int_ARRAY_ARRAY();
		}
	}
	~int_ARRAY_ARRAY()
	{
		;//_free(this->addr);
	}
	int_ARRAY operator [](unsigned int i)//仅仅能够读取，不能赋值
	{		
		return this->addr[i];
	}
	bool assignment(unsigned int lines, unsigned int columns, int value)
	{
		return this->addr[lines].assignment(columns, value);
	}
};

int main()
{
	Initialize();//内存初始化
	unsigned char pid = 1;
	CreateProcess(pid, PAGE_SIZE);

	_int i = _int(pid);
	i = -100;
	printf("%d\n",+i);
	i = 200;
	printf("%d\n",+i);
	for (i = 0; i < 5; i++)
	{
		printf("%d\n",(+i) + 1);	
	}

	int_ARRAY a = int_ARRAY(pid, 5);
	for (i = 0; i < 5; i++)	
	{
		a.assignment(+i, +i);
		printf("%d\n",a[+i]);
	}
	int_ARRAY_ARRAY array = int_ARRAY_ARRAY(pid, 5,3);
	for (i = 0; i < 5; i++)	
	{
		array.assignment(+i, 0, +i);
		array.assignment(+i, 1,(+i) + 1);
		
		printf("%d %d\n",array[+i][0],array[+i][1]);
	}

	{
		int segmentAddr = CreateProcess(100, PAGE_SIZE);		
		segmentAddr = CreateProcess(101, PAGE_SIZE);
		segmentAddr = CreateProcess(102, PAGE_SIZE);
		_int a101 = _int(101);
		_int a102 = _int(102);
		_int a100 = _int(100);
		a101 = 101;				
		a102 = 102;		
		a100 = 100;
		printf("%d %d %d", +a100, +a101, +a102);
	}
	return 0;
}
/*
int main()
{
	Initialize();
	int pid = 1;
	CreateProcess(pid,PAGE_SIZE);
	VARIABLE i;
	int(i,pid);
	for (i = 0; i < 5; i++)
	{
		printf("done\n");
	}	
}
*/