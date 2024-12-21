#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

const int n1 = 5, n2 = 1, n3 = 10, n4 = 1, n5 = 1; /*���幫˾����ְ������
(n1������Ա������n2:����������n3������Ա������n4:���۾������� ;n5����������������
���Ը�����ؼ���Ա������Ա�������������۾��������*/
const double m_salary = 20000;					   // ����̶��¹���
const double hourpay = 0.05;					   // ����ԱСʱ����
const double tbasicpay = 6000;					   // ������Ա�ĵ�н
const double basicpay = 8000;					   // ���۾���ĵ�н
const double sbasicpay = 4000;					   // ������Ա�ĵ�н
const double s_proportion = 1.0 / 100;			   // ����Ա�Ĺ�����ɱ���
const double sm_proportion = 5.0 / 1000;		   // ���۾������ɱ���
const double tm_proportion = 0.2 / 100;			   // ��������Ľ���������
// �����������֣�
void menu();		// ���˵�
void menu2();		// ��������˵�
void menu3();		// ��������˵�
void data_input();	// �������뺯��
void data_print();	// ���ݴ�ӡ
void charthead1();	// ������ͷ1������ͳ�����۶�
void charthead2();	// ������ͷ2���������ݴ�ӡ
void charthead3();	// �Ʊ�ͷ3������ͳ�ƹ���ʱ��
void chartend();	// ������β
void statistics();	// ����ͳ��
double sm_salary(); // ���۾����ʼ���
double tm_salary(); // ���������ʼ���
void sm_print();	// ���۾����ӡ����
void tm_print();	// ���������ӡ����
void data_find();	// ���ݲ�ѯ
string f_name;		// ȫ�ֱ�������ѯ�ã�
// �����ࣺ
class Person // Ա���ࣨ���ࣩ
{
public:
	int num;
	string name;
	double pay;
	void input() // �������뺯��
	{
		while (1)
		{
			cout << "���:";
			cin >> num;
			if (num > 0 && num < 99999)
				break;
			else
				cout << "������ȷ�ı��" << endl;
			cin.clear();
			cin.sync();
		}
		cout << "����:";
		cin >> name;
	}
	void print() // ��ӡ���ݺ���
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << num << "   " << setw(8) << name << "   " << setw(7) << pay << "   " << endl;
	}
	void find() // ��ѯ����
	{
		if (f_name == name)
		{
			charthead2();
			print();
			chartend();
			cout << endl;
		}
	}
};
class Technician : public Person // ��Ա�ࣨ���ࣩ
								 // ����Ա�ࣨ���м̳У�
{
public:
	void input()
	{
		cout << "����Ա��";
		Person::input();
		while (1)
		{
			cout << "����ʱ��:";
			cin >> work_cmount;
			if (work_cmount >= 0 && work_cmount <= 720)
				break;
			else
				cout << "������ȷ�Ĺ���ʱ��" << endl;
			cin.clear();
			cin.sync();
		}
		while (1)
		{
			cout << "������������ı��:";
			cin >> tu;
			if (tu > 0 && tu < 9999)
				break;
			else
				cout << "������ȷ�ľ�����" << endl;
			cin.clear();
			cin.sync();
		}
	}
	void print()
	{
		pay = work_cmount * hourpay + tbasicpay;
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "2" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << pay << "  " << setw(13) << tu << endl;
	}
	int t_number() // ���ü���Ա������������ְ����
	{
		return tu;
	}
	double cmount() // ���ü���Ա����ʱ��
	{
		return work_cmount;
	}
	void t_grade() // ����Ա����ʱ�����
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "2" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << work_cmount << "  " << endl;
	}
	void find()
	{
		Person::find();
		if (f_name == name)
		{
			cout << " ********************************************************\n"
				 << endl;
			cout << " �� ��    ְ �� ��    �� ��   �� ��    �������ž�����  \n"
				 << endl;
			print();
			cout << " ********************************************************\n"
				 << endl;
		}
	}

protected:
	int tu;				// ������������ְ����
	double work_cmount; // ����ʱ�䣨Сʱ��
};
class Manager : public Person // ������
{
public:
	void input()
	{
		cout << "�����";
		Person::input();
	}
	void print()
	{
		pay = m_salary;
		//	Person::print();
		cout << " ********************************************************\n"
			 << endl;
		cout << " " << setw(6) << "4" << "  " << setw(6) << num << "  " << setw(8) << name << "    " << setw(7) << pay << endl;
	}
	void find()
	{
		Person::find();
	}
};
class Tech_manager : public Person // ����������
{
public:
	void input()
	{
		cout << "���������";
		Person::input();
	}
	int tm_number() // ���ü�������ְ����
	{
		return num;
	}
	string tm_name() // ���ü�����������
	{
		return name;
	}
	void print()
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "3" << "  " << setw(6) << num << "  " << setw(8) << name << "   ";
	}
};
class Sell_manager : public Person // ���۾�����
{
public:
	void input()
	{
		cout << "���۾����";
		Person::input();
	}
	int sm_number() // �������۾���ְ����
	{
		return num;
	}
	string sm_name() // �������۾�������
	{
		return name;
	}
	void print()
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "3" << "  " << setw(6) << num << "  " << setw(8) << name << "  ";
	}
};
class Seller : public Person // ����Ա��
{
public:
	Seller() { sold_amount = 0; } // ���캯�������۶��ʼ��Ϊ0
	void input()
	{
		cout << "����Ա��";
		Person::input();
		while (1)
		{
			cout << "���۶�:";
			cin >> sold_amount;
			if (sold_amount >= 0 && sold_amount <= 99999)
				break;
			else
				cout << "������ȷ�����۶�" << endl;
			cin.clear();
			cin.sync();
		}
		while (1)
		{
			cout << "�������۾���ı��:";
			cin >> nu;
			if (nu > 0 && nu <= 9999)
				break;
			else
				cout << "������ȷ�ľ�����" << endl;
			cin.clear();
			cin.sync();
		}
	}
	void grade() // ����Աҵ�����
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "1" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << sold_amount << "  " << endl;
	}
	void print()
	{
		pay = sold_amount * s_proportion + sbasicpay;
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "1" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << pay << "  " << setw(13) << nu << "  " << endl;
	}
	int s_number() // ��������Ա�������۾���ְ����
	{
		return nu;
	}
	double amount() // ��������Ա���۶�
	{
		return sold_amount;
	}
	void find()
	{
		if (f_name == name)
		{
			cout << " ********************************************************\n"
				 << endl;
			cout << " �� ��   ְ �� ��    �� ��   �� ��    �������ž�����  \n"
				 << endl;
			print();
			cout << " ********************************************************\n"
				 << endl;
		}
	}

protected:
	double sold_amount; // ���۶�
	int nu;				// �������۾���ְ����
};
// ����ȫ�ֶ�������
Technician techStaff[n1];	 // ����Ա
Manager m[n2];		 // ����
Seller salesStaff[n3];		 // ����Ա
Sell_manager salesManagers[n4]; // ���۾���������������Ա��
Tech_manager techManagers[n5]; // ���������������ɼ���Ա��
// ���������֣�
int main()
{
	char n;
	menu();
	for (int i = 0; i < 1000; i++) // �趨ѭ�����������ڸ���������л��������ѯ��
	{
		cin >> n;
		switch (n)
		{
		case '1': // ��������
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ�������룬���������" << endl
				 << endl;
			data_input();
			cout << endl;
			system("cls");
			menu();
			break;
		case '2': // ����ͳ��
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ����ͳ�ƣ����������" << endl
				 << endl;
			statistics();
			cout << endl
				 << "���۾�����������Ϊ:" << '\n'
				 << endl;
			sm_print();
			cout << endl
				 << "����������������Ϊ:" << '\n'
				 << endl;
			tm_print();
			cout << endl;
			system("cls");
			menu();
			break;
		case '3': // ���ݴ�ӡ
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ������������������" << endl
				 << endl;
			data_print();
			cout << endl
				 << endl;
			cout << '\a' << "�������������ϡ���" << '\n'
				 << '\n'
				 << endl;
			menu();
			break;
		case '4': // ���ݲ�ѯ
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ���ݲ�ѯ�����������" << endl
				 << endl;
			cout << "��������Ҫ��ѯ��ְ�������� ";
			cin >> f_name;
			cout << "����ѯ����Ϣ���£�" << endl
				 << endl;
			data_find();
			cout << endl
				 << endl;
			menu();
			break;
		case '5': // �˳�ϵͳ
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ�˳�ϵͳ����ȷ�ϡ���" << endl
				 << endl;
			cout << " ��( y )" << " " << "��( n ) ";
			cin >> n;
			if (n == 'y')
			{
				cout << '\n'
					 << "�����밴������˳�ϵͳ����" << endl;
				exit(0);
				cout << endl;
			}
			else
				menu();
			break;
		default:
			system("cls");
			cout << endl
				 << "��������������ѡ������� " << '\n'
				 << endl;
			menu();
			break;
		}
	}
	return 0;
}
// �Զ��庯�����֣�
void menu() // �˵�����
{
	system("cls");
	cout << "��ѡ��������Ĳ���: " << endl;
	cout << "+=====================================================================+" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|                         ��ӭ����ְ������ϵͳ                        |" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|               ��1����������           ��2������ͳ��                 |" << endl;
	cout << "|               ��3���������           ��4�����ݲ�ѯ                 |" << endl;
	cout << "|               ��5���˳�ϵͳ                                         |" << endl;
	cout << "+=====================================================================+" << endl;
	cout << endl;
	cout << "��ѡ��:";
}
void menu2() // ������������˵�����
{
	cout << "��ѡ��������Ĳ���: " << endl;
	cout << "+=====================================================================+" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|                         ��ӭ����ְ������ϵͳ                        |" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|          ��1��������������           ��2��������Ա��������          |" << endl;
	cout << "|          ��3������Ա��������         ��4�����۾�����������          |" << endl;
	cout << "|          ��5������������������       ��6��������һ��                |" << endl;
	cout << "+=====================================================================+" << endl;
	cout << endl;
	cout << " ��ѡ��:";
}
void menu3() // ���ݴ�ӡ�����˵�����
{
	cout << "��ѡ��������Ĳ���: " << endl;
	cout << "+=====================================================================+" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|                         ��ӭ����ְ������ϵͳ                        |" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|          ��1�������������           ��2��������Ա�������          |" << endl;
	cout << "|          ��3������Ա�������         ��4�����۾����������          |" << endl;
	cout << "|          ��5�����������������       ��6��������һ��                |" << endl;
	cout << "+=====================================================================+" << endl;
	cout << endl;
	cout << " ��ѡ��:";
}
void data_input() // �������뺯��
{
	char p, q;
	int i;
	menu2();
	for (int j = 0; j < 100; j++)
	{
		cin >> p;
		if (p >= '6' || p < 1)
			break;
		else
		{
			switch (p)
			{
			case '1':
				for (i = 0; i < n2; i++)
					m[i].input();
				cout << endl
					 << "-----------------------------------------------------" << endl;
				menu2();
				break;
			case '2':
				for (i = 0; i < n1; i++)
				{
					cout << "�Ƿ���м���Ա���������루y/n)��";
					cin >> q;
					if (q == 'y')
						techStaff[i].input();
					else
						break;
				}
				cout << endl
					 << "-----------------------------------------------------" << endl;
				menu2();
				break;
			case '3':
				for (i = 0; i < n3; i++)
				{
					cout << "�Ƿ��������Ա���������루y/n)��";
					cin >> q;
					if (q == 'y')
						salesStaff[i].input();
					else
						break;
				}
				cout << endl
					 << "-----------------------------------------------------" << endl;
				menu2();
				break;
			case '4':
				for (i = 0; i < n4; i++)
				{
					cout << "�Ƿ�������۾�����������루y/n)��";
					cin >> q;
					if (q == 'y')
						salesManagers[i].input();
					else
						break;
				}
				cout << endl
					 << "--------------------------------------------------" << endl;
				menu2();
				break;
			case '5':
				for (i = 0; i < n4; i++)
				{
					cout << "�Ƿ���м���������������루y/n)��";
					cin >> q;
					if (q == 'y')
						techManagers[i].input();
					else
						break;
				}
				cout << endl
					 << "--------------------------------------------------" << endl;
				menu2();
				break;
			}
		}
	}
}
void charthead1() // �Ʊ�ͷ1
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "�� ��   ְ �� ��   �� ��   �� �� ��  " << endl;
}
void charthead3() // �Ʊ�ͷ3
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "�� ��   ְ �� ��   �� ��   �� �� ʱ ��  " << endl;
}
void charthead2() // �Ʊ�ͷ2
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "   �� ��   ְ �� ��   �� ��     �� ��    " << endl;
}
void chartend() // �Ʊ�β
{
	cout << " ********************************************************\n"
		 << endl;
}
void statistics() // ����ͳ�ƺ���
{
	int i, j;
	for (i = 0; i < n4; i++)
	{
		double sum = 0;
		cout << endl
			 << "ְ����Ϊ " << salesManagers[i].sm_number() << " ���۾��� " << salesManagers[i].sm_name()
			 << " ��������Ա��ҵ��Ϊ:" << endl
			 << endl;
		charthead1();
		for (j = 0; j < n3; j++)
			if (salesStaff[j].s_number() == salesManagers[i].sm_number())
			{
				sum = sum + salesStaff[j].amount();
				salesStaff[j].grade();
			}
		cout << " ********************************************************\n"
			 << endl;
		cout << "   ���۶��ܼ�   " << setw(12) << sum << "   " << endl;
		cout << " ********************************************************\n"
			 << endl;
	}
	for (i = 0; i < n5; i++)
	{
		cout << endl
			 << "ְ����Ϊ " << techManagers[i].tm_number() << " �������� " << techManagers[i].tm_name()
			 << " ��������Ա��ҵ��Ϊ:" << endl
			 << endl;
		double sum = 0;
		charthead3();
		for (j = 0; j < n1; j++)
		{
			if (techStaff[j].t_number() == techManagers[i].tm_number())
			{
				sum = sum + techStaff[j].cmount();
				techStaff[j].t_grade();
			}
		}
		cout << " ********************************************************\n"
			 << endl;
		cout << "   ����ʱ���ܼ�   " << setw(12) << sum << "   " << endl;
		cout << " ********************************************************\n"
			 << endl;
	}
}
double salary[n4];
double sm_salary() // ���۾����ʼ��㼰����
{
	int i, j;
	double a;
	Sell_manager b;
	for (int k = 0; k < n4; k++)
		salary[k] = 0;
	for (i = 0; i < n4; i++)
	{
		double sum = 0;
		for (j = 0; j < n3; j++)
			if (salesStaff[j].s_number() == salesManagers[i].sm_number())
			{
				sum = sum + salesStaff[j].amount();
				salary[i] = sum * sm_proportion + basicpay;
			}
	}
	for (j = 0; j < n4 - 1; j++)
		for (i = 0; i < n4 - 1 - j; i++)
			if (salary[i] < salary[i + 1])
			{
				a = salary[i + 1];
				salary[i + 1] = salary[i];
				salary[i] = a;
				b = salesManagers[i + 1];
				salesManagers[i + 1] = salesManagers[i];
				salesManagers[i] = b;
			}
	return 0;
}
double t_salary[n5];
double tm_salary() // ���������ʼ���
{
	int i, j;
	double a;
	Tech_manager b;
	for (int k = 0; k < n5; k++)
		t_salary[k] = 0;
	for (i = 0; i < n5; i++)
	{
		double sum = 0;
		for (j = 0; j < n1; j++)
			if (techStaff[j].t_number() == techManagers[i].tm_number())
			{
				sum = sum + techStaff[j].cmount();
				t_salary[i] = sum * tm_proportion + basicpay;
			}
	}
	for (j = 0; j < n4 - 1; j++)
		for (i = 0; i < n4 - 1 - j; i++)
			if (t_salary[i] < t_salary[i + 1])
			{
				a = t_salary[i + 1];
				t_salary[i + 1] = t_salary[i];
				t_salary[i] = a;
				b = techManagers[i + 1];
				techManagers[i + 1] = techManagers[i];
				techManagers[i] = b;
			}
	return 0;
}
void sm_print() // ���۾��������
{
	sm_salary();
	charthead2();
	for (int i = 0; i < n4; i++)
	{
		salesManagers[i].print();
		cout << setw(7) << salary[i] << "   " << endl;
	}
	chartend();
	cout << endl;
}
void tm_print() // �������������
{
	tm_salary();
	charthead2();
	for (int i = 0; i < n5; i++)
	{
		techManagers[i].print();
		cout << setw(7) << t_salary[i] << "   " << endl;
	}
	chartend();
	cout << endl;
}
void data_print() // ���ݴ�ӡ
{
	char p;
	int i, j;
	menu3();
	for (j = 0; j < 100; j++)
	{
		cin >> p;
		if (p < '1' || p >= '6')
			break;
		else
		{
			switch (p)
			{
			case '1':
				cout << endl
					 << "����" << endl; // ������Ϣ
				charthead2();
				for (i = 0; i < n2; i++)
					m[i].print();
				chartend();
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl;
				menu3();
				break;
			case '2':
				cout << endl
					 << "������Ա" << endl; // ����Ա��Ϣ
				cout << " ********************************************************\n"
					 << endl;
				cout << "   �� ��   ְ �� ��   �� ��     �� ��   �������ž�����   " << endl;
				for (i = 0; i < n1; i++)
					techStaff[i].print();
				cout << " ********************************************************\n"
					 << endl;
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl;
				menu3();
				break;
			case '3':
				cout << endl
					 << "������Ա" << endl; // ����Ա��Ϣ
				cout << "********************************************************\n"
					 << endl;
				cout << "   �� ��   ְ �� ��   �� ��     �� ��   �������ž�����   " << endl;
				for (i = 0; i < n3; i++)
					salesStaff[i].print();
				cout << " ********************************************************\n"
					 << endl;
				cout << endl
					 << endl
					 << "------------------------------------------------------------------------" << '\n'
					 << endl;
				menu3();
				break;
			case '4':
				cout << endl
					 << "���۾���" << endl; // ���۾�����Ϣ
				sm_salary();
				sm_print();
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl
					 << endl;
				menu3();
				break;
			case '5':
				cout << endl
					 << "��������" << endl; // ����������Ϣ
				tm_salary();
				tm_print();
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl
					 << endl;
				menu3();
				break;
			}
		}
	}
}
void data_find() // ���ݲ�ѯ����
{
	int i;
	for (i = 0; i < n1; i++)
		techStaff[i].find();
	for (i = 0; i < n2; i++)
		m[i].find();
	for (i = 0; i < n3; i++)
		salesStaff[i].find();
	for (i = 0; i < n4; i++)
		if (f_name == salesManagers[i].sm_name())
		{
			charthead2();
			salesManagers[i].print();
			cout << setw(7) << salary[i] << "   " << endl;
			chartend();
			cout << endl;
			break;
		}
	for (i = 0; i < n5; i++)
		if (f_name == techManagers[i].tm_name())
		{
			charthead2();
			techManagers[i].print();
			cout << setw(7) << t_salary[i] << "   " << endl;
			chartend();
			cout << endl;
			break;
		}
}
