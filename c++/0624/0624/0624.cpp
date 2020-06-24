#include <iostream>

#define ROW 8
#define COL 8
using namespace std;

int(*Queen(int board[][ROW], int idx)) [ROW]
{
	int tmpCol = 0;
	int tmpRow = 0;

	//if (idx > 7)				//마지막 퀸까지 전부두면 보드 리턴
		//return board;

	//ex)

	board[0][0] = 1;	//퀸
	tmpCol = 0;
	tmpRow = 0;

	/* 탐색해서 2대입 */
	for (int i = 0; i < ROW; i++)
	{
		if (i + tmpRow >= ROW-1)
		{
			if (board[tmpCol][i + tmpRow] == 0)				//오른쪽으로 1줄
				board[tmpCol][i + tmpRow] = 2;
		}
		
		if (i + tmpCol >= ROW - 1)
		{
			if (board[i + tmpCol][tmpRow] == 0)				//아래로 1줄
				board[i + tmpCol][tmpRow] = 2;
		}
		

		if (board[tmpCol][ROW - i - 1] == 0)	//왼쪽으로 1줄
			board[tmpCol][ROW - i - 1] = 2;

		if (board[ROW - i - 1][tmpRow] == 0)	//위로 1줄
			board[ROW - i - 1][tmpRow] = 2;

		if (board[i][i] == 0)					//대각선 오른쪽아래 1줄
			board[i][i] = 2;

		if (board[ROW - i - 1][ROW - i - 1] == 0)//대각선 왼쪽 위 1줄
			board[ROW - i - 1][ROW - i - 1] = 2;

		if (board[i][ROW - i - 1] == 0)			//대각선 왼쪽 아래 1줄
			board[i][ROW - i - 1] = 2;

		if (board[ROW - i - 1][i] == 0)			//대각선 오른쪽 위 1줄
			board[ROW - i - 1][i] = 2;
	}

	return board;

	/*for (int i = 0; i < ROW*COL; i++)
	{
		if(board[i][])
	}*/

	//idx++;
	//Queen(board, queen, idx);
}

void Print(int board[][ROW])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << board[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int board[COL][ROW] = { 0 };

	Print(Queen(board, 0));
}

//int main()
//{
//	bool locker[100] = { false };
//	int student = 1;
//
//	for (int i = 0; i < 100; i++)
//	{
//		for (int j = student-1; j < 100; j += student)
//			locker[j] = !locker[j];
//
//		student++;
//	}
//
//	cout << "열린 사물함은 : ";
//
//	for (int i = 0; i < 100; i++)
//	{
//		if (locker[i])
//			cout << i+1 << "번" << " ";
//	}
//	cout << endl;
//}