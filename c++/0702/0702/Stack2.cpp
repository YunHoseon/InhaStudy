//#include "Stack2.h"
//
//int main()
//{
//	Stack2<string> st;
//	char ch;
//	string po;
//
//	cout << "�ֹ����� �߰��Ϸ��� A, �ֹ����� ó���Ϸ��� P, \n" << "�����Ϸ��� Q�� �Է��Ͻʽÿ�. : \n";
//	while (cin >> ch && toupper(ch) != 'Q')
//	{
//		while (cin.get() != '\n')
//			continue;
//		if (!isalpha(ch))
//		{
//			cout << '\a';
//			continue;
//		}
//
//		switch (ch)
//		{
//		case 'A':
//		case 'a':
//			cout << "�߰��� �ֹ����� ��ȣ�� �Է��Ͻʽÿ� : ";
//			cin >> po;
//			if (st.isFull())
//				cout << "������ ���� ���ֽ��ϴ�.\n";
//			else
//				st.push(po);
//			break;
//
//		case 'P':
//		case 'p':
//			if (st.isEmpty())
//				cout << "������ ����ֽ��ϴ�.\n";
//			else
//			{
//				st.pop(po);
//				cout << "#" << po << "�ֹ����� ó���߽��ϴ�.\n";
//				break;
//			}
//		}
//		cout << "�ֹ����� �߰��Ϸ��� A, �ֹ����� ó���Ϸ��� P, \n" << "�����Ϸ��� Q�� �Է��ϼ���.\n";
//	}
//	cout << "���α׷��� �����մϴ�.\n";
//}
