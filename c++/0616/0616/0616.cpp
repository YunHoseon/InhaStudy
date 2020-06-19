#include<iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <stdlib.h>

const int SIZE = 60;
using namespace std;

int int_cmp(const int *a, const int *b)	//값 비교
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
	size_t size, int(*compar)(const void*, const void*))	//이진검색함수(찾을 값 / 배열/ 요소개수/ 요소크기/ 비교함수)
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
		case 1:		//오른쪽 서치
			head = pivot + 1;

			if (head < 0)
				head = 0;
			int_cmp((int*)key, &tmp[pivot]);
			break;

		case 0:		//값을 찾았을 때
			//선형검색
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

		case -1:	//왼쪽 서치
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
		puts("bsearch함수를 사용하여 검색");
		cout << "요소 개수 : ";
		cin >> nx;
		x = (int*)calloc(nx, sizeof(int));
	
		cout << "오름차순으로 입력하세요.\n";
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
		cout << "검색 값 : ";
		cin >> ky;
	
		p = (int*)bsearchx(&ky, x, nx, sizeof(int),
			(int(*)(const void*, const void*)) int_cmp);
	
		if (p == NULL)
			cout << "검색에 실패했습니다.";
		else
			printf("%d은(는) x[%d]에 있습니다.\n", ky, (int)(p - x));
	
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
//		{"김영준", 179, 79},
//		{ "박현규", 172, 63 },
//		{ "이수진", 176, 52 },
//		{ "최윤미", 165, 51 },
//		{ "함진아", 181, 73 },
//		{ "홍연의", 172, 84 }
//	};
//
//	int nx = sizeof(x) / sizeof(x[0]);
//	int retry;
//	puts("이름으로 검색합니다.");
//
//	do
//	{
//		Person temp, *p;
//		cout << "이름 : ";
//		cin >> temp.name;
//
//		p = (Person*)bsearch(&temp, x, nx, sizeof(Person),
//			(int(*)(const void*, const void*))npcmp);
//
//		if (p == NULL)
//			cout << "검색에 실패했습니다.";
//		else
//		{
//			cout << "검색 성공! 아래요소를 찾았습니다.";
//			printf("x[%d] : %s %dcm %dkg\n",
//				(int)(p-x), p->name, p->height, p->weight);
//		}
//
//		cout << "다시 검색할까요? (1)예 (2)아니오 : ";
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
//	cout << "덧셈표\n";
//	kuku(sum);
//	cout << "\n곱셈표\n";
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
//	puts("bsearch함수를 사용하여 검색");
//	cout << "요소 개수 : ";
//	cin >> nx;
//	x = (int*)calloc(nx, sizeof(int));
//
//	cout << "오름차순으로 입력하세요.\n";
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
//	cout << "검색 값 : ";
//	cin >> ky;
//
//	p = (int*)bsearch(&ky, x, nx, sizeof(int),
//		(int(*)(const void*, const void*))int_cmp);
//
//	if (p == NULL)
//		cout << "검색에 실패했습니다.";
//	else
//		printf("%d은(는) x[%d]에 있습니다.\n", ky, (int)(p - x));
//
//	free(x);
//}

//int main()
//{
//	string pwd;
//	int alpha = 0, num = 0, others = 0;
//
//	cout << "비밀번호를 입력하세요 : ";
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
//	cout << "단어들을 입력하시오 (끝내려면 q) : ";
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
//	cout << "모음으로 시작하는 단어 수 : " << moum << endl;
//	cout << "자음으로 시작하는 단어 수 : " << jaum << endl;
//	cout << "기타 : " << others << endl;
//}

//int main()
//{
	/*char fileName[SIZE];
	ifstream inFile;
	cout << "데이터 파일의 이름을 입력하시오 : ";
	cin.getline(fileName, SIZE);
	inFile.open(fileName);
	if (!inFile.is_open())
	{
		cout << fileName << "파일을 열 수 없습니다." << endl;
		cout << "프로그램을 종료합니다.\n";
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
		cout << "파일의 끝입니다.";
	else if (inFile.fail())
		cout << "데이터 불일치로 입력이 종료됩니다.\n";
	else
		cout << "알 수 없는 이유로 입력이 종료되었습니다.";

	if (count == 0)
		cout << "데이터가 없습니다.";
	else
	{
		cout << "읽은 항목의 개수 : " << count << endl;
		cout << "합계 : " << sum << endl;
		cout << "평균 : " << sum/count << endl;
	}
	inFile.close();*/

	/*char automobile[50];
	int year;
	double a_price;
	double d_price;

	ofstream outFile;
	outFile.open("carInfo.txt");

	cout << "자동차 메이커와 차종을 입력하세요 : ";
	cin.getline(automobile, 50);
	cout << "연식을 입력하세요 : ";
	cin >> year;
	cout << "구입 가격을 입력하세요 : ";
	cin >> a_price;
	d_price = 0.913*a_price;

	cout << fixed;
	cout.precision(2);
	cout.setf(ios_base::showpoint);
	cout << "메이커와 차종 : " << automobile <<  endl;
	cout << "연식 : " << year << endl;
	cout << "구입 가격 $" << a_price << endl;
	cout << "현재 가격 $" << d_price << endl;

	outFile << fixed;
	outFile.precision(2);
	outFile.setf(ios_base::showpoint);
	outFile << "메이커와 차종 : " << automobile << endl;
	outFile << "연식 : " << year << endl;
	outFile << "구입 가격 $" << a_price << endl;
	outFile << "현재 가격 $" << d_price << endl;

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
//			cout << "사장님은 오늘 회사에 가셨습니다.";
//			break;
//		case 4:
//			comfort();
//			break;
//
//		default:
//			cout << "선택 x";
//		}
//		showmenu();
//		cin >> choice;
//	}
//	cout << "프로그램 종료";
//}
//
//void showmenu()
//{
//	cout << "1, 2, 3, 4, 5번중에 하나를 선택 : \n";
//	"1) 경고음\t2) 보고서\n"
//		"3) 알리바이\t2) 격려사\n"
//		"5) 종료\n";
//}
//
//void report()
//{
//	cout << "이번 분기는 경영실적이 아주 좋습니다.\n"
//			"판매량은 120% 늘어났고, 비용은 35% 줄었습니다.\n";
//}
//
//void comfort()
//{
//	cout << "최고의 CEO\n";
//}

//int main()
//{
//	cout << "분석할 테스트를 입력하십시오. "
//		"입력의 끝을 @로 표시하십시오\n";
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
//	cout << "네 개 점의 좌표를 입력하세요 : ";
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
//		cout << "교차점 x : " << x << " y : " << y << endl;
//	else
//		cout << "교차점이 없습니다.";
//}