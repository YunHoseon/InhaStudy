//#include "AcctABC.h"
//
//
//
//AcctABC::AcctABC(const string &s, long an, double bal)
//{
//	fullName = s;
//	acctNum = an;
//	balance = bal;
//}
//
//void AcctABC::Deposit(double amt)
//{
//	if (amt < 0)
//	{
//		cout << "���̳ʽ� �Ա��� ������ �ʽ��ϴ�." << endl;
//		cout << "�׷��� �Ա��� ��ҵǾ����ϴ�." << endl;
//	}
//	else
//		balance += amt;
//}
//
//
//AcctABC::~AcctABC()
//{
//}
//
//void AcctABC::Withdraw(double amt)
//{
//	balance -= amt;
//}
//
//AcctABC::Formatting AcctABC::SetFormat() const
//{
//	Formatting f;
//	f.flag =
//		cout.setf(ios_base::fixed, ios_base::floatfield);
//	f.pr = cout.precision(2);
//	return f;
//}
//
//void AcctABC::Restore(Formatting &f) const
//{
//	cout.setf(f.flag, ios_base::floatfield);
//	cout.precision(f.pr);
//}
//
//void Brass::Withdraw(double amt)
//{
//	if (amt < 0)
//	{
//		cout << "���̳ʽ� ������ ������ �ʽ��ϴ�." << endl;
//		cout << "�׷��� ������ ��ҵǾ����ϴ�." << endl;
//	}
//	else if (amt <= Balnace())
//		AcctABC::Withdraw(amt);
//	else
//		cout << "������ �䱸�� �ݾ� $ " << amt
//		<< "�� ���� �ܾ��� �ʰ��մϴ�.\n"
//		<< "�׷��� ������ ��ҵǾ����ϴ�.\n";
//}
//
//void Brass::ViewAcct() const
//{
//	Formatting f = SetFormat();
//	cout << "Brass �� : " << FullName() << endl;
//	cout << "���� ��ȣ : " << AcctNum() << endl;
//	cout << "���� �ܾ� : " << Balnace() << endl;
//	Restore(f);
//}
//
//BrassPlus::BrassPlus(const string & s, long an, double bal, double ml, double r)
//{
//	maxLoan = ml;
//	owesBank = 0.0;
//	rate = r;
//}
//
//BrassPlus::BrassPlus(const string & ba, double ml, double r) : AcctABC(ba)
//{
//	maxLoan = ml;
//	owesBank = 0.0;
//	rate = r;
//}
//
//void BrassPlus::ViewAcct() const
//{
//	Formatting f = SetFormat();
//
//	cout << "BrassPlus �� : " << FullName() << endl;
//	cout << "���� ��ȣ : " << AcctNum() << endl;
//	cout << "���� �ܾ� $ " << Balnace() << endl;
//	cout << "���� ��� �ѵ� $ " << maxLoan << endl;
//	cout << "��ȯ�� ������ $ " << owesBank << endl;
//	cout.precision(3);
//	cout << "���� �ܾ� : " << Balnace() << endl;
//	Restore(f);
//}
//
//void BrassPlus::Withdraw(double amt)
//{
//	Formatting f = SetFormat();
//
//	double bal = Balnace();
//	if (amt <= bal)
//		AcctABC::Withdraw(amt);
//	else if (amt <= bal + maxLoan - owesBank)
//	{
//		double advance = amt - bal;
//		owesBank += advance * (1.0 + rate);
//		cout << "���� ��� �ݾ� $ " << advance << endl;
//		cout << "��ȯ�� ������ $ " << advance * rate << endl;
//		Deposit(advance);
//		AcctABC::Withdraw(amt);
//	}
//	else
//		cout << "���� ��� �ѵ��� �ʰ��Ǿ� �ŷ��� ��ҵǾ����ϴ�.\n";
//	Restore(f);
//}
