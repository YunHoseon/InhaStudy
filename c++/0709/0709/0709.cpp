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
//		cout << "������ ã�ҽ��ϴ�.\n";
//
//		copyF.open(newFileName, ios_base::binary | ios_base::out);
//		if (!copyF.is_open())
//			cout << "ī�� ����" << endl;
//
//		while (f.read(&szBuffer, 1))
//			copyF.write(&(szBuffer += pswd), 1);
//
//		f.close();
//		copyF.close();
//	}
//	cout << "���� ��ȣȭ ����!" << endl;
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
//		cout << "������ ã�ҽ��ϴ�.\n";
//
//		f.open(fileName, ios_base::out | ios_base::binary);
//		if (!f.is_open())
//			cout << "ī�� ����" << endl;
//
//		while (copyF.read(&szBuffer, 1))
//			f.write(&(szBuffer -= pswd), 1);
//
//		f.close();
//		copyF.close();
//	}
//	cout << "���� ��ȣȭ ����!" << endl;
//}
//
//int main()
//{
//	cout << "�Է� ���� �̸��� �Է��ϼ��� : ";
//	cin >> fileName;
//	cout << "��� ���� �̸��� �Է��ϼ��� : ";
//	cin >> newFileName;
//
//	EncodingFile();
//
//	cout << "��ȣȭ �� ������ �̸��� �Է��ϼ��� : ";
//	cin >> newFileName;
//	cout << "��ȣȭ ������ �̸��� �Է��ϼ��� : ";
//	cin >> fileName;
//
//	DecodingFile();
//}