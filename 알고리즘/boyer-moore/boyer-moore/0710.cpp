#include <iostream>
#include <string>

using namespace std;

string text;
string pattern;

void BoyerMoore()
{
	int hop = 0;
	int dif = 0;

	for (int i = pattern.size() - 1; i < text.size() - pattern.size() + 1; i += hop)
	{
		for (int j = pattern.size()-1; j > 0; j--)
		{
			if (pattern[j] == text[i])
			{
				i--;
				hop++;
			}
			else
			{
				dif++;
			}

			if (dif == pattern.size())
				hop = pattern.size();
		}
		dif = 0;
	}
}

int main()
{
	text = "ABCXDEZCAVACABAC";

	cout << text << endl;

	cout << "찾을 문자열을 입력하세요 : ";
	cin >> pattern;

	BoyerMoore();
}