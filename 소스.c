#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996 )
#include <stdio.h>
#include <windows.h>            // gotoxy, system, sleep Ȱ��
#include <time.h>               // srand Ȱ��
#include <conio.h>				 // getch() Ȱ��

#define ARROW_UP    72
#define ARROW_DOWN  80     /*���� Ű�� ASCHII �ݺ��� ���ο��� �ι�° getch�� Ȱ���� ���� �ִ� ���� ���� �� �ֽ��ϴ�. */
#define ENTER       13

int chip = 10000;

// CP949 ���ڵ��� Ư�����ڸ� �����ͷ� ���� _row�� �̸����� ����� ������ cp949ǥ�� ���̰� _col�� ���� �ǹ��� , �� ������ %c%c�� ����ϸ� ���ϴ� Ư�����ڸ� ����� �� �ֽ��ϴ�.
int spades_row = 0xa2;   // Spades (��)
int spades_col = 0xbc;

int hearts_row = 0xa2;  // Hearts (��)
int hearts_col = 0xbe;

int diamonds_row = 0xa1; // Diamonds 
int diamonds_col = 0xdf;  

int clubs_row = 0xa2;   // Clubs (��)
int clubs_col = 0xc0;    

typedef struct _return_of_Card_Detail_function    /*Card_Detail_function�� ��ȯ���� �����ϴ� ����ü >> ��Ʈ�� cp949�� ����Ͽ� �ΰ��� ������ ����*/
{
	int suit_row;

	int suit_col;

	char value;
}Details;


int row = 0xa2;       /*CP949�� Ȱ���� Ư�� ���ڸ� ����ϱ� ���� �ڵ��Դϴ�. 16������ �����ϰ� hv�� printf�ϸ� 2*1�� �ڽ��� ����� �� �ֽ��ϴ�.*/
int col = 0xcc;

void gotoxy(int x, int y);  // GUI ������ ���� �Լ� 1
void SetColor(int color);

void Draw_Edge();    // GUI ������ ���� �Լ� 2
void Draw_Bakara(); //���� ���
void Clear(); // �ܼ�ȭ���� �׵θ� (����)���� ������ �����̽��ٷ� �о >> �ش������ gotoxy�� Ȱ�밡���� 
void Draw();
void Draw_Casino(); // play�Լ����� Ȱ��� 
void Draw_Congratulation(); // ��ǥ �޼��� ��µǴ� �ڵ���

Details Card_Detail_Function(int* row);

void Menu();
void Rule();
void Play();
void Exit();

void Rule_Print1();
void Rule_Print2();
void Rule_Print3();
void Rule_Print4();
void Rule_Print5();
void Rule_Print6();


int main(void)
{
	SetConsoleOutputCP(949);
	srand(time(NULL));
	system("cls");
	Draw();
	Menu();

}

void gotoxy(int x, int y)       
{	// gotoxy
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


void Draw_Edge() {
	int i;

	for (i = 0; i <= 58; i++)
	{										// Main Horizontal
		gotoxy(i * 2, 0);
		printf("%c%c", row, col);


		gotoxy(i * 2, 29);
		printf("%c%c", row, col);
	}

	for (i = 0; i <30; i++) {				// Main Vertical
		gotoxy(0, i);
		printf("%c%c", row, col);

		gotoxy(118, i);
		printf("%c%c", row, col);
	}


	gotoxy(0, 29);
}


void Draw_Bakara()      /*�ƽ�Ű ��Ʈ*/
{
	SetColor(13);
	gotoxy(28, 1);
	printf(" ******       **       ******      **     *******       **");
	gotoxy(28, 2);
	printf("/*////**     ****     **////**    ****   /**////**     ****");
	gotoxy(28, 3);
	printf("/*   /**    **//**   **    //    **//**  /**   /**    **//**");
	gotoxy(28, 4);
	printf("/******    **  //** /**         **  //** /*******    **  //**");
	gotoxy(28, 5);
	printf("/*//// ** **********/**        **********/**///**   **********");
	gotoxy(28, 6);
	printf("/*    /**/**//////**//**    **/**//////**/**  //** /**//////**");
	gotoxy(28, 7);
	printf("/******* /**     /** //****** /**     /**/**   //**/**     /**");
	gotoxy(28, 8);
	printf("///////  //      //   //////  //      // //     // //      //");
	SetColor(15);
}

void Clear()
{


	for (int j = 1; j <= 28; j++) /*27ȸ*/
	{
		gotoxy(2, j);
		for (int i = 2; i <= 116; i++)      /*115ȸ*/
		{
			printf(" ");
		}
	}
}

void Draw()
{
	Clear();
	Draw_Edge();
	Draw_Bakara();
}

void Menu()
{
	gotoxy(50, 13);
	printf("���� Ĩ ���� : %d", chip);
	
	gotoxy(40, 16);

	SetColor(9);
	printf("%c%c %c%c to move , press Enter key to select", 0xa1, 0xe8, 0xa1, 0xe9);
	SetColor(15);

	int option = 1;
	int key;

	while (1)
	{
		gotoxy(40, 18);
		printf(option == 1 ? "-> RULE" : "   RULE");
		gotoxy(40, 20);
		printf(option == 2 ? "-> PLAY" : "   PLAY");
		gotoxy(40, 22);
		printf(option == 3 ? "-> EXIT" : "   EXIT");

		key = getch();

		// ȭ��ǥ Ű ó��
		if (key == 224)
		{
			key = getch();
			switch (key)
			{
			case ARROW_UP:
				if (option > 1) option--;
				break;
			case ARROW_DOWN:
				if (option < 3) option++;
				break;
			default:
				break;
			}
		}
		else if (key == ENTER)
		{
			// ���� Ű�� ������ ���õ� �ɼ��� ����
			Clear();
			if (option == 1)
			{
				Rule(); /*RULE�� ����������*/
				break;
			}
			else if (option == 2)
			{
				Play(); /*PLAY �� ����������*/
				break;
			}
			else
			{
				Exit();/*EXIT�� ����������*/
				break;
			}
		}
	}
}

void Rule_Print1()        /*���η��� Ȯ�� �� �� �ִ� �ڵ�*/
{
	gotoxy(20, 6);
	SetColor(9);
	printf("���� ��ǥ");
	SetColor(15);
	gotoxy(20, 18);
	printf("�÷��̾�� ��Ŀ �� ��� ���� 9�� ����� ������ ������� �����Ͽ� �����մϴ�. ");
	gotoxy(20, 20);
	printf("������ �÷��̾� ��, ��Ŀ ��, �������� 3���� ������ �� �ϳ��� ������ �� �ֽ��ϴ�. ");
	gotoxy(20, 22);
	printf("������ ������ �������� ���� ������ ������ ������ �� �ֽ��ϴ�. ");

	gotoxy(20, 24);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}

void Rule_Print2()
{
	gotoxy(20, 6);
	SetColor(9);
	printf("ī�� ��ġ");
	SetColor(15);
	gotoxy(20, 18);
	printf("���� ī�� (2-9): ī�忡 ���� ���� ���� �����Դϴ�.");
	gotoxy(20, 20);
	printf("10, J, Q, K: 10���� ���ֵ˴ϴ�. ");
	gotoxy(20, 22);
	printf("A (���̽�): 1�� ���ֵ˴ϴ�.");

	gotoxy(20, 24);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}

void Rule_Print3()
{
	gotoxy(20, 6);
	SetColor(9);
	printf("���� ���");
	SetColor(15);
	gotoxy(20, 18);
	printf("�� ī���� ������ �ջ��� ��, 10�� �ڸ��� ������ ���� �ڸ��� ������ ����մϴ�.");
	gotoxy(20, 20);
	printf("��: ī�� 7�� 8�� �հ�� 15, ������ 5�Դϴ�.");

	gotoxy(20, 24);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}

void Rule_Print4()
{
	gotoxy(20, 6);
	SetColor(9);
	printf("���� ����");
	SetColor(15);
	gotoxy(20, 10);
	printf("1. ����: �÷��̾�� '�÷��̾�', '��Ŀ', �Ǵ� 'Ÿ��(���º�)' �� �ϳ��� �����մϴ�.");
	gotoxy(20, 12);
	printf("2. ī�� �й�: �÷��̾�� ��Ŀ���� ���� �� ���� ī�尡 �й�˴ϴ�.");
	gotoxy(20, 14);
	printf("3. �÷��̾��� �߰� ī�� ��Ģ: �÷��̾��� �� ���� ī�� ������ 0~5�� ���, �߰� ī�带 �޽��ϴ�.");
	gotoxy(20, 16);
	printf("3-1. 6 �Ǵ� 7�� ���, �߰� ī�带 ���� �ʽ��ϴ�.");
	gotoxy(20, 18);
	printf("4. ��Ŀ�� �߰� ī�� ��Ģ: ��Ŀ�� �߰� ī�� ��Ģ�� �÷��̾��� �߰� ī�� ��Ģ�� ���� �޶����ϴ�. ");
	gotoxy(20, 20);
	printf("4-1. Ư�� ���ǿ� ���� �߰� ī�带 ���� �� �ֽ��ϴ�.");


	gotoxy(20, 26);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}



void Rule_Print5()
{
	gotoxy(20, 6);
	SetColor(9);
	printf("���� ����");
	SetColor(15);
	gotoxy(20, 18);
	printf("�¸�: �÷��̾� �Ǵ� ��Ŀ �� ������ 9�� ���� ����� ���� �¸��մϴ�.");
	gotoxy(20, 20);
	printf("Ÿ��: �÷��̾�� ��Ŀ�� ������ ������ ���ºη�, Ÿ�� ������ �� ����� �¸��մϴ�.");

	gotoxy(20, 24);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}

void Rule_Print6()
{
	gotoxy(20, 6);
	SetColor(9);
	printf("����");
	SetColor(15);
	gotoxy(20, 18);
	printf("�÷��̾� ����: �¸� �� 1:1�� ����.");
	gotoxy(20, 20);
	printf("��Ŀ ����: �¸� �� 1:1�� ����, �� 5%%�� �����ᰡ �ٽ��ϴ�.");
	gotoxy(20, 22);
	printf("Ÿ�� ����: �Ϲ������� 8:1 �Ǵ� 9:1�� ����.");

	gotoxy(20, 24);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}

void Rule()   /*�޴��� ù��° �ɼ��� ������ >> RULE*/
{
	SetColor(9);
	gotoxy(40, 8);
	printf("%c%c %c%c to move , press Enter key to select", 0xa1, 0xe8, 0xa1, 0xe9);
	SetColor(15);

	int rule_option = 1;
	int rule_key;

	while (1)
	{
		gotoxy(40, 12);
		printf(rule_option == 1 ? "-> ���� ��ǥ" : "   ���� ��ǥ");
		gotoxy(40, 14);
		printf(rule_option == 2 ? "-> ī�� ��ġ" : "   ī�� ��ġ");
		gotoxy(40, 16);
		printf(rule_option == 3 ? "-> ���� ���" : "   ���� ���");
		gotoxy(40, 18);
		printf(rule_option == 4 ? "-> ���� ����" : "   ���� ����");
		gotoxy(40, 20);
		printf(rule_option == 5 ? "-> ���� ����" : "   ���� ����");
		gotoxy(40, 22);
		printf(rule_option == 6 ? "-> ����" : "   ����");

		rule_key = getch();

		if (rule_key == 224)
		{
			rule_key = getch();
			switch (rule_key)
			{
			case ARROW_UP:
				if (rule_option > 1) rule_option--;
				break;
			case ARROW_DOWN:
				if (rule_option < 6) rule_option++;
				break;
			default:
				break;
			}
		}
		else if (rule_key == ENTER)
		{
			Clear();

			if (rule_option == 1)
			{
				Rule_Print1();
				break;
			}
			else if (rule_option == 2)
			{

				Rule_Print2();
				break;
			}
			else if (rule_option == 3)
			{
				Rule_Print3();
				break;
			}
			else if (rule_option == 4)
			{
				Rule_Print4();
				break;
			}
			else if (rule_option == 5)
			{
				Rule_Print5();
				break;
			}
			else
			{
				Rule_Print6();
				break;
			}
		}
	}
}

void Exit()
{
	system("cls");
}

void Draw_Casino()
{
	for (int i = 0; i < 58; i++)                /*1/3������ ���� ���*/
	{
		gotoxy(2 + i * 2, 11);
		printf("%c%c", row, col);
	}

	for (int i = 0; i < 12; i++)
	{
		gotoxy(59, 12 + i);
		printf("%c%c", row, col);                    /*���� ���� �� y = 24���� ��� */
	}

	for (int i = 0; i < 58; i++)                /* Y = 24 ������ ���� ���*/
	{
		gotoxy(2 + i * 2, 24);
		printf("%c%c", row, col);
	}

	for (int i = 0; i < 6; i++)                        		/*ī�� Ʋ �̱� */
	{
		gotoxy(10 + 18 * i, 15);
		printf("���������������� ");                /* 8*7�� ī�� Ʋ ī��Ʋ ���� 10ĭ�� �� */
		gotoxy(10 + 18 * i, 16);
		printf("��?     �� ");
		gotoxy(10 + 18 * i, 17);
		printf("��      �� ");
		gotoxy(10 + 18 * i, 18);
		printf("��  ?   �� ");                      /*ī�尡 �������� ����� �����ϱ����� ����ǥ�� ���� ����� */
		gotoxy(10 + 18 * i, 19);
		printf("��      �� ");
		gotoxy(10 + 18 * i, 20);
		printf("��     ?�� ");
		gotoxy(10 + 18 * i, 21);
		printf("���������������� ");

	}

	SetColor(11);                        /*ī�� Ʋ �Ʒ� ī���� ������ �˷���*/
	gotoxy(10, 23);
	printf("First Card");
	gotoxy(28, 23);
	printf("Second Card");
	gotoxy(46, 23);
	printf("Third Card");

	gotoxy(64, 23);
	printf("First Card");
	gotoxy(82, 23);
	printf("Second Card");
	gotoxy(100, 23);
	printf("Third Card");

	SetColor(6);						/*�ڵ带 ������(���� = player & ���� = banker) */
	gotoxy(23, 13);
	printf("PLAYER'S HAND");
	gotoxy(83, 13);
	printf("BANKER'S HAND");
	SetColor(15);

	for (int i = 0; i < 58; i++)                /* Y = 9 ������ ������ �׸�*/
	{
		gotoxy(2 + i * 2,9);
		printf("%c%c", row, col);
	}

	SetColor(7);
	gotoxy(4, 10);
	printf("CHIP: %d ", chip);              /* ���� ������ �ִ� Ĩ�� ������ �Է���(2��° �ڽ�)*/
	SetColor(15);
}

Details Card_Detail_Function(int* row)
{
	Details result;                     /* row[0]���� �������� ī���� ��Ʈ ���� ��ȯ��*/

	switch (row[0]) {
	case 0:
		result.suit_row = spades_row;
		result.suit_col = spades_col;
		break;
	case 1:
		result.suit_row = diamonds_row;
		result.suit_col = diamonds_col;
		break;
	case 2:
		result.suit_row = hearts_row;
		result.suit_col = hearts_col;
		break;
	default:
		result.suit_row = clubs_row;
		result.suit_col = clubs_col;
		break;
	}

											// row[1]�� �������� ī���� ����� �����
	switch (row[1]) {
	case 0:
		result.value = 'A';
		break;
	case 1:
		result.value = '2';
		break;
	case 2:
		result.value = '3';
		break;
	case 3:
		result.value = '4';
		break;
	case 4:
		result.value = '5';
		break;
	case 5:
		result.value = '6';
		break;
	case 6:
		result.value = '7';
		break;
	case 7:
		result.value = '8';
		break;
	case 8:
		result.value = '9';
		break;
	case 9:
		result.value = 'T';						// 10�� T�� ǥ��
		break;
	case 10:
		result.value = 'J';
		break;
	case 11:
		result.value = 'Q';
		break;
	default:
		result.value = 'K';
		break;
	}

	return result;
}

void Draw_Congratulation() /*����ڰ� 10�� �̻��� Ĩ�� ȹ���ϸ� ��µǴ� �ƽ�Ű��Ʈ*/
{
	SetColor(13);
	gotoxy(14, 4);
	printf(" ##    ##   #  #   ##   ###    ##   ###   #  #  #      ##   ###   ###    ##   #  #    #     #");
	gotoxy(14, 5);
	printf("#  #  #  #  ## #  #  #  #  #  #  #   #    #  #  #     #  #   #     #    #  #  ## #    #     #");
	gotoxy(14, 6);
	printf("#     #  #  ## #  #     #  #  #  #   #    #  #  #     #  #   #     #    #  #  ## #    #     #");
	gotoxy(14, 7);
	printf("#     #  #  # ##  # ##  ###   ####   #    #  #  #     ####   #     #    #  #  # ##    #     #");
	gotoxy(14, 8);
	printf("#  #  #  #  # ##  #  #  # #   #  #   #    #  #  #     #  #   #     #    #  #  # ##");
	gotoxy(14, 9);
	printf(" ##    ##   #  #   ###  #  #  #  #   #     ##   ####  #  #   #    ###    ##   #  #    #     #");
	SetColor(15);
}

void Play()
{
	Draw_Bakara();

	int  bet;
	int banker_point = 0, player_point = 0;
	int duplicate;									 /*�ߺ� ���θ� ǥ���ϴ� �����̴�*/

	int* card_num = malloc(sizeof(int) * 6);
	int* player_hand_ptr[3];						/*������ �迭���� ������ ��*/
	int* banker_hand_ptr[3];

	int** card_info_13;								 /*���� �������� ����>>> ������ �迭�� malloc��  */

	int betting_option = 1;
	int play_key;

	gotoxy(40, 13);
	SetColor(9);
	printf("%c%c %c%c to move , press Enter key to select", 0xa1, 0xe8, 0xa1, 0xe9);   /*cp949�� Ȱ���� Ư������ ���*/
	SetColor(15);

	gotoxy(40, 17);
	printf("���� �ɼ��� �����Ͻÿ�.");

	while (1)
	{
		gotoxy(40, 19);
		printf(betting_option == 1 ? "-> bet on PLAYER WIN" : "   bet on PLAYER WIN");
		gotoxy(40, 21);
		printf(betting_option == 2 ? "-> bet on BANKER WIN" : "   bet on BANKER WIN");
		gotoxy(40, 23);
		printf(betting_option == 3 ? "-> bet on TIED" : "   bet on TIED");

		play_key = getch();

		if (play_key == 224)
		{
			play_key = getch();
			switch (play_key)
			{
			case ARROW_UP:
				if (betting_option > 1)
				{
					betting_option--;
					break;
				}
			case ARROW_DOWN:
				if (betting_option < 3)
				{
					betting_option++;
					break;
				}
			default:
				break;
			}
		}
		else if (play_key == ENTER)
		{
			Clear();
			Draw_Bakara();

			gotoxy(40, 18);
			printf("���� ���� Ĩ ���� : %d", chip);
			
			gotoxy(40, 16);
			printf("������ �ݾ��� �Է��Ͻÿ�.");
			scanf("%d", &bet);

			if (bet > 0 && bet <= chip)
			{
				Clear();
				break;
			}
			else
			{
				SetColor(8);
				gotoxy(53, 18);
				printf("��Ȯ�� ���ڸ� �ٽ� �Է��Ͻÿ�");
				SetColor(15);
				gotoxy(53, 20);
				system("pause");
				Clear();
				gotoxy(40, 16);
				printf("������ �ݾ��� �Է��Ͻÿ�.");
				scanf("%d", &bet);
			}
		}

	}														 /*���� �ɼǰ� ���� �ݾ��� �޾ƿ� */

	chip -= bet;

	Draw_Bakara();
	Draw_Casino();
	
	gotoxy(15, 10);

	switch (betting_option)
	{
	case 1:
		printf("Betting option: Player   Wagered: %d", bet);
		break;
	case 2:
		printf("Betting option: Banker   Wagered: %d", bet);
		break;
	default:
		printf("Betting option: TIED   Wagered: %d", bet);
		break;
	}
	Sleep(3000);                       /*3�� ��ٸ���*/

	for (int i = 0; i < 6; i++)
	{
		do
		{
			card_num[i] = rand() % 52; // 0���� 51������ ������ ����

			duplicate = 0;
			for (int j = 0; j < i; j++)
			{
				if (card_num[i] == card_num[j])
				{
					duplicate = 1;
					break;
				}
			}
		} while (duplicate); /*ī�� �ѹ��� �ߺ��Ǹ� ���ø�����Ʈ�� 1�� �ʱ�ȭ�� >> ���ø�����Ʈ�� 1�ϋ� �ݺ����� ���� ���ο� ī�� �ѹ��� �ʱ�ȭ��*/
	}


	card_info_13 = (int**)malloc(6 * sizeof(int*));

	for (int i = 0; i < 6; i++)
	{
		card_info_13[i] = (int*)malloc(2 * sizeof(int));
	}

	/*������ �迭�� �̿��� ī�� �ѹ��� 13�����÷� ǥ���� */

	for (int i = 0; i < 6; i++)                        /* ���� �迭�� ���� �ʱ�ȭ��*/
	{
		card_info_13[i][1] = card_num[i] % 13;				/* 1>>> ������ >>> �̰� ī���� ����� ������ */
		card_info_13[i][0] = card_num[i] / 13;            /* 0>>> ���� ������ >>>�̰� ī���� ��Ʈ�� ������  */
	}

	free(card_num);       /*card_num�� �޸𸮸� �ʱ�ȭ�� 13������ ������ ���� Ȱ����*/

	player_hand_ptr[0] = card_info_13[0];
	banker_hand_ptr[0] = card_info_13[1];
	player_hand_ptr[1] = card_info_13[2];
	banker_hand_ptr[1] = card_info_13[3];  

	player_hand_ptr[2] = card_info_13[4];
	banker_hand_ptr[2] = card_info_13[5];																					/*�꿡 �´� ������ �⺻ �и� ������ ���η� ��� ī��� ����ϰ� �߰� �迭��*/

	
	/*First Split >> �и� ������  */

	for (int i = 0; i < 2; i++)           /*First split��  player hand�� ����� >> ? �Ųٱ� */
	{
		Details detail = Card_Detail_Function(player_hand_ptr[i]);
		
		gotoxy(13 + 18 * i, 18);
		printf("%c%c",detail.suit_row, detail.suit_col);       /*suit�� �����*/
		gotoxy(11 + 18 * i, 16);
		printf("%c", detail.value);         /*value�� �����1 */
		gotoxy(16 + 18 * i, 20);
		printf("%c",detail.value);           /*value�� �����2 */
		Sleep(1000);
	}


	for (int i = 0; i < 2; i++)           /*First split��  banker hand�� ����� >> ? �Ųٱ� */
	{
		Details detail = Card_Detail_Function(banker_hand_ptr[i]);
		
		gotoxy(67 + 18 * i, 18);
		printf("%c%c", detail.suit_row, detail.suit_col);       /*suit�� �����*/
		gotoxy(65 + 18 * i, 16);
		printf("%c",detail.value);         /*value�� �����1 */
		gotoxy(70 + 18 * i, 20);
		printf("%c", detail.value);           /*value�� �����2 */
		Sleep(1000);
	}


	for (int i = 0; i < 2; i++)             /*�⺻ ���� ������ ������ >>> case �з��� ��� ī�� �� ���θ� Ȯ���ϴ� ���� */
	{
		if (player_hand_ptr[i][1] < 9)
		{
			player_point += player_hand_ptr[i][1];
			player_point += 1;
		}
		
		if (banker_hand_ptr[i][1] < 9)
		{
			banker_point += banker_hand_ptr[i][1];
			banker_point += 1;
		}					/*�÷��̾� ����Ʈ�� ��Ŀ ����Ʈ�� ���� �ڸ��� ���� ���·� �ٽ� �ʱ�ȭ�� */
	}	

	player_point = player_point % 10;
	banker_point = banker_point % 10;

	gotoxy(54, 25);
	SetColor(4);
	printf("FIRST SPLIT");             /*ī���� ��Ʈ�� ��ũ�� �����ִ� �ڵ尡 �ʿ��� */
	SetColor(15);
	gotoxy(3, 26);
	printf("player point :%d", player_point);
	gotoxy(20, 26);
	printf("banker point: %d", banker_point);
	gotoxy(37, 26);

	Sleep(3000);

	if (player_point >= 8 || banker_point >= 8)  /*������ ��� */
	{
		SetColor(6);
		printf("  NATURAL!!");
		printf("  result :");

		if (player_point == banker_point)    /*��� ����� tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);            
				SetColor(15);

			}
		}
		else if (player_point > banker_point )      /*��� ����� Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet *2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}

		else  /*��� ����� banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}

	}
	else if (player_point >= 6 && banker_point == 7)     /*�Ѵ� ���ĵ忩�� ��� ī�带 ���� �ʿ䰡 ���� ��Ȳ*/
	{
		SetColor(6);
		printf("  Both stand!!");
		printf("  result :");

		if (player_point == banker_point)    /*��� ����� tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*��� ����� Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}

		else  /*��� ����� banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}
	}
	else if (player_point <= 5 && banker_point == 7)                                                        /*��� ī�� ���� ��Ȳ1 -player hit & banker stand-*/
	{
		SetColor(6);
		printf("	result: Player hit Third card & Banker Stand");

		Sleep(2000);

		Details detail_3rd;
		detail_3rd = Card_Detail_Function(player_hand_ptr[2]);
		SetColor(15);

		gotoxy(13 + 18 * 2, 18);
		printf("%c%c", detail_3rd.suit_row, detail_3rd.suit_col);       /*suit�� �����*/
		gotoxy(11 + 18 * 2, 16);
		printf("%c", detail_3rd.value);         /*value�� �����1 */
		gotoxy(16 + 18 * 2, 20);
		printf("%c", detail_3rd.value);           /*value�� �����2 */
		
		if (player_hand_ptr[2][1] < 9)
		{
			player_point = player_point+player_hand_ptr[2][1] + 1;
			player_point = player_point % 10;
		}

		gotoxy(54, 27);
		SetColor(4);
		printf("SECOND SPLIT");             /*ī���� ��Ʈ�� ��ũ�� �����ִ� �ڵ尡 �ʿ��� */
		SetColor(15);
		gotoxy(3, 28);
		printf("player point :%d", player_point);
		gotoxy(20, 28);
		printf("banker point: %d", banker_point);

		if (player_point == banker_point)    /*��� ����� tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);

				
				printf("  YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*��� ����� Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				
				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}

		else  /*��� ����� banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				
				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);
			}
		}
	}
	else if (player_point >= 6 && banker_point <= 6 )               /*player stand & banker hit*/
	{
		SetColor(6);
		printf("	result: Player Stand & Banker hit Third card");

		Sleep(2000);

		Details detail_3rd;
		detail_3rd = Card_Detail_Function(banker_hand_ptr[2]);

		gotoxy(13 + 18 * 5, 18);
		printf("%c%c", detail_3rd.suit_row, detail_3rd.suit_col);       /*suit�� �����*/
		gotoxy(11 + 18 * 5, 16);
		printf("%c", detail_3rd.value);         /*value�� �����1 */
		gotoxy(16 + 18 * 5, 20);
		printf("%c", detail_3rd.value);           /*value�� �����2 */

		if (banker_hand_ptr[2][1] < 9)
		{
			banker_point = banker_point + banker_hand_ptr[2][1] + 1;
			banker_point = banker_point % 10;
		}

		gotoxy(54, 27);
		SetColor(4);
		printf("SECOND SPLIT");             /*ī���� ��Ʈ�� ��ũ�� �����ִ� �ڵ尡 �ʿ��� */
		SetColor(15);
		gotoxy(3, 28);
		printf("player point :%d", player_point);
		gotoxy(20, 28);
		printf("banker point: %d", banker_point);

		if (player_point == banker_point)    /*��� ����� tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);


				printf("  YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*��� ����� Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}

		else  /*��� ����� banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);
			}
		}
	}
	
	else																			/*�÷��̾� ��Ŀ ��� �� */                                                   
	{ 
		SetColor(6);
		printf("	result: Player & Banker hit Third card ");

		Sleep(2000);
		SetColor(15);

		Details player_detail_3rd;
		player_detail_3rd = Card_Detail_Function(player_hand_ptr[2]);


		gotoxy(13 + 18 * 2, 18);
		printf("%c%c", player_detail_3rd.suit_row, player_detail_3rd.suit_col);       /*suit�� �����*/
		gotoxy(11 + 18 * 2, 16);
		printf("%c", player_detail_3rd.value);         /*value�� �����1 */
		gotoxy(16 + 18 * 2, 20);
		printf("%c", player_detail_3rd.value);           /*value�� �����2 */
		Sleep(1000);

		if (player_hand_ptr[2][1] < 9)
		{
			player_point = player_point + player_hand_ptr[2][1] + 1;
			player_point = player_point % 10;
		}

		gotoxy(54, 27);
		SetColor(4);
		printf("SECOND SPLIT");             /*ī���� ��Ʈ�� ��ũ�� �����ִ� �ڵ尡 �ʿ��� */
		SetColor(15);
		gotoxy(3, 28);
		printf("player point :%d", player_point);

		if (banker_point < 3 || (player_point != 8 && banker_point == 3) || ((player_point == '2' || player_point == 7) && banker_point == 4) || ((player_point == '4' || player_point == 7) && banker_point == 3) || ((player_point == '6' || player_point == 7) && banker_point == 3))  /*Ư�� ���� ������ �ڵ�*/
		{
			Details banker_detail_3rd;
			banker_detail_3rd = Card_Detail_Function(banker_hand_ptr[2]);

			gotoxy(13 + 18 * 5, 18);
			printf("%c%c", banker_detail_3rd.suit_row, banker_detail_3rd.suit_col);       /*suit�� �����*/
			gotoxy(11 + 18 * 5, 16);
			printf("%c", banker_detail_3rd.value);         /*value�� �����1 */
			gotoxy(16 + 18 * 5, 20);
			printf("%c", banker_detail_3rd.value);           /*value�� �����2 */

			if (banker_hand_ptr[2][1] < 9)
			{
				banker_point = banker_point+banker_hand_ptr[2][1] + 1;
				banker_point = banker_point % 10;
			}

			gotoxy(20, 28);
			printf("banker point: %d", banker_point);

		}
		else                                      /*���η� ���� */
		{
			gotoxy(20, 28);
			printf("banker point: %d", banker_point);
		}
		if (player_point == banker_point)    /*��� ����� tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);


				printf("  YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*��� ����� Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);

			}
		}

		else  /*��� ����� banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   ���� Ĩ���� : %d", chip);              /*������ ������ �ľ��ϰ� ������ �����ִ� �ڵ�*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				printf("YOU LOSE!!   ���� Ĩ���� : %d", chip);
				SetColor(15);
			}
		}
	}

	free(card_info_13); /*���� �Ҵ��� Ǯ���� >> ���� ������ �غ��� or���α׷��� ����*/

	Sleep(10000);
	Clear();

	if (chip == 0) /*��� Ĩ�� ���� >> ���α׷��� ������ */
	{
		system("cls");
		gotoxy(0, 0);
		printf("�Ļ� �߽��ϴ� !!\n");
		system("pause");
	}
	else if (chip >= 100000) /*��ǥġ ���� ū Ĩ�� ȹ���� >> ���α׷��� ������ */
	{
		Draw_Congratulation();

		gotoxy(40, 20);
		printf("�� %d���� Ĩ�� ������ϴ�!!",chip);
		gotoxy(45, 25);
		system("pause");
		system("cls");

	}
	else  /*��ī�� �����ϰ� �޴��� ���ư�  */
	{
		Draw_Bakara();
		Menu();
	}
}
