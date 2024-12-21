/*本系统实现外币兑换功能分为三步
	1.选择兑换方式
	2.选择币种
	3.获取数值进行计算
  当用户输入数据不符合要求时，将自动返回，并提醒用户重新输入*/
#include<iostream>
#include<ctype.h>
#include<string>
#include<string.h>

using namespace std;
//声明需要调用的函数
void currencies();
void calculate();
int main()//main函数用于生成系统的初始页面，获取用户的兑换方式
{
	char sev_type;
	cout << "--------------------------------" << endl;
	cout << "|*****欢迎进入外币兑换系统*****|" << endl;
	cout << "--------------------------------" << endl;
	while (1)//数据不符合要求时，重新执行循环
	{

		cout << "一、请选择兑换方式:" << endl;
		cout << "    1.外币兑换人民币(1)" << endl;
		cout << "    2.人民币兑换外币(2)" << endl;
		cout << "    3.退出系统(0)" << endl;
		cin >> sev_type;
		if (sev_type != '1' && sev_type != '2' && sev_type != '0')
			cout << "无效选择，请重新输入..." << endl;
		else if (sev_type == '1')
		{
			cout << "您的选择是：外币兑换人民币" << endl;
			currencies();//执行判断币种函数
		}
		else if (sev_type == '2')
		{
			cout << "您的选择是：人民币兑换外币" << endl;
			currencies();//执行判断币种函数
		}
		else if (sev_type == '0')
		{
			cout << "感谢您的使用" << endl;
			return 0;//直接退出程序
		}
	}
}

void currencies() //选择兑换币种函数 
{
	int kind;
	while (1)//数据不符合要求时，重新执行循环
	{
		cout << endl;
		cout << "二、请选择兑换币种：" << endl;
		cout << "    1.英镑(1)" << endl;
		cout << "    2.欧元(2)" << endl;
		cout << "    3.美元(3)" << endl;
		cout << "    4.港币(4)" << endl;
		cout << "    5.澳元(5)" << endl;
		cout << "    6.日元(6)" << endl;
		cout << "    7.韩元(7)" << endl;
		cout << "    8.泰铢(8)" << endl;
		cout << "    9.卢布(9)" << endl;
		cin >> kind;

		if (kind == 1)
		{
			cout << "您的选择是：英镑" << endl;
			calculate();//调用计算金额函数
			break;
		}
		else if (kind == 2)
		{
			cout << "您的选择是：欧元" << endl;
			calculate();//调用计算金额函数 
			break;
		}
		else if (kind == 3)
		{
			cout << "您的选择是：美元" << endl;
			calculate();
			break;
		}
		else if (kind == 4)
		{
			cout << "您的选择是：港币" << endl;
			calculate();
			break;
		}
		else if (kind == 5)
		{
			cout << "您的选择是：澳元" << endl;
			calculate();
			break;
		}
		else if (kind == 6)
		{
			cout << "您的选择是：日元" << endl;
			calculate();
			break;
		}
		else if (kind == 7)
		{
			cout << "您的选择是：韩元" << endl;
			calculate();
			break;
		}
		else if (kind == 8)
		{
			cout << "您的选择是：泰铢" << endl;
			calculate();
			break;
		}
		else if (kind == 9)
		{
			cout << "您的选择是：卢布" << endl;
			calculate();
			break;
		}
		else//判断输入是否是需要的输入 
		{
			cout << "无效选择，请重新输入..." << endl;
			cin.clear();
			cin.sync();
		}
	}
}
void calculate()//计算兑换结果函数 
{
	float exchange, rate, num;
	while (1)//数据不符合要求时，重新执行循环
	{
		cout << endl;
		cout << "三、计算兑换结果" << endl;
		cout << "  请输入兑换金额：";
		cin >> num;
		if (num <= 0 || isalpha(num) || ispunct(num))//判断输入是否是需要的输入,小于0、字母、符号、空格都不可以 
		{
			cout << "无效输入" << endl;
			cin.clear();
			cin.sync();//清空输入,sync用来清空缓冲区
		}
		else
		{
			break;
		}
	}
	while (1)//数据不符合要求时，重新执行循环
	{
		cout << "  请前往：https://www.waihui999.com/usdcny/#100" << endl;
		cout << "  请输入当前汇率:";
		cin >> rate;
		getchar();
		if (rate <= 0 || rate > 10000 || isalpha(rate) || ispunct(rate))//判断输入是否是需要的输入 
		{
			cout << "无效输入" << endl;
			cin.clear();//清空输入,sync用来清空缓冲区
			cin.sync();
		}
		else
		{
			exchange = num * rate;
			cout << "兑换所得为：" << exchange << endl;
			break;
		}
	}
}