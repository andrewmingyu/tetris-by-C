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
#define Board_Heiht 25
#define Board_Width 17
#define Block_Test_Index 2
int Board_x = 20;
int Board_y = 10;
int x = 32; //블록 초기 x 값, 현제 블록의 커서
int y = 9;//블록 초기 y 값, 현제 블록의 커서
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

void creatBoard(int Board[Board_Heiht][Board_Width]) { //배경 보드 생성
	gotoxy(Board_x, Board_y);
	for (int H = 0; H < Board_Heiht; H++)
	{
		for (int W = 0; W < Board_Width; W++) {
			if (Board[H][W] == 1)
			{
				gotoxy(Board_x + W * 2, Board_y + H);
				printf("□");
			}
		}
	}
}

void creatBlock(int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE]) {// 7개의 블럭 출력 반복문
	for (int col = 0; col < 4; col++) // 블럭 출력 반복문
	{
		for (int row = 0; row < 4; row++)
		{
			if (blocks[Block_Test_Index][change][col][row] == 1)
			{
				gotoxy(x + row * 2, y + col);
				printf("□");
			}
		}
	}
}

int checkLeftTouck(int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE]) {
	for (int row = 0; row < 3; row++) // 블럭 출력 반복문
	{
		for (int col = 0; col < 4; col++)
		{
			if (blocks[Block_Test_Index][change][col][row] == 1)
			{
				if (row == 0) {
					return 20;
				}
				else if (row == 1) {
					return 18;
				}
				else if (row == 2) {
					return 16;
				}
			}
		}
	}
}

int checkRightTouck(int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE]) {
	for (int row = 3; row > 1; row--) // 블럭 출력 반복문
	{
		for (int col = 0; col < 4; col++)
		{
			if (blocks[Block_Test_Index][change][col][row] == 1)
			{
				if (row == 3) {
					return 46;
				}
				else if (row == 2) {
					return 48;
				}
				else if (row == 1) {
					return 50;
				}
			}
		}
	}
}
//아래 함수 수정해야됨 1
int checkCollision(int x, int y, int rot, int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE], int Board[Board_Heiht][Board_Width]) { //반박자 늦게 반응(부딛히기전에 접근이 안되야 되는데 부딛히고 접근금지)
	for (int col = 0; col < 4; col++) // y
	{
		for (int row = 0; row < 4; row++) // x
		{
			// 해당 회전(rot) 상태의 블록에 1이 있는 부분만 검사
			if (blocks[Block_Test_Index][rot][col][row] == 1)
			{
				// [화면 좌표] -> [배열 인덱스] 변환 공식
				// 보드 내부 x인덱스 = (현재화면x - 보드시작x) / 2 + 블록내부row
				int boardX = (x - Board_x) / 2 + row;
				int boardY = (y - Board_y) + col;

				// 1. 보드 범위를 벗어나는지 확인 (배열 인덱스 오류 방지)
				if (boardX < 0 || boardX >= Board_Width || boardY < 0 || boardY >= Board_Heiht) {
					return 1; // 충돌
				}

				// 2. 보드 배열에서 해당 위치가 벽(1)인지 확인
				if (Board[boardY][boardX] == 1) {
					return 1; // 충돌 (벽or 바닥)
				}
			}
		}
	}
	return 0; // 충돌 없음
}
//아래 함수 수정해야도미 2
void lockBlock(int x, int y, int rot, int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE], int Board[][Board_Width]) { //블록을 배경에 저장
	for (int col = 0; col < 4; col++) // 블록 내부 y축 (세로)
	{
		for (int row = 0; row < 4; row++) // 블록 내부 x축 (가로)
		{
			// 1. 현재 회전 상태(rot)의 블록 해당 위치에 '1'이 있는지 확인
			if (blocks[Block_Test_Index][rot][col][row] == 1)
			{
				// 2. 화면 좌표(x, y)를 보드 배열 인덱스로 변환 (checkCollision에 있는 공식 활용)
				// x는 2칸씩 차지하므로 (x - Board_x) / 2
				// y는 1칸씩 차지하므로 (y - Board_y)

				int boardX = (x - Board_x) / 2 + row;
				int boardY = (y - Board_y) + col;

				// 3. 보드 배열의 해당 위치를 1(벽/블록)로 변경
				// 주의: boardY, boardX가 배열 범위를 넘지 않는지 확인하는 안전장치가 있으면 더 좋음
				Board[boardY][boardX] = 1;
			}
		}
	}
}
int main() {
	int blocks[Block_Kinds][Block_SIZE][Block_SIZE][Block_SIZE] = {
	0,0,0,0 //ㅁ 0
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
	,0,0,0,0 // ㅡ 1
	,0,0,0,0
	,1,1,1,1
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,0,0
	,0,0,0,0
	,1,1,1,1
	,0,0,0,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,0
	,
	0,0,0,0	//ㄹ 꺼꾸로 2
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
	,0,1,1,0	//ㄹ 3
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
	,0,1,1,1		//ㄱ 꺼꾸로 4
	,0,1,0,0
	,0,0,0,0
	,0,0,1,0
	,0,0,1,0
	,0,0,1,1
	,0,0,0,0
	,0,0,0,0
	,0,0,0,1
	,0,1,1,1
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
	,0,0,0,0
	,0,1,0,0
	,0,1,1,1
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
	,0,0,0,0
	,0,0,0,0
	,0,0,1,0
	,0,1,1,1
	,0,0,1,0
	,0,1,1,0
	,0,0,1,0
	,0,0,0,0
	};
	int Board[Board_Heiht][Board_Width] = { //가로 17, 높이 25인 보드 생성
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	CursorView(0);
	creatBoard(Board);
	gotoxy(x, y);
	creatBlock(blocks);

	while (1)
	{
		if (_kbhit()) { //kbhit 함수는 키보드 입력 안하면 0 리턴
			int nkey = _getch(); //방향키 입력시 224 받음
			if ((char)nkey == 'c') { //방향 바꾸기
				int nextRot = (change + 1) % 4; // 다음 회전 모양 예측
				if (checkCollision(x, y, nextRot, blocks, Board) == 0) {
					change = nextRot; // 안전하니까 실제로 변경
				}
				system("cls");
				creatBoard(Board);
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
				if ((x - 2 == checkLeftTouck(blocks)) || (checkCollision(x, y, change, blocks, Board) == 1))
				{
					continue;
				}
				system("cls"); //콘솔창 출력된 모든 내용을 지움
				creatBoard(Board);
				gotoxy(x = x - 2, y);// 왼쪽 이동 반영
				creatBlock(blocks);
				break;
			case RIGHT:
				if ((x + 2 == checkRightTouck(blocks))||(checkCollision(x, y, change, blocks, Board) == 1))
				{
					continue;
				}
				system("cls");
				creatBoard(Board);
				gotoxy(x = x + 2, y);
				creatBlock(blocks);
				break;
			case UP:
				system("cls");
				creatBoard(Board);
				gotoxy(x, --y);
				creatBlock(blocks);
				break;
			case DOWN:
				if (checkCollision(x, y, change, blocks, Board) == 1) { //바닥 터치
					lockBlock(x, y, change, blocks, Board);
					continue;
				}
				system("cls");
				creatBoard(Board);
				gotoxy(x, ++y);
				creatBlock(blocks);
				break;
			}
		}
	}
}
