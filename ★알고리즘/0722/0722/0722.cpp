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
		cout << "(1)���� (2)���� (3)�˻� (4)��� (0) ���� : " << endl;
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
			cout << "�ٽ� �Է�" << endl;
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

	cout << "��ȣ : ";
	cin >> std->no;
	cout << "�̸� : ";
	cin >> std->name;

	if (head == NULL)	//�� ó�� �Է��� ��
		head = std;
	else
	{
		tmp = head;

		while (1)
		{
			if (tmp->no > std->no)		//head���� ���� ��
			{
				if (tmp->left == NULL)
				{
					tmp->left = std;
					return;
				}
				else
					tmp = tmp->left;
			}
			else if (tmp->no < std->no) //head���� Ŭ ��
			{
				if (tmp->right == NULL)
				{
					tmp->right = std;
					return;
				}
				else
					tmp = tmp->right;
			}
			else						//���� ���� �϶�
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

	cout << "��ȣ : ";
	cin >> num;

	while (1)
	{
		if (head->no > num)
			head = head->left;

		else if (head->no < num)
			head = head->right;

		else						//���� ���� �϶�
		{
			cout << "��ȣ : " << head->no << "\t�̸� : " << head->name << endl;
			return;
		}
	}
}

void PrintData(Student *head)
{
	if (head == NULL)
		return;

	PrintData(head->left);
	cout << "��ȣ : " << head->no << "\t�̸� : " << head->name << endl;
	PrintData(head->right);
}
