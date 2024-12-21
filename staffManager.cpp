#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

// ��������
const int n1 = 5, n2 = 1, n3 = 10, n4 = 1, n5 = 1; // ����ְ������
const double MANAGER_SALARY = 20000;               // ����̶��¹���
const double TECH_HOURLY_PAY = 0.05;               // ����ԱСʱ����
const double TECH_BASE_PAY = 6000;                 // ������Ա�ĵ�н
const double SALES_MANAGER_BASE_PAY = 8000;        // ���۾���ĵ�н
const double SALES_BASE_PAY = 4000;                // ������Ա�ĵ�н
const double SALES_COMMISSION = 0.01;              // ����Ա�Ĺ�����ɱ���
const double SALES_MANAGER_COMMISSION = 0.005;     // ���۾������ɱ���
const double TECH_MANAGER_BONUS_RATE = 0.002;      // ��������Ľ������

// �����������֣�
void print_main_menu();					 // ���˵�
void print_input_menu();				 // ��������˵�
void print_output_menu();		 		 // ��������˵�
void input_employee_data();			 	 // �������뺯��
void print_employee_data(); 		     // ���ݴ�ӡ
void print_sales_statistics();		 	 // ������ͷ1������ͳ�����۶�
void print_data_statistics();		     // ������ͷ2���������ݴ�ӡ
void print_work_statistics();			 // �Ʊ�ͷ3������ͳ�ƹ���ʱ��
void print_table_footer();				 // ������β
void calculate_statistics();	 		 // ����ͳ��
double calculate_sales_manager_salary(); // ���۾����ʼ���
double calculate_tech_manager_salary();  // ���������ʼ���
void print_sales_manager_data();	     // ���۾����ӡ����
void print_tech_manager_data();	    	 // ���������ӡ����
void find_employee_data();				 // ���ݲ�ѯ

// ȫ�ֱ���
string search_name; // ��ѯ�õ�ȫ�ֱ���

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
		if (search_name == name)
		{
			print_work_statistics();
			print();
			print_table_footer();
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
		pay = work_cmount * TECH_HOURLY_PAY + TECH_BASE_PAY;
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "2" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << pay << "  " << setw(13) << tu << endl;
	}
	int get_technician_manager_id() // ���ü���Ա������������ְ����
	{
		return tu;
	}
	double getWorkHours() // ���ü���Ա����ʱ��
	{
		return work_cmount;
	}
	void display_technician_work_hours() // ����Ա����ʱ�����
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "2" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << work_cmount << "  " << endl;
	}
	void find()
	{
		Person::find();
		if (search_name == name)
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
		pay = MANAGER_SALARY;
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
	int get_technical_manager_number() // ���ü�������ְ����
	{
		return num;
	}
	string get_technical_manager_name() // ���ü�����������
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
	int get_sales_manager_number() // �������۾���ְ����
	{
		return num;
	}
	string get_sales_manager_name() // �������۾�������
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
		pay = sold_amount * SALES_COMMISSION + SALES_BASE_PAY;
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "1" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << pay << "  " << setw(13) << nu << "  " << endl;
	}
	int get_sales_manager_employee_i_d() // ��������Ա�������۾���ְ����
	{
		return nu;
	}
	double getSoldAmount() // ��������Ա���۶�
	{
		return sold_amount;
	}
	void find()
	{
		if (search_name == name)
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
	print_main_menu();
	for (int i = 0; i < 1000; i++) // �趨ѭ�����������ڸ���������л��������ѯ��
	{
		cin >> n;
		switch (n)
		{
		case '1': // ��������
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ�������룬�����" << endl
				 << endl;
			input_employee_data();
			cout << endl;
			system("cls");
			print_main_menu();
			break;
		case '2': // ����ͳ��
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ����ͳ�ƣ������" << endl
				 << endl;
			calculate_statistics();
			cout << endl
				 << "���۾�����������Ϊ:" << '\n'
				 << endl;
			print_sales_manager_data();
			cout << endl
				 << "����������������Ϊ:" << '\n'
				 << endl;
			print_tech_manager_data();
			cout << endl;
			system("cls");
			print_main_menu();
			break;
		case '3': // ���ݴ�ӡ
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ��������������" << endl
				 << endl;
			print_employee_data();
			cout << endl
				 << endl;
			cout << '\a' << "�������������ϡ���" << '\n'
				 << '\n'
				 << endl;
			print_main_menu();
			break;
		case '4': // ���ݲ�ѯ
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ���ݲ�ѯ�������" << endl
				 << endl;
			cout << "��������Ҫ��ѯ��ְ�������� ";
			cin >> search_name;
			cout << "����ѯ����Ϣ���£�" << endl
				 << endl;
			find_employee_data();
			cout << endl
				 << endl;
			print_main_menu();
			break;
		case '5': // �˳�ϵͳ
			system("cls");
			cout << endl
				 << "����ѡ����Ϊ�˳�ϵͳ����ȷ��" << endl
				 << endl;
			cout << " ��( y )" << " " << "��( n ) ";
			cin >> n;
			if (n == 'y')
			{
				cout << '\n'
					 << "��������˳�ϵͳ" << endl;
				exit(0);
				cout << endl;
			}
			else
				print_main_menu();
			break;
		default:
			system("cls");
			cout << endl
				 << "����������ѡ������� " << '\n'
				 << endl;
			print_main_menu();
			break;
		}
	}
	return 0;
}
// �Զ��庯�����֣�
void print_main_menu() // �˵�����
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
void print_input_menu() // ������������˵�����
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
void print_output_menu() // ���ݴ�ӡ�����˵�����
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
void input_employee_data() // �������뺯��
{
	char p, q;
	int i;
	print_input_menu();
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
				print_input_menu();
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
				print_input_menu();
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
				print_input_menu();
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
				print_input_menu();
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
				print_input_menu();
				break;
			}
		}
	}
}
void print_sales_statistics() // �Ʊ�ͷ1
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "�� ��   ְ �� ��   �� ��   �� �� ��  " << endl;
}
void print_work_statistics() // �Ʊ�ͷ3
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "�� ��   ְ �� ��   �� ��   �� �� ʱ ��  " << endl;
}
void print_data_statistics() // �Ʊ�ͷ2
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "   �� ��   ְ �� ��   �� ��     �� ��    " << endl;
}
void print_table_footer() // �Ʊ�β
{
	cout << " ********************************************************\n"
		 << endl;
}
void calculate_statistics() // ����ͳ�ƺ���
{
	int i, j;
	for (i = 0; i < n4; i++)
	{
		double sum = 0;
		cout << endl
			 << "ְ����Ϊ " << salesManagers[i].get_sales_manager_number() << " ���۾��� " << salesManagers[i].get_sales_manager_name()
			 << " ��������Ա��ҵ��Ϊ:" << endl
			 << endl;
		print_sales_statistics();
		for (j = 0; j < n3; j++)
			if (salesStaff[j].get_sales_manager_employee_i_d() == salesManagers[i].get_sales_manager_number())
			{
				sum = sum + salesStaff[j].getSoldAmount();
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
			 << "ְ����Ϊ " << techManagers[i].get_technical_manager_number() << " �������� " << techManagers[i].get_technical_manager_name()
			 << " ��������Ա��ҵ��Ϊ:" << endl
			 << endl;
		double sum = 0;
		print_work_statistics();
		for (j = 0; j < n1; j++)
		{
			if (techStaff[j].get_technician_manager_id() == techManagers[i].get_technical_manager_number())
			{
				sum = sum + techStaff[j].getWorkHours();
				techStaff[j].display_technician_work_hours();
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
double calculate_sales_manager_salary() // ���۾����ʼ��㼰����
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
			if (salesStaff[j].get_sales_manager_employee_i_d() == salesManagers[i].get_sales_manager_number())
			{
				sum = sum + salesStaff[j].getSoldAmount();
				salary[i] = sum * SALES_MANAGER_COMMISSION + SALES_MANAGER_BASE_PAY;
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
double calculate_tech_manager_salary() // ���������ʼ���
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
			if (techStaff[j].get_technician_manager_id() == techManagers[i].get_technical_manager_number())
			{
				sum = sum + techStaff[j].getWorkHours();
				t_salary[i] = sum * TECH_MANAGER_BONUS_RATE + SALES_MANAGER_BASE_PAY;
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
void print_sales_manager_data() // ���۾��������
{
	calculate_sales_manager_salary();
	print_work_statistics();
	for (int i = 0; i < n4; i++)
	{
		salesManagers[i].print();
		cout << setw(7) << salary[i] << "   " << endl;
	}
	print_table_footer();
	cout << endl;
}
void print_tech_manager_data() // �������������
{
	calculate_tech_manager_salary();
	print_work_statistics();
	for (int i = 0; i < n5; i++)
	{
		techManagers[i].print();
		cout << setw(7) << t_salary[i] << "   " << endl;
	}
	print_table_footer();
	cout << endl;
}
void print_employee_data() // ���ݴ�ӡ
{
	char p;
	int i, j;
	print_output_menu();
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
				print_work_statistics();
				for (i = 0; i < n2; i++)
					m[i].print();
				print_table_footer();
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl;
				print_output_menu();
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
				print_output_menu();
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
				print_output_menu();
				break;
			case '4':
				cout << endl
					 << "���۾���" << endl; // ���۾�����Ϣ
				calculate_sales_manager_salary();
				print_sales_manager_data();
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl
					 << endl;
				print_output_menu();
				break;
			case '5':
				cout << endl
					 << "��������" << endl; // ����������Ϣ
				calculate_tech_manager_salary();
				print_tech_manager_data();
				cout << endl
					 << endl
					 << "-----------------------------------------------------------------------" << endl
					 << endl;
				print_output_menu();
				break;
			}
		}
	}
}
void find_employee_data() // ���ݲ�ѯ����
{
	int i;
	for (i = 0; i < n1; i++)
		techStaff[i].find();
	for (i = 0; i < n2; i++)
		m[i].find();
	for (i = 0; i < n3; i++)
		salesStaff[i].find();
	for (i = 0; i < n4; i++)
		if (search_name == salesManagers[i].get_sales_manager_name())
		{
			print_work_statistics();
			salesManagers[i].print();
			cout << setw(7) << salary[i] << "   " << endl;
			print_table_footer();
			cout << endl;
			break;
		}
	for (i = 0; i < n5; i++)
		if (search_name == techManagers[i].get_technical_manager_name())
		{
			print_work_statistics();
			techManagers[i].print();
			cout << setw(7) << t_salary[i] << "   " << endl;
			print_table_footer();
			cout << endl;
			break;
		}
}
