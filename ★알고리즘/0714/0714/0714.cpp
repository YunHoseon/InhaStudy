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

	while (1)
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
			clm->DeleteStudent();
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

	if (head == NULL)	//맨 처음 입력일 때
		head = clm;
	else
	{
		tmp = head;

		if (tmp->next == NULL)	//자료가 한개 있을 때
		{
			if (clm->no < tmp->no)
			{
				clm->next = tmp;

				if (tmp == head)
					head = clm;
			}
			else
				tmp->next = clm;
		}
		else
		{
			while (tmp->next != NULL)	//마지막 자료까지
			{
				if (clm->no < tmp->no)
				{
					clm->next = tmp;

					if (tmp == head)
						head = clm;
				}
				tmp = tmp->next;
			}
		}
	}
}

void ClassMate::DeleteStudent()
{
	ClassMate *tmp;
	tmp = head;
	int dNum;

	cout << "삭제할 학생의 번호 : ";
	cin >> dNum;

	while (tmp != NULL)
	{
		if (dNum == tmp->no)
		{
			delete tmp;
			break;
		}
	}

	cout << "해당하는 번호의 학생이 없습니다." << endl;
}

void ClassMate::PrintStudent()
{
	ClassMate *tmp;
	tmp = head;

	while (head != NULL)
	{
		cout << "번호 : " << head->no << endl;
		cout << "이름 : " << head->name << endl;
		cout << endl;

		head = head->next;
	}
	head = tmp;
}
