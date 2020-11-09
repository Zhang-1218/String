#include "string.h"

void test1()
{
	//���캯��
	String str1("hello");
	str1.Getinfor();

	//��������
	String str2(str1);
	str2.Getinfor();

	// ��ֵ���������
	String str3;
	str3 = str2;
	str3.Getinfor();

	// [] ����
	str2[3] = 'x';
	str2.Getinfor();
}

void test2()
{
	//β��
	String str1("hello");
	str1.Pushback('s');
	str1.Getinfor();

	//���뵥���ַ�
	String str2("world");
	str2.Getinfor();
	str2.insert(0, 'x');
	str2.Getinfor();

	//�����ַ���
	String str3("hello");
	str3.insert(3, "888");
	str3.Getinfor();
}

void test3()
{
	//ɾ���ַ�����ָ������
	String str3("hello");
	str3.Erase(3, 2);
	str3.Getinfor();
}

void test4()
{
	//����ָ���ַ�
	String str1("hello");
	int tmp1 = str1.Find('o');
	cout << tmp1 << endl;

	//����ָ���ַ���
	String str2("hello world");
	int tmp2 = str2.Find("el");
	cout << tmp2 << endl;
}

void test5()
{
	String str1("he");
	String str2("he");

	// '<' ����
	cout << (str1 < str2 )<< endl;

	// '>' ����
	cout << (str1 > str2) << endl;

	// '==' ����
	cout << (str1 == str2) << endl;

	// '!=' ����
	cout << (str1 != str2) << endl;
}

void test6()
{
	String s1;
	const char* c1 = s1.c_str();
	cin >> s1;
	cout << s1;
}

void test7()
{
	String s1 = "123456";
	String::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	String s2 = "123";
	s2 += "456";
	cout << s2 << endl;
	s2 += s1;
	cout << s2 << endl;

	String s3;
	s3.Append("haha");
	cout << s3 << endl;
}

int main()
{
	
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
	system("pause");
	return 0;
}
