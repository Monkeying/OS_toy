/*
重载运算符的封装
 */
#include "funcPart3.c"

class _int//返回段内地址，进程名称默认为main. -1内存已满，-2程序不存在
{
public:
	_int addr;

	_int(unsigned _char processName)
	{
		this->addr = _malloc(processName, sizeof(_int));
		if (this < 0)
		{
			pr_intf("申请失败\n");
			this->~_int();
		}
	}
	_int(_int addr)
	{
		this->addr = addr;
		if (this < 0)
		{
			pr_intf("申请失败\n");
			this->~_int();
		}
	}
	~_int()
	{
		_free(this->addr);
	}
	bool setAddr(unsigned _int addr)
	{
		this->addr = addr;
		return  1;
	}
	_int operator +()
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		return *temp;
	}
	_int * operator &()
	{
		//return this->addr;
		return this;
	}	
	void operator =(_int num)//注意和申请语句分开，这个只有赋值功能
	{
		_write(this->addr,sizeof(_int), 1, &num);
	}
	_int operator +(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = *temp + num;
		return *temp;
	}
	_int operator -(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = *temp - num;
		return *temp;
	}
	_int operator *(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = (*temp) * num;
		return *temp;
	}
	_int operator /(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = *temp / num;
		return *temp;
	}
	_int operator %(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = *temp % num;
		return *temp;
	}
	_int operator ++(_int)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = *temp + 1;
		_write(this->addr,sizeof(_int), 1, temp);
		temp = (_int *)_read(this->addr,sizeof(_int), 1);
		return *temp;
	}
	void operator +=(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		*temp = *temp + num;
		_write(this->addr,sizeof(_int), 1, temp);
		temp = (_int *)_read(this->addr,sizeof(_int), 1);
	}
	bool operator <(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		if (*temp < num)
		{
			return 1;
		}
		return 0;
	}
	bool operator >(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		if (*temp > num)
		{
			return 1;
		}
		return 0;
	}
	bool operator ==(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
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
	_int addr;

	_char(unsigned _char processName)
	{
		this->addr = _malloc(processName, sizeof(_char));
		if (this < 0)
		{
			pr_intf("申请失败\n");
			this->~_char();
		}
	}
	~_char()
	{
		_free(this->addr);
	}
	_int operator *()
	{
		_char *temp = (_char *)_read(this->addr,sizeof(_char), 1);
		return *temp;
	}
	_int operator &()
	{
		return this->addr;
	}
	void operator =(_char _character)//注意和申请语句分开，这个只有赋值功能
	{
		_write(this->addr,sizeof(_char), 1, &_character);
	}
	_int operator +(_int num)
	{
		_char *temp = (_char *)_read(this->addr,sizeof(_char), 1);
		*temp = *temp + num;
		return *temp;
	}
	_int operator -(_int num)
	{
		_char *temp = (_char *)_read(this->addr,sizeof(_char), 1);
		*temp = *temp - num;
		return *temp;
	}
	bool operator <(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		if (*temp < num)
		{
			return 1;
		}
		return 0;
	}
	bool operator >(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		if (*temp > num)
		{
			return 1;
		}
		return 0;
	}
	bool operator ==(_int num)
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), 1);
		if (*temp == num)
		{
			return 1;
		}
		return 0;
	}
	bool operator ==(_char _character)
	{
		_char *temp = (_char *)_read(this->addr,sizeof(_char), 1);
		if (*temp == _character)
		{
			return 1;
		}
		return 0;
	}
	bool operator >(_char _character)
	{
		_char *temp = (_char *)_read(this->addr,sizeof(_char), 1);
		if (*temp > _character)
		{
			return 1;
		}
		return 0;
	}
	bool operator <(_char _character)
	{
		_char *temp = (_char *)_read(this->addr,sizeof(_char), 1);
		if (*temp < _character)
		{
			return 1;
		}
		return 0;
	}
};
class _int_ARRAY
{
public:
	_int addr;
	unsigned _int count;

	_int_ARRAY(unsigned _char processName, unsigned _int count)
	{
		this->addr = _malloc(processName, sizeof(_int)*count);
		this->count = count;
		if (this->addr < 0)
		{
			pr_intf("申请失败\n");
			this->~_int_ARRAY();
		}
	}
	~_int_ARRAY()
	{
		_free(this->addr);
	}
	_int * operator &()
	{
		_int *temp = (_int *)_read(this->addr,sizeof(_int), this->count);
		return temp;
	}
	_int operator [](unsigned _int i)//仅仅能够读取，不能赋值
	{
		_int *temp = (_int *)_read(this->addr + i * sizeof(_int), sizeof(_int), 1);
		return *temp;
	}
	bool assignment(unsigned _int i, _int value)
	{
		if (_write(this->addr + i * sizeof(_int), sizeof(_int), 1, &value))
		{
			_int *temp = (_int *)_read(this->addr + i * sizeof(_int),sizeof(_int), 1);
			return 1;
		}	
		else
		{
			return 0;
		}	
	}
};

_int main()
{
	Initialize();
	unsigned _char pid = 1;
	CreateProcess(pid, PAGE_SIZE);

	_int i = _int(pid);
	i = -100;
	pr_intf("%d\n",+i);
	i = 200;
	pr_intf("%d\n",+i);
	for (i = 0; i < 5; i++)
	{
		pr_intf("%d\n",+i);	
	}

	_int_ARRAY a = _int_ARRAY(pid, 5);
	for (i = 0; i < 5; i++)
	{
		a.assignment(+i, +i);
		pr_intf("%d\n",a[+i]);
	}
}
/*
_int main()
{
	Initialize();
	_int pid = 1;
	CreateProcess(pid,PAGE_SIZE);
	VARIABLE i;
	_int(i,pid);
	for (i = 0; i < 5; i++)
	{
		pr_intf("done\n");
	}	
}
*/