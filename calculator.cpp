#include <iostream>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <typeinfo>
#include <algorithm>
#define MAX 100
using namespace std;

class Bignumber
{
public: // 对大数进行储存，可以更改位数
	char a[100];
	char b[100];
	char c; // 运算符号
};

void addition(char d[100], char e[100])
{
	int x[100] = {0}, y[100] = {0}, z[105] = {0};
	int len1 = strlen(d), len2 = strlen(e);
	int i, carry = 0, maxLen = max(len1, len2); // carry 表示进位

	// 将输入字符串倒序存储到数组中
	for (i = 0; i < len1; i++)
		x[i] = d[len1 - 1 - i] - '0';
	for (i = 0; i < len2; i++)
		y[i] = e[len2 - 1 - i] - '0';

	// 从最低位开始计算
	for (i = 0; i < maxLen; i++)
	{
		int sum = x[i] + y[i] + carry;
		z[i] = sum % 10;  // 当前位的值
		carry = sum / 10; // 更新进位
	}

	// 如果最后还有进位，则补充最高位
	if (carry > 0)
	{
		z[maxLen] = carry;
		maxLen++;
	}

	// 输出完整算式
	cout << d << " + " << e << " = ";

	// 输出结果
	bool leadingZero = true; // 去除前导零
	for (i = maxLen - 1; i >= 0; i--)
	{
		if (z[i] != 0 || !leadingZero)
		{
			cout << z[i];
			leadingZero = false;
		}
	}

	if (leadingZero) // 如果结果全为零
		cout << "0";
	cout << endl;
}

void subtraction(char d[100], char e[100])
{
	char x[100] = {0}, y[100] = {0}, z[105] = {0};
	int len1, len2, len;
	int i, j = 0, k = 0;

	len1 = strlen(d);
	len2 = strlen(e);
	len = max(len1, len2);

	// 标记是否需要输出负号
	bool isNegative = false;

	// 如果被减数小于减数，标记为负数并交换两数
	if (strcmp(d, e) < 0)
	{
		isNegative = true;
		swap(d, e);
		swap(len1, len2);
	}

	// 将两个字符串中的字符转化为数字，并倒序存储到数组中
	for (i = len1 - 1, j = 0; i >= 0; i--)
		x[j++] = d[i] - '0';
	for (i = len2 - 1, k = 0; i >= 0; i--)
		y[k++] = e[i] - '0';

	// 相减
	int m = 0; // 借位标志
	for (i = 0; i < len; i++)
	{
		int diff = x[i] - y[i] - m;
		if (diff >= 0)
		{
			z[i] = diff; // 直接存储结果
			m = 0;
		}
		else
		{
			z[i] = diff + 10; // 借位
			m = 1;
		}
	}

	// 去掉前导零并输出结果
	int lastNonZero = len - 1;
	while (lastNonZero > 0 && z[lastNonZero] == 0)
		lastNonZero--; // 找到最后一个非零位

	// 打印完整算式
	if (isNegative)
		cout << "-"; // 输出负号
	cout << d;
	cout << " - ";
	cout << e;
	cout << " = ";
	for (i = lastNonZero; i >= 0; i--)
		cout << (int)z[i]; // 从高位到低位输出结果
	cout << endl;
}

void multiplication(char d[100], char e[100])
{
	char x[105] = {0}, y[105] = {0}, z[210] = {0}; // 定义足够大的数组
	int len1 = strlen(d), len2 = strlen(e), i, j, m = 0;

	// 将字符串中字符转化为数字，并倒序存储
	for (j = 0, i = len1 - 1; i >= 0; i--)
		x[j++] = d[i] - '0';
	for (j = 0, i = len2 - 1; i >= 0; i--)
		y[j++] = e[i] - '0';

	// 大数乘法核心逻辑
	for (int j = 0; j <= len1 + len2 - 2; j++)
	{
		for (int i = 0; i <= len1 - 1; i++)
		{
			if (i <= j)
				z[j] += x[i] * y[j - i];
		}
	}

	// 处理进位
	for (int j = 0; j <= len1 + len2 - 1; j++)
	{
		int temp = z[j] + m;
		z[j] = temp % 10; // 存储当前位的数字
		m = temp / 10;	  // 存储进位
	}

	// 计算结果长度，去掉前导零
	int resultLen = len1 + len2;
	while (resultLen > 1 && z[resultLen - 1] == 0)
		resultLen--; // 忽略高位的零

	// 输出完整算式
	cout << d << " * " << e << " = ";

	// 输出结果
	for (i = resultLen - 1; i >= 0; i--)
	{
		cout << (int)z[i];
	}
	cout << endl;
}

void sub(int x[], int y[], int len1, int len2) // 除法子函数
{
	int i;
	int digit; // 大数的位数
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
	for (i = len1 - 1; i >= 0; i--) // 判断减法结束之后，被除数的位数
	{
		if (x[i])
		{
			digit = i + 1;
			break;
		}
	}
}
int judge(int x[], int y[], int len1, int len2)
{
	int i;
	if (len1 < len2)
		return -1; // 如果被除数长度小于除数长度，返回-1
	if (len1 == len2)
	{ // 若两个数位数相等
		for (i = len1 - 1; i >= 0; i--)
		{
			if (x[i] == y[i]) // 对应位的数相等
				continue;
			if (x[i] > y[i]) // 被除数大于除数，返回1
				return 1;
			if (x[i] < y[i]) // 被除数小于除数，返回-1
				return -1;
		}
		return 0; // 被除数等于除数，返回0
	}
	// 如果 len1 大于 len2，应该在这里返回一个值
	return 1; // 假设被除数大于除数，返回1
}

int adjustLength(int x[], int len1)
{
	// 从高位开始检查，找到非零的位置
	while (len1 > 0 && x[len1 - 1] == 0)
	{
		len1--;
	}
	return len1;
}

void division(char d[100], char e[100])
{
	int i, j, temp;
	int x[100] = {0}, y[100] = {0}, z[100] = {0};
	int len1 = strlen(d), len2 = strlen(e), len;

	// 将字符串倒序存储到数组中
	for (i = len1 - 1, j = 0; i >= 0; i--)
		x[j++] = d[i] - '0';
	for (i = len2 - 1, j = 0; i >= 0; i--)
		y[j++] = e[i] - '0';

	// 如果除数为 1，直接输出被除数
	if (len2 == 1 && y[0] == 1)
	{
		cout << d << " / " << e << " = " << d << endl;
		return;
	}

	// 判断被除数是否小于除数
	if (len1 < len2 || (len1 == len2 && strcmp(d, e) < 0))
	{
		cout << d << " / " << e << " = 0.00" << endl;
		return;
	}

	// 补零对齐被除数和除数的长度
	len = len1 - len2;
	for (i = len1 - 1; i >= 0; i--)
	{
		if (i >= len)
			y[i] = y[i - len];
		else
			y[i] = 0;
	}
	len2 = len1;

	// 商的计算
	for (j = 0; j <= len; j++)
	{
		z[len - j] = 0;
		while ((temp = judge(x, y, len1, len2)) >= 0)
		{
			sub(x, y, len1, len2); // 大数减法
			z[len - j]++;
			len1 = adjustLength(x, len1); // 调整被除数的有效长度
		}
		// 除数右移一位
		for (i = 1; i < len2; i++)
			y[i - 1] = y[i];
		y[len2 - 1] = 0;
		len2--;
	}

	// 去掉商的前导零
	int firstNonZero = 0;
	for (i = 99; i >= 0; i--)
	{
		if (z[i] != 0)
		{
			firstNonZero = i;
			break;
		}
	}

	// 输出完整算式
	cout << d << " / " << e << " = ";
	for (i = firstNonZero; i >= 0; i--)
		cout << z[i];
	cout << endl;
}

int main()
{
	Bignumber number;
	char m;
	cout << "--------------------------------" << endl;
	cout << "|******欢迎使用大数计算器******|" << endl;
	cout << "--------------------------------" << endl;

	while (true)
	{

		// 输入第一个数
		while (true)
		{
			cout << "输入第一个数：";
			cin >> number.a;
			bool valid = true;
			for (int i = 0; i < strlen(number.a); i++)
			{
				if (number.a[i] < '0' || number.a[i] > '9')
				{
					valid = false;
					break;
				}
			}
			if (valid)
				break;
			else
				cout << "请输入正确的数字！" << endl;
		}

		// 输入运算符
		while (true)
		{
			cout << "输入运算符号：";
			cin >> number.c;
			if (number.c == '+' || number.c == '-' || number.c == '*' || number.c == '/')
			{
				break;
			}
			else
			{
				cout << "输入正确的运算符号！" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
			}
		}

		// 输入第二个数
		while (true)
		{
			cout << "输入第二个数：";
			cin >> number.b;
			bool valid = true;
			for (int i = 0; i < strlen(number.b); i++)
			{
				if (number.b[i] < '0' || number.b[i] > '9')
				{
					valid = false;
					break;
				}
			}
			if (valid)
				break;
			else
				cout << "请输入正确的数字！" << endl;
		}

		// 调用运算函数
		if (number.c == '+')
			addition(number.a, number.b);
		else if (number.c == '-')
			subtraction(number.a, number.b);
		else if (number.c == '*')
			multiplication(number.a, number.b);
		else if (number.c == '/')
			division(number.a, number.b);

		// 是否继续
		cout << "是否继续使用：（y/n) ";
		cin >> m;
		if (m == 'n' || m == 'N')
			break;
	}

	cout << "感谢使用大数计算器！" << endl;
	_sleep(1500);
	return 0;
}