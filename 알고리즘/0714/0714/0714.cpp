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
		cout << "�޴� ��ȣ�� �Է��ϼ���." << endl << endl;
		cout << "1. �л� �߰�" << endl;
		cout << "2. �л� ����" << endl;
		cout << "3. ��ü ���" << endl;
		cout << "4. ����" << endl;

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

	cout << "��ȣ�� �Է��ϼ��� : ";
	cin >> clm->no;
	cout << "�̸��� �Է��ϼ��� : ";
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
		cout << "��ȣ : " << head->no << endl;
		cout << "�̸� : " << head->name << endl;
		cout << endl;

		head = head->next;
	}
}
