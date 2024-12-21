#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
using namespace std;

struct Card
{
	string mark;
	string point;
};

class Poker
{
private:
	Card card[52];
	static int num;
public:
	const string Mark[4] = { "红桃", "黑桃", "方块", "梅花" };
	const string Point[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	Poker()
	{
		for (int i = 0; i < 52; i++)
		{
			card[i].mark = Mark[i % 4];
			card[i].point = Point[i % 13];
		}
	};
	void randomPoker()
	{
		srand((unsigned int)time(0));

		for (int i = 0; i < 52; i++)
		{
			Card temp;
			temp = card[i];

			int r = rand() % 52;

			card[i] = card[r];
			card[r] = temp;
		}
	};
	Card& dealPoker(int num)
	{
		if (num < 52)
			return card[num];
		else
			cout << "No more cards!\n";
		exit(EXIT_FAILURE);
	};
};
//全部创建函数优先声明
void showBlackjack_banker(Poker blackjack, int card_now, Card dealer[1][8], Card player[][8], int player_game[7], int player_num, int count[8]);
void showBlackjack_player(const Card c[7][8], int player_game[7], int player_num, int count[8]);
void ask_deal(int player_game[7], int player_index);
int ask_banker();
char start_pass();
void bustBlackjack(const Card c[][8], int player_game[7], int player_num, int count[8]);
int bustdealer(const Card d[][8], int count);
void winBlackjack(const Card c[][8], const Card d[][8], int player_game[7], int player_num, int count[8]);
int menu(int banker_game, int card_now, int count[8], int player_num, int player_game[7], Poker blackjack, Card dealer[1][8], Card player[][8]);
int deal(int banker_game, int card_now, int count[8], int player_num, int player_game[7], Poker blackjack, Card dealer[1][8], Card player[][8]);
int is_all_player_finished(int player_game[7], int player_num);

int player_sum[7] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 };//玩家成绩

int player_game[7] = { 0 , 0  ,0 , 0 , 0 , 0 , 0 };//玩家对牌的操作，-1代表爆，0代表无此玩家，1代表取消要牌但是小于21点，2代表还在要牌,9代表初始化

int card_now = 0;//现在已经用掉的牌数

int main()
{

	char start_again = '0';
	while (start_again == '0' || start_again == 'c')
	{
		system("cls");
		int banker_game = 9;//庄家对牌的操作
		Poker blackjack;//建立52张扑克牌
		blackjack.randomPoker();//洗牌

		int count[8];//对于每一个玩家的持有牌数
		count[0] = 2;
		int player_num;

		//player_exist[0] = 1;//庄家
		//庄家为-1代表游戏结束
		cout << "--------------------------------" << endl;
		cout << "|******您已进入21点的世界******|" << endl;
		cout << "--------------------------------" << endl;
		cout << "请输入玩家个数(1-7):";
		cin >> player_num;
		while (player_num > 7 | player_num < 1)
		{
			cout << endl;
			cout << "输入错误，请再次输入：";
			cin >> player_num;
		}

		for (int i = 1; i <= player_num; i++) {
			//player_exist[i] = 1;
			player_game[i - 1] = 9;
			count[i] = 2;
		}//对存在玩家进行确定

		Card dealer[1][8], player[7][8];

		//card_now = 0;//发牌初始化
		card_now = menu(banker_game, card_now, count, player_num, player_game, blackjack, dealer, player);
		int is_finished = is_all_player_finished(player_game, player_num);
		if (is_finished == -1) {
			cout << endl << "游戏结束！" << endl;
			showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
			showBlackjack_player(player, player_game, player_num, count);
			winBlackjack(dealer, player, player_game, player_num, count);
		}
		else if (is_finished == 3) {
			if (banker_game == 9) {
				//所有玩家都完成了对自己牌的操作，接下来是庄家对自己牌的操作
				cout << endl << "所有玩家操作结束，";
				cout << "请【BANKER】亮牌" << endl;
				showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
			}
			while (banker_game == 2 || banker_game == 9)
			{
				//判断庄家手上的点数是否小于等于16，如果一直小于等于16则一直给庄家发牌
				while (bustdealer(dealer, count[0]) <= 16) {
					cout << "玩家牌状况如下" << endl;
					showBlackjack_player(player, player_game, player_num, count);
					cout << endl << "庄家牌状况如下" << endl;
					showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
					//展示庄家的手牌
					int sum = bustdealer(dealer, count[0]);
					cout << "【BANKER】 手牌总和为 " << sum << " " << "【BANKER】需要继续摸牌" << endl << endl;
					//给庄家发牌
					card_now = deal(2, card_now, count, player_num, player_game, blackjack, dealer, player);
				}
				//庄家手牌大于16
				cout << "玩家牌状况如下" << endl;
				showBlackjack_player(player, player_game, player_num, count);
				cout << endl << "庄家牌状况如下" << endl;
				showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
				//展示庄家的手牌
				if (bustdealer(dealer, count[0]) <= 21)
				{
					banker_game = ask_banker();
					if (banker_game == 2)
					{
						//给庄家加牌的函数
						card_now = deal(banker_game, card_now, count, player_num, player_game, blackjack, dealer, player);
					}
					int sum = bustdealer(dealer, count[0]);
					cout << "【BANKER】 手牌点数为 " << sum << endl;
				}
				else
					break;

				//banker_game = 999;
			}
			cout << endl << "游戏结束！本轮牌型如下" << endl;
			showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
			showBlackjack_player(player, player_game, player_num, count);
			winBlackjack(dealer, player, player_game, player_num, count);

		}

		start_again = start_pass();
	}
	return 0;
}

int menu(int banker_game, int card_now, int count[8], int player_num, int player_game[7], Poker blackjack, Card dealer[1][8], Card player[][8])
{
	cout << "—————正在发牌中—————" << endl;

	for (int i = 0; i < player_num; i++) {
		count[i + 1] = 0;
		while (count[i + 1] < 2)
		{
			dealer[0][count[i + 1]] = blackjack.dealPoker(card_now++);

			if (player_game[i] >= 2) {
				player[i][count[i + 1]++] = blackjack.dealPoker(card_now++);
			}

		}
	}
	cout << "【BANKER】 ";
	showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
	cout << endl;

	bustBlackjack(player, player_game, player_num, count);
	showBlackjack_player(player, player_game, player_num, count);
	card_now = deal(banker_game, card_now, count, player_num, player_game, blackjack, dealer, player);
	bustBlackjack(player, player_game, player_num, count);
	for (int i = 0; i < player_num; i++)//将此循环注释后，可以实现玩家多次取牌
	{
		if (player_sum[i] <= 21)
			player_game[i] = 1;
		else if (player_sum[i] > 21)
			player_game[i] = -1;
	}
	return card_now;
}

int deal(int banker_game, int card_now, int count[8], int player_num, int player_game[7], Poker blackjack, Card dealer[1][8], Card player[][8])
{
	int is_finished = is_all_player_finished(player_game, player_num);
	if (is_finished == 1) {
		//初始化阶段
	}
	else if (is_finished == 2) {
		//还有玩家未结束要牌阶段
		for (int i = 0; i < player_num; i++) {
			//只有当玩家处于要牌阶段时才给该玩家发牌
			if (player_game[i] == 2)
				player[i][count[i + 1]++] = blackjack.dealPoker(card_now++);
		}
	}
	else if (is_finished == 3) {
		//所有玩家结束要牌，给庄家发牌
		if (banker_game == 2)
			dealer[0][count[0]++] = blackjack.dealPoker(card_now++);
	}
	return card_now;
}

int is_all_player_finished(int player_game[7], int player_num)
{
	int sum = 0;
	int sum_bao = 0;
	int result = 0;
	for (int i = 0; i < player_num; i++) {
		sum += player_game[i] * player_game[i];
		sum_bao += player_game[i];
	}

	if (sum == player_num) {
		//所有玩家都结束要牌阶段
		if (sum_bao == -player_num)
			result = -1;//所有玩家爆牌
		else
			result = 3;//轮到庄家开始要牌
	}
	else if (sum > player_num && sum < player_num * 81) {
		//还有玩家处于要牌阶段
		result = 2;//只显示出庄家的牌但是不轮到庄家要牌
	}
	else if (sum == player_num * 81) {
		//初始化阶段，所有玩家都没有开始要牌阶段，此时只显示一张庄家的牌
		result = 1;
	}
	return result;
}

//将庄家的牌展示出来
void showBlackjack_banker(Poker blackjack, int card_now, Card dealer[1][8], Card player[][8], int player_game[7], int player_num, int count[8])
//庄家的牌库，玩家持牌状态数组，玩家数量，对于庄家和玩家的持牌数
{
	int is_finished;
	is_finished = is_all_player_finished(player_game, player_num);
	if (is_finished == 1) {
		cout << "花色：";
		//开始阶段，庄家只显示第一张牌
		cout << dealer[0][0].mark << dealer[0][0].point;
	}
	else if (is_finished == 2)
	{
		cout << "花色：";
		//展示庄家的两张牌，不要牌
		for (int i = 0; i < count[0]; i++)
			cout << dealer[0][i].mark << dealer[0][i].point << "   ";
		cout << "点数:" << bustdealer(dealer, count[0]);
		cout << endl;
	}
	else if (is_finished == 3) {
		//展示庄家的所有牌，并询问是否要牌
		cout << "【BANKER】 " << "花色：";
		for (int i = 0; i < count[0]; i++)
			cout << dealer[0][i].mark << dealer[0][i].point << "   ";
		cout << "点数:" << bustdealer(dealer, count[0]);
		cout << endl;
	}
}

//展示玩家的牌
void showBlackjack_player(const Card c[7][8], int player_game[7], int player_num, int count[8])
//玩家的牌库，玩家是否爆掉，玩家个数，每个玩家持有牌数
{
	cout << "玩家手中持有的牌" << endl;
	for (int i = 0; i < player_num; i++)
	{
		cout << "【PLAYER" << i + 1 << "】";
		for (int j = 0; j < count[i + 1]; j++) {
			cout << c[i][j].mark << c[i][j].point;
			cout << "   ";
		}
		cout << "点数：" << player_sum[i];
		cout << endl;
	}
	cout << endl;
	if (player_game[0] != -1 && player_game[0] != 1)
		cout << "询问玩家是否摸牌：" << endl;
	else
		cout << "玩家状态：" << endl;
	for (int i = 0; i < player_num; i++)
	{
		//玩家没有爆输出

		if (player_game[i] == 1)
			cout << "【PLAYER" << i + 1 << "】不能取牌" << endl;
		else if (player_game[i] == -1)
			cout << "【PLAYER" << i + 1 << "】BOOM!" << endl;
		else if (player_game[i] == 2 || player_game[i] == 9)
			ask_deal(player_game, i);
	}
	cout << endl;
}

char start_pass()
{
	cout << "再来一局?(c/q):";
	string str;
	char ch = 'x';
	int temp = 0;

	while (cin >> str)
	{
		if (str.length() > 1)
			ch = 'x';
		else
			ch = str[0];
		if (!isalpha(ch))
		{
			cout << "再来一局?(c/q):";
			continue;
		}

		switch (ch)
		{
		case 'c':
			temp++;
			break;
		case 'q':
			temp++;
			break;
		default:
			cout << "再来一局?(c/q):";
			continue;
		}//break和continue存在的循环

		if (temp == 1)
			break;
	}
	return ch;
}

//询问庄家是否发牌
int ask_banker()
{
	int banker_game = 9;
	cout << "【BANKER】 是否继续发牌?(y/n):";
	string str;
	char ch;
	int temp = 0;

	while (cin >> str)
	{
		if (str.length() > 1)
			ch = '0';
		else
			ch = str[0];
		if (!isalpha(ch))
		{
			cout << "是否继续发牌?(y/n):";
			continue;
		}

		switch (ch)
		{
		case 'y':
			banker_game = 2;
			temp++;
			break;
		case 'n':
			banker_game = 1;
			temp++;
			break;
		default:
			cout << "是否继续发牌?(y/n):";
			continue;
		}//break和continue存在的循环

		if (temp == 1)
			break;
	}
	return banker_game;
}

//询问是否发牌
void ask_deal(int player_game[7], int player_index)
{//玩家持牌状态，当前玩家在玩家持牌状态中的下标
	cout << "【PLAYER" << player_index + 1 << "】是否继续发牌?(y/n):";
	string str;
	char ch;
	int temp = 0;

	while (cin >> str)
	{
		if (str.length() > 1)
			ch = '0';
		else
			ch = str[0];
		if (!isalpha(ch))
		{
			cout << "是否继续发牌?(y/n):";
			continue;
		}

		switch (ch)
		{
		case 'y':
			player_game[player_index] = 2;
			temp++;
			break;
		case 'n':
			player_game[player_index] = 1;
			temp++;
			break;

		default:
			cout << "是否继续发牌?(y/n):";
			continue;
		}//break和continue存在的循环

		if (temp == 1)
			break;

	}
}

//检测玩家的牌是否爆炸 这里只针对玩家的牌
void bustBlackjack(const Card c[][8], int player_game[7], int player_num, int count[8])
{
	int count_c1[7] = { 0,0,0,0,0,0,0 };
	int exist_num = player_num;//还存在的玩家数

	for (int i = 0; i < player_num; i++)
	{
		for (int j = 0; j < count[i + 1]; j++) {
			if (c[i][j].point == "A")
			{
				count_c1[i] += 1;
			}
			else if (c[i][j].point == "2")
			{
				count_c1[i] += 2;
			}
			else if (c[i][j].point == "3")
			{
				count_c1[i] += 3;
			}
			else if (c[i][j].point == "4")
			{
				count_c1[i] += 4;
			}
			else if (c[i][j].point == "5")
			{
				count_c1[i] += 5;
			}
			else if (c[i][j].point == "6")
			{
				count_c1[i] += 6;
			}
			else if (c[i][j].point == "7")
			{
				count_c1[i] += 7;
			}
			else if (c[i][j].point == "8")
			{
				count_c1[i] += 8;
			}
			else if (c[i][j].point == "9")
			{
				count_c1[i] += 9;
			}
			else if (c[i][j].point == "10" || c[i][j].point == "J" || c[i][j].point == "Q" || c[i][j].point == "K")
			{
				count_c1[i] += 10;
			}
		}
		player_sum[i] = count_c1[i];
	}

	for (int i = 0; i < player_num; i++) {
		if (count_c1[i] > 21)
		{
			player_game[i] = -1;
			exist_num--;
		}
	}
}

//庄家手上所有牌的点数之和
int bustdealer(const Card d[][8], int count)
{
	int sum = 0;
	for (int j = 0; j < count; j++) {
		if (d[0][j].point == "A")
		{
			sum += 1;
		}
		else if (d[0][j].point == "2")
		{
			sum += 2;
		}
		else if (d[0][j].point == "3")
		{
			sum += 3;
		}
		else if (d[0][j].point == "4")
		{
			sum += 4;
		}
		else if (d[0][j].point == "5")
		{
			sum += 5;
		}
		else if (d[0][j].point == "6")
		{
			sum += 6;
		}
		else if (d[0][j].point == "7")
		{
			sum += 7;
		}
		else if (d[0][j].point == "8")
		{
			sum += 8;
		}
		else if (d[0][j].point == "9")
		{
			sum += 9;
		}
		else if (d[0][j].point == "10" || d[0][j].point == "J" || d[0][j].point == "Q" || d[0][j].point == "K")
		{
			sum += 10;
		}
	}
	return sum;
}
//检测玩家选择开牌之后庄家赢还是玩家赢
void winBlackjack(const Card c[][8], const Card d[][8], int player_game[7], int player_num, int count[8])
{
	int count_c1 = 0;
	int count_c2 = 0;//庄家
	int count_d1[7] = { 0,0,0,0,0,0,0 };
	int count_d2[7] = { 0,0,0,0,0,0,0 };//玩家

	for (int i = 0; i < count[0]; i++) {
		if (c[0][i].point == "A")
		{
			if (count_c1 == 1) {
				count_c1 += 1; count_c2 = count_c1 + 11;
			}
			else {
				count_c1 += 1; count_c2 += 11;

			}
		}
		else if (c[0][i].point == "2")
		{
			count_c1 += 2; count_c2 += 2;
		}
		else if (c[0][i].point == "3")
		{
			count_c1 += 3; count_c2 += 3;
		}
		else if (c[0][i].point == "4")
		{
			count_c1 += 4; count_c2 += 4;
		}
		else if (c[0][i].point == "5")
		{
			count_c1 += 5; count_c2 += 5;
		}
		else if (c[0][i].point == "6")
		{
			count_c1 += 6; count_c2 += 6;
		}
		else if (c[0][i].point == "7")
		{
			count_c1 += 7; count_c2 += 7;
		}
		else if (c[0][i].point == "8")
		{
			count_c1 += 8; count_c2 += 8;
		}
		else if (c[0][i].point == "9")
		{
			count_c1 += 9; count_c2 += 9;
		}
		else if (c[0][i].point == "10")
		{
			count_c1 += 10; count_c2 += 10;
		}
		else if (c[0][i].point == "J")
		{
			count_c1 += 10; count_c2 += 10;
		}
		else if (c[0][i].point == "Q")
		{
			count_c1 += 10; count_c2 += 10;
		}
		else if (c[0][i].point == "K")
		{
			count_c1 += 10; count_c2 += 10;
		}
	}

	for (int i = 0; i < player_num; i++)
	{
		for (int j = 0; j < count[i + 1]; j++) {
			if (d[i][j].point == "A")
			{
				count_d1[i] += 1; count_d2[i] += 11;
			}
			else if (d[i][j].point == "2")
			{
				count_d1[i] += 2; count_d2[i] += 2;
			}
			else if (d[i][j].point == "3")
			{
				count_d1[i] += 3; count_d2[i] += 3;
			}
			else if (d[i][j].point == "4")
			{
				count_d1[i] += 4; count_d2[i] += 4;
			}
			else if (d[i][j].point == "5")
			{
				count_d1[i] += 5; count_d2[i] += 5;
			}
			else if (d[i][j].point == "6")
			{
				count_d1[i] += 6; count_d2[i] += 6;
			}
			else if (d[i][j].point == "7")
			{
				count_d1[i] += 7; count_d2[i] += 7;
			}
			else if (d[i][j].point == "8")
			{
				count_d1[i] += 8; count_d2[i] += 8;
			}
			else if (d[i][j].point == "9")
			{
				count_d1[i] += 9; count_d2[i] += 9;
			}
			else if (d[i][j].point == "10")
			{
				count_d1[i] += 10; count_d2[i] += 10;
			}
			else if (d[i][j].point == "J")
			{
				count_d1[i] += 10; count_d2[i] += 10;
			}
			else if (d[i][j].point == "Q")
			{
				count_d1[i] += 10; count_d2[i] += 10;
			}
			else if (d[i][j].point == "K")
			{
				count_d1[i] += 10; count_d2[i] += 10;
			}
		}
	}

	if (count_c1 < count_c2 && count_c2 <= 21)
		count_c1 = count_c2;

	for (int i = 0; i < player_num; i++) {
		if (count_d1[i] < count_d2[i] && count_d2[i] <= 21)
			count_d1[i] = count_d2[i];
	}

	cout << endl << "游戏结果:" << endl;
	if (is_all_player_finished(player_game, player_num) == -1)
	{    //说明所有玩家都爆了
		cout << "所有玩家都点数都大于21点，爆!" << endl << "【BANKER】WIN！" << endl;
	}
	else
	{
		if (count_c1 > 21)
		{
			cout << "【BANKER】 " << count_c1 << "点,【BANKER】BOOM！\n";
			for (int i = 0; i < 7; i++)
			{
				if (player_game[i] == 1)
				{
					cout << "【PLAYER" << i + 1 << "】" << count_d1[i] << "点,【PLAYER" << i + 1 << "】WIN!" << endl;
					cout << endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < player_num; i++)
			{
				cout << "【PLAYER" << i + 1 << "】:" << endl;
				if (count_d1[i] > 21) {
					cout << "【BANKER】 " << count_c1 << "点" << endl
						<< "【PLAYER" << i + 1 << "】" << count_d1[i] << "点	"
						<< "【PLAYER" << i + 1 << "】BOOM,【BANKER】WIN" << endl;
				}
				else
				{
					if (count_c1 > count_d1[i])
					{
						cout << "【BANKER】 " << count_c1 << "点" << endl
							<< "【PLAYER" << i + 1 << "】" << count_d1[i] << "点	"
							<< "【BANKER】WIN" << endl;
					}

					else if (count_c1 < count_d1[i])
					{
						cout << "【BANKER】 " << count_c1 << "点" << endl
							<< "【PLAYER" << i + 1 << "】" << count_d1[i] << "点	"
							<< "【PLAYER" << i + 1 << "】" << "WIN" << endl;
					}
					else
					{
						cout << "【BANKER】 " << count_c1 << "点" << endl
							<< "【PLAYER" << i + 1 << "】" << count_d1[i] << "点	"
							<< "DOGFALL" << endl;
					}
				}
				cout << endl;
			}
		}
	}
}