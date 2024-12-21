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
	const string Mark[4] = { "����", "����", "����", "÷��" };
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
//ȫ������������������
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

int player_sum[7] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 };//��ҳɼ�

int player_game[7] = { 0 , 0  ,0 , 0 , 0 , 0 , 0 };//��Ҷ��ƵĲ�����-1������0�����޴���ң�1����ȡ��Ҫ�Ƶ���С��21�㣬2������Ҫ��,9�����ʼ��

int card_now = 0;//�����Ѿ��õ�������

int main()
{

	char start_again = '0';
	while (start_again == '0' || start_again == 'c')
	{
		system("cls");
		int banker_game = 9;//ׯ�Ҷ��ƵĲ���
		Poker blackjack;//����52���˿���
		blackjack.randomPoker();//ϴ��

		int count[8];//����ÿһ����ҵĳ�������
		count[0] = 2;
		int player_num;

		//player_exist[0] = 1;//ׯ��
		//ׯ��Ϊ-1������Ϸ����
		cout << "--------------------------------" << endl;
		cout << "|******���ѽ���21�������******|" << endl;
		cout << "--------------------------------" << endl;
		cout << "��������Ҹ���(1-7):";
		cin >> player_num;
		while (player_num > 7 | player_num < 1)
		{
			cout << endl;
			cout << "����������ٴ����룺";
			cin >> player_num;
		}

		for (int i = 1; i <= player_num; i++) {
			//player_exist[i] = 1;
			player_game[i - 1] = 9;
			count[i] = 2;
		}//�Դ�����ҽ���ȷ��

		Card dealer[1][8], player[7][8];

		//card_now = 0;//���Ƴ�ʼ��
		card_now = menu(banker_game, card_now, count, player_num, player_game, blackjack, dealer, player);
		int is_finished = is_all_player_finished(player_game, player_num);
		if (is_finished == -1) {
			cout << endl << "��Ϸ������" << endl;
			showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
			showBlackjack_player(player, player_game, player_num, count);
			winBlackjack(dealer, player, player_game, player_num, count);
		}
		else if (is_finished == 3) {
			if (banker_game == 9) {
				//������Ҷ�����˶��Լ��ƵĲ�������������ׯ�Ҷ��Լ��ƵĲ���
				cout << endl << "������Ҳ���������";
				cout << "�롾BANKER������" << endl;
				showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
			}
			while (banker_game == 2 || banker_game == 9)
			{
				//�ж�ׯ�����ϵĵ����Ƿ�С�ڵ���16�����һֱС�ڵ���16��һֱ��ׯ�ҷ���
				while (bustdealer(dealer, count[0]) <= 16) {
					cout << "�����״������" << endl;
					showBlackjack_player(player, player_game, player_num, count);
					cout << endl << "ׯ����״������" << endl;
					showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
					//չʾׯ�ҵ�����
					int sum = bustdealer(dealer, count[0]);
					cout << "��BANKER�� �����ܺ�Ϊ " << sum << " " << "��BANKER����Ҫ��������" << endl << endl;
					//��ׯ�ҷ���
					card_now = deal(2, card_now, count, player_num, player_game, blackjack, dealer, player);
				}
				//ׯ�����ƴ���16
				cout << "�����״������" << endl;
				showBlackjack_player(player, player_game, player_num, count);
				cout << endl << "ׯ����״������" << endl;
				showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
				//չʾׯ�ҵ�����
				if (bustdealer(dealer, count[0]) <= 21)
				{
					banker_game = ask_banker();
					if (banker_game == 2)
					{
						//��ׯ�Ҽ��Ƶĺ���
						card_now = deal(banker_game, card_now, count, player_num, player_game, blackjack, dealer, player);
					}
					int sum = bustdealer(dealer, count[0]);
					cout << "��BANKER�� ���Ƶ���Ϊ " << sum << endl;
				}
				else
					break;

				//banker_game = 999;
			}
			cout << endl << "��Ϸ������������������" << endl;
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
	cout << "�������������ڷ����С���������" << endl;

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
	cout << "��BANKER�� ";
	showBlackjack_banker(blackjack, card_now, dealer, player, player_game, player_num, count);
	cout << endl;

	bustBlackjack(player, player_game, player_num, count);
	showBlackjack_player(player, player_game, player_num, count);
	card_now = deal(banker_game, card_now, count, player_num, player_game, blackjack, dealer, player);
	bustBlackjack(player, player_game, player_num, count);
	for (int i = 0; i < player_num; i++)//����ѭ��ע�ͺ󣬿���ʵ����Ҷ��ȡ��
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
		//��ʼ���׶�
	}
	else if (is_finished == 2) {
		//�������δ����Ҫ�ƽ׶�
		for (int i = 0; i < player_num; i++) {
			//ֻ�е���Ҵ���Ҫ�ƽ׶�ʱ�Ÿ�����ҷ���
			if (player_game[i] == 2)
				player[i][count[i + 1]++] = blackjack.dealPoker(card_now++);
		}
	}
	else if (is_finished == 3) {
		//������ҽ���Ҫ�ƣ���ׯ�ҷ���
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
		//������Ҷ�����Ҫ�ƽ׶�
		if (sum_bao == -player_num)
			result = -1;//������ұ���
		else
			result = 3;//�ֵ�ׯ�ҿ�ʼҪ��
	}
	else if (sum > player_num && sum < player_num * 81) {
		//������Ҵ���Ҫ�ƽ׶�
		result = 2;//ֻ��ʾ��ׯ�ҵ��Ƶ��ǲ��ֵ�ׯ��Ҫ��
	}
	else if (sum == player_num * 81) {
		//��ʼ���׶Σ�������Ҷ�û�п�ʼҪ�ƽ׶Σ���ʱֻ��ʾһ��ׯ�ҵ���
		result = 1;
	}
	return result;
}

//��ׯ�ҵ���չʾ����
void showBlackjack_banker(Poker blackjack, int card_now, Card dealer[1][8], Card player[][8], int player_game[7], int player_num, int count[8])
//ׯ�ҵ��ƿ⣬��ҳ���״̬���飬�������������ׯ�Һ���ҵĳ�����
{
	int is_finished;
	is_finished = is_all_player_finished(player_game, player_num);
	if (is_finished == 1) {
		cout << "��ɫ��";
		//��ʼ�׶Σ�ׯ��ֻ��ʾ��һ����
		cout << dealer[0][0].mark << dealer[0][0].point;
	}
	else if (is_finished == 2)
	{
		cout << "��ɫ��";
		//չʾׯ�ҵ������ƣ���Ҫ��
		for (int i = 0; i < count[0]; i++)
			cout << dealer[0][i].mark << dealer[0][i].point << "   ";
		cout << "����:" << bustdealer(dealer, count[0]);
		cout << endl;
	}
	else if (is_finished == 3) {
		//չʾׯ�ҵ������ƣ���ѯ���Ƿ�Ҫ��
		cout << "��BANKER�� " << "��ɫ��";
		for (int i = 0; i < count[0]; i++)
			cout << dealer[0][i].mark << dealer[0][i].point << "   ";
		cout << "����:" << bustdealer(dealer, count[0]);
		cout << endl;
	}
}

//չʾ��ҵ���
void showBlackjack_player(const Card c[7][8], int player_game[7], int player_num, int count[8])
//��ҵ��ƿ⣬����Ƿ񱬵�����Ҹ�����ÿ����ҳ�������
{
	cout << "������г��е���" << endl;
	for (int i = 0; i < player_num; i++)
	{
		cout << "��PLAYER" << i + 1 << "��";
		for (int j = 0; j < count[i + 1]; j++) {
			cout << c[i][j].mark << c[i][j].point;
			cout << "   ";
		}
		cout << "������" << player_sum[i];
		cout << endl;
	}
	cout << endl;
	if (player_game[0] != -1 && player_game[0] != 1)
		cout << "ѯ������Ƿ����ƣ�" << endl;
	else
		cout << "���״̬��" << endl;
	for (int i = 0; i < player_num; i++)
	{
		//���û�б����

		if (player_game[i] == 1)
			cout << "��PLAYER" << i + 1 << "������ȡ��" << endl;
		else if (player_game[i] == -1)
			cout << "��PLAYER" << i + 1 << "��BOOM!" << endl;
		else if (player_game[i] == 2 || player_game[i] == 9)
			ask_deal(player_game, i);
	}
	cout << endl;
}

char start_pass()
{
	cout << "����һ��?(c/q):";
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
			cout << "����һ��?(c/q):";
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
			cout << "����һ��?(c/q):";
			continue;
		}//break��continue���ڵ�ѭ��

		if (temp == 1)
			break;
	}
	return ch;
}

//ѯ��ׯ���Ƿ���
int ask_banker()
{
	int banker_game = 9;
	cout << "��BANKER�� �Ƿ��������?(y/n):";
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
			cout << "�Ƿ��������?(y/n):";
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
			cout << "�Ƿ��������?(y/n):";
			continue;
		}//break��continue���ڵ�ѭ��

		if (temp == 1)
			break;
	}
	return banker_game;
}

//ѯ���Ƿ���
void ask_deal(int player_game[7], int player_index)
{//��ҳ���״̬����ǰ�������ҳ���״̬�е��±�
	cout << "��PLAYER" << player_index + 1 << "���Ƿ��������?(y/n):";
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
			cout << "�Ƿ��������?(y/n):";
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
			cout << "�Ƿ��������?(y/n):";
			continue;
		}//break��continue���ڵ�ѭ��

		if (temp == 1)
			break;

	}
}

//�����ҵ����Ƿ�ը ����ֻ�����ҵ���
void bustBlackjack(const Card c[][8], int player_game[7], int player_num, int count[8])
{
	int count_c1[7] = { 0,0,0,0,0,0,0 };
	int exist_num = player_num;//�����ڵ������

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

//ׯ�����������Ƶĵ���֮��
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
//������ѡ����֮��ׯ��Ӯ�������Ӯ
void winBlackjack(const Card c[][8], const Card d[][8], int player_game[7], int player_num, int count[8])
{
	int count_c1 = 0;
	int count_c2 = 0;//ׯ��
	int count_d1[7] = { 0,0,0,0,0,0,0 };
	int count_d2[7] = { 0,0,0,0,0,0,0 };//���

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

	cout << endl << "��Ϸ���:" << endl;
	if (is_all_player_finished(player_game, player_num) == -1)
	{    //˵��������Ҷ�����
		cout << "������Ҷ�����������21�㣬��!" << endl << "��BANKER��WIN��" << endl;
	}
	else
	{
		if (count_c1 > 21)
		{
			cout << "��BANKER�� " << count_c1 << "��,��BANKER��BOOM��\n";
			for (int i = 0; i < 7; i++)
			{
				if (player_game[i] == 1)
				{
					cout << "��PLAYER" << i + 1 << "��" << count_d1[i] << "��,��PLAYER" << i + 1 << "��WIN!" << endl;
					cout << endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < player_num; i++)
			{
				cout << "��PLAYER" << i + 1 << "��:" << endl;
				if (count_d1[i] > 21) {
					cout << "��BANKER�� " << count_c1 << "��" << endl
						<< "��PLAYER" << i + 1 << "��" << count_d1[i] << "��	"
						<< "��PLAYER" << i + 1 << "��BOOM,��BANKER��WIN" << endl;
				}
				else
				{
					if (count_c1 > count_d1[i])
					{
						cout << "��BANKER�� " << count_c1 << "��" << endl
							<< "��PLAYER" << i + 1 << "��" << count_d1[i] << "��	"
							<< "��BANKER��WIN" << endl;
					}

					else if (count_c1 < count_d1[i])
					{
						cout << "��BANKER�� " << count_c1 << "��" << endl
							<< "��PLAYER" << i + 1 << "��" << count_d1[i] << "��	"
							<< "��PLAYER" << i + 1 << "��" << "WIN" << endl;
					}
					else
					{
						cout << "��BANKER�� " << count_c1 << "��" << endl
							<< "��PLAYER" << i + 1 << "��" << count_d1[i] << "��	"
							<< "DOGFALL" << endl;
					}
				}
				cout << endl;
			}
		}
	}
}