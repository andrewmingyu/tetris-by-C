#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32
#define MOVE 224
#define Block_Kinds 7
#define Block_SIZE 4

int x = 30;
int y = 20;
int change = 0; //블록 방향

void gotoxy(int x, int y) { //x, y로 커서 이동 <- x, y에 좌표 입력
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show; //커서를 보이게 할지
	ConsoleCursor.dwSize = 1; //커서 사이즈
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void creatBlock(int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE]) {
	for (int col = 0; col < 4; col++) // 블럭 출력 반복문
	{
		for (int row = 0; row < 4; row++)
		{
			if (blocks[4][change][col][row] == 1)
			{
				gotoxy(x + row*2, y + col);
				printf("□");
			}
		}
	}
}

int main() {
	int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE] = {
	0,0,0,0 //ㅁ
	,0,1,1,0
	,0,1,1,0
	,0,0,0,0
	,0,0,0,0
	,0,1,1,0
	,0,1,1,0
	,0,0,0,0
	,0,0,0,0
	,0,1,1,0
	,0,1,1,0
	,0,0,0,0
	,0,0,0,0
	,0,1,1,0
	,0,1,1,0
	,0,0,0,0
	,
	0,0,0,0
	,1,1,1,1 // ㅡ
	,0,0,0,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,0,0
	,1,1,1,1
	,0,0,0,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,
	0,0,0,0	//ㄹ 꺼꾸로
	,0,0,1,1
	,0,1,1,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,1
	,0,0,0,1
	,0,0,0,0
	,0,0,0,0
	,0,0,1,1
	,0,1,1,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,1
	,0,0,0,1
	,0,0,0,0
	,
	0,0,0,0
	,0,1,1,0	//ㄹ
	,0,0,1,1
	,0,0,0,0
	,0,0,0,1
	,0,0,1,1
	,0,0,1,0
	,0,0,0,0
	,0,0,0,0
	,0,1,1,0
	,0,0,1,1
	,0,0,0,0
	,0,0,0,1
	,0,0,1,1
	,0,0,1,0
	,0,0,0,0
	,
	0,0,0,0
	,0,1,1,1		//ㄱ 꺼꾸로
	,0,1,0,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,1
	,0,0,0,0
	,0,0,0,1
	,0,1,1,1
	,0,0,0,0
	,0,0,0,0
	,0,1,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,0,0
	,
	0,0,0,0
	,1,1,1,0	//ㄱ
	,0,0,1,0
	,0,0,0,0
	,0,0,1,1
	,0,0,1,0
	,0,0,1,0
	,0,0,0,0
	,0,1,0,0
	,0,1,1,1
	,0,0,0,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,0
	,0,1,1,0
	,0,0,0,0
,
	0,0,0,0
	,0,1,1,1
	,0,0,1,0// ㅗ
	,0,0,0,0
	,0,0,1,0
	,0,0,1,1
	,0,0,1,0
	,0,0,0,0
	,0,0,1,0
	,0,1,1,1
	,0,0,0,0
	,0,0,0,0
	,0,0,1,0
	,0,1,1,0
	,0,0,1,0
	,0,0,0,0
	};

	CursorView(0);
	gotoxy(x, y);
	creatBlock(blocks);

	while (1)
	{
		if (_kbhit()) { //kbhit 함수는 키보드 입력 안하면 0 리턴
			int nkey = _getch(); //방향키 입력시 224 받음
			if ((char)nkey == 'c') { //방향 바꾸기
				change = (change + 1) % 4;
				system("cls");
				gotoxy(x, y);
				creatBlock(blocks);
			}
			if (nkey == MOVE)
			{
				nkey = _getch(); //방향키에 맞는 코드값 받음
			}
			switch (nkey)
			{
			case LEFT:
				system("cls"); //콘솔창 출력된 모든 내용을 지움
				gotoxy(x = x - 2, y);// 왼쪽 이동 반영
				creatBlock(blocks);
				break;
			case RIGHT:
				system("cls");
				gotoxy(x = x + 2, y);
				creatBlock(blocks);
				break;
			case UP:
				system("cls");
				gotoxy(x, --y);
				creatBlock(blocks);
				break;
			case DOWN:
				system("cls");
				gotoxy(x, ++y);
				creatBlock(blocks);
				break;
			}
		}
	}
}
