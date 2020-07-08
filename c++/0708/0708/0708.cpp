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
		cout << "������ ã�ҽ��ϴ�.\n";

		f.seekg(0, ios::end);
		fileSize = f.tellg();
		f.seekg(0, ios::beg);

		while (fileSize > 0)
		{
			f.read(szBuffer, _size);
			copyF.open(_fileName + "(" + to_string(cnt) + ")", ios_base::out | ios_base::binary);

			if (!copyF.is_open())
				cout << "ī�� ����" << endl;

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
		cout << "������ ���������ʽ��ϴ�.\n";
		exit(1);
	}	
	cout << "���� �и� ����!" << endl;
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
	cout << "���� ��ġ�� ����!" << endl;

	delete szBuffer;
}

//int main()
//{
//	string fileName;
//	string fileName2;
//	int fileNum = 0;
//	int size = 0;
//
//	cout << "������ �̸��� �Է��ϼ��� : ";
//	cin >> fileName;
//	cout << "���� ����� �Է��ϼ��� : ";
//	cin >> size;
//
//	FileSplit(fileName, size);
//
//	cout << "��ġ���� ������ ������ �Է��ϼ��� : ";
//	cin >> fileNum;
//	cout << "��ġ���� ������ �̸��� �Է��ϼ��� : ";
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
//		cout << file << " ������ ���� ������ ������ �����ϴ�. : \n";
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
//			cerr << file << "������ �дٰ� ���� �߻�.\n";
//			exit(EXIT_FAILURE);
//		}
//	}
//	else
//	{
//		cerr << file << "������ �� �� �����ϴ�. ����.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	cout << "������ ���ڵ� ��ȣ�� �Է��Ͻʽÿ� : ";
//	long rec;
//	cin >> rec;
//	eatline();
//
//	if (rec < 0 || rec >= ct)
//	{
//		cerr << "�߸��� ���ڵ� ��ȣ�Դϴ�. ����.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	streampos place = rec * sizeof pl;
//	finout.seekg(place);
//
//	if (finout.fail())
//	{
//		cerr << "���ڵ带 ã�ٰ� ���� �߻�.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	finout.read((char*)&pl, sizeof pl);
//	cout << "���� ���ڵ��� ���� : \n";
//	cout << rec << " : " << setw(LIM) << pl.name << ": "
//		<< setprecision(0) << setw(12) << pl.population
//		<< setprecision(2) << setw(6) << pl.g << endl;
//
//	if (finout.eof())
//		finout.clear();
//
//	cout << "�༺�� �̸��� �Է��Ͻʽÿ� : ";
//	cin.get(pl.name, LIM);
//	eatline();
//	cout << "�༺�� �α��� �Է��Ͻʽÿ� : ";
//	cin >> pl.population;
//	cout << "�༺�� �߷°��ӵ��� �Է��Ͻʽÿ� : ";
//	cin >> pl.g;
//	finout.seekp(place);
//	finout.write((char*)&pl, sizeof pl);
//
//	if (finout.fail())
//	{
//		cerr << "���ٰ� ���� �߻�.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	ct = 0;
//	finout.seekg(0);
//	cout << file << " ������ ������ ������ ������ �����ϴ� : \n";
//
//	while (finout.read((char*) &pl, sizeof pl))
//	{
//		cout << ct++ << " : " << setw(LIM) << pl.name << ": "
//			<< setprecision(0) << setw(12) << pl.population
//			<< setprecision(2) << setw(6) << pl.g << endl;
//	}
//	finout.close();
//	cout << "���α׷��� �����մϴ�.\n";
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
//		cout << file << " ������ ���� ������ ������ �����ϴ�. : \n";
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
//	cout << "�༺�� �̸��� �Է��Ͻʽÿ�(�������� �� �� �Է�) : \n";
//	cin.get(pl.name, 20);
//	while (pl.name[0] != '\0')
//	{
//		eatline();
//		cout << "�༺�� �α��� �Է��Ͻʽÿ� : ";
//		cin >> pl.population;
//		cout << "�༺�� �߷°��ӵ��� �Է��Ͻʽÿ� : ";
//		cin >> pl.g;
//		eatline();
//		fout.write((char*)&pl, sizeof pl);
//		cout << "�༺�� �̸��� �Է��Ͻʽÿ� (�������� �� �� �Է�) : \n";
//		cin.get(pl.name, 20);
//	}
//	fout.close();
//
//	fin.clear();
//	fin.open(file, ios_base::in | ios_base::binary);
//
//	if (fin.is_open())
//	{
//		cout << file << " ������ ������ ������ ������ �����ϴ� : \n";
//		
//		while (fin.read((char*) &pl, sizeof pl))
//		{
//			cout << setw(20) << pl.name << ": "
//				<< setprecision(0) << setw(12) << pl.population
//				<< setprecision(2) << setw(6) << pl.g << endl;
//		}
//		fin.close();
//	}
//	cout << "���α׷��� �����մϴ�.\n";
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
//		cout << file << " ������ ���� ������ ������ �����ϴ� : \n";
//		while (fin.get(ch))
//			cout << ch;
//		fin.close();
//	}
//
//	ofstream fout(file, ios_base::out | ios_base::app);
//	
//	if(!fout.is_open())
//	{
//		cerr << "����� ���� " << file << "������ �� �� �����ϴ�.\n";
//		exit(EXIT_FAILURE);
//	}
//
//	cout << "���ο� �մ� �̸����� �Է��Ͻʽÿ� (�������� �� �� �Է�) : \n";
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
//		cout << file << " ������ ������ ������ ������ �����ϴ�.\n";
//		while (fin.get(ch))
//		{
//			cout << ch;
//		}
//		cout << "���α׷��� �����մϴ�.\n";
//	}
//}

//int main()
//{
//	string filename;
//	cout << "�� ������ ���� �̸��� �Է��Ͻʽÿ� : ";
//	cin >> filename;
//
//	ofstream fout(filename.c_str());
//
//	fout << "��й�ȣ ���⿡ �����Ͻʽÿ�.\n";
//	cout << "��й�ȣ�� �Է��Ͻʽÿ� : ";
//	float secret;
//	cin >> secret;
//	fout << "������ ��й�ȣ�� " << secret << "�Դϴ�.\n";
//	fout.close();
//
//	ifstream fin(filename.c_str());
//	cout << filename << "������ ������ ������ �����ϴ� : \n";
//	char ch;
//	while (fin.get(ch))
//	{
//		cout << ch;
//	}
//	cout << "���α׷��� �����մϴ�.\n";
//	fin.close();
//}

//const int Limit = 255;
//
//int main()
//{
//	char input[Limit];
//
//	cout << "getline()�� ó���� ���ڿ��� �Է��Ͻʽÿ� : \n";
//	cin.getline(input, Limit, '#');
//	cout << "������ ���� �Է��ϼ̽��ϴ� : \n";
//	cout << input << "\n1�ܰ�Ϸ�\n";
//
//	char ch;
//	cin.get(ch);
//	cout << "���� �Է� ���ڴ� " << ch << "�Դϴ�." << endl;
//
//	if (ch != '\n')
//		cin.ignore(Limit, '\n');
//
//	cout << "get()�� ó���� ���ڿ��� �Է��Ͻʽÿ� : \n";
//	cin.getline(input, Limit, '#');
//	cout << "������ ���� �Է��ϼ̽��ϴ� : \n";
//	cout << input << "\n2�ܰ�Ϸ�\n";
//
//	cin.get(ch);
//	cout << "���� �Է� ���ڴ� " << ch << "�Դϴ�." << endl;
//}

//int main()
//{
//	cin.exceptions(ios_base::failbit);
//	cout << "���� �Է��Ͻʽÿ� : ";
//	int sum = 0;
//	int input;
//
//	while (cin >> input)
//	{
//		sum += input;
//	}
//
//	cout << "���������� �Է��� �� = " << input << endl;
//	cout << "�հ� : " << sum << endl;
//
//	if (cin.fail() && cin.eof())
//	{
//		cin.clear();
//		while (!isspace(cin.get()))
//			continue;
//	}
//	else
//	{
//		cout << "����� �� �����ϴ�!\n";
//		exit(1);
//	}
//	cout << "���� �ϳ��� ���� �Է��Ͻʽÿ� : ";
//	cin >> input;
//}

//int main()
//{
//	cout << fixed << right;
//	cout << setw(6) << "N" << setw(14) << "������" << setw(15) << "��������\n";
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
//	cout << "���� ���� : \n";
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
//	cout << "����(internal)���� : \n";
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
//	cout << "������ ���� : \n";
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
//	cout << "������ ���� : ";
//	cout.setf(ios_base::showpos);
//	cout << temperature << endl;
//
//	cout << "���α׷��ӵ鿡�� �� ���� \n";
//	cout << hex << temperature << endl;
//	cout.setf(ios_base::uppercase);
//	cout.setf(ios_base::showbase);
//
//	cout << "�Ǵ� \n";
//	cout << temperature << endl;
//	cout << true << "!�� ���� ";
//	cout.setf(ios_base::boolalpha);
//	cout << true << "�̴�.\n";
//}

//int main()
//{
//	float price1 = 20.40;
//	float price2 = 1.9 + 8.0 / 9.0;
//
//	cout.setf(ios_base::showpoint);
//	cout << "\"�տ��� ����\" $" << price1 << "!\n";
//	cout << "\"����� ����\" $" << price2 << "!\n";
//
//	cout.precision(2);
//	cout << "\"�տ��� ����\" $" << price1 << "!\n";
//	cout << "\"����� ����\" $" << price2 << "!\n";
//}

//int main()
//{
//	float price1 = 20.40;
//	float price2 = 1.9 + 8.0 / 9.0;
//
//	cout << "\"�տ��� ����\" $" << price1 << "!\n";
//	cout << "\"����� ����\" $" << price2 << "!\n";
//
//	cout.precision(2);
//	cout << "\"�տ��� ����\" $" << price1 << "!\n";
//	cout << "\"����� ����\" $" << price2 << "!\n";
//}

//int main()
//{
//	cout.fill('*');
//	const char *staff[2] = { "������", "�ڼ���" };
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
//	cout << "���� �ε��� ���� : \n";
//	int i;
//
//	for (i = 1; i <= len; i++)
//	{
//		cout.write(state2, i);
//		cout << endl;
//	}
//
//	cout << "���� �ε��� ���� : \n";
//	for (i = len;i > 0; i--)
//		cout.write(state2, i) << endl;
//
//	cout << "���ڿ� ���� �ʰ� : \n";
//	cout.write(state2, len+5) << endl;
//}