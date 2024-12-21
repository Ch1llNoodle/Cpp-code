#include<iostream>
#include<math.h> 
#include<ctype.h>
#include<string.h>
#include<typeinfo>
#include<algorithm>
#define MAX 100
using namespace std;

class Bignumber
{
public://对大数进行储存，可以更改位数 
	char a[100];
	char b[100];
	char c;//运算符号 
};

void addition(char d[100], char e[100])//加法功能主函数 
{
	int x[100] = { 0 }, y[100] = { 0 }, z[105] = { 0 };
	int len1, len2, len;
	int i, c, j = 0, k = 0, l = 0;
	len1 = strlen(d);
	len2 = strlen(e);
	for (i = len1 - 1; i >= 0; i--)//将两个字符串中的字符转化为数字，并倒序储存到数组中 
	{
		x[j] = d[i] - '0';
		j++;
	}
	for (c = len2 - 1; c >= 0; c--)
	{
		y[k] = e[c] - '0';
		k++;
	}
	if (len1 > len2)
		len = len1;
	else
		len = len2;
	i = 0;//从最低位(个位)开始进行计算
	int m = 0;
	for (i = 0; i < len; i++)
	{
		z[i] = (x[i] + y[i] + m) % 10;//将所得数的个位存到数组z[i]中去 
		if ((x[i] + y[i] + m) >= 10)
			m = 1;
		else
			m = 0;
	}
	if ((x[i - 1] + y[i - 1] + m) >= 10)//判断运算的最大位的和是否>=10 ,此时i=len-1
		z[i] = 1;
	else
		i = i - 1;
	cout << "相加运算结果=";
	for (i = i; i >= 0; i--)
	{
		cout << z[i];
	}
	cout << endl;
}

void subtraction(char d[100], char e[100])//减法主函数 
{
	char x[100] = { 0 }, y[100] = { 0 }, z[105] = { 0 };
	int len1, len2, len;
	int i, j = 0, k = 0;
	len1 = strlen(d);
	len2 = strlen(e);
	len = max(len1, len2);
	cout << "相减运算结果=：";
	if (strcmp(d, e) < 0)
	{
		cout << "-";
		swap(d, e);
	}
	for (i = len1 - 1, j = 0; i >= 0; i--)//将两个字符串中的字符转化为数字，并倒序储存到数组中
		x[j++] = d[i] - '0';
	for (i = len2 - 1, k = 0; i >= 0; i--)
		y[k++] = e[i] - '0';
	//相减
	int m = 0;//借位标志
	for (int i = 0; i <= len - 1; i++)
	{
		if (x[i] - y[i] - m >= 0)
		{
			z[i] = x[i] - y[i] - m + '0';
			m = 0;
		}
		else
		{
			z[i] = x[i] - y[i] - m + 10 + '0';
			m = 1;
		}
	}
	for (int i = strlen(z) - 1; i >= 0; i--)
	{
		cout << z[i];
	}
	cout << endl;
}
void multiplication(char d[100], char e[100])//乘法主函数 
{
	char x[MAX + 10] = { 0 }, y[MAX + 10] = { 0 }, z[MAX * 2 + 10] = { 0 };
	int len1, len2, i, j, m = 0;
	char temp;
	len1 = strlen(d);
	len2 = strlen(e);
	for (j = 0, i = len1 - 1; i >= 0; i--)//将字符串中字符转化为数字，并倒序储存 
		x[j++] = d[i] - '0';
	for (j = 0, i = len2 - 1; i >= 0; i--)
		y[j++] = e[i] - '0';
	for (int j = 0; j <= len1 + len2 - 2; j++)
	{
		for (int i = 0; i <= len1 - 1; i++)
		{
			if (i <= j)
				z[j] += x[i] * y[j - i];
		}
	}
	for (int j = 0; j <= len1 + len2 - 1; j++)
	{
		if (z[j] + m < 10)
		{
			z[j] = z[j] + m + '0';
			m = 0;
		}
		else
		{
			temp = z[j] + m;
			z[j] = temp % 10 + '0';
			m = (int)(temp / 10);
		}
	}
	cout << "相乘运算结果=";
	for (i = strlen(z) - 1; i >= 0; i--)
	{
		cout << z[i];
	}
}
void sub(int x[], int y[], int len1, int len2)//除法子函数 
{
	int i;
	int digit;//大数的位数 
	for (i = 0; i < len1; i++)
	{
		if (x[i] < y[i])
		{
			x[i] = x[i] + 10 - y[i];
			x[i + 1]--;
		}
		else
			x[i] = x[i] - y[i];
	}
	for (i = len1 - 1; i >= 0; i--)//判断减法结束之后，被除数的位数 
	{
		if (x[i])
		{
			digit = i + 1;
			break;
		}
	}
}
int judge(int x[], int y[], int len1, int len2)//除法子函数 
{
	int i;
	if (len1 < len2)
		return -1;
	if (len1 == len2)//若两个数位数相等 
	{
		for (i = len1 - 1; i >= 0; i--)
		{
			if (x[i] == y[i])//对应位的数相等 
				continue;
			if (x[i] > y[i])//被除数 大于 除数，返回值为1 
				return 1;
			if (x[i] < y[i])//被除数 小于 除数，返回值为-1 
				return -1;
		}
		return 0;//被除数 等于 除数，返回值为0 
	}
}
void division(char d[100], char e[100])//除法主函数 
{
	int i, j = 3, k = 0, m = 0, temp;
	int x[100] = { 0 }, y[100] = { 0 }, z[100] = { 0 };
	int digit;//大数的位数 
	int len1, len2, len;//len两个大数位数的差值   
	len1 = strlen(d) + 3;//被除数位数，为四舍五入保留两位小数，对被除数放大 1000倍 
	len2 = strlen(e);//除数位数
	for (i = len1 - 1, j = 0; i >= 0; i--)//将字符串中各个元素倒序储存在数组中 
		x[j++] = d[i] - '0';
	for (i = len2 - 1, k = 0; i >= 0; i--)
		y[k++] = e[i] - '0';
	if (len1 < len2)//当被除数位数 小于 除数位数时 
	{
		cout << "0.00" << endl;
		cout << "被除数也太小了吧，敢不敢再大一点!" << endl;
	}
	else //当被除数位数 大于或者 除数位数时
	{
		len = len1 - len2;//两个大数位数的差值
		for (i = len1 - 1; i >= 0; i--)//将除数后补零，使得两个大数位数相同
		{
			if (i >= len)
				y[i] = y[i - len];
			else
				y[i] = 0;
		}
		len2 = len1;//将两个大数数位相同 		
		digit = len1;	//将原被除数位数赋值给digit 
		for (j = 0; j <= len; j++)
		{
			z[len - j] = 0;
			while (((temp = judge(x, y, len1, len2)) >= 0) && digit >= k)//判断两个数之间的关系以及位数与除数原位数的关系 
			{
				sub(x, y, len1, len2);	//大数减法函数			    
				z[len - j]++;//储存商的每一位
				len1 = digit;//重新修改被除数的长度
				if (len1 < len2 && y[len2 - 1] == 0)
					len2 = len1;//将len1长度赋给len2;						
			}
			if (temp < 0)//若被除数 小于 除数，除数减小一位。
			{
				for (i = 1; i < len2; i++)
					y[i - 1] = y[i];
				y[i - 1] = 0;
				if (len1 < len2)
					len2--;
			}
		}
		cout << "相除运算结果=";
		for (i = len; i > 0; i--)//去掉前缀0 
		{
			if (z[i])
				break;
		}
		if (z[0] >= 5)
			z[1] = z[1] + 1;
		for (i = 99; i >= 0; i--)
		{
			if (z[i] != 0)
			{
				m = i;
				break;
			}
		}
		if (m >= 3)
		{
			if (z[m - 3] >= 5)
				z[m - 2] = z[m - 2] + 1;
			cout << z[m] << "." << z[m - 1] << z[m - 2] << "E+" << m - 3 << endl;
		}
		else
		{
			for (; i > 2; i--)
			{
				cout << z[i];
			}
			cout << z[3];
			cout << ".";
			for (i = 2; i >= 1; i--)
			{
				cout << z[i];
			}
		}
		cout << endl;
	}
}
int main()//主函数 
{
	Bignumber number;
	int x[100] = { 0 }, y[100] = { 0 }, z[105] = { 0 }, n[105] = { 0 };
	int i, j = 0, len1, len2;
	char m, b, shu1, shu2;
	cout << "--------------------------------" << endl;
	cout << "|******欢迎使用大数计算器******|" << endl;
	cout << "--------------------------------" << endl;
	while (1)//可以多次连续输入 
	{

		cout << "请输入计算表达式：" << endl;
		while (1)
		{
			cout << "输入第一个数：";
			cin >> number.a;
			len1 = strlen(number.a);
			for (i = len1 - 1, j = 0; i >= 0; i--)
			{
				x[j] = number.a[i] - '0';
				j++;
			}
			for (j = len1 - 1; j > 0; j--)
			{
				if (x[j] <= 9 && x[j] >= 0 && x[j - 1] <= 9 && x[j - 1] >= 0)
				{
					shu1 = 'n';
				}
				else
					cout << "输入正确的数字" << endl;
				break;
			}
			if (shu1 == 'n')
				break;
		}
		while (1)
		{
			cout << "输入运算符号：";
			cin >> number.c;
			if (number.c != '+' && number.c != '-' && number.c != '*' && number.c != '/')
			{
				cout << "输入正确的运算符号" << endl;
			}
			else
				break;
		}
		while (1)
		{
			cout << "输入第二个数：";
			cin >> number.b;
			len2 = strlen(number.b);
			for (i = len2 - 1, j = 0; i >= 0; i--)
			{
				x[j] = number.b[i] - '0';
				j++;
			}
			for (j = len2 - 1; j > 0; j--)
			{
				if (x[j] <= 9 && x[j] >= 0 && x[j - 1] <= 9 && x[j - 1] >= 0)
				{
					shu2 = 'n';
				}
				else
				{
					cout << "输入正确的数字" << endl;
					break;
				}
			}
			if (shu2 == 'n')
				break;
		}
		if (number.c == '+')
			addition(number.a, number.b);// 调用加法函数 
		else if (number.c == '-')
			subtraction(number.a, number.b);// 调用减法函数 
		else if (number.c == '*')
			multiplication(number.a, number.b);//调用乘法函数 
		else if (number.c == '/')
			division(number.a, number.b);//调用除法函数 	
		cout << endl;
		cout << "是否继续使用：（y/n)" << endl;
		cin >> m;
		if (m == 'n')
			break;
	}
}