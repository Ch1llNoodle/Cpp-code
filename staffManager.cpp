#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

const int n1 = 5, n2 = 1, n3 = 10, n4 = 1, n5 = 1; /*定义公司各类职工人数
(n1：技术员人数；n2:经理人数；n3：销售员人数；n4:销售经理人数 ;n5：技术经理人数）
可以更改相关技术员、销售员、技术经理、销售经理的数量*/
const double m_salary = 20000;					   // 经理固定月工资
const double hourpay = 0.05;					   // 技术员小时工资
const double tbasicpay = 6000;					   // 技术人员的底薪
const double basicpay = 8000;					   // 销售经理的底薪
const double sbasicpay = 4000;					   // 销售人员的底薪
const double s_proportion = 1.0 / 100;			   // 销售员的工资提成比例
const double sm_proportion = 5.0 / 1000;		   // 销售经理的提成比例
const double tm_proportion = 0.2 / 100;			   // 技术经理的奖金计算比例
// 函数声明部分：
void menu();		// 主菜单
void menu2();		// 输入二级菜单
void menu3();		// 输出二级菜单
void data_input();	// 数据输入函数
void data_print();	// 数据打印
void charthead1();	// 制作表头1函数，统计销售额
void charthead2();	// 制作表头2函数，数据打印
void charthead3();	// 制表头3函数，统计工作时间
void chartend();	// 制作表尾
void statistics();	// 数据统计
double sm_salary(); // 销售经理工资计算
double tm_salary(); // 技术经理工资计算
void sm_print();	// 销售经理打印数据
void tm_print();	// 技术经理打印数据
void data_find();	// 数据查询
string f_name;		// 全局变量（查询用）
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
		if (f_name == name)
		{
			charthead2();
			print();
			chartend();
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
		pay = work_cmount * hourpay + tbasicpay;
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "2" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << pay << "  " << setw(13) << tu << endl;
	}
	int t_number() // 调用技术员所属技术经理职工号
	{
		return tu;
	}
	double cmount() // 调用技术员工作时间
	{
		return work_cmount;
	}
	void t_grade() // 技术员工作时间输出
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
class Tech_manager : public Person // 技术经理类
{
public:
	void input()
	{
		cout << "技术经理的";
		Person::input();
	}
	int tm_number() // 调用技术经理职工号
	{
		return num;
	}
	string tm_name() // 调用技术经理姓名
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
	int sm_number() // 调用销售经理职工号
	{
		return num;
	}
	string sm_name() // 调用销售经理姓名
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
		pay = sold_amount * s_proportion + sbasicpay;
		cout << " ********************************************************\n"
			 << endl;
		cout << "  " << setw(6) << "1" << "  " << setw(6) << num << "  " << setw(8) << name << "  " << setw(7) << pay << "  " << setw(13) << nu << "  " << endl;
	}
	int s_number() // 调用销售员所属销售经理职工号
	{
		return nu;
	}
	double amount() // 调用销售员销售额
	{
		return sold_amount;
	}
	void find()
	{
		if (f_name == name)
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
	menu();
	for (int i = 0; i < 1000; i++) // 设定循环次数（便于各项操作的切换及方便查询）
	{
		cin >> n;
		switch (n)
		{
		case '1': // 数据输入
			system("cls");
			cout << endl
				 << "您所选操作为数据输入，请继续——" << endl
				 << endl;
			data_input();
			cout << endl;
			system("cls");
			menu();
			break;
		case '2': // 数据统计
			system("cls");
			cout << endl
				 << "您所选操作为数据统计，请继续——" << endl
				 << endl;
			statistics();
			cout << endl
				 << "销售经理按工资排序为:" << '\n'
				 << endl;
			sm_print();
			cout << endl
				 << "技术经理按工资排序为:" << '\n'
				 << endl;
			tm_print();
			cout << endl;
			system("cls");
			menu();
			break;
		case '3': // 数据打印
			system("cls");
			cout << endl
				 << "您所选操作为数据输出，请继续——" << endl
				 << endl;
			data_print();
			cout << endl
				 << endl;
			cout << '\a' << "——数据输出完毕——" << '\n'
				 << '\n'
				 << endl;
			menu();
			break;
		case '4': // 数据查询
			system("cls");
			cout << endl
				 << "您所选操作为数据查询，请继续——" << endl
				 << endl;
			cout << "请输入您要查询的职工姓名： ";
			cin >> f_name;
			cout << "您查询的信息如下：" << endl
				 << endl;
			data_find();
			cout << endl
				 << endl;
			menu();
			break;
		case '5': // 退出系统
			system("cls");
			cout << endl
				 << "您所选操作为退出系统，请确认——" << endl
				 << endl;
			cout << " 是( y )" << " " << "否( n ) ";
			cin >> n;
			if (n == 'y')
			{
				cout << '\n'
					 << "——请按任意键退出系统——" << endl;
				exit(0);
				cout << endl;
			}
			else
				menu();
			break;
		default:
			system("cls");
			cout << endl
				 << "——出错！请重新选择操作！ " << '\n'
				 << endl;
			menu();
			break;
		}
	}
	return 0;
}
// 自定义函数部分：
void menu() // 菜单函数
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
void menu2() // 数据输入二级菜单函数
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
void menu3() // 数据打印二级菜单函数
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
void data_input() // 数据输入函数
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
					cout << "是否进行技术员的数据输入（y/n)：";
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
					cout << "是否进行销售员的数据输入（y/n)：";
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
					cout << "是否进行销售经理的数据输入（y/n)：";
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
					cout << "是否进行技术经理的数据输入（y/n)：";
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
void charthead1() // 制表头1
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "级 别   职 工 号   姓 名   销 售 额  " << endl;
}
void charthead3() // 制表头3
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "级 别   职 工 号   姓 名   工 作 时 间  " << endl;
}
void charthead2() // 制表头2
{
	cout << " ********************************************************\n"
		 << endl;
	cout << "   级 别   职 工 号   姓 名     工 资    " << endl;
}
void chartend() // 制表尾
{
	cout << " ********************************************************\n"
		 << endl;
}
void statistics() // 数据统计函数
{
	int i, j;
	for (i = 0; i < n4; i++)
	{
		double sum = 0;
		cout << endl
			 << "职工号为 " << salesManagers[i].sm_number() << " 销售经理 " << salesManagers[i].sm_name()
			 << " 下属销售员的业绩为:" << endl
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
		cout << "   销售额总计   " << setw(12) << sum << "   " << endl;
		cout << " ********************************************************\n"
			 << endl;
	}
	for (i = 0; i < n5; i++)
	{
		cout << endl
			 << "职工号为 " << techManagers[i].tm_number() << " 技术经理 " << techManagers[i].tm_name()
			 << " 下属技术员的业绩为:" << endl
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
		cout << "   工作时间总计   " << setw(12) << sum << "   " << endl;
		cout << " ********************************************************\n"
			 << endl;
	}
}
double salary[n4];
double sm_salary() // 销售经理工资计算及排序
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
double tm_salary() // 技术经理工资计算
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
void sm_print() // 销售经理工资输出
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
void tm_print() // 技术经理工资输出
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
void data_print() // 数据打印
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
					 << "经理" << endl; // 经理信息
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
				menu3();
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
				menu3();
				break;
			case '4':
				cout << endl
					 << "销售经理" << endl; // 销售经理信息
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
					 << "技术经理" << endl; // 技术经理信息
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
void data_find() // 数据查询函数
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
