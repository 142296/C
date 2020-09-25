#include<stdio.h>								//棋盘跳行+深度探索
#include<stdlib.h>
int Count = 0;
int check(int chesser_board[], int line, int row, int n)
{
	if (chesser_board[n * line + row] == '.')    //判断空白与否
		return 0;
	for (int i = 0; i < n; i++)         //判断列
	{
		if (chesser_board[i * n + row] == 1 && i != line)
			return 0;
	}
	for (int i = 0; i < n; i++)             //判断行
	{
		if (chesser_board[n * line + i] == 1 && i != row)
			return 0;
	}
	return 1;
}
void put_piece(int chesser_board[], int k, int n, int line)
{
	if (k == 0)
	{
		Count++;
		return;
	}
	if (line >= n)
		return;
	for (int i = 0; i < n; i++)                      //按列       
	{
		if (check(chesser_board, line, i, n))
		{
			chesser_board[line * n + i] = 1;
			put_piece(chesser_board, k - 1, n, line + 1);       //用递归控制行
			chesser_board[line * n + i] = '#';
		}
	}
	put_piece(chesser_board, k, n, line + 1);      //该行没放棋子，进行下一行
}
int main()
{
	int n, k, * chesser_board, ch, length = 0;
	while (scanf_s("%d%d", &n, &k) && n != -1 && k != -1)
	{
		getchar();
		chesser_board = (int*)malloc(sizeof(int) * n * n);
		for (int i = 0; i < n * n; i++)
		{
			ch = getchar();
			while (ch == '\n')												//吃掉所有回车
				ch = getchar();
			chesser_board[i] = ch;
		}
		put_piece(chesser_board, k, n, 0);
		printf("%d\n", Count);
		Count = 0;
	}
}