#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int plateNum = 0;
	vector<int> plates;
	bool ol = false;
	int cnt = 0;

	cout << "���� ���� �Է� : ";
	cin >> plateNum;

	cout << "���ÿ� ���� ���� ���� �Է� : ";

	for (int i = 0; i < plateNum; i++)
	{
		plates.push_back(0);
		cin >> plates[i];
	}

	while (!ol)
	{
		if (plates[0] == 0 && cnt < 0)
		{
			for (int i = 1; i < plateNum; i++)
			{
				if (plates[i] > 1)
				{
					cout << -1 << endl;
					return 0;
				}
			}
		}
		else if(plates[0] == 0 && cnt > 0)
		{
			for (int i = 1; i < plateNum; i++)
			{
				if (plates[i] > 1)
				{
					cout << -1 << endl;
					return 0;
				}
			}
		}

		for (int i = 1; i < plateNum / 2 + 1; i++)
		{
			for (int j = i + 1; j <= plateNum; j++)
			{
				if (j%i == 0)
				{
					plates[j - 1] -= plates[i - 1];

					if (plates[j - 1] < 0)
					{
						cout << -1 << endl;
						return 0;
					}
				}
			}
		}
		cnt++;

		/*for (int i = 0; i < plateNum; i++)
			cout << plates[i] << " ";
		cout << endl;*/

		for (int i = 0; i < plateNum; i++)
		{
			if (plates[i] > 1)
			{
				ol = false;
				break;
			}
			else
				ol = true;
		}
	}

	cout << "�ð� : " << cnt << endl;

	for (int i = 0; i < plateNum; i++)
		cout << plates[i] << " ";
	cout << endl;
}

//string text;
//
//void BruteForce()
//{
//	string pattern = "def";
//	int bingo = 0;
//
//	for (int i = 0; i < text.size(); i++)
//	{
//		if (pattern[0] == text[i])
//		{
//			bingo++;
//			for (int j = 1; j <= pattern.size(); j++)
//			{
//				if (pattern[j] == text[j + i])
//					bingo++;
//					
//				if (bingo == pattern.size())
//				{
//					for (int k = 0; k < pattern.size(); k++)
//					{
//						text[i + k] = '*';
//					}
//					cout << "ã�� ���ڿ��� " << i << " �ε����� �ֽ��ϴ�." << endl;
//					cout << text << endl;
//					return;
//				}
//			}
//		}
//		bingo = 0;
//	}
//	cout << "ã�� ���ڿ��� �����ϴ�." << endl;
//}
//
//void SearchString()
//{
//	int patternIdx;
//	string pattern = "hello";
//	string temp;
//
//	patternIdx = text.find(pattern);
//
//	if (patternIdx != string::npos)
//	{
//		for (int i = 0; i < pattern.size(); i++)
//			temp += "*";
//
//		text.replace(patternIdx, pattern.size(), temp);
//		cout << text << endl;
//		cout << "ã�� ���ڿ��� " << patternIdx << " �ε����� �ֽ��ϴ�." << endl;
//	}
//	else
//		cout << "ã�� ���ڿ��� �����ϴ�." << endl;
//}
//
//int main()
//{
//	cout << "���ڿ��� �Է��ϼ��� : ";
//	cin >> text;
//
//	//BruteForce();
//
//	SearchString();
//}