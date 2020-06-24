#include <iostream>

#define ROW 8
#define COL 8
using namespace std;

int(*Queen(int board[][ROW], int idx)) [ROW]
{
	int tmpCol = 0;
	int tmpRow = 0;

	//if (idx > 7)				//������ ������ ���εθ� ���� ����
		//return board;

	//ex)

	board[0][0] = 1;	//��
	tmpCol = 0;
	tmpRow = 0;

	/* Ž���ؼ� 2���� */
	for (int i = 0; i < ROW; i++)
	{
		if (i + tmpRow >= ROW-1)
		{
			if (board[tmpCol][i + tmpRow] == 0)				//���������� 1��
				board[tmpCol][i + tmpRow] = 2;
		}
		
		if (i + tmpCol >= ROW - 1)
		{
			if (board[i + tmpCol][tmpRow] == 0)				//�Ʒ��� 1��
				board[i + tmpCol][tmpRow] = 2;
		}
		

		if (board[tmpCol][ROW - i - 1] == 0)	//�������� 1��
			board[tmpCol][ROW - i - 1] = 2;

		if (board[ROW - i - 1][tmpRow] == 0)	//���� 1��
			board[ROW - i - 1][tmpRow] = 2;

		if (board[i][i] == 0)					//�밢�� �����ʾƷ� 1��
			board[i][i] = 2;

		if (board[ROW - i - 1][ROW - i - 1] == 0)//�밢�� ���� �� 1��
			board[ROW - i - 1][ROW - i - 1] = 2;

		if (board[i][ROW - i - 1] == 0)			//�밢�� ���� �Ʒ� 1��
			board[i][ROW - i - 1] = 2;

		if (board[ROW - i - 1][i] == 0)			//�밢�� ������ �� 1��
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
//	cout << "���� �繰���� : ";
//
//	for (int i = 0; i < 100; i++)
//	{
//		if (locker[i])
//			cout << i+1 << "��" << " ";
//	}
//	cout << endl;
//}