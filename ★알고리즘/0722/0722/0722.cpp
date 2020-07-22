#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
	int no;
	string name;
	
	Student *prev;
	Student *left;
	Student *right;

public:
	Student();
	~Student();
};

void InsertData();
void DeleteData();
void SearchData(Student *head);
void PrintData(Student *head);

Student *head;

int main()
{
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
			SearchData(head);
			break;

		case 4:
			PrintData(head);
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
	prev = NULL;
	left = NULL;
	right = NULL;
}

Student::~Student()
{
}

void InsertData()
{
	Student *std = new Student;
	Student *tmp = NULL;

	cout << "번호 : ";
	cin >> std->no;
	cout << "이름 : ";
	cin >> std->name;

	if (head == NULL)	//맨 처음 입력일 때
		head = std;
	else
	{
		tmp = head;

		while (1)
		{
			if (tmp->no > std->no)		//head보다 작을 때
			{
				if (tmp->left == NULL)
				{
					tmp->left = std;
					return;
				}
				else
					tmp = tmp->left;
			}
			else if (tmp->no < std->no) //head보다 클 때
			{
				if (tmp->right == NULL)
				{
					tmp->right = std;
					return;
				}
				else
					tmp = tmp->right;
			}
			else						//같은 숫자 일때
				return;
		}
	}
}

void DeleteData()
{
}

void SearchData(Student *head)
{
	Student *tmp;

	if (head == NULL)
		return;

	int num;

	cout << "번호 : ";
	cin >> num;

	while (1)
	{
		if (head->no > num)
			head = head->left;

		else if (head->no < num)
			head = head->right;

		else						//같은 숫자 일때
		{
			cout << "번호 : " << head->no << "\t이름 : " << head->name << endl;
			return;
		}
	}
}

void PrintData(Student *head)
{
	if (head == NULL)
		return;

	PrintData(head->left);
	cout << "번호 : " << head->no << "\t이름 : " << head->name << endl;
	PrintData(head->right);
}
