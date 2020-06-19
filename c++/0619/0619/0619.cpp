#include "0619.h"

int main()
{
	string operations;
	CharStack *cs = new CharStack;
	CharQueue *cq = new CharQueue;

	StackInitialize(cs, 32);
	QueueInitialize(cq, 32);

	SplitStr(ReadFile(operations), cs, cq);
	StackPrint(cs);
	QueuePrint(cq);

}

string ReadFile(string s)
{
	ifstream in("data.txt");

	if (in.is_open())
	{
		in >> s;

		cout << "받은 문자열 : " << s << endl;
		return s;
	}
	else
		cout << "파일을 열 수 없습니다.";
}

void SplitStr(string s, CharStack *cs, CharQueue *cq)
{
	int i = 0;
	char* tmp = new char[s.size()+1];
	for (size_t i = 0; i < s.size()+1; i++)
	{
		tmp[i] = s[i];
	}

	while (i < s.size())
	{
		switch (tmp[i])
		{
		case '(':
			Push(cs, tmp[i]);
			break;

		case ')':
			break;

		case '+':
		case '-':
			while (cs->stk[cs->ptr - 1] != '(')
			{
				char x;
				Pop(cs, &x);
				EnQue(cq, x);
			}
			Push(cs, tmp[i]);
			break;

		case '*':
		case '/':
			Push(cs, tmp[i]);
			break;

		default:
			if (isdigit(tmp[i]) != 0)	//숫자라면
			{
				for(int i = 0; i < )
				//if (isdigit(tmp[i + 1]) != 0)	//다음 문자도 숫자라면
				//{

				//}
				//else
				//	EnQue(cq, tmp[i]);
			}
			break;
		}
		i++;
	}

}

int StackInitialize(CharStack * s, char max)
{
	s->stk = new char[max];
	s->ptr = 0;
	s->max = max;

	return 0;
}

int Push(CharStack * s, char x)
{
	if (s->ptr >= s->max)
		return -1;

	s->stk[s->ptr++] = x;
	return 0;
}

int Pop(CharStack * s, char * x)
{
	if (s->ptr <= 0)
		return -1;

	*x = s->stk[s->ptr - 1];
	s->ptr--;
	return 0;
}

int StackPeek(const CharStack * s, char *x)
{
	if (s->ptr <= 0)
		return -1;
	*x = s->stk[s->ptr - 1];

	return 0;
}

void StackClear(CharStack * s)
{
	s->ptr = 0;
}

int StackSearch(const CharStack * s, int x)
{
	for (int i = s->ptr - 1; i >= 0; i++)
	{
		if (s->stk[i] == x)
			return i;
	}
	return -1;
}

void StackPrint(const CharStack * s)
{
	cout << "스택 값 : ";
	for (int i = 0; i < s->ptr; i++)
		cout << s->stk[i];
	cout << endl;
}

void StackTerminate(CharStack * s)
{
	if (s->stk != NULL)
		free(s->stk);
	s->max = 0;
	s->ptr = 0;
}

/////////////////////////////////////////////////

int QueueInitialize(CharQueue * iq, char max)
{
	iq->que = new char[max];
	iq->head = 0;
	iq->tail = 0;
	iq->num = 0;

	iq->max = max;

	return 0;
}

int EnQue(CharQueue * iq, char x)
{
	if (iq->num == iq->max)
		return -1;

	iq->num++;
	iq->que[iq->tail++] = x;

	if (iq->tail == iq->max)
		iq->tail = 0;
	return 0;
}

int Deque(CharQueue * iq, char * x)
{
	if (iq->num <= 0)
		return -1;

	iq->num--;
	*x = iq->que[iq->head++];

	if (iq->head == iq->max)
		iq->head = 0;
}

int QueuePeek(const CharQueue * iq, char * x)
{
	if (iq->num <= 0)
		return -1;

	*x = iq->que[iq->head];
	return 0;
}

void QueueClear(CharQueue * iq)
{
	iq->num = 0;
	iq->head = 0;
	iq->tail = 0;
}

int QueueSearch(const CharQueue * iq, int x)
{
	for (int i = 0; i < iq->num; i++)
	{
		if (x == iq->que[(i + iq->head) % iq->max])
			return i;
	}
	return -1;
}

void QueuePrint(const CharQueue * iq)
{
	cout << "큐 값 : ";
	for (int i = 0; i < iq->num; i++)
	{
		cout << iq->que[(i + iq->head) % iq->max] << " ";
	}
	cout << endl;
}

void QueueTerminate(CharQueue * iq)
{
	if (iq->que != NULL)
		delete iq->que;

	iq->head = 0;
	iq->tail = 0;
	iq->num = 0;
	iq->max = 0;
}

//template <typename T>
//T Max5(T arr[5])
//{
//	T max = arr[0];
//	for (int i = 0; i < 5; i++)
//	{
//		if (arr[i] > max)
//		{
//			max = arr[i];
//		}
//	}
//	return max;
//}
//
//template <typename T> 
//T MaxN(T *arr, int num)
//{
//	T max = arr[0];
//	for (int i = 0; i < num; i++)
//	{
//		if (arr[i] > max)
//		{
//			max = arr[i];
//		}
//	}
//	return max;
//}
//
//template<>
//char* MaxN<char*>(char** chArr, int num)
//{
//	size_t maxLen = strlen(chArr[0]);
//	int maxIdx = 0;
//
//	for (int i = 0; i < num; i++)
//	{
//		if (strlen(chArr[i]) > maxLen)
//		{
//			maxLen = strlen(chArr[i]);
//			maxIdx = i;
//		}
//	}
//	return chArr[maxIdx];
//}
//
//int main()
//{
//	/*int iArr[5] = { 1,2,3,4,5 };
//	double dArr[5] = { 1.2222, 2.33333, 3.4444, 1, 6.7542};
//
//	cout << "iArr의 가장 큰 항목 : "<< Max5(iArr) << endl;
//	cout << "dArr의 가장 큰 항목 : " << Max5(dArr) << endl;*/
//
//	int iArr[6] = { 5, 6, 1, 3, 7, 2 };
//	double dArr[4] = { 5.777, 2.789, 666, 41 };
//	char **chArr = new char*[32];
//	
//	for (int i = 0; i < 5; i++)
//	{
//		chArr[i] = new char[32];
//		cout << "문자열을 입력하세요 : ";
//		cin >> chArr[i];
//	}
//
//	for (int j = 0; j < 5; j++)
//	{
//		MaxN(*chArr, 5);
//	}
//
//	/*for (int i = 0; i < 5; i++)
//	{
//		cout << chArr[i] << " ";
//	}
//	cout << endl;*/
//
//	cout << "iArr의 가장 큰 항목 : " << MaxN(iArr, sizeof(iArr)/sizeof(int)) << endl;
//	cout << "dArr의 가장 큰 항목 : " << MaxN(dArr, sizeof(dArr) / sizeof(double)) << endl;
//	cout << "chArr의 가장 큰 항목 : " << MaxN(chArr, 5) << endl;
//}

//template <class T>
//T lesser(T a, T b)
//{
//	return a < b ? a : b;
//}
//
//int lesser(int a, int b)
//{
//	a = a < 0 ? -a : a;
//	b = b < 0 ? -b : b;
//	return a < b ? a : b;
//}
//
//int main()
//{
//	int m = 20;
//	int n = -30;
//	double x = 15.5;
//	double y = 25.9;
//
//	cout << lesser(m, n) << endl;
//	cout << lesser(x, y) << endl;
//	cout << lesser<>(m, n) << endl;
//	cout << lesser<int>(x, y) << endl;
//}

//template <typename T>
//void Swap(T &a, T &b);
//
//typedef struct JOB
//{
//	char name[40];
//	double salary;
//	int floor;
//}JOB;
//
//template <>void Swap<JOB>(JOB &j1, JOB &j2);
//void Show(JOB &j);
//
//int main()
//{
//	cout.precision(2);
//	cout.setf(ios::fixed, ios::floatfield);
//	int i = 10, j = 20;
//	cout << "i, j = " << i << ", " << j << ".\n";
//	cout << "컴파일러가 생성한 int형 교환기를 사용하면\n";
//	Swap(i, j);
//	cout << "이제 i, j = " << i << ", " << j << ".\n";
//
//	JOB sue = { "Susan Yaffee", 73000.60, 7 };
//	JOB sidney = { "Sidney Taffee", 78060.72, 9 };
//	cout << " job 교환전 : \n";
//	Show(sue);
//	Show(sidney);
//	Swap(sue, sidney);
//	cout << "job 교환후 : \n";
//	Show(sue);
//	Show(sidney);
//}
//
//template <typename T>
//void Swap(T &a, T &b)
//{
//	T temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//template <>void Swap<JOB>(JOB &j1, JOB &j2)
//{
//	double t1;
//	int t2;
//	
//	t1 = j1.salary;
//	j1.salary = j2.salary;
//	j2.salary = t1;
//
//	t2 = j1.floor;
//	j1.floor = j2.floor;
//	j2.floor = t2;
//}
//
//void Show(JOB &j)
//{
//	cout << j.name << " : (" << j.floor << "층에 거주) "
//		<< "$" << j.salary << endl;
//}

//template <typename T>
//void Swap(T &a, T &b);
//
//template <typename T>
//void Swap(T *a, T *b, int n);
//
//void Show(int a[]);
//const int Lim = 8;
//
//int main()
//{
//	int i = 10, j = 20;
//	cout << "i, j = " << i << ", " << j << ".\n";
//	cout << "컴파일러가 생성한 int형 교환기를 사용하면\n";
//	Swap(i, j);
//	cout << "이제 i, j = " << i << ", " << j << ".\n";
//
//	int d1[Lim] = { 0,7,0,4,1,7,7,6 };
//	int d2[Lim] = { 0,6,2,0,1,9,6,9 };
//	cout << "원본 배열 : \n";
//	Show(d1);
//	Show(d2);
//	Swap(d1, d2, Lim);
//	cout << "교환된 배열 : \n";
//	Show(d1);
//	Show(d2);
//}
//
//template <typename T>
//void Swap(T &a, T &b)
//{
//	T temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//template <typename T>
//void Swap(T *a, T *b, int n)
//{
//	T temp;
//	for(int i = 0; i < n; i++)
//	{
//		temp = a[i];
//		a[i] = b[i];
//		b[i] = temp;
//	}
//}
//
//void Show(int a[])
//{
//	cout << a[0] << a[1] << " / ";
//	cout << a[2] << a[3] << " / ";
//	for (int i = 4; i < Lim; i++)
//		cout << a[i];
//	cout << endl;
//}

//template <typename Any>
//void Swap(Any &a, Any &b);
//
//int main()
//{
//	int i = 10;
//	int j = 20;
//	cout << "i, j = " << i << ", " << j << ".\n";
//	cout << "컴파일러가 생성한 int형 교환기를 사용하면\n";
//	Swap(i, j);
//	cout << "이제 i, j = " << i << ", " << j << ".\n";
//
//	double x = 24.5;
//	double y = 81.7;
//	cout << "x, y = " << x << ", " << y << ".\n";
//	cout << "컴파일러가 생성한 double형 교환기를 사용하면\n";
//	Swap(x, y);
//	cout << "이제 x, y = " << x << ", " << y << ".\n";
//}
//
//template <typename Any>
//void Swap(Any &a, Any &b)
//{
//	Any temp;
//	temp = a;
//	a = b;
//	b = temp;
//}

//unsigned long left(unsigned long num, unsigned ct);
//char *left(const char *str, int n = 1);
//
//int main()
//{
//	char *trip = "Hawaii!!";
//	unsigned long n = 12345678;
//	int i;
//	char *temp;
//
//	for (i = 0; i < 10; i++)
//	{
//		cout << left(n, i) << endl;
//		temp = left(trip, i);
//		cout << temp << endl;
//		delete[] temp;
//	}
//}
//
//unsigned long left(unsigned long num, unsigned ct)
//{
//	unsigned digits = 1;
//	unsigned long n = num;
//
//	if (ct == 0 || num == 0)
//		return 0;
//	while (n /= 10)
//		digits++;
//
//	if (digits > ct)
//	{
//		ct = digits - ct;
//		while (ct--)
//			num /= 10;
//		return num;
//	}
//	else
//		return num;
//}
//
//char *left(const char *str, int n)
//{
//	if (n < 0)
//		n = 0;
//	char *p = new char[n + 1];
//	int i;
//
//	for (i = 0; i < i<n && str[i]; i++)
//		p[i] = str[i];
//	while (i <= n)
//		p[i++] = '\0';
//	return p;
//}