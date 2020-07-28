#include<iostream>

using namespace std;

class Box
{
public:
	int length;
	int breadth;
	int height;

	Box()
	{

	}
	Box(int l, int b, int h) { length = l; breadth = b; height = h; }
	Box(Box &B) { length = B.length; breadth = B.breadth; height = B.height; }

	int getLength() { return length; }
	int getbreadth() { return breadth; }
	int getheight() { return height; }
	long long CalculateVolume() { return length * breadth * height; }

	bool operator<(Box& b)
	{
		return (this->CalculateVolume() < b.CalculateVolume());
	}

	friend ostream& operator<<(ostream& out, const Box& B);
};

ostream & operator<<(ostream & out, const Box & B)
{
	{
		out << B.length << B.breadth << B.height;
		return out;
	}
	// TODO: 여기에 반환 구문을 삽입합니다.
}

void check2()
{
	int n;
	cin >> n;
	Box temp;
	for (int i = 0;i<n;i++)
	{
		int type;
		cin >> type;
		if (type == 1)
		{
			cout << temp << endl;
		}
		if (type == 2)
		{
			int l, b, h;
			cin >> l >> b >> h;
			Box NewBox(l, b, h);
			temp = NewBox;
			cout << temp << endl;
		}
		if (type == 3)
		{
			int l, b, h;
			cin >> l >> b >> h;
			Box NewBox(l, b, h);
			if (NewBox<temp)
			{
				cout << "Lesser\n";
			}
			else
			{
				cout << "Greater\n";
			}
		}
		if (type == 4)
		{
			cout << temp.CalculateVolume() << endl;
		}
		if (type == 5)
		{
			Box NewBox(temp);
			cout << NewBox << endl;
		}

	}
}

int main()
{
	check2();
}
