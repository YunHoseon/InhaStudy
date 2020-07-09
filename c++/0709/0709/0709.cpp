//#include<iostream>
//#include <string>
//#include <fstream>
//
//using namespace std;
//
//const int pswd = 5;
//
//string fileName;
//string newFileName;
//
//void EncodingFile()
//{
//	fstream f;
//	ofstream copyF;
//	char szBuffer = 0;
//
//	f.open(fileName, ios_base::in | ios_base::binary);
//
//	if (f.is_open())
//	{
//		cout << "파일을 찾았습니다.\n";
//
//		copyF.open(newFileName, ios_base::binary | ios_base::out);
//		if (!copyF.is_open())
//			cout << "카피 실패" << endl;
//
//		while (f.read(&szBuffer, 1))
//			copyF.write(&(szBuffer += pswd), 1);
//
//		f.close();
//		copyF.close();
//	}
//	cout << "파일 부호화 성공!" << endl;
//}
//
//void DecodingFile()
//{
//	fstream f;
//	ifstream copyF;
//	char szBuffer = 0;
//
//	copyF.open(newFileName, ios_base::binary | ios_base::in);
//
//	if (copyF.is_open())
//	{
//		cout << "파일을 찾았습니다.\n";
//
//		f.open(fileName, ios_base::out | ios_base::binary);
//		if (!f.is_open())
//			cout << "카피 실패" << endl;
//
//		while (copyF.read(&szBuffer, 1))
//			f.write(&(szBuffer -= pswd), 1);
//
//		f.close();
//		copyF.close();
//	}
//	cout << "파일 복호화 성공!" << endl;
//}
//
//int main()
//{
//	cout << "입력 파일 이름을 입력하세요 : ";
//	cin >> fileName;
//	cout << "출력 파일 이름을 입력하세요 : ";
//	cin >> newFileName;
//
//	EncodingFile();
//
//	cout << "부호화 된 파일의 이름을 입력하세요 : ";
//	cin >> newFileName;
//	cout << "복호화 파일의 이름을 입력하세요 : ";
//	cin >> fileName;
//
//	DecodingFile();
//}