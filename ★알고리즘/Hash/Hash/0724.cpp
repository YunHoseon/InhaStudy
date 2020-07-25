#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student
{
public:
	int no;
	string name;

	Student *next;

public:
	Student();
	~Student();
};

int HashFunc(int _no)
{
	return _no % 10;
}

void InsertData();
void DeleteData();
void SearchData();
void PrintData();

Student *head[10];

int main()
{
	for (size_t i = 0; i < 10; i++)
		head[i] = nullptr;

	int num;

	while (1)
	{
		cout << "(1)삽입 (2)삭제 (3)검색 (4)출력 (0) 종료 : " << endl;
		cin >> num;

		switch (num)
		{
		case 1:
			InsertData();
			break;

		case 2:
			DeleteData();
			break;

		case 3:
			SearchData();
			break;

		case 4:
			PrintData();
			break;

		case 0:
			exit(0);
			break;

		default:
			cout << "다시 입력" << endl;
			break;
		}
	}
}

Student::Student()
{
	next = NULL;
}

Student::~Student()
{
}

void InsertData()
{
	Student *std = new Student;

	cout << "번호 : ";
	cin >> std->no;
	cout << "이름 : ";
	cin >> std->name;

	Student *tmp = head[HashFunc(std->no)];		//키 구분

	if (tmp == NULL)
		head[HashFunc(std->no)] = std;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = std;
	}
}

void DeleteData()
{

}

void SearchData()
{
	int num;

	cout << "번호 : ";
	cin >> num;

	Student *tmp = head[HashFunc(num)];

	while (tmp != NULL)
	{
		if (tmp->no == num)
		{
			cout << "번호 : " << num << endl;
			cout << "이름 : " << tmp->name << endl;
			cout << endl;
			return;
		}
		tmp = tmp->next;
	}
	cout << "번호가 없습니다." << endl;
}

void PrintData()
{
	Student *tmp = NULL;
	
	for (int i = 0; i < 10; i++)
	{
		tmp = head[i];

		while (tmp != NULL)
		{
			if (tmp != NULL)
			{
				cout << "번호 : " << tmp->no << endl;
				cout << "이름 : " << tmp->name << endl;
				cout << endl;
			}
			tmp = tmp->next;
		}
	}
}
