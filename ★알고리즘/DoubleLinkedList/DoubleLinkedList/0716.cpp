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
	void SearchStudent();
	void PrintStudent();
};

ClassMate *head = NULL;

int main()
{
	int num;
	ClassMate *clm = new ClassMate;

	while (1)
	{
		cout << "�޴� ��ȣ�� �Է��ϼ���." << endl << endl;
		cout << "1. �л� �߰�" << endl;
		cout << "2. �л� ����" << endl;
		cout << "3. �л� �˻�" << endl;
		cout << "4. ��ü ���" << endl;
		cout << "5. ����" << endl;

		cin >> num;
		system("cls");

		switch (num)
		{
		case 1:
			clm->AddStudent();
			break;
		case 2:
			clm->DeleteStudent();
			break;
		case 3:
			clm->SearchStudent();
			break;
		case 4:
			clm->PrintStudent();
			break;
		case 5:
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

	cout << "��ȣ�� �Է��ϼ��� : ";
	cin >> clm->no;
	cout << "�̸��� �Է��ϼ��� : ";
	cin >> clm->name;

	if (head == NULL)	//�� ó�� �Է��� ��
	{
		head = clm;
		head->next = NULL;
	}
	else
	{
		tmp = head;

		while (tmp->next != NULL)	//������ �ڷ����
		{
			if (tmp->next->no > clm->no)	//�Էµ� ��ȣ�� tmp->next�� ��ȣ���� ũ��
			{
				clm->next = tmp->next;
				tmp->next = clm;
				break;
			}
			tmp = tmp->next;
		}

		if (tmp->next == NULL)		//�Է¹��� ��ȣ�� ���� Ŭ ��
		{
			if (tmp->no > clm->no)
			{
				clm->next = tmp;

				if (tmp == head)	//tmp�� �� ó���� ��
					head = clm;
			}
			else                    //tmp�� ������ ������ ���� ��
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

				if (tmp == head)	//tmp�� �� ó���� ��
					head = clm;
			}
		}
	}
}

void ClassMate::DeleteStudent()
{
	ClassMate *tmp = NULL;

	cout << "������ ��ȣ�� �Է��ϼ��� : ";
	cin >> tmp->no;

	if (tmp->no == head->no)	//head�� ������ ��
	{

	}
}

void ClassMate::SearchStudent()
{
	ClassMate *tmp;
	tmp = head;
	int num;

	cout << "�л��� ��ȣ�� �Է��ϼ��� : ";
	cin >> num;

	while (tmp != NULL)
	{
		if (num == tmp->no)
		{
			cout << "��ȣ : " << tmp->no << endl;
			cout << "�̸� : " << tmp->name << endl;
			cout << endl;
			return;
		}
		tmp = tmp->next;
	}
	cout << "��ȣ�� �����ϴ�." << endl;
}

void ClassMate::PrintStudent()
{
	ClassMate *tmp;
	tmp = head;

	while (tmp != NULL)
	{
		cout << "��ȣ : " << tmp->no << endl;
		cout << "�̸� : " << tmp->name << endl;
		cout << endl;

		tmp = tmp->next;
	}
}
