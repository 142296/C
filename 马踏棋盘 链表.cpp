#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#define size 5

struct TempPace
{
	int tem[size][size];
	TempPace* next;
};

int pace(int chess[size][size], int line, int row, TempPace** head);             //走一步
void show(TempPace* head);														 //输出
int check(int chess[size][size]);												 //检查
void gotoxy(int x, int y);										                 //光标移动到（x，y）位置
void HideCursor();																 //隐藏光标

void gotoxy(int x, int y)										                //光标移动到（x，y）位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()																//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int pace(int chess[size][size], int line, int row, TempPace** head)
{
	TempPace* chesspace, * temp;
	int tem[size][size] = { 0 };
	int key = 0, i, j;
	for (i = 0; i < size; i++)                                //保存该棋盘
	{
		for (j = 0; j < size; j++)
		{
			tem[i][j] = chess[i][j];
		}
	}
	chess[line][row] = 1;
	if (line - 1 >= 0 && row - 2 >= 0 && chess[line - 1][row - 2] != 1)  //上1左2
		key = pace(chess, line - 1, row - 2, head);
	if (line - 2 >= 0 && row - 1 >= 0 && chess[line - 2][row - 1] != 1)  //上2左1
		key = pace(chess, line - 2, row - 1, head);
	if (line - 2 >= 0 && row + 1 < size && chess[line - 2][row + 1] != 1)  //上2右1
		key = pace(chess, line - 2, row + 1, head);
	if (line - 1 >= 0 && row + 2 < size && chess[line - 1][row + 2] != 1)  //上1右2
		key = pace(chess, line - 1, row + 2, head);
	if (line + 1 < size && row + 2 < size && chess[line + 1][row + 2] != 1)  //下1右2
		key = pace(chess, line + 1, row + 2, head);
	if (line + 2 < size && row + 1 < size && chess[line + 2][row + 1] != 1)  //下2右1
		key = pace(chess, line + 2, row + 1, head);
	if (line + 2 < size && row - 1 >= 0 && chess[line + 2][row - 1] != 1)  //下2左1
		key = pace(chess, line + 2, row - 1, head);
	if (line + 1 < size && row - 2 >= 0 && chess[line + 1][row - 2] != 1)  //下1左2
		key = pace(chess, line + 1, row - 2, head);
	if (check(chess) && key != 1)											//当无路可走时判断 
	{
		chesspace = (TempPace*)malloc(sizeof(TempPace));
		for (i = 0; i < size; i++)								     // 头插法保存当前棋盘
			for (j = 0; j < size; j++)
				chesspace->tem[i][j] = chess[i][j];
		temp = *head;
		*head = chesspace;
		chesspace->next = temp;
		key = 1;
	}
	if (key)														//如果满了，则进栈
	{
		chesspace = (TempPace*)malloc(sizeof(TempPace));
		for (i = 0; i < size; i++)       // 头插法保存当前棋盘
			for (j = 0; j < size; j++)
				chesspace->tem[i][j] = tem[i][j];
		temp = *head;
		*head = chesspace;
		chesspace->next = temp;
	}
	else
		chess[line][row] = 0;			//不符合则逐项归零
	return key;										//如果满了，chess一直是满的
}
void show(TempPace* head)
{
	int i, j, begin;
	while (head != NULL)
	{
		begin = time(0);
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				if (!head->tem[i][j])
					printf("□");
				else
					printf("■");
			}
			printf("\n");
		}
		while (time(0) <= begin);
		gotoxy(0, 0);
		head = head->next;
	}
}
int check(int chess[size][size])
{
	int key = 1;
	for (int i = 0; key != 0 && i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (chess[i][j] == 0)
			{
				key = 0;
				break;
			}
		}
	}
	return key;
}
int main()
{
	TempPace* head = NULL;
	int chess[size][size] = { 0 }, i, j;
	HideCursor();
	printf("请输入起点坐标(x y)（用空格隔开）");
	scanf_s("%d%d", &i, &j);
	printf("计算中...");
	if (pace(chess, i - 1, j - 1, &head))
	{
		system("cls");
		show(head);
		system("cls");
		printf("结束");
	}
	else
		printf("当前点没有走法");
	getchar();
}