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
public: // �Դ������д��棬���Ը���λ��
	char a[100];
	char b[100];
	char c; // �������
};

void addition(char d[100], char e[100])
{
	int x[100] = {0}, y[100] = {0}, z[105] = {0};
	int len1 = strlen(d), len2 = strlen(e);
	int i, carry = 0, maxLen = max(len1, len2); // carry ��ʾ��λ

	// �������ַ�������洢��������
	for (i = 0; i < len1; i++)
		x[i] = d[len1 - 1 - i] - '0';
	for (i = 0; i < len2; i++)
		y[i] = e[len2 - 1 - i] - '0';

	// �����λ��ʼ����
	for (i = 0; i < maxLen; i++)
	{
		int sum = x[i] + y[i] + carry;
		z[i] = sum % 10;  // ��ǰλ��ֵ
		carry = sum / 10; // ���½�λ
	}

	// �������н�λ���򲹳����λ
	if (carry > 0)
	{
		z[maxLen] = carry;
		maxLen++;
	}

	// ���������ʽ
	cout << d << " + " << e << " = ";

	// ������
	bool leadingZero = true; // ȥ��ǰ����
	for (i = maxLen - 1; i >= 0; i--)
	{
		if (z[i] != 0 || !leadingZero)
		{
			cout << z[i];
			leadingZero = false;
		}
	}

	if (leadingZero) // ������ȫΪ��
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

	// ����Ƿ���Ҫ�������
	bool isNegative = false;

	// ���������С�ڼ��������Ϊ��������������
	if (strcmp(d, e) < 0)
	{
		isNegative = true;
		swap(d, e);
		swap(len1, len2);
	}

	// �������ַ����е��ַ�ת��Ϊ���֣�������洢��������
	for (i = len1 - 1, j = 0; i >= 0; i--)
		x[j++] = d[i] - '0';
	for (i = len2 - 1, k = 0; i >= 0; i--)
		y[k++] = e[i] - '0';

	// ���
	int m = 0; // ��λ��־
	for (i = 0; i < len; i++)
	{
		int diff = x[i] - y[i] - m;
		if (diff >= 0)
		{
			z[i] = diff; // ֱ�Ӵ洢���
			m = 0;
		}
		else
		{
			z[i] = diff + 10; // ��λ
			m = 1;
		}
	}

	// ȥ��ǰ���㲢������
	int lastNonZero = len - 1;
	while (lastNonZero > 0 && z[lastNonZero] == 0)
		lastNonZero--; // �ҵ����һ������λ

	// ��ӡ������ʽ
	if (isNegative)
		cout << "-"; // �������
	cout << d;
	cout << " - ";
	cout << e;
	cout << " = ";
	for (i = lastNonZero; i >= 0; i--)
		cout << (int)z[i]; // �Ӹ�λ����λ������
	cout << endl;
}

void multiplication(char d[100], char e[100])
{
	char x[105] = {0}, y[105] = {0}, z[210] = {0}; // �����㹻�������
	int len1 = strlen(d), len2 = strlen(e), i, j, m = 0;

	// ���ַ������ַ�ת��Ϊ���֣�������洢
	for (j = 0, i = len1 - 1; i >= 0; i--)
		x[j++] = d[i] - '0';
	for (j = 0, i = len2 - 1; i >= 0; i--)
		y[j++] = e[i] - '0';

	// �����˷������߼�
	for (int j = 0; j <= len1 + len2 - 2; j++)
	{
		for (int i = 0; i <= len1 - 1; i++)
		{
			if (i <= j)
				z[j] += x[i] * y[j - i];
		}
	}

	// �����λ
	for (int j = 0; j <= len1 + len2 - 1; j++)
	{
		int temp = z[j] + m;
		z[j] = temp % 10; // �洢��ǰλ������
		m = temp / 10;	  // �洢��λ
	}

	// ���������ȣ�ȥ��ǰ����
	int resultLen = len1 + len2;
	while (resultLen > 1 && z[resultLen - 1] == 0)
		resultLen--; // ���Ը�λ����

	// ���������ʽ
	cout << d << " * " << e << " = ";

	// ������
	for (i = resultLen - 1; i >= 0; i--)
	{
		cout << (int)z[i];
	}
	cout << endl;
}

void sub(int x[], int y[], int len1, int len2) // �����Ӻ���
{
	int i;
	int digit; // ������λ��
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
	for (i = len1 - 1; i >= 0; i--) // �жϼ�������֮�󣬱�������λ��
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
		return -1; // �������������С�ڳ������ȣ�����-1
	if (len1 == len2)
	{ // ��������λ�����
		for (i = len1 - 1; i >= 0; i--)
		{
			if (x[i] == y[i]) // ��Ӧλ�������
				continue;
			if (x[i] > y[i]) // ���������ڳ���������1
				return 1;
			if (x[i] < y[i]) // ������С�ڳ���������-1
				return -1;
		}
		return 0; // ���������ڳ���������0
	}
	// ��� len1 ���� len2��Ӧ�������ﷵ��һ��ֵ
	return 1; // ���豻�������ڳ���������1
}

int adjustLength(int x[], int len1)
{
	// �Ӹ�λ��ʼ��飬�ҵ������λ��
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

	// ���ַ�������洢��������
	for (i = len1 - 1, j = 0; i >= 0; i--)
		x[j++] = d[i] - '0';
	for (i = len2 - 1, j = 0; i >= 0; i--)
		y[j++] = e[i] - '0';

	// �������Ϊ 1��ֱ�����������
	if (len2 == 1 && y[0] == 1)
	{
		cout << d << " / " << e << " = " << d << endl;
		return;
	}

	// �жϱ������Ƿ�С�ڳ���
	if (len1 < len2 || (len1 == len2 && strcmp(d, e) < 0))
	{
		cout << d << " / " << e << " = 0.00" << endl;
		return;
	}

	// ������뱻�����ͳ����ĳ���
	len = len1 - len2;
	for (i = len1 - 1; i >= 0; i--)
	{
		if (i >= len)
			y[i] = y[i - len];
		else
			y[i] = 0;
	}
	len2 = len1;

	// �̵ļ���
	for (j = 0; j <= len; j++)
	{
		z[len - j] = 0;
		while ((temp = judge(x, y, len1, len2)) >= 0)
		{
			sub(x, y, len1, len2); // ��������
			z[len - j]++;
			len1 = adjustLength(x, len1); // ��������������Ч����
		}
		// ��������һλ
		for (i = 1; i < len2; i++)
			y[i - 1] = y[i];
		y[len2 - 1] = 0;
		len2--;
	}

	// ȥ���̵�ǰ����
	int firstNonZero = 0;
	for (i = 99; i >= 0; i--)
	{
		if (z[i] != 0)
		{
			firstNonZero = i;
			break;
		}
	}

	// ���������ʽ
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
	cout << "|******��ӭʹ�ô���������******|" << endl;
	cout << "--------------------------------" << endl;

	while (true)
	{

		// �����һ����
		while (true)
		{
			cout << "�����һ������";
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
				cout << "��������ȷ�����֣�" << endl;
		}

		// ���������
		while (true)
		{
			cout << "����������ţ�";
			cin >> number.c;
			if (number.c == '+' || number.c == '-' || number.c == '*' || number.c == '/')
			{
				break;
			}
			else
			{
				cout << "������ȷ��������ţ�" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Դ�������
			}
		}

		// ����ڶ�����
		while (true)
		{
			cout << "����ڶ�������";
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
				cout << "��������ȷ�����֣�" << endl;
		}

		// �������㺯��
		if (number.c == '+')
			addition(number.a, number.b);
		else if (number.c == '-')
			subtraction(number.a, number.b);
		else if (number.c == '*')
			multiplication(number.a, number.b);
		else if (number.c == '/')
			division(number.a, number.b);

		// �Ƿ����
		cout << "�Ƿ����ʹ�ã���y/n) ";
		cin >> m;
		if (m == 'n' || m == 'N')
			break;
	}

	cout << "��лʹ�ô�����������" << endl;
	_sleep(1500);
	return 0;
}