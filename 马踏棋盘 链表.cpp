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

int pace(int chess[size][size], int line, int row, TempPace** head);             //��һ��
void show(TempPace* head);														 //���
int check(int chess[size][size]);												 //���
void gotoxy(int x, int y);										                 //����ƶ�����x��y��λ��
void HideCursor();																 //���ع��

void gotoxy(int x, int y)										                //����ƶ�����x��y��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()																//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int pace(int chess[size][size], int line, int row, TempPace** head)
{
	TempPace* chesspace, * temp;
	int tem[size][size] = { 0 };
	int key = 0, i, j;
	for (i = 0; i < size; i++)                                //���������
	{
		for (j = 0; j < size; j++)
		{
			tem[i][j] = chess[i][j];
		}
	}
	chess[line][row] = 1;
	if (line - 1 >= 0 && row - 2 >= 0 && chess[line - 1][row - 2] != 1)  //��1��2
		key = pace(chess, line - 1, row - 2, head);
	if (line - 2 >= 0 && row - 1 >= 0 && chess[line - 2][row - 1] != 1)  //��2��1
		key = pace(chess, line - 2, row - 1, head);
	if (line - 2 >= 0 && row + 1 < size && chess[line - 2][row + 1] != 1)  //��2��1
		key = pace(chess, line - 2, row + 1, head);
	if (line - 1 >= 0 && row + 2 < size && chess[line - 1][row + 2] != 1)  //��1��2
		key = pace(chess, line - 1, row + 2, head);
	if (line + 1 < size && row + 2 < size && chess[line + 1][row + 2] != 1)  //��1��2
		key = pace(chess, line + 1, row + 2, head);
	if (line + 2 < size && row + 1 < size && chess[line + 2][row + 1] != 1)  //��2��1
		key = pace(chess, line + 2, row + 1, head);
	if (line + 2 < size && row - 1 >= 0 && chess[line + 2][row - 1] != 1)  //��2��1
		key = pace(chess, line + 2, row - 1, head);
	if (line + 1 < size && row - 2 >= 0 && chess[line + 1][row - 2] != 1)  //��1��2
		key = pace(chess, line + 1, row - 2, head);
	if (check(chess) && key != 1)											//����·����ʱ�ж� 
	{
		chesspace = (TempPace*)malloc(sizeof(TempPace));
		for (i = 0; i < size; i++)								     // ͷ�巨���浱ǰ����
			for (j = 0; j < size; j++)
				chesspace->tem[i][j] = chess[i][j];
		temp = *head;
		*head = chesspace;
		chesspace->next = temp;
		key = 1;
	}
	if (key)														//������ˣ����ջ
	{
		chesspace = (TempPace*)malloc(sizeof(TempPace));
		for (i = 0; i < size; i++)       // ͷ�巨���浱ǰ����
			for (j = 0; j < size; j++)
				chesspace->tem[i][j] = tem[i][j];
		temp = *head;
		*head = chesspace;
		chesspace->next = temp;
	}
	else
		chess[line][row] = 0;			//���������������
	return key;										//������ˣ�chessһֱ������
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
					printf("��");
				else
					printf("��");
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
	printf("�������������(x y)���ÿո������");
	scanf_s("%d%d", &i, &j);
	printf("������...");
	if (pace(chess, i - 1, j - 1, &head))
	{
		system("cls");
		show(head);
		system("cls");
		printf("����");
	}
	else
		printf("��ǰ��û���߷�");
	getchar();
}