#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <exception>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void FileSplit(string _fileName, int _size)
{
	fstream f;
	ofstream copyF;
	int fileSize;
	int cnt = 1;
	char *szBuffer = new char[_size];

	f.open(_fileName, ios_base::in | ios_base::binary);
	
	if (f.is_open())
	{
		cout << "파일을 찾았습니다.\n";

		f.seekg(0, ios::end);
		fileSize = f.tellg();
		f.seekg(0, ios::beg);

		while (fileSize > 0)
		{
			f.read(szBuffer, _size);
			copyF.open(_fileName + "(" + to_string(cnt) + ")", ios_base::out | ios_base::binary);

			if (!copyF.is_open())
				cout << "카피 실패" << endl;

			if (fileSize - _size >= 0)
				copyF.write(szBuffer, _size);
			else
				copyF.write(szBuffer, fileSize % _size);

			fileSize -= _size;
			cnt++;
			copyF.close();
		}
		f.close();
	}
	else
	{
		cout << "파일이 존재하지않습니다.\n";
		exit(1);
	}	
	cout << "파일 분리 성공!" << endl;
	delete szBuffer;
}

void FileMerge(string _fileName2, int fileNum, string _filename)
{
	fstream copyF;
	ofstream mergeF;
	int fileSize;

	copyF.open(_filename + "(" + to_string(1) + ")", ios_base::in | ios_base::binary);

	copyF.seekg(0, ios::end);
	fileSize = copyF.tellg();
	copyF.seekg(0, ios::beg);

	copyF.close();

	char *szBuffer = new char[fileSize];

	mergeF.open(_fileName2, ios_base::out | ios_base::binary);

	for (int i = 1; i <= fileNum; i++)
	{
		copyF.open(_filename + "(" + to_string(i) + ")", ios_base::in | ios_base::binary);

		copyF.seekg(0, ios::end);
		fileSize = copyF.tellg();
		copyF.seekg(0, ios::beg);

		copyF.read(szBuffer, fileSize);

		mergeF.write(szBuffer, fileSize);
		copyF.close();
	}
	mergeF.close();
	cout << "파일 합치기 성공!" << endl;

	delete szBuffer;
}

//int main()
//{
//	string fileName;
//	string fileName2;
//	int fileNum = 0;
//	int size = 0;
//
//	cout << "파일의 이름을 입력하세요 : ";
//	cin >> fileName;
//	cout << "파일 사이즈를 입력하세요 : ";
//	cin >> size;
//
//	FileSplit(fileName, size);
//
//	cout << "합치려는 파일의 개수를 입력하세요 : ";
//	cin >> fileNum;
//	cout << "합치려는 파일의 이름을 입력하세요 : ";
//	cin >> fileName2;
//
//	FileMerge(fileName2, fileNum, fileName);
//}

//const int LIM = 20;
//
//struct planet
//{
//	char name[LIM];
//	double population;
//	double g;
//};
//
//const char *file = "planets.dat";
//inline void eatline() { while (cin.get() != '\n') continue; }
//
//int main()
//{
//	planet pl;
//	cout << fixed;
//
//	fstream finout;
//	finout.open(file, ios_base::in | ios_base::out | ios_base::binary);
//
//	int ct = 0;
//	if (finout.is_open())
//	{
//		finout.seekg(0);
//		cout << file << " 파일의 현재 내용은 다음과 같습니다. : \n";
//
//		while (finout.read((char*)&pl, sizeof (pl)))
//		{
//			cout << ct++ << " : " << setw(LIM) << pl.name << " : "
//				<< setprecision(0) << setw(12) << pl.population
//				<< setprecision(2) << setw(6) << pl.g << endl;
//		}
//		if (finout.eof())
//			finout.clear();
//		else
//		{
//			cerr << file << "파일을 읽다가 에러 발생.\n";
//			exit(EXIT_FAILURE);
//		}
//	}
//	else
//	{
//		cerr << file << "파일을 열 수 없습니다. 종료.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	cout << "수정할 레코드 번호를 입력하십시오 : ";
//	long rec;
//	cin >> rec;
//	eatline();
//
//	if (rec < 0 || rec >= ct)
//	{
//		cerr << "잘못된 레코드 번호입니다. 종료.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	streampos place = rec * sizeof pl;
//	finout.seekg(place);
//
//	if (finout.fail())
//	{
//		cerr << "레코드를 찾다가 에러 발생.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	finout.read((char*)&pl, sizeof pl);
//	cout << "현재 레코드의 내용 : \n";
//	cout << rec << " : " << setw(LIM) << pl.name << ": "
//		<< setprecision(0) << setw(12) << pl.population
//		<< setprecision(2) << setw(6) << pl.g << endl;
//
//	if (finout.eof())
//		finout.clear();
//
//	cout << "행성의 이름을 입력하십시오 : ";
//	cin.get(pl.name, LIM);
//	eatline();
//	cout << "행성의 인구를 입력하십시오 : ";
//	cin >> pl.population;
//	cout << "행성의 중력가속도를 입력하십시오 : ";
//	cin >> pl.g;
//	finout.seekp(place);
//	finout.write((char*)&pl, sizeof pl);
//
//	if (finout.fail())
//	{
//		cerr << "쓰다가 에러 발생.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	ct = 0;
//	finout.seekg(0);
//	cout << file << " 파일의 개정된 내용은 다음과 같습니다 : \n";
//
//	while (finout.read((char*) &pl, sizeof pl))
//	{
//		cout << ct++ << " : " << setw(LIM) << pl.name << ": "
//			<< setprecision(0) << setw(12) << pl.population
//			<< setprecision(2) << setw(6) << pl.g << endl;
//	}
//	finout.close();
//	cout << "프로그램을 종료합니다.\n";
//}

//inline void eatline() { while (cin.get() != '\n') continue; }
//struct planet
//{
//	char name[20];
//	double population;
//	double g;
//};
//
//const char *file = "planets.dat";
//
//int main()
//{
//	planet pl;
//	cout << fixed << right;
//
//	ifstream fin;
//	fin.open(file, ios_base::in | ios_base::binary);
//
//	if (fin.is_open())
//	{
//		cout << file << " 파일의 현재 내용은 다음과 같습니다. : \n";
//		while (fin.read((char*) &pl, sizeof(pl)))
//		{
//			cout << setw(20) << pl.name << ": "
//				<< setprecision(0) << setw(12) << pl.population
//				<< setprecision(2) << setw(6) << pl.g << endl;
//		}
//		fin.close();
//	}
//
//	ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);
//
//	cout << "행성의 이름을 입력하십시오(끝내려면 빈 줄 입력) : \n";
//	cin.get(pl.name, 20);
//	while (pl.name[0] != '\0')
//	{
//		eatline();
//		cout << "행성의 인구를 입력하십시오 : ";
//		cin >> pl.population;
//		cout << "행성의 중력가속도를 입력하십시오 : ";
//		cin >> pl.g;
//		eatline();
//		fout.write((char*)&pl, sizeof pl);
//		cout << "행성의 이름을 입력하십시오 (끝내려면 빈 줄 입력) : \n";
//		cin.get(pl.name, 20);
//	}
//	fout.close();
//
//	fin.clear();
//	fin.open(file, ios_base::in | ios_base::binary);
//
//	if (fin.is_open())
//	{
//		cout << file << " 파일의 개정된 내용은 다음과 같습니다 : \n";
//		
//		while (fin.read((char*) &pl, sizeof pl))
//		{
//			cout << setw(20) << pl.name << ": "
//				<< setprecision(0) << setw(12) << pl.population
//				<< setprecision(2) << setw(6) << pl.g << endl;
//		}
//		fin.close();
//	}
//	cout << "프로그램을 종료합니다.\n";
//}

//const char *file = "guests.txt";
//
//int main()
//{
//	char ch;
//	ifstream fin;
//	fin.open(file);
//
//	if (fin.is_open())
//	{
//		cout << file << " 파일의 현재 내용은 다음과 같습니다 : \n";
//		while (fin.get(ch))
//			cout << ch;
//		fin.close();
//	}
//
//	ofstream fout(file, ios_base::out | ios_base::app);
//	
//	if(!fout.is_open())
//	{
//		cerr << "출력을 위해 " << file << "파일을 열 수 없습니다.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	cout << "새로운 손님 이름들을 입력하십시오 (끝내려는 빈 줄 입력) : \n";
//	string name;
//
//	while (getline(cin, name) && name.size() > 0)
//	{
//		fout << name << endl;
//	}
//	fout.close();
//
//	fin.clear();
//	fin.open(file);
//	
//	if (fin.is_open())
//	{
//		cout << file << " 파일의 개정된 내용은 다음과 같습니다.\n";
//		while (fin.get(ch))
//		{
//			cout << ch;
//		}
//		cout << "프로그램을 종료합니다.\n";
//	}
//}

//int main()
//{
//	string filename;
//	cout << "새 파일을 위한 이름을 입력하십시오 : ";
//	cin >> filename;
//
//	ofstream fout(filename.c_str());
//
//	fout << "비밀번호 노출에 주의하십시오.\n";
//	cout << "비밀번호를 입력하십시오 : ";
//	float secret;
//	cin >> secret;
//	fout << "귀하의 비밀번호는 " << secret << "입니다.\n";
//	fout.close();
//
//	ifstream fin(filename.c_str());
//	cout << filename << "파일의 내용은 다음과 같습니다 : \n";
//	char ch;
//	while (fin.get(ch))
//	{
//		cout << ch;
//	}
//	cout << "프로그램을 종료합니다.\n";
//	fin.close();
//}

//const int Limit = 255;
//
//int main()
//{
//	char input[Limit];
//
//	cout << "getline()이 처리할 문자열을 입력하십시오 : \n";
//	cin.getline(input, Limit, '#');
//	cout << "다음과 같이 입력하셨습니다 : \n";
//	cout << input << "\n1단계완료\n";
//
//	char ch;
//	cin.get(ch);
//	cout << "다음 입력 문자는 " << ch << "입니다." << endl;
//
//	if (ch != '\n')
//		cin.ignore(Limit, '\n');
//
//	cout << "get()이 처리할 문자열을 입력하십시오 : \n";
//	cin.getline(input, Limit, '#');
//	cout << "다음과 같이 입력하셨습니다 : \n";
//	cout << input << "\n2단계완료\n";
//
//	cin.get(ch);
//	cout << "다음 입력 문자는 " << ch << "입니다." << endl;
//}

//int main()
//{
//	cin.exceptions(ios_base::failbit);
//	cout << "수를 입력하십시오 : ";
//	int sum = 0;
//	int input;
//
//	while (cin >> input)
//	{
//		sum += input;
//	}
//
//	cout << "마지막으로 입력한 값 = " << input << endl;
//	cout << "합계 : " << sum << endl;
//
//	if (cin.fail() && cin.eof())
//	{
//		cin.clear();
//		while (!isspace(cin.get()))
//			continue;
//	}
//	else
//	{
//		cout << "계속할 수 없습니다!\n";
//		exit(1);
//	}
//	cout << "새로 하나의 수를 입력하십시오 : ";
//	cin >> input;
//}

//int main()
//{
//	cout << fixed << right;
//	cout << setw(6) << "N" << setw(14) << "제곱근" << setw(15) << "네제곱근\n";
//
//	double root;
//	for (int n = 10; n <= 100; n += 10)
//	{
//		root = sqrt(double(n));
//		cout << setw(6) << setfill('.') << n << setfill(' ')
//			<< setw(12) << setprecision(3) << root
//			<< setw(14) << setprecision(4) << sqrt(root) << endl;
//	}
//}

//int main()
//{
//	cout.setf(ios_base::left, ios_base::adjustfield);
//	cout.setf(ios_base::showpos);
//	cout.setf(ios_base::showpoint);
//	cout.precision(3);
//
//	ios_base::fmtflags old = cout.setf(ios_base::scientific, ios_base::floatfield);
//	cout << "왼쪽 정렬 : \n";
//	long n;
//
//	for (n = 1; n <= 41; n += 10)
//	{
//		cout.width(4);
//		cout << n << "|";
//		cout.width(12);
//		cout << sqrt(double(n)) << "|\n";
//	}
//
//	cout.setf(ios_base::internal, ios_base::adjustfield);
//	cout.setf(old, ios_base::floatfield);
//
//	cout << "내부(internal)정렬 : \n";
//	for (n = 1; n <= 41; n += 10)
//	{
//		cout.width(4);
//		cout << n << "|";
//		cout.width(12);
//		cout << sqrt(double(n)) << "|\n";
//	}
//
//	cout.setf(ios_base::right, ios_base::adjustfield);
//	cout.setf(ios_base::fixed, ios_base::floatfield);
//
//	cout << "오른쪽 정렬 : \n";
//	for (n = 1; n <= 41; n += 10)
//	{
//		cout.width(4);
//		cout << n << "|";
//		cout.width(12);
//		cout << sqrt(double(n)) << "|\n";
//	}
//}

//int main()
//{
//	int temperature = 63;
//
//	cout << "오늘의 수온 : ";
//	cout.setf(ios_base::showpos);
//	cout << temperature << endl;
//
//	cout << "프로그래머들에게 그 값은 \n";
//	cout << hex << temperature << endl;
//	cout.setf(ios_base::uppercase);
//	cout.setf(ios_base::showbase);
//
//	cout << "또는 \n";
//	cout << temperature << endl;
//	cout << true << "!의 값은 ";
//	cout.setf(ios_base::boolalpha);
//	cout << true << "이다.\n";
//}

//int main()
//{
//	float price1 = 20.40;
//	float price2 = 1.9 + 8.0 / 9.0;
//
//	cout.setf(ios_base::showpoint);
//	cout << "\"손오공 인형\" $" << price1 << "!\n";
//	cout << "\"사오정 인형\" $" << price2 << "!\n";
//
//	cout.precision(2);
//	cout << "\"손오공 인형\" $" << price1 << "!\n";
//	cout << "\"사오정 인형\" $" << price2 << "!\n";
//}

//int main()
//{
//	float price1 = 20.40;
//	float price2 = 1.9 + 8.0 / 9.0;
//
//	cout << "\"손오공 인형\" $" << price1 << "!\n";
//	cout << "\"사오정 인형\" $" << price2 << "!\n";
//
//	cout.precision(2);
//	cout << "\"손오공 인형\" $" << price1 << "!\n";
//	cout << "\"사오정 인형\" $" << price2 << "!\n";
//}

//int main()
//{
//	cout.fill('*');
//	const char *staff[2] = { "윤성일", "박순용" };
//	long bonus[2] = { 900, 1350 };
//
//	for (int i = 0; i < 2; i++)
//	{
//		cout << staff[i] << ": $";
//		cout.width(7);
//		cout << bonus[i] << "\n";
//	}
//}

//int main()
//{
//	const char *state1 = "Florida";
//	const char *state2 = "Kansas";
//	const char *state3 = "Euphoria";
//	int len = strlen(state2);
//
//	cout << "루프 인덱스 증가 : \n";
//	int i;
//
//	for (i = 1; i <= len; i++)
//	{
//		cout.write(state2, i);
//		cout << endl;
//	}
//
//	cout << "루프 인덱스 감소 : \n";
//	for (i = len;i > 0; i--)
//		cout.write(state2, i) << endl;
//
//	cout << "문자열 길이 초과 : \n";
//	cout.write(state2, len+5) << endl;
//}