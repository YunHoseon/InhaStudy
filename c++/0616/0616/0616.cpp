#include<iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <stdlib.h>

const int SIZE = 60;
using namespace std;

int int_cmp(const int *a, const int *b)	//�� ��
{
	if (*a < *b)
		return -1;
	else if (*a > *b)
		return 1;
	else if (*a == *b)
		return 0;
	else
		return -100;
}

void *bsearchx(const void *key, const void *base, size_t nmemb,
	size_t size, int(*compar)(const void*, const void*))	//�����˻��Լ�(ã�� �� / �迭/ ��Ұ���/ ���ũ��/ ���Լ�)
{
	int pivot;
	int head, tail;
	int minIdx;
	head = 0;
	tail = nmemb - 1;
	int* tmp = (int*)base;

	while (1)
	{
		pivot = (head + tail) / 2;
		int caseNum = int_cmp((int*)key, &tmp[pivot]);

		switch (caseNum)
		{
		case 1:		//������ ��ġ
			head = pivot + 1;

			if (head < 0)
				head = 0;
			int_cmp((int*)key, &tmp[pivot]);
			break;

		case 0:		//���� ã���� ��
			//�����˻�
			minIdx = pivot;
			for (int i = pivot; i >= 0; i--)
			{
				if (tmp[i] == tmp[pivot])
				{
					if (pivot > i)
					{
						minIdx = i;
					}
				}
			}
			return &tmp[minIdx];

		case -1:	//���� ��ġ
			tail = pivot - 1;
			int_cmp((int*)key, &tmp[pivot]);
			break;

		case -100:
			return NULL;
		}
	}
}

int main()
{
		int i, nx, ky;
		int *x;
		int *p;
		puts("bsearch�Լ��� ����Ͽ� �˻�");
		cout << "��� ���� : ";
		cin >> nx;
		x = (int*)calloc(nx, sizeof(int));
	
		cout << "������������ �Է��ϼ���.\n";
		cout << "x[0] : ";
		cin >> x[0];
	
		for (i = 1; i < nx; i++)
		{
			do
			{
				printf("x[%d] : ", i);
				cin >> x[i];
			} while (x[i] < x[i - 1]);
		}
		cout << "�˻� �� : ";
		cin >> ky;
	
		p = (int*)bsearchx(&ky, x, nx, sizeof(int),
			(int(*)(const void*, const void*)) int_cmp);
	
		if (p == NULL)
			cout << "�˻��� �����߽��ϴ�.";
		else
			printf("%d��(��) x[%d]�� �ֽ��ϴ�.\n", ky, (int)(p - x));
	
		free(x);
}

//typedef struct {
//	char name[10];
//	int height;
//	int weight;
//}Person;
//
//int npcmp(const Person *x, const Person *y)
//{
//	cout << "x : " << x->name << " y : " << y->name << endl;
//	return strcmp(x->name, y->name);
//}
//
//int main()
//{
//	Person x[] =
//	{
//		{"�迵��", 179, 79},
//		{ "������", 172, 63 },
//		{ "�̼���", 176, 52 },
//		{ "������", 165, 51 },
//		{ "������", 181, 73 },
//		{ "ȫ����", 172, 84 }
//	};
//
//	int nx = sizeof(x) / sizeof(x[0]);
//	int retry;
//	puts("�̸����� �˻��մϴ�.");
//
//	do
//	{
//		Person temp, *p;
//		cout << "�̸� : ";
//		cin >> temp.name;
//
//		p = (Person*)bsearch(&temp, x, nx, sizeof(Person),
//			(int(*)(const void*, const void*))npcmp);
//
//		if (p == NULL)
//			cout << "�˻��� �����߽��ϴ�.";
//		else
//		{
//			cout << "�˻� ����! �Ʒ���Ҹ� ã�ҽ��ϴ�.";
//			printf("x[%d] : %s %dcm %dkg\n",
//				(int)(p-x), p->name, p->height, p->weight);
//		}
//
//		cout << "�ٽ� �˻��ұ��? (1)�� (2)�ƴϿ� : ";
//		cin >> retry;
//	}
//	while (retry == 1);
//}

//int sum(int x1, int x2)
//{
//	return x1 + x2;
//}
//
//int mul(int x1, int x2)
//{
//	return x1 * x2;
//}
//
//void kuku(int(*calc)(int, int))
//{
//	int i, j;
//	for (i = 1; i <= 9; i++)
//	{
//		for ( j = 1; j < 9; j++)
//		{
//			printf("%3d", (*calc)(i, j));
//		}
//		putchar('\n');
//	}
//}
//
//int main()
//{
//	cout << "����ǥ\n";
//	kuku(sum);
//	cout << "\n����ǥ\n";
//	kuku(mul);
//}

//int int_cmp(const int *a, const int *b)
//{
//	cout << "a : " << *a << "b : " << *b << endl;
//	if (*a < *b)
//		return -1;
//	else if (*a > *b)
//		return 1;
//	else
//		return 0;
//}
//
//int main()
//{
//	int i, nx, ky;
//	int *x;
//	int *p;
//	puts("bsearch�Լ��� ����Ͽ� �˻�");
//	cout << "��� ���� : ";
//	cin >> nx;
//	x = (int*)calloc(nx, sizeof(int));
//
//	cout << "������������ �Է��ϼ���.\n";
//	cout << "x[0] : ";
//	cin >> x[0];
//
//	for (i = 1; i < nx; i++)
//	{
//		do
//		{
//			printf("x[%d] : ", i);
//			cin >> x[i];
//		} while (x[i] < x[i - 1]);
//	}
//	cout << "�˻� �� : ";
//	cin >> ky;
//
//	p = (int*)bsearch(&ky, x, nx, sizeof(int),
//		(int(*)(const void*, const void*))int_cmp);
//
//	if (p == NULL)
//		cout << "�˻��� �����߽��ϴ�.";
//	else
//		printf("%d��(��) x[%d]�� �ֽ��ϴ�.\n", ky, (int)(p - x));
//
//	free(x);
//}

//int main()
//{
//	string pwd;
//	int alpha = 0, num = 0, others = 0;
//
//	cout << "��й�ȣ�� �Է��ϼ��� : ";
//	getline(cin, pwd);
//
//	for (int i = 0; i < pwd.size(); i++)
//	{
//		if (isalpha(pwd[i]))
//			alpha++;
//		else if (isdigit(pwd[i]))
//			num++;
//		else
//			others++;
//	}
//
//	if (num >= 2 && others == 0 && pwd.size() > 8)
//		cout << "valid password" << endl;
//	else
//		cout << "invalid password" << endl;
//}

//int main()
//{
//	string str;
//	
//	int moum = 0, jaum = 0, others = 0;
//
//	cout << "�ܾ���� �Է��Ͻÿ� (�������� q) : ";
//	
//	getline(cin, str);
//
//	for (int i = 0; i < str.size(); i++)
//	{
//		if (isspace(str[i]))
//		{
//			if (str[i + 1] == 'a' || str[i + 1] == 'e'|| str[i + 1] == 'i'|| str[i + 1] == 'o'|| str[i + 1] == 'u')
//			{
//				moum++;
//			}
//			else
//			{
//				jaum++;
//			}
//		}
//		else if(isspace(str[i]))
//		{
//			others++;
//		}
//	}
//
//	cout << "�������� �����ϴ� �ܾ� �� : " << moum << endl;
//	cout << "�������� �����ϴ� �ܾ� �� : " << jaum << endl;
//	cout << "��Ÿ : " << others << endl;
//}

//int main()
//{
	/*char fileName[SIZE];
	ifstream inFile;
	cout << "������ ������ �̸��� �Է��Ͻÿ� : ";
	cin.getline(fileName, SIZE);
	inFile.open(fileName);
	if (!inFile.is_open())
	{
		cout << fileName << "������ �� �� �����ϴ�." << endl;
		cout << "���α׷��� �����մϴ�.\n";
		exit(EXIT_FAILURE);
	}
	double value;
	double sum = 0;
	int count = 0;

	inFile >> value;
	while (inFile.good())
	{
		++count;
		sum += value;
		inFile >> value;
	}
	if (inFile.eof())
		cout << "������ ���Դϴ�.";
	else if (inFile.fail())
		cout << "������ ����ġ�� �Է��� ����˴ϴ�.\n";
	else
		cout << "�� �� ���� ������ �Է��� ����Ǿ����ϴ�.";

	if (count == 0)
		cout << "�����Ͱ� �����ϴ�.";
	else
	{
		cout << "���� �׸��� ���� : " << count << endl;
		cout << "�հ� : " << sum << endl;
		cout << "��� : " << sum/count << endl;
	}
	inFile.close();*/

	/*char automobile[50];
	int year;
	double a_price;
	double d_price;

	ofstream outFile;
	outFile.open("carInfo.txt");

	cout << "�ڵ��� ����Ŀ�� ������ �Է��ϼ��� : ";
	cin.getline(automobile, 50);
	cout << "������ �Է��ϼ��� : ";
	cin >> year;
	cout << "���� ������ �Է��ϼ��� : ";
	cin >> a_price;
	d_price = 0.913*a_price;

	cout << fixed;
	cout.precision(2);
	cout.setf(ios_base::showpoint);
	cout << "����Ŀ�� ���� : " << automobile <<  endl;
	cout << "���� : " << year << endl;
	cout << "���� ���� $" << a_price << endl;
	cout << "���� ���� $" << d_price << endl;

	outFile << fixed;
	outFile.precision(2);
	outFile.setf(ios_base::showpoint);
	outFile << "����Ŀ�� ���� : " << automobile << endl;
	outFile << "���� : " << year << endl;
	outFile << "���� ���� $" << a_price << endl;
	outFile << "���� ���� $" << d_price << endl;

	outFile.close();*/
//}

//void showmenu();
//void report();
//void comfort();
//
//int main()
//{
//	showmenu();
//	int choice;
//	cin >> choice;
//
//	while (choice != 5)
//	{
//		switch (choice)
//		{
//		case 1 :
//			cout << "\a\n";
//			break;
//		case 2:
//			report();
//			break;
//		case 3:
//			cout << "������� ���� ȸ�翡 ���̽��ϴ�.";
//			break;
//		case 4:
//			comfort();
//			break;
//
//		default:
//			cout << "���� x";
//		}
//		showmenu();
//		cin >> choice;
//	}
//	cout << "���α׷� ����";
//}
//
//void showmenu()
//{
//	cout << "1, 2, 3, 4, 5���߿� �ϳ��� ���� : \n";
//	"1) �����\t2) ����\n"
//		"3) �˸�����\t2) �ݷ���\n"
//		"5) ����\n";
//}
//
//void report()
//{
//	cout << "�̹� �б�� �濵������ ���� �����ϴ�.\n"
//			"�Ǹŷ��� 120% �þ��, ����� 35% �پ����ϴ�.\n";
//}
//
//void comfort()
//{
//	cout << "�ְ��� CEO\n";
//}

//int main()
//{
//	cout << "�м��� �׽�Ʈ�� �Է��Ͻʽÿ�. "
//		"�Է��� ���� @�� ǥ���Ͻʽÿ�\n";
//
//	char ch;
//	int whitespace = 0;
//	int digits = 0;
//	int chars = 0;
//	int punct = 0;
//	int others = 0;
//
//	cin.get(ch);
//
//	while (ch != '@')
//	{
//		if (isalpha(ch))
//			chars++;
//		else if (isspace(ch))
//			whitespace++;
//		else if (isdigit(ch))
//			digits++;
//		else if (ispunct(ch))
//			punct++;
//		else
//			others++;
//		cin.get(ch);
//	}
//
//	cout << chars << ", "
//		<< whitespace << ", "
//		<< digits << ", "
//		<< punct << ", "
//		<< others << endl;
//}

//int main()
//{
//	float x1, x2, x3, x4, y1, y2, y3, y4;
//	float a, b, c, d, e, f;
//	float x, y;
//
//	cout << "�� �� ���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
//
//	a = y1 - y2;
//	b = -(x1 - x2);
//	c = y3 - y4;
//	d = -(x3 - x4);
//	e = a*x1 + b*y1;
//	f = c*x3 + d*y3;
//
//	x = ((e*d - b*f)) / ((a*d - b*c));
//	y = ((a*f - e*c)) / ((a*d - b*c));
//
//	if (abs(x) != INFINITY && abs(y) != INFINITY)
//		cout << "������ x : " << x << " y : " << y << endl;
//	else
//		cout << "�������� �����ϴ�.";
//}