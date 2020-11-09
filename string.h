#define  _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include <assert.h>
using namespace std;
class String
{
public:

	friend ostream& operator<<(const ostream& _cout, const String& str);
	friend istream& operator>>(const istream& _cin, String& str);
	 
	// 构造函数
	String(char * str = "")	// 全缺省，空对象时，其仍有地址，其内保存：\n
		:_str(new char[strlen(str) + 1])
		, _size(strlen(str))
		, _capacity(strlen(str))
	{
		strcpy(_str, str);
	}

	// 拷贝构造函数
	String(const String& s)
		:_str(nullptr)
		,_size(0)
		,_capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}

	// 剥夺函数
	void Swap(String & s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	// ‘=’重载
	String & operator=(const String& s)
	{
		if (this != &s)
		{
			String tmp(s._str);
			Swap(tmp);
		}
		 
		return *this;
	}

	// 增容函数
	void reserve(size_t n)
	{
		if (_capacity <= n)
		{
			char* tmp = new char[n + 1];    //多一个来放\0
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_str[_size] = '\0';
			_capacity = n;

		}
	}

	// 尾插单个字符
	void Pushback(const char& word)
	{
		insert(_size, word);
	}

	// 指定位置插入单个字符
	void insert(size_t pos, const char& ch)
	{
		// 判断是否需要扩容
		if (_size == _capacity)
		{
			size_t newcap= _capacity == 0 ? 15 : _capacity*2;
			reserve(newcap);
		}

		// 是否需要移动数据
		size_t end = _size;
		while (end > pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}

		// 插入数据
		_str[pos] = ch;
		++_size;

		// 加上字符串结束标记
		_str[_size] = '\0';
	}

	// 指定位置插入字符串
	void insert(size_t pos, const char* str)
	{
		int len = strlen(str);
		if ((_size + len) >= _capacity)
		{
			reserve(_size + len);
		}

		// 挪动数据
		size_t end = _size;
		while (end > pos)
		{
			_str[end + len] = _str[end];
			end--;
		}

		// 插入数据
		const char *tmp = str;
		while (*tmp)
		{
			_str[pos++] = *tmp++;
		}
		// 更新数据量
		_size += len;
		// 加上字符串结束标记
		_str[_size] = '\0';
	}

	// 指定位置字符串删除
	void Erase(size_t pos, size_t count)
	{
		while (pos + count <= _size)
		{
			_str[pos++] = _str[pos + count];
		}
		_size -= count;
	}

	// 字符串查找
	size_t Find(char ch) const
	{
		const char *tmp = _str;
		while (*tmp++)
		{

			if (ch == *tmp)
			{
				return (tmp - _str) + 1;
			}
		}
		return -1;
	}

	// 字符串的查找
	size_t Find(const char* str) const
	{
		const char* src = _str;
		const char* prev = str;
		const char* tmp = src;

		while (*src)
		{
			tmp = src;
			prev = (char*)str;

			while (*tmp++ == *prev++)
				;
			if (*prev == '\0')
			{
				return (tmp - _str) - strlen(str);
			}
			src++;
		}
		return -1;
	}

	// 返回存储数据大小
	size_t Size()const
	{
		return _size;
	}

	// 设置实际数据大小
	void Resize(size_t sz, char ch = '\0')
	{
		// 扩容
		if (sz > _capacity)
		{
			reserve(sz);
		}
		else if (sz > _size)
		{
			// 赋值
			size_t pos = _size;
			memset(_str + pos, ch, sz - _size);

		}
		
		_size = sz;
		// 加上字符串结束标记
		_str[_size] = '\0';
	}

	// 追加字符串函数
	void Append(const char* ch)
	{
		int len = strlen(ch);
		if (len + _size >= _capacity)
		{
			reserve(len+_size);
		}

		// 尾插字符串
		strcpy(_str + _size, ch);
		_size += len;
	}

	// ‘[]’运算符重载
	char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	// ‘+=’重载：加字符串
	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}

	// ‘+=’重载：加String对象
	String& operator+=(const String& s)
	{
		int len = strlen(s._str);
		if (_size + len >= _capacity)
		{
			reserve(_size + len);
		}

		size_t pos = 0;
		while (pos < len)
		{
			_str[_size+pos] = s._str[pos++];
		}

		_size += len;
		_str[_size] = '\0';
		return *this;
	}

	// ‘+=’重载：加字符
	String& operator+=(const char& ch)
	{
		Pushback(ch);
		return *this;
	}

	// ‘==’重载
	bool operator==(const String& s) const
	{
		const char* dest = s._str;
		const char* src = this->_str;
		while (*src && *dest)
		{
			if (*src == *dest)
			{
				src++;
				dest++;
			}
			else
			{
				break;
			}
		}
		if (*src == '\0' && *dest == '\0')
			return true;
		else
			return false;
	}

	// != 重载
	bool operator!=(const String& s)const
	{
		if (*this == s)
		{
			return false;
		}
		return true;
	}

	// '<'重载
	bool operator<(const String& s) const
	{
		const char* dest = s._str;
		const char* src = _str;

		while (*dest && *src)
		{
			if (*dest == *src)
			{
				dest++;
				src++;
			}
			else if (*dest < *src)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		if ((*dest == '\0' && *src != '\0') || (*dest == '\0' && *src == '\0'))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// '>'重载
	bool operator>(const String& s) const
	{
		if (*this == s || *this < s)
		{
			return false;
		}

		return true;
	}

	// '<=' 重载
	bool operator<=(const String& s) const
	{
		if (*this < s || *this == s)
		{
			return true;
		}
		return false;
	}

	// 返回C风格字符串
	const char* c_str()const
	{
		return _str;
	}

	// 输出信息
	void Getinfor()
	{
		cout << _str << endl;
		cout << "size: "<< _size << endl;
		cout << "capacity: " << _capacity << endl;
	}

	// 迭代器
	typedef char* iterator;				// 可读可写迭代器
	typedef const char* const_iterator;	// 可读迭代器

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin() const 
	{
		return _str;
	}

	const_iterator end() const
	{
		return _str + _size;
	}

	// 析构函数
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

private:
	char* _str;			// 字符串
	size_t _size;		// 有效字符个数
	size_t _capacity;	// 实际空间
};

// 重载输出运算符
ostream& operator<<(ostream& _cout, const String& str)
{
	for (int i = 0; i < str.Size(); i++)
	{
		_cout << str[i];
	}
	
	return _cout;
}

// 重载输出运算符
istream& operator>>(istream& _cin, String& str)
{
	char ch;

	while ((ch=getchar())!=EOF)
	{
		if (ch == '\n')
			break;
		str.Pushback(ch);
	}
	return _cin;
}
