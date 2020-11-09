#define  _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include <assert.h>
using namespace std;
class String
{
public:

	friend ostream& operator<<(const ostream& _cout, const String& str);
	friend istream& operator>>(const istream& _cin, String& str);
	 
	// ���캯��
	String(char * str = "")	// ȫȱʡ���ն���ʱ�������е�ַ�����ڱ��棺\n
		:_str(new char[strlen(str) + 1])
		, _size(strlen(str))
		, _capacity(strlen(str))
	{
		strcpy(_str, str);
	}

	// �������캯��
	String(const String& s)
		:_str(nullptr)
		,_size(0)
		,_capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}

	// ���ắ��
	void Swap(String & s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	// ��=������
	String & operator=(const String& s)
	{
		if (this != &s)
		{
			String tmp(s._str);
			Swap(tmp);
		}
		 
		return *this;
	}

	// ���ݺ���
	void reserve(size_t n)
	{
		if (_capacity <= n)
		{
			char* tmp = new char[n + 1];    //��һ������\0
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_str[_size] = '\0';
			_capacity = n;

		}
	}

	// β�嵥���ַ�
	void Pushback(const char& word)
	{
		insert(_size, word);
	}

	// ָ��λ�ò��뵥���ַ�
	void insert(size_t pos, const char& ch)
	{
		// �ж��Ƿ���Ҫ����
		if (_size == _capacity)
		{
			size_t newcap= _capacity == 0 ? 15 : _capacity*2;
			reserve(newcap);
		}

		// �Ƿ���Ҫ�ƶ�����
		size_t end = _size;
		while (end > pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}

		// ��������
		_str[pos] = ch;
		++_size;

		// �����ַ����������
		_str[_size] = '\0';
	}

	// ָ��λ�ò����ַ���
	void insert(size_t pos, const char* str)
	{
		int len = strlen(str);
		if ((_size + len) >= _capacity)
		{
			reserve(_size + len);
		}

		// Ų������
		size_t end = _size;
		while (end > pos)
		{
			_str[end + len] = _str[end];
			end--;
		}

		// ��������
		const char *tmp = str;
		while (*tmp)
		{
			_str[pos++] = *tmp++;
		}
		// ����������
		_size += len;
		// �����ַ����������
		_str[_size] = '\0';
	}

	// ָ��λ���ַ���ɾ��
	void Erase(size_t pos, size_t count)
	{
		while (pos + count <= _size)
		{
			_str[pos++] = _str[pos + count];
		}
		_size -= count;
	}

	// �ַ�������
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

	// �ַ����Ĳ���
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

	// ���ش洢���ݴ�С
	size_t Size()const
	{
		return _size;
	}

	// ����ʵ�����ݴ�С
	void Resize(size_t sz, char ch = '\0')
	{
		// ����
		if (sz > _capacity)
		{
			reserve(sz);
		}
		else if (sz > _size)
		{
			// ��ֵ
			size_t pos = _size;
			memset(_str + pos, ch, sz - _size);

		}
		
		_size = sz;
		// �����ַ����������
		_str[_size] = '\0';
	}

	// ׷���ַ�������
	void Append(const char* ch)
	{
		int len = strlen(ch);
		if (len + _size >= _capacity)
		{
			reserve(len+_size);
		}

		// β���ַ���
		strcpy(_str + _size, ch);
		_size += len;
	}

	// ��[]�����������
	char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	// ��+=�����أ����ַ���
	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}

	// ��+=�����أ���String����
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

	// ��+=�����أ����ַ�
	String& operator+=(const char& ch)
	{
		Pushback(ch);
		return *this;
	}

	// ��==������
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

	// != ����
	bool operator!=(const String& s)const
	{
		if (*this == s)
		{
			return false;
		}
		return true;
	}

	// '<'����
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

	// '>'����
	bool operator>(const String& s) const
	{
		if (*this == s || *this < s)
		{
			return false;
		}

		return true;
	}

	// '<=' ����
	bool operator<=(const String& s) const
	{
		if (*this < s || *this == s)
		{
			return true;
		}
		return false;
	}

	// ����C����ַ���
	const char* c_str()const
	{
		return _str;
	}

	// �����Ϣ
	void Getinfor()
	{
		cout << _str << endl;
		cout << "size: "<< _size << endl;
		cout << "capacity: " << _capacity << endl;
	}

	// ������
	typedef char* iterator;				// �ɶ���д������
	typedef const char* const_iterator;	// �ɶ�������

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

	// ��������
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
	char* _str;			// �ַ���
	size_t _size;		// ��Ч�ַ�����
	size_t _capacity;	// ʵ�ʿռ�
};

// ������������
ostream& operator<<(ostream& _cout, const String& str)
{
	for (int i = 0; i < str.Size(); i++)
	{
		_cout << str[i];
	}
	
	return _cout;
}

// ������������
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
