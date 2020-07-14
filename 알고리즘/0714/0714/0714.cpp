#include <iostream>
#include <string>

using namespace std;

class ClassMate
{
	int no;
	string name;
	ClassMate *next;

public:
	ClassMate();
	~ClassMate();

	void AddStudent();
	void DeleteStudent();
	void PrintStudent();
};

ClassMate *head = NULL;

int main()
{
	int num;
	ClassMate *clm = new ClassMate;

	while (true)
	{
		cout << "메뉴 번호를 입력하세요." << endl << endl;
		cout << "1. 학생 추가" << endl;
		cout << "2. 학생 삭제" << endl;
		cout << "3. 전체 출력" << endl;
		cout << "4. 종료" << endl;

		cin >> num;

		switch (num)
		{
		case 1:
			clm->AddStudent();
			break;
		case 2:

			break;
		case 3:
			clm->PrintStudent();
			break;
		case 4:
			exit(0);
			break;

		default:
			break;
		}
	}
}

ClassMate::ClassMate()
{
}

ClassMate::~ClassMate()
{
}

void ClassMate::AddStudent()
{
	ClassMate *clm = new ClassMate;
	ClassMate *tmp = NULL;

	cout << "번호를 입력하세요 : ";
	cin >> clm->no;
	cout << "이름을 입력하세요 : ";
	cin >> clm->name;

	clm->next = NULL;

	if (head == NULL)
		head = clm;
	else
	{
		tmp = head;

		while (tmp->next != NULL)
		{
			if (clm->no < tmp->no)
			{
				clm->next = tmp;

				if (tmp == head)
					head = clm;
			}
			tmp = tmp->next;
		}

		if(tmp->next == NULL)
			tmp->next = clm;
	}
	/*if (head->no > clm->no)
	{
		clm->next = head;
		head->next = NULL;
	}
	else
	{
		head->next = clm;
		clm->next = NULL;
	}*/
}

void ClassMate::DeleteStudent()
{

}

void ClassMate::PrintStudent()
{
	while (head != NULL)
	{
		cout << "번호 : " << head->no << endl;
		cout << "이름 : " << head->name << endl;
		cout << endl;

		head = head->next;
	}
}
