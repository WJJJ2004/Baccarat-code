#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996 )
#include <stdio.h>
#include <windows.h>            // gotoxy, system, sleep 활용
#include <time.h>               // srand 활용
#include <conio.h>				 // getch() 활용

#define ARROW_UP    72
#define ARROW_DOWN  80     /*방향 키의 ASCHII 반복문 내부에서 두번째 getch를 활용해 옆에 있는 값을 받을 수 있습니다. */
#define ENTER       13

int chip = 10000;

// CP949 인코딩의 특수문자를 포인터로 선언 _row의 이름으로 선언된 변수는 cp949표의 행이고 _col은 열을 의미함 , 두 변수를 %c%c로 출력하면 원하는 특수문자를 출력할 수 있습니다.
int spades_row = 0xa2;   // Spades (♠)
int spades_col = 0xbc;

int hearts_row = 0xa2;  // Hearts (♥)
int hearts_col = 0xbe;

int diamonds_row = 0xa1; // Diamonds 
int diamonds_col = 0xdf;  

int clubs_row = 0xa2;   // Clubs (♣)
int clubs_col = 0xc0;    

typedef struct _return_of_Card_Detail_function    /*Card_Detail_function의 반환값을 저장하는 구조체 >> 슈트는 cp949를 고려하여 두개의 행으로 받음*/
{
	int suit_row;

	int suit_col;

	char value;
}Details;


int row = 0xa2;       /*CP949를 활용해 특수 문자를 출력하기 위한 코드입니다. 16진수를 저장하고 hv를 printf하면 2*1의 박스를 출력할 수 있습니다.*/
int col = 0xcc;

void gotoxy(int x, int y);  // GUI 구성을 위한 함수 1
void SetColor(int color);

void Draw_Edge();    // GUI 구성을 위한 함수 2
void Draw_Bakara(); //제목 출력
void Clear(); // 콘솔화면의 테두리 (엣지)내부 공간을 스페이스바로 밀어냄 >> 해당공간을 gotoxy로 활용가능함 
void Draw();
void Draw_Casino(); // play함수에서 활용됨 
void Draw_Congratulation(); // 목표 달성시 출력되는 코드임

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


void Draw_Bakara()      /*아스키 아트*/
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


	for (int j = 1; j <= 28; j++) /*27회*/
	{
		gotoxy(2, j);
		for (int i = 2; i <= 116; i++)      /*115회*/
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
	printf("보유 칩 개수 : %d", chip);
	
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

		// 화살표 키 처리
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
			// 엔터 키를 누르면 선택된 옵션을 실행
			Clear();
			if (option == 1)
			{
				Rule(); /*RULE을 선택했을떄*/
				break;
			}
			else if (option == 2)
			{
				Play(); /*PLAY 를 선택했을떄*/
				break;
			}
			else
			{
				Exit();/*EXIT을 선택했을때*/
				break;
			}
		}
	}
}

void Rule_Print1()        /*세부룰을 확인 할 수 있는 코드*/
{
	gotoxy(20, 6);
	SetColor(9);
	printf("게임 목표");
	SetColor(15);
	gotoxy(20, 18);
	printf("플레이어와 뱅커 중 어느 쪽이 9에 가까운 점수를 얻는지를 예측하여 베팅합니다. ");
	gotoxy(20, 20);
	printf("유저는 플레이어 승, 뱅커 승, 동률으로 3가지 선택지 중 하나에 베팅할 수 있습니다. ");
	gotoxy(20, 22);
	printf("유저는 베팅한 선택지에 따라 차등한 배당금을 가져갈 수 있습니다. ");

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
	printf("카드 가치");
	SetColor(15);
	gotoxy(20, 18);
	printf("숫자 카드 (2-9): 카드에 적힌 숫자 값이 점수입니다.");
	gotoxy(20, 20);
	printf("10, J, Q, K: 10으로 간주됩니다. ");
	gotoxy(20, 22);
	printf("A (에이스): 1로 간주됩니다.");

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
	printf("점수 계산");
	SetColor(15);
	gotoxy(20, 18);
	printf("각 카드의 점수를 합산한 후, 10의 자리는 버리고 일의 자리만 점수로 사용합니다.");
	gotoxy(20, 20);
	printf("예: 카드 7과 8의 합계는 15, 점수는 5입니다.");

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
	printf("게임 진행");
	SetColor(15);
	gotoxy(20, 10);
	printf("1. 베팅: 플레이어는 '플레이어', '뱅커', 또는 '타이(무승부)' 중 하나에 베팅합니다.");
	gotoxy(20, 12);
	printf("2. 카드 분배: 플레이어와 뱅커에게 각각 두 장의 카드가 분배됩니다.");
	gotoxy(20, 14);
	printf("3. 플레이어의 추가 카드 규칙: 플레이어의 두 장의 카드 점수가 0~5일 경우, 추가 카드를 받습니다.");
	gotoxy(20, 16);
	printf("3-1. 6 또는 7일 경우, 추가 카드를 받지 않습니다.");
	gotoxy(20, 18);
	printf("4. 뱅커의 추가 카드 규칙: 뱅커의 추가 카드 규칙은 플레이어의 추가 카드 규칙에 따라 달라집니다. ");
	gotoxy(20, 20);
	printf("4-1. 특정 조건에 따라 추가 카드를 받을 수 있습니다.");


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
	printf("승패 결정");
	SetColor(15);
	gotoxy(20, 18);
	printf("승리: 플레이어 또는 뱅커 중 점수가 9에 가장 가까운 쪽이 승리합니다.");
	gotoxy(20, 20);
	printf("타이: 플레이어와 뱅커의 점수가 같으면 무승부로, 타이 베팅을 한 사람이 승리합니다.");

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
	printf("배당금");
	SetColor(15);
	gotoxy(20, 18);
	printf("플레이어 베팅: 승리 시 1:1의 배당금.");
	gotoxy(20, 20);
	printf("뱅커 베팅: 승리 시 1:1의 배당금, 단 5%%의 수수료가 붙습니다.");
	gotoxy(20, 22);
	printf("타이 베팅: 일반적으로 8:1 또는 9:1의 배당금.");

	gotoxy(20, 24);
	printf("Press any key to return to the menu...");
	getch();
	Clear();
	Menu();
	Draw_Bakara();
}

void Rule()   /*메뉴의 첫번째 옵션을 실행함 >> RULE*/
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
		printf(rule_option == 1 ? "-> 게임 목표" : "   게임 목표");
		gotoxy(40, 14);
		printf(rule_option == 2 ? "-> 카드 가치" : "   카드 가치");
		gotoxy(40, 16);
		printf(rule_option == 3 ? "-> 점수 계산" : "   점수 계산");
		gotoxy(40, 18);
		printf(rule_option == 4 ? "-> 게임 진행" : "   게임 진행");
		gotoxy(40, 20);
		printf(rule_option == 5 ? "-> 승패 결정" : "   승패 결정");
		gotoxy(40, 22);
		printf(rule_option == 6 ? "-> 배당금" : "   배당금");

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
	for (int i = 0; i < 58; i++)                /*1/3지점에 수평선 출력*/
	{
		gotoxy(2 + i * 2, 11);
		printf("%c%c", row, col);
	}

	for (int i = 0; i < 12; i++)
	{
		gotoxy(59, 12 + i);
		printf("%c%c", row, col);                    /*수직 분할 선 y = 24까지 출력 */
	}

	for (int i = 0; i < 58; i++)                /* Y = 24 지점에 수평선 출력*/
	{
		gotoxy(2 + i * 2, 24);
		printf("%c%c", row, col);
	}

	for (int i = 0; i < 6; i++)                        		/*카드 틀 뽑기 */
	{
		gotoxy(10 + 18 * i, 15);
		printf("┏━━━━━━┓ ");                /* 8*7의 카드 틀 카드틀 마다 10칸씩 띔 */
		gotoxy(10 + 18 * i, 16);
		printf("┃?     ┃ ");
		gotoxy(10 + 18 * i, 17);
		printf("┃      ┃ ");
		gotoxy(10 + 18 * i, 18);
		printf("┃  ?   ┃ ");                      /*카드가 뒤집히는 모션을 구현하기위해 물음표를 먼저 출력함 */
		gotoxy(10 + 18 * i, 19);
		printf("┃      ┃ ");
		gotoxy(10 + 18 * i, 20);
		printf("┃     ?┃ ");
		gotoxy(10 + 18 * i, 21);
		printf("┗━━━━━━┛ ");

	}

	SetColor(11);                        /*카드 틀 아래 카드의 순서를 알려줌*/
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

	SetColor(6);						/*핸드를 구분함(좌측 = player & 우측 = banker) */
	gotoxy(23, 13);
	printf("PLAYER'S HAND");
	gotoxy(83, 13);
	printf("BANKER'S HAND");
	SetColor(15);

	for (int i = 0; i < 58; i++)                /* Y = 9 지점에 수평선을 그림*/
	{
		gotoxy(2 + i * 2,9);
		printf("%c%c", row, col);
	}

	SetColor(7);
	gotoxy(4, 10);
	printf("CHIP: %d ", chip);              /* 현재 가지고 있는 칩의 개수를 입력함(2번째 박스)*/
	SetColor(15);
}

Details Card_Detail_Function(int* row)
{
	Details result;                     /* row[0]값을 바탕으로 카드의 슈트 값을 반환함*/

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

											// row[1]을 바탕으로 카드의 밸류를 배당함
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
		result.value = 'T';						// 10은 T로 표시
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

void Draw_Congratulation() /*사용자가 10배 이상의 칩을 획득하면 출력되는 아스키아트*/
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
	int duplicate;									 /*중복 여부를 표현하는 변수이다*/

	int* card_num = malloc(sizeof(int) * 6);
	int* player_hand_ptr[3];						/*포인터 배열임을 유의할 것*/
	int* banker_hand_ptr[3];

	int** card_info_13;								 /*이중 포인터의 도입>>> 이차원 배열을 malloc함  */

	int betting_option = 1;
	int play_key;

	gotoxy(40, 13);
	SetColor(9);
	printf("%c%c %c%c to move , press Enter key to select", 0xa1, 0xe8, 0xa1, 0xe9);   /*cp949를 활용한 특수문자 출력*/
	SetColor(15);

	gotoxy(40, 17);
	printf("베팅 옵션을 선택하시오.");

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
			printf("현재 보유 칩 개수 : %d", chip);
			
			gotoxy(40, 16);
			printf("배팅할 금액을 입력하시오.");
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
				printf("정확한 숫자를 다시 입력하시오");
				SetColor(15);
				gotoxy(53, 20);
				system("pause");
				Clear();
				gotoxy(40, 16);
				printf("배팅할 금액을 입력하시오.");
				scanf("%d", &bet);
			}
		}

	}														 /*베팅 옵션과 베팅 금액을 받아옴 */

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
	Sleep(3000);                       /*3초 기다리기*/

	for (int i = 0; i < 6; i++)
	{
		do
		{
			card_num[i] = rand() % 52; // 0부터 51까지의 무작위 숫자

			duplicate = 0;
			for (int j = 0; j < i; j++)
			{
				if (card_num[i] == card_num[j])
				{
					duplicate = 1;
					break;
				}
			}
		} while (duplicate); /*카드 넘버가 중복되면 듀플리케이트를 1로 초기화함 >> 듀플리케이트가 1일떄 반복문을 통해 새로운 카드 넘버로 초기화함*/
	}


	card_info_13 = (int**)malloc(6 * sizeof(int*));

	for (int i = 0; i < 6; i++)
	{
		card_info_13[i] = (int*)malloc(2 * sizeof(int));
	}

	/*이차원 배열을 이용해 카드 넘버를 13진수꼴로 표현함 */

	for (int i = 0; i < 6; i++)                        /* 이중 배열을 전부 초기화함*/
	{
		card_info_13[i][1] = card_num[i] % 13;				/* 1>>> 나머지 >>> 이게 카드의 밸류를 저장함 */
		card_info_13[i][0] = card_num[i] / 13;            /* 0>>> 정수 나누기 >>>이게 카드의 슈트를 저장함  */
	}

	free(card_num);       /*card_num의 메모리를 초기화함 13진수로 설정된 값을 활용함*/

	player_hand_ptr[0] = card_info_13[0];
	banker_hand_ptr[0] = card_info_13[1];
	player_hand_ptr[1] = card_info_13[2];
	banker_hand_ptr[1] = card_info_13[3];  

	player_hand_ptr[2] = card_info_13[4];
	banker_hand_ptr[2] = card_info_13[5];																					/*룰에 맞는 순서로 기본 패를 나눠줌 세부룰 써드 카드는 배당하고 추가 배열함*/

	
	/*First Split >> 패를 보여줌  */

	for (int i = 0; i < 2; i++)           /*First split의  player hand를 출력함 >> ? 매꾸기 */
	{
		Details detail = Card_Detail_Function(player_hand_ptr[i]);
		
		gotoxy(13 + 18 * i, 18);
		printf("%c%c",detail.suit_row, detail.suit_col);       /*suit를 출력함*/
		gotoxy(11 + 18 * i, 16);
		printf("%c", detail.value);         /*value를 출력함1 */
		gotoxy(16 + 18 * i, 20);
		printf("%c",detail.value);           /*value를 출력함2 */
		Sleep(1000);
	}


	for (int i = 0; i < 2; i++)           /*First split의  banker hand를 출력함 >> ? 매꾸기 */
	{
		Details detail = Card_Detail_Function(banker_hand_ptr[i]);
		
		gotoxy(67 + 18 * i, 18);
		printf("%c%c", detail.suit_row, detail.suit_col);       /*suit를 출력함*/
		gotoxy(65 + 18 * i, 16);
		printf("%c",detail.value);         /*value를 출력함1 */
		gotoxy(70 + 18 * i, 20);
		printf("%c", detail.value);           /*value를 출력함2 */
		Sleep(1000);
	}


	for (int i = 0; i < 2; i++)             /*기본 패의 점수를 측정함 >>> case 분류로 써드 카드 딜 여부를 확인하는 과정 */
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
		}					/*플레이어 포인트와 뱅커 포인트의 십의 자리를 버린 상태로 다시 초기화함 */
	}	

	player_point = player_point % 10;
	banker_point = banker_point % 10;

	gotoxy(54, 25);
	SetColor(4);
	printf("FIRST SPLIT");             /*카드의 슈트와 랭크를 보여주는 코드가 필요함 */
	SetColor(15);
	gotoxy(3, 26);
	printf("player point :%d", player_point);
	gotoxy(20, 26);
	printf("banker point: %d", banker_point);
	gotoxy(37, 26);

	Sleep(3000);

	if (player_point >= 8 || banker_point >= 8)  /*내츄럴일 경우 */
	{
		SetColor(6);
		printf("  NATURAL!!");
		printf("  result :");

		if (player_point == banker_point)    /*경기 결과가 tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);            
				SetColor(15);

			}
		}
		else if (player_point > banker_point )      /*경기 결과가 Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet *2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}

		else  /*경기 결과가 banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}

	}
	else if (player_point >= 6 && banker_point == 7)     /*둘다 스탠드여서 써드 카드를 받을 필요가 없는 상황*/
	{
		SetColor(6);
		printf("  Both stand!!");
		printf("  result :");

		if (player_point == banker_point)    /*경기 결과가 tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*경기 결과가 Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}

		else  /*경기 결과가 banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				gotoxy(3, 27);
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}
	}
	else if (player_point <= 5 && banker_point == 7)                                                        /*써드 카드 등장 상황1 -player hit & banker stand-*/
	{
		SetColor(6);
		printf("	result: Player hit Third card & Banker Stand");

		Sleep(2000);

		Details detail_3rd;
		detail_3rd = Card_Detail_Function(player_hand_ptr[2]);
		SetColor(15);

		gotoxy(13 + 18 * 2, 18);
		printf("%c%c", detail_3rd.suit_row, detail_3rd.suit_col);       /*suit를 출력함*/
		gotoxy(11 + 18 * 2, 16);
		printf("%c", detail_3rd.value);         /*value를 출력함1 */
		gotoxy(16 + 18 * 2, 20);
		printf("%c", detail_3rd.value);           /*value를 출력함2 */
		
		if (player_hand_ptr[2][1] < 9)
		{
			player_point = player_point+player_hand_ptr[2][1] + 1;
			player_point = player_point % 10;
		}

		gotoxy(54, 27);
		SetColor(4);
		printf("SECOND SPLIT");             /*카드의 슈트와 랭크를 보여주는 코드가 필요함 */
		SetColor(15);
		gotoxy(3, 28);
		printf("player point :%d", player_point);
		gotoxy(20, 28);
		printf("banker point: %d", banker_point);

		if (player_point == banker_point)    /*경기 결과가 tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);

				
				printf("  YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*경기 결과가 Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				
				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}

		else  /*경기 결과가 banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);

				
				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
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
		printf("%c%c", detail_3rd.suit_row, detail_3rd.suit_col);       /*suit를 출력함*/
		gotoxy(11 + 18 * 5, 16);
		printf("%c", detail_3rd.value);         /*value를 출력함1 */
		gotoxy(16 + 18 * 5, 20);
		printf("%c", detail_3rd.value);           /*value를 출력함2 */

		if (banker_hand_ptr[2][1] < 9)
		{
			banker_point = banker_point + banker_hand_ptr[2][1] + 1;
			banker_point = banker_point % 10;
		}

		gotoxy(54, 27);
		SetColor(4);
		printf("SECOND SPLIT");             /*카드의 슈트와 랭크를 보여주는 코드가 필요함 */
		SetColor(15);
		gotoxy(3, 28);
		printf("player point :%d", player_point);
		gotoxy(20, 28);
		printf("banker point: %d", banker_point);

		if (player_point == banker_point)    /*경기 결과가 tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);


				printf("  YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*경기 결과가 Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}

		else  /*경기 결과가 banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);
			}
		}
	}
	
	else																			/*플레이어 뱅커 모두 힛 */                                                   
	{ 
		SetColor(6);
		printf("	result: Player & Banker hit Third card ");

		Sleep(2000);
		SetColor(15);

		Details player_detail_3rd;
		player_detail_3rd = Card_Detail_Function(player_hand_ptr[2]);


		gotoxy(13 + 18 * 2, 18);
		printf("%c%c", player_detail_3rd.suit_row, player_detail_3rd.suit_col);       /*suit를 출력함*/
		gotoxy(11 + 18 * 2, 16);
		printf("%c", player_detail_3rd.value);         /*value를 출력함1 */
		gotoxy(16 + 18 * 2, 20);
		printf("%c", player_detail_3rd.value);           /*value를 출력함2 */
		Sleep(1000);

		if (player_hand_ptr[2][1] < 9)
		{
			player_point = player_point + player_hand_ptr[2][1] + 1;
			player_point = player_point % 10;
		}

		gotoxy(54, 27);
		SetColor(4);
		printf("SECOND SPLIT");             /*카드의 슈트와 랭크를 보여주는 코드가 필요함 */
		SetColor(15);
		gotoxy(3, 28);
		printf("player point :%d", player_point);

		if (banker_point < 3 || (player_point != 8 && banker_point == 3) || ((player_point == '2' || player_point == 7) && banker_point == 4) || ((player_point == '4' || player_point == 7) && banker_point == 3) || ((player_point == '6' || player_point == 7) && banker_point == 3))  /*특수 룰을 적용한 코드*/
		{
			Details banker_detail_3rd;
			banker_detail_3rd = Card_Detail_Function(banker_hand_ptr[2]);

			gotoxy(13 + 18 * 5, 18);
			printf("%c%c", banker_detail_3rd.suit_row, banker_detail_3rd.suit_col);       /*suit를 출력함*/
			gotoxy(11 + 18 * 5, 16);
			printf("%c", banker_detail_3rd.value);         /*value를 출력함1 */
			gotoxy(16 + 18 * 5, 20);
			printf("%c", banker_detail_3rd.value);           /*value를 출력함2 */

			if (banker_hand_ptr[2][1] < 9)
			{
				banker_point = banker_point+banker_hand_ptr[2][1] + 1;
				banker_point = banker_point % 10;
			}

			gotoxy(20, 28);
			printf("banker point: %d", banker_point);

		}
		else                                      /*세부룰 예외 */
		{
			gotoxy(20, 28);
			printf("banker point: %d", banker_point);
		}
		if (player_point == banker_point)    /*경기 결과가 tied */
		{
			printf("  tied!!");

			if (betting_option == 3)
			{
				bet = bet * 8;
				chip = chip + bet;

				SetColor(3);


				printf("  YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}
		else if (player_point > banker_point)      /*경기 결과가 Player Win*/
		{
			printf("  Player Win!!");

			if (betting_option == 1)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);


				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);

			}
		}

		else  /*경기 결과가 banker win*/
		{
			printf("  Banker Win!!");

			if (betting_option == 2)
			{
				bet = bet * 2;
				chip = chip + bet;

				SetColor(3);


				printf("YOU WIN!!   현재 칩개수 : %d", chip);              /*유저의 배팅을 파악하고 배당금을 돌려주는 코드*/
				SetColor(15);

			}
			else
			{
				bet = 0;

				SetColor(3);

				printf("YOU LOSE!!   현재 칩개수 : %d", chip);
				SetColor(15);
			}
		}
	}

	free(card_info_13); /*동적 할당을 풀어줌 >> 다음 게임을 준비함 or프로그램을 종료*/

	Sleep(10000);
	Clear();

	if (chip == 0) /*모든 칩을 잃음 >> 프로그램을 종료함 */
	{
		system("cls");
		gotoxy(0, 0);
		printf("파산 했습니다 !!\n");
		system("pause");
	}
	else if (chip >= 100000) /*목표치 보다 큰 칩을 획득함 >> 프로그램을 종료함 */
	{
		Draw_Congratulation();

		gotoxy(40, 20);
		printf("총 %d개의 칩을 얻었습니다!!",chip);
		gotoxy(45, 25);
		system("pause");
		system("cls");

	}
	else  /*바카라를 종료하고 메뉴로 돌아감  */
	{
		Draw_Bakara();
		Menu();
	}
}
