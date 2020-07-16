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

	cout << "��ȣ�� �Է��ϼ��� : ";
	cin >> clm->no;
	cout << "�̸��� �Է��ϼ��� : ";
	cin >> clm->name;

	clm->next = NULL;

	if (head == NULL)	//�� ó�� �Է��� ��
		head = clm;
	else
	{
		tmp = head;

		if (tmp->next == NULL)	//�ڷᰡ �Ѱ� ���� ��
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
			while (tmp->next != NULL)	//������ �ڷ����
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

	cout << "������ �л��� ��ȣ : ";
	cin >> dNum;

	while (tmp != NULL)
	{
		if (dNum == tmp->no)
		{
			delete tmp;
			break;
		}
	}

	cout << "�ش��ϴ� ��ȣ�� �л��� �����ϴ�." << endl;
}

void ClassMate::PrintStudent()
{
	ClassMate *tmp;
	tmp = head;

	while (head != NULL)
	{
		cout << "��ȣ : " << head->no << endl;
		cout << "�̸� : " << head->name << endl;
		cout << endl;

		head = head->next;
	}
	head = tmp;
}
