/*��ϵͳʵ����Ҷһ����ܷ�Ϊ����
	1.ѡ��һ���ʽ
	2.ѡ�����
	3.��ȡ��ֵ���м���
  ���û��������ݲ�����Ҫ��ʱ�����Զ����أ��������û���������*/
#include<iostream>
#include<ctype.h>
#include<string>
#include<string.h>

using namespace std;
//������Ҫ���õĺ���
void currencies();
void calculate();
int main()//main������������ϵͳ�ĳ�ʼҳ�棬��ȡ�û��Ķһ���ʽ
{
	char sev_type;
	cout << "--------------------------------" << endl;
	cout << "|*****��ӭ������Ҷһ�ϵͳ*****|" << endl;
	cout << "--------------------------------" << endl;
	while (1)//���ݲ�����Ҫ��ʱ������ִ��ѭ��
	{

		cout << "һ����ѡ��һ���ʽ:" << endl;
		cout << "    1.��Ҷһ������(1)" << endl;
		cout << "    2.����Ҷһ����(2)" << endl;
		cout << "    3.�˳�ϵͳ(0)" << endl;
		cin >> sev_type;
		if (sev_type != '1' && sev_type != '2' && sev_type != '0')
			cout << "��Чѡ������������..." << endl;
		else if (sev_type == '1')
		{
			cout << "����ѡ���ǣ���Ҷһ������" << endl;
			currencies();//ִ���жϱ��ֺ���
		}
		else if (sev_type == '2')
		{
			cout << "����ѡ���ǣ�����Ҷһ����" << endl;
			currencies();//ִ���жϱ��ֺ���
		}
		else if (sev_type == '0')
		{
			cout << "��л����ʹ��" << endl;
			return 0;//ֱ���˳�����
		}
	}
}

void currencies() //ѡ��һ����ֺ��� 
{
	int kind;
	while (1)//���ݲ�����Ҫ��ʱ������ִ��ѭ��
	{
		cout << endl;
		cout << "������ѡ��һ����֣�" << endl;
		cout << "    1.Ӣ��(1)" << endl;
		cout << "    2.ŷԪ(2)" << endl;
		cout << "    3.��Ԫ(3)" << endl;
		cout << "    4.�۱�(4)" << endl;
		cout << "    5.��Ԫ(5)" << endl;
		cout << "    6.��Ԫ(6)" << endl;
		cout << "    7.��Ԫ(7)" << endl;
		cout << "    8.̩��(8)" << endl;
		cout << "    9.¬��(9)" << endl;
		cin >> kind;

		if (kind == 1)
		{
			cout << "����ѡ���ǣ�Ӣ��" << endl;
			calculate();//���ü������
			break;
		}
		else if (kind == 2)
		{
			cout << "����ѡ���ǣ�ŷԪ" << endl;
			calculate();//���ü������ 
			break;
		}
		else if (kind == 3)
		{
			cout << "����ѡ���ǣ���Ԫ" << endl;
			calculate();
			break;
		}
		else if (kind == 4)
		{
			cout << "����ѡ���ǣ��۱�" << endl;
			calculate();
			break;
		}
		else if (kind == 5)
		{
			cout << "����ѡ���ǣ���Ԫ" << endl;
			calculate();
			break;
		}
		else if (kind == 6)
		{
			cout << "����ѡ���ǣ���Ԫ" << endl;
			calculate();
			break;
		}
		else if (kind == 7)
		{
			cout << "����ѡ���ǣ���Ԫ" << endl;
			calculate();
			break;
		}
		else if (kind == 8)
		{
			cout << "����ѡ���ǣ�̩��" << endl;
			calculate();
			break;
		}
		else if (kind == 9)
		{
			cout << "����ѡ���ǣ�¬��" << endl;
			calculate();
			break;
		}
		else//�ж������Ƿ�����Ҫ������ 
		{
			cout << "��Чѡ������������..." << endl;
			cin.clear();
			cin.sync();
		}
	}
}
void calculate()//����һ�������� 
{
	float exchange, rate, num;
	while (1)//���ݲ�����Ҫ��ʱ������ִ��ѭ��
	{
		cout << endl;
		cout << "��������һ����" << endl;
		cout << "  ������һ���";
		cin >> num;
		if (num <= 0 || isalpha(num) || ispunct(num))//�ж������Ƿ�����Ҫ������,С��0����ĸ�����š��ո񶼲����� 
		{
			cout << "��Ч����" << endl;
			cin.clear();
			cin.sync();//�������,sync������ջ�����
		}
		else
		{
			break;
		}
	}
	while (1)//���ݲ�����Ҫ��ʱ������ִ��ѭ��
	{
		cout << "  ��ǰ����https://www.waihui999.com/usdcny/#100" << endl;
		cout << "  �����뵱ǰ����:";
		cin >> rate;
		getchar();
		if (rate <= 0 || rate > 10000 || isalpha(rate) || ispunct(rate))//�ж������Ƿ�����Ҫ������ 
		{
			cout << "��Ч����" << endl;
			cin.clear();//�������,sync������ջ�����
			cin.sync();
		}
		else
		{
			exchange = num * rate;
			cout << "�һ�����Ϊ��" << exchange << endl;
			break;
		}
	}
}

