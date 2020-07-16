#include <iostream>
#include <string>

using namespace std;

class ClassMate
{
	int no;
	string name;
	ClassMate *next;
	ClassMate *prev;

public:
	ClassMate();
	~ClassMate();

	void AddStudent();
	void DeleteStudent();
	ClassMate SearchStudent();
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
	next = NULL;
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

	if (head == NULL)	//맨 처음 입력일 때
	{
		head = clm;
		head->next = NULL;
	}
	else
	{
		tmp = head;

		while (tmp->next != NULL)	//마지막 자료까지
		{
			if (tmp->next->no > clm->no)	//입력된 번호가 tmp->next의 번호보다 크면
			{
				clm->next = tmp->next;
				tmp->next = clm;
				break;
			}
			tmp = tmp->next;
		}

		if (tmp->next == NULL)		//입력받은 번호가 가장 클 때
		{
			if (tmp->no > clm->no)
			{
				clm->next = tmp;

				if (tmp == head)	//tmp가 맨 처음일 때
					head = clm;
			}
			else                    //tmp가 마지막 노드까지 갔을 때
			{
				tmp->next = clm;
				clm->next = NULL;
			}
		}
		else
		{
			if (tmp->no > clm->no)
			{
				clm->next = tmp;

				if (tmp == head)	//tmp가 맨 처음일 때
					head = clm;
			}
		}
	}
}

void ClassMate::DeleteStudent()
{
}

void ClassMate::PrintStudent()
{
	ClassMate *tmp;
	tmp = head;

	while (tmp != NULL)
	{
		cout << "번호 : " << tmp->no << endl;
		cout << "이름 : " << tmp->name << endl;
		cout << endl;

		tmp = tmp->next;
	}
}
