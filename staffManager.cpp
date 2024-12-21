#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

// 常量定义
const int n1 = 5, n2 = 1, n3 = 10, n4 = 1, n5 = 1; // 各类职工人数
const double MANAGER_SALARY = 20000;               // 经理固定月工资
const double TECH_HOURLY_PAY = 0.05;               // 技术员小时工资
const double TECH_BASE_PAY = 6000;                 // 技术人员的底薪
const double SALES_MANAGER_BASE_PAY = 8000;        // 销售经理的底薪
const double SALES_BASE_PAY = 4000;                // 销售人员的底薪
const double SALES_COMMISSION = 0.01;              // 销售员的工资提成比例
const double SALES_MANAGER_COMMISSION = 0.005;     // 销售经理的提成比例
const double TECH_MANAGER_BONUS_RATE = 0.002;      // 技术经理的奖金比例

// 函数声明部分：
void print_main_menu();					 // 主菜单
void print_input_menu();				 // 输入二级菜单
void print_output_menu();		 		 // 输出二级菜单
void input_employee_data();			 	 // 数据输入函数
void print_employee_data(); 		     // 数据打印
void print_sales_statistics();		 	 // 制作表头1函数，统计销售额
void print_data_statistics();		     // 制作表头2函数，数据打印
void print_work_statistics();			 // 制表头3函数，统计工作时间
void print_table_footer();				 // 制作表尾
void calculate_statistics();	 		 // 数据统计
double calculate_sales_manager_salary(); // 销售经理工资计算
double calculate_tech_manager_salary();  // 技术经理工资计算
void print_sales_manager_data();	     // 销售经理打印数据
void print_tech_manager_data();	    	 // 技术经理打印数据
void find_employee_data();				 // 数据查询

// 全局变量
string search_name; // 查询用的全局变量

// 定义类：
class Person // 员工类（基类）
{
public:
	int num;
	string name;
	double pay;
	void input() // 数据输入函数
	{
		while (1)
		{
			cout << "编号:";
			cin >> num;
			if (num > 0 && num < 99999)
				break;
			else
				cout << "输入正确的编号" << endl;
			cin.clear();
			cin.sync();
		}
		cout << "姓名:";
		cin >> name;
	}
	void print() // 打印数据函数
	{
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << num << "   " << setw(8) << name << "   " << setw(7) << pay << "   " << endl;
	}
	void find() // 查询函数
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
class Technician : public Person // 雇员类（基类）
								 // 技术员类（公有继承）
{
public:
	void input()
	{
		cout << "技术员的";
		Person::input();
		while (1)
		{
			cout << "工作时间:";
			cin >> work_cmount;
			if (work_cmount >= 0 && work_cmount <= 720)
				break;
			else
				cout << "输入正确的工作时间" << endl;
			cin.clear();
			cin.sync();
		}
		while (1)
		{
			cout << "所属技术经理的编号:";
			cin >> tu;
			if (tu > 0 && tu < 9999)
				break;
			else
				cout << "输入正确的经理编号" << endl;
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
	int get_technician_manager_id() // 调用技术员所属技术经理职工号
	{
		return tu;
	}
	double getWorkHours() // 调用技术员工作时间
	{
		return work_cmount;
	}
	void display_technician_work_hours() // 技术员工作时间输出
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
			cout << " 级 别    职 工 号    姓 名   工 资    所属部门经理编号  \n"
				 << endl;
			print();
			cout << " ********************************************************\n"
				 << endl;
		}
	}

protected:
	int tu;				// 所属技术经理职工号
	double work_cmount; // 工作时间（小时）
};
class Manager : public Person // 经理类
{
public:
	void input()
	{
		cout << "经理的";
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
class Tech_manager : public Person // 技术经理类
{
public:
	void input()
	{
		cout << "技术经理的";
		Person::input();
	}
	int get_technical_manager_number() // 调用技术经理职工号
	{
		return num;
	}
	string get_technical_manager_name() // 调用技术经理姓名
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
class Sell_manager : public Person // 销售经理类
{
public:
	void input()
	{
		cout << "销售经理的";
		Person::input();
	}
	int get_sales_manager_number() // 调用销售经理职工号
	{
		return num;
	}
	string get_sales_manager_name() // 调用销售经理姓名
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
class Seller : public Person // 销售员类
{
public:
	Seller() { sold_amount = 0; } // 构造函数，销售额初始化为0
	void input()
	{
		cout << "销售员的";
		Person::input();
		while (1)
		{
			cout << "销售额:";
			cin >> sold_amount;
			if (sold_amount >= 0 && sold_amount <= 99999)
				break;
			else
				cout << "输入正确的销售额" << endl;
			cin.clear();
			cin.sync();
		}
		while (1)
		{
			cout << "所属销售经理的编号:";
			cin >> nu;
			if (nu > 0 && nu <= 9999)
				break;
			else
				cout << "输入正确的经理编号" << endl;
			cin.clear();
			cin.sync();
		}
	}
	void grade() // 销售员业绩输出
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
	int get_sales_manager_employee_i_d() // 调用销售员所属销售经理职工号
	{
		return nu;
	}
	double getSoldAmount() // 调用销售员销售额
	{
		return sold_amount;
	}
	void find()
	{
		if (search_name == name)
		{
			cout << " ********************************************************\n"
				 << endl;
			cout << " 级 别   职 工 号    姓 名   工 资    所属部门经理编号  \n"
				 << endl;
			print();
			cout << " ********************************************************\n"
				 << endl;
		}
	}

protected:
	double sold_amount; // 销售额
	int nu;				// 所属销售经理职工号
};
// 定义全局对象数组
Technician techStaff[n1];	 // 技术员
Manager m[n2];		 // 经理
Seller salesStaff[n3];		 // 销售员
Sell_manager salesManagers[n4]; // 销售经理（下属若干销售员）
Tech_manager techManagers[n5]; // 技术经理（下属若干技术员）
// 主函数部分：
int main()
{
	char n;
	print_main_menu();
	for (int i = 0; i < 1000; i++) // 设定循环次数（便于各项操作的切换及方便查询）
	{
		cin >> n;
		switch (n)
		{
		case '1': // 数据输入
			system("cls");
			cout << endl
				 << "您所选操作为数据输入，请继续" << endl
				 << endl;
			input_employee_data();
			cout << endl;
			system("cls");
			print_main_menu();
			break;
		case '2': // 数据统计
			system("cls");
			cout << endl
				 << "您所选操作为数据统计，请继续" << endl
				 << endl;
			calculate_statistics();
			cout << endl
				 << "销售经理按工资排序为:" << '\n'
				 << endl;
			print_sales_manager_data();
			cout << endl
				 << "技术经理按工资排序为:" << '\n'
				 << endl;
			print_tech_manager_data();
			cout << endl;
			system("cls");
			print_main_menu();
			break;
		case '3': // 数据打印
			system("cls");
			cout << endl
				 << "您所选操作为数据输出，请继续" << endl
				 << endl;
			print_employee_data();
			cout << endl
				 << endl;
			cout << '\a' << "——数据输出完毕——" << '\n'
				 << '\n'
				 << endl;
			print_main_menu();
			break;
		case '4': // 数据查询
			system("cls");
			cout << endl
				 << "您所选操作为数据查询，请继续" << endl
				 << endl;
			cout << "请输入您要查询的职工姓名： ";
			cin >> search_name;
			cout << "您查询的信息如下：" << endl
				 << endl;
			find_employee_data();
			cout << endl
				 << endl;
			print_main_menu();
			break;
		case '5': // 退出系统
			system("cls");
			cout << endl
				 << "您所选操作为退出系统，请确认" << endl
				 << endl;
			cout << " 是( y )" << " " << "否( n ) ";
			cin >> n;
			if (n == 'y')
			{
				cout << '\n'
					 << "按任意键退出系统" << endl;
				exit(0);
				cout << endl;
			}
			else
				print_main_menu();
			break;
		default:
			system("cls");
			cout << endl
				 << "出错！请重新选择操作！ " << '\n'
				 << endl;
			print_main_menu();
			break;
		}
	}
	return 0;
}
// 自定义函数部分：
void print_main_menu() // 菜单函数
{
	system("cls");
	cout << "请选择您所需的操作: " << endl;
	cout << "+=====================================================================+" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|                         欢迎进入职工管理系统                        |" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|               【1】数据输入           【2】数据统计                 |" << endl;
	cout << "|               【3】数据输出           【4】数据查询                 |" << endl;
	cout << "|               【5】退出系统                                         |" << endl;
	cout << "+=====================================================================+" << endl;
	cout << endl;
	cout << "请选择:";
}
void print_input_menu() // 数据输入二级菜单函数
{
	cout << "请选择您所需的操作: " << endl;
	cout << "+=====================================================================+" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|                         欢迎进入职工管理系统                        |" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|          【1】经理数据输入           【2】技术人员数据输入          |" << endl;
	cout << "|          【3】销售员数据输入         【4】销售经理数据输入          |" << endl;
	cout << "|          【5】技术经理数据输入       【6】返回上一级                |" << endl;
	cout << "+=====================================================================+" << endl;
	cout << endl;
	cout << " 请选择:";
}
void print_output_menu() // 数据打印二级菜单函数
{
	cout << "请选择您所需的操作: " << endl;
	cout << "+=====================================================================+" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|                         欢迎进入职工管理系统                        |" << endl;
	cout << "|                                                                     |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|          【1】经理数据输出           【2】技术人员数据输出          |" << endl;
	cout << "|          【3】销售员数据输出         【4】销售经理数据输出          |" << endl;
	cout << "|          【5】技术经理数据输出       【6】返回上一级                |" << endl;
	cout << "+=====================================================================+" << endl;
	cout << endl;
	cout << " 请选择:";
}
void input_employee_data() // 数据输入函数
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
					cout << "是否进行技术员的数据输入（y/n)：";
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
					cout << "是否进行销售员的数据输入（y/n)：";
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
					cout << "是否进行销售经理的数据输入（y/n)：";
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
					cout << "是否进行技术经理的数据输入（y/n)：";
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
void print_sales_statistics() // 制表头1
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "级 别   职 工 号   姓 名   销 售 额  " << endl;
}
void print_work_statistics() // 制表头3
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "级 别   职 工 号   姓 名   工 作 时 间  " << endl;
}
void print_data_statistics() // 制表头2
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "   级 别   职 工 号   姓 名     工 资    " << endl;
}
void print_table_footer() // 制表尾
{
	cout << " ********************************************************\n"
		 << endl;
}
void calculate_statistics() // 数据统计函数
{
	int i, j;
	for (i = 0; i < n4; i++)
	{
		double sum = 0;
		cout << endl
			 << "职工号为 " << salesManagers[i].get_sales_manager_number() << " 销售经理 " << salesManagers[i].get_sales_manager_name()
			 << " 下属销售员的业绩为:" << endl
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
		cout << "   销售额总计   " << setw(12) << sum << "   " << endl;
		cout << " ********************************************************\n"
			 << endl;
	}
	for (i = 0; i < n5; i++)
	{
		cout << endl
			 << "职工号为 " << techManagers[i].get_technical_manager_number() << " 技术经理 " << techManagers[i].get_technical_manager_name()
			 << " 下属技术员的业绩为:" << endl
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
		cout << "   工作时间总计   " << setw(12) << sum << "   " << endl;
		cout << " ********************************************************\n"
			 << endl;
	}
}
double salary[n4];
double calculate_sales_manager_salary() // 销售经理工资计算及排序
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
double calculate_tech_manager_salary() // 技术经理工资计算
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
void print_sales_manager_data() // 销售经理工资输出
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
void print_tech_manager_data() // 技术经理工资输出
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
void print_employee_data() // 数据打印
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
					 << "经理" << endl; // 经理信息
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
					 << "技术人员" << endl; // 技术员信息
				cout << " ********************************************************\n"
					 << endl;
				cout << "   级 别   职 工 号   姓 名     工 资   所属部门经理编号   " << endl;
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
					 << "销售人员" << endl; // 销售员信息
				cout << "********************************************************\n"
					 << endl;
				cout << "   级 别   职 工 号   姓 名     工 资   所属部门经理编号   " << endl;
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
					 << "销售经理" << endl; // 销售经理信息
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
					 << "技术经理" << endl; // 技术经理信息
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
void find_employee_data() // 数据查询函数
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
