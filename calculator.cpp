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
public://�Դ������д��棬���Ը���λ�� 
	char a[100];
	char b[100];
	char c;//������� 
};

void addition(char d[100], char e[100])//�ӷ����������� 
{
	int x[100] = { 0 }, y[100] = { 0 }, z[105] = { 0 };
	int len1, len2, len;
	int i, c, j = 0, k = 0, l = 0;
	len1 = strlen(d);
	len2 = strlen(e);
	for (i = len1 - 1; i >= 0; i--)//�������ַ����е��ַ�ת��Ϊ���֣������򴢴浽������ 
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
	i = 0;//�����λ(��λ)��ʼ���м���
	int m = 0;
	for (i = 0; i < len; i++)
	{
		z[i] = (x[i] + y[i] + m) % 10;//���������ĸ�λ�浽����z[i]��ȥ 
		if ((x[i] + y[i] + m) >= 10)
			m = 1;
		else
			m = 0;
	}
	if ((x[i - 1] + y[i - 1] + m) >= 10)//�ж���������λ�ĺ��Ƿ�>=10 ,��ʱi=len-1
		z[i] = 1;
	else
		i = i - 1;
	cout << "���������=";
	for (i = i; i >= 0; i--)
	{
		cout << z[i];
	}
	cout << endl;
}

void subtraction(char d[100], char e[100])//���������� 
{
	char x[100] = { 0 }, y[100] = { 0 }, z[105] = { 0 };
	int len1, len2, len;
	int i, j = 0, k = 0;
	len1 = strlen(d);
	len2 = strlen(e);
	len = max(len1, len2);
	cout << "���������=��";
	if (strcmp(d, e) < 0)
	{
		cout << "-";
		swap(d, e);
	}
	for (i = len1 - 1, j = 0; i >= 0; i--)//�������ַ����е��ַ�ת��Ϊ���֣������򴢴浽������
		x[j++] = d[i] - '0';
	for (i = len2 - 1, k = 0; i >= 0; i--)
		y[k++] = e[i] - '0';
	//���
	int m = 0;//��λ��־
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
void multiplication(char d[100], char e[100])//�˷������� 
{
	char x[MAX + 10] = { 0 }, y[MAX + 10] = { 0 }, z[MAX * 2 + 10] = { 0 };
	int len1, len2, i, j, m = 0;
	char temp;
	len1 = strlen(d);
	len2 = strlen(e);
	for (j = 0, i = len1 - 1; i >= 0; i--)//���ַ������ַ�ת��Ϊ���֣������򴢴� 
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
	cout << "���������=";
	for (i = strlen(z) - 1; i >= 0; i--)
	{
		cout << z[i];
	}
}
void sub(int x[], int y[], int len1, int len2)//�����Ӻ��� 
{
	int i;
	int digit;//������λ�� 
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
	for (i = len1 - 1; i >= 0; i--)//�жϼ�������֮�󣬱�������λ�� 
	{
		if (x[i])
		{
			digit = i + 1;
			break;
		}
	}
}
int judge(int x[], int y[], int len1, int len2)//�����Ӻ��� 
{
	int i;
	if (len1 < len2)
		return -1;
	if (len1 == len2)//��������λ����� 
	{
		for (i = len1 - 1; i >= 0; i--)
		{
			if (x[i] == y[i])//��Ӧλ������� 
				continue;
			if (x[i] > y[i])//������ ���� ����������ֵΪ1 
				return 1;
			if (x[i] < y[i])//������ С�� ����������ֵΪ-1 
				return -1;
		}
		return 0;//������ ���� ����������ֵΪ0 
	}
}
void division(char d[100], char e[100])//���������� 
{
	int i, j = 3, k = 0, m = 0, temp;
	int x[100] = { 0 }, y[100] = { 0 }, z[100] = { 0 };
	int digit;//������λ�� 
	int len1, len2, len;//len��������λ���Ĳ�ֵ   
	len1 = strlen(d) + 3;//������λ����Ϊ�������뱣����λС�����Ա������Ŵ� 1000�� 
	len2 = strlen(e);//����λ��
	for (i = len1 - 1, j = 0; i >= 0; i--)//���ַ����и���Ԫ�ص��򴢴��������� 
		x[j++] = d[i] - '0';
	for (i = len2 - 1, k = 0; i >= 0; i--)
		y[k++] = e[i] - '0';
	if (len1 < len2)//��������λ�� С�� ����λ��ʱ 
	{
		cout << "0.00" << endl;
		cout << "������Ҳ̫С�˰ɣ��Ҳ����ٴ�һ��!" << endl;
	}
	else //��������λ�� ���ڻ��� ����λ��ʱ
	{
		len = len1 - len2;//��������λ���Ĳ�ֵ
		for (i = len1 - 1; i >= 0; i--)//���������㣬ʹ����������λ����ͬ
		{
			if (i >= len)
				y[i] = y[i - len];
			else
				y[i] = 0;
		}
		len2 = len1;//������������λ��ͬ 		
		digit = len1;	//��ԭ������λ����ֵ��digit 
		for (j = 0; j <= len; j++)
		{
			z[len - j] = 0;
			while (((temp = judge(x, y, len1, len2)) >= 0) && digit >= k)//�ж�������֮��Ĺ�ϵ�Լ�λ�������ԭλ���Ĺ�ϵ 
			{
				sub(x, y, len1, len2);	//������������			    
				z[len - j]++;//�����̵�ÿһλ
				len1 = digit;//�����޸ı������ĳ���
				if (len1 < len2 && y[len2 - 1] == 0)
					len2 = len1;//��len1���ȸ���len2;						
			}
			if (temp < 0)//�������� С�� ������������Сһλ��
			{
				for (i = 1; i < len2; i++)
					y[i - 1] = y[i];
				y[i - 1] = 0;
				if (len1 < len2)
					len2--;
			}
		}
		cout << "���������=";
		for (i = len; i > 0; i--)//ȥ��ǰ׺0 
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
int main()//������ 
{
	Bignumber number;
	int x[100] = { 0 }, y[100] = { 0 }, z[105] = { 0 }, n[105] = { 0 };
	int i, j = 0, len1, len2;
	char m, b, shu1, shu2;
	cout << "--------------------------------" << endl;
	cout << "|******��ӭʹ�ô���������******|" << endl;
	cout << "--------------------------------" << endl;
	while (1)//���Զ���������� 
	{

		cout << "�����������ʽ��" << endl;
		while (1)
		{
			cout << "�����һ������";
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
					cout << "������ȷ������" << endl;
				break;
			}
			if (shu1 == 'n')
				break;
		}
		while (1)
		{
			cout << "����������ţ�";
			cin >> number.c;
			if (number.c != '+' && number.c != '-' && number.c != '*' && number.c != '/')
			{
				cout << "������ȷ���������" << endl;
			}
			else
				break;
		}
		while (1)
		{
			cout << "����ڶ�������";
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
					cout << "������ȷ������" << endl;
					break;
				}
			}
			if (shu2 == 'n')
				break;
		}
		if (number.c == '+')
			addition(number.a, number.b);// ���üӷ����� 
		else if (number.c == '-')
			subtraction(number.a, number.b);// ���ü������� 
		else if (number.c == '*')
			multiplication(number.a, number.b);//���ó˷����� 
		else if (number.c == '/')
			division(number.a, number.b);//���ó������� 	
		cout << endl;
		cout << "�Ƿ����ʹ�ã���y/n)" << endl;
		cin >> m;
		if (m == 'n')
			break;
	}
}