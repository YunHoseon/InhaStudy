#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <list>
#include <time.h>

using namespace std;

//vector<int> Lotto(int lNum, int uNum)
//{
//	vector<int> lottoNum;
//	vector<int> lotto;
//
//	for (int i = 1; i < lNum+1; i++)
//		lottoNum.push_back(i);
//
//	srand(time(NULL));
//	random_shuffle(lottoNum.begin(), lottoNum.end());
//
//	for(int j = 0; j < uNum; j++)
//		lotto.push_back(lottoNum[j]);
//
//	return lotto;
//}
//
//int main()
//{
//	vector<int> winners;
//	winners = Lotto(45, 6);
//
//	cout << " 로또 번호 : ";
//	for (int i = 0; i < 6; i++)
//		cout << winners[i] << " ";
//	cout << endl;
//}

//void Show(int);
//const int LIM = 10;
//
//int main()
//{
//	int ar[LIM] = { 4,5,4,2,2,3,4,8,1,4 };
//	list<int> la(ar, ar + LIM);
//	list<int> lb(la);
//	
//	cout << "오리지널 리스트의 내용 : \n\t";
//	for_each(la.begin(), la.end(), Show);
//	cout << endl;
//	la.remove(4);
//	
//	cout << "remove() 메서드를 사용한 후 : \n";
//	cout << "la:\t";
//	for_each(la.begin(), la.end(), Show);
//	cout << endl;
//
//	list<int>::iterator last;
//	last = remove(lb.begin(), lb.end(), 4);
//
//	cout << "remove() 함수를 사용한 후 : \n";
//	cout << "lb:\t";
//	for_each(lb.begin(), lb.end(), Show);
//	cout << endl;
//
//	lb.erase(last, lb.end());
//	cout << "erase() 메서드를 사용한 후 : \n";
//	cout << "lb : \t";
//	for_each(lb.begin(), lb.end(), Show);
//	cout << endl;
//}
//
//void Show(int v)
//{
//	cout << v << ' ';
//}

//template<class T>
//class TooBig
//{
//	T cutoff;
//public:
//	TooBig(const T &t) : cutoff(t) { }
//	bool operator() (const T &v) 
//	{ 
//		return v > cutoff; 
//	}
//};
//
//void outint(int n) { cout << n << " "; }
//
//int main()
//{
//	TooBig<int> f100(100);
//	int vals[10] = { 50, 100, 90, 180, 60, 210, 415, 88, 188, 201 };
//	list<int> yadayada (vals, vals + 10);
//	list<int> etcetera (vals, vals + 10);
//
//	cout << "원래의 리스트 : \n";
//	for_each(yadayada.begin(), yadayada.end(), outint);
//	cout << endl;
//	for_each(etcetera.begin(), etcetera.end(), outint);
//	cout << endl;
//
//	yadayada.remove_if(f100);
//	etcetera.remove_if(TooBig<int>(200));
//
//	cout << "정비된 리스트 : \n";
//	for_each(yadayada.begin(), yadayada.end(), outint);
//	cout << endl;
//	for_each(etcetera.begin(), etcetera.end(), outint);
//	cout << endl;
//}

//typedef int KeyType;
//typedef pair<const KeyType, string> Pair;
//typedef multimap<KeyType, string> MapCode;
//
//int main()
//{
//	MapCode codes;
//
//	codes.insert(Pair(415, "샌프란시스코"));
//	codes.insert(Pair(510, "오클랜드"));
//	codes.insert(Pair(718, "브루클린"));
//	codes.insert(Pair(718, "스태슨 섬"));
//	codes.insert(Pair(415, "샌라파엘"));
//	codes.insert(Pair(510, "버클리"));
//
//	cout << "지역코드가 415인 도시수 : "
//		<< codes.count(415) << endl;
//	cout << "지역코드가 718인 도시수 : "
//		<< codes.count(415) << endl;
//	cout << "지역코드가 510인 도시수 : "
//		<< codes.count(415) << endl;
//	cout << "지역 코드   도시\n";
//
//	MapCode::iterator it;
//
//	for (it = codes.begin(); it != codes.end(); it++)
//		cout << "    " << (*it).first << "    " << (*it).second << endl;
//
//	pair<MapCode::iterator, MapCode::iterator> range = codes.equal_range(718);
//	cout << "지역코드가 718인 도시들 : \n";
//
//	for (it = range.first; it != range.second; ++it)
//		cout << (*it).second << endl;
//
//}

//void output(const string &s) { cout << s << " "; }
//
//int main()
//{
//	string s1[4] = { "fine", "fish", "fashion", "fate" };
//	string s2[2] = { "busy", "bats" };
//	string s3[2] = { "silly", "singers" };
//	vector<string> words(4);
//
//	copy(s1, s1 + 4, words.begin());
//	for_each(words.begin(), words.end(), output);
//	cout << endl;
//
//	copy(s2, s2 + 2, back_insert_iterator<vector<string>>(words));
//	for_each(words.begin(), words.end(), output);
//	cout << endl;
//
//	copy(s3, s3 + 2, insert_iterator<vector<string>>(words, words.begin()));
//	for_each(words.begin(), words.end(), output);
//	cout << endl;
//}

//struct Review
//{
//	string title;
//	int rating;
//};
//
//bool FillReview(Review &rr);
//void ShowReview(const Review &rr);
//
//int main()
//{
//	vector<Review> books;
//	Review temp;
//
//	while (FillReview(temp))
//		books.push_back(temp);
//
//	int num = books.size();
//	if (num > 0)
//	{
//		cout << "감사합니다. 당신은 다음과 같이 입력하셨습니다.\n" << "등급\t제목\n";
//
//		for (int i = 0; i < num; i++)
//			ShowReview(books[i]);
//
//		cout << "한번 더 출력한다. : \n" << "등급\t제목\n";
//
//		vector<Review>::iterator pr;
//
//		for (pr = books.begin(); pr != books.end(); pr++)
//			ShowReview(*pr);
//
//		vector<Review> oldlist(books);
//
//		if (num > 3)
//		{
//			books.erase(books.begin() + 1, books.begin() + 3);
//			cout << "삭제한 후 : \n";
//
//			for (pr = books.begin(); pr != books.end(); pr++)
//				ShowReview(*pr);
//			books.insert(books.begin(), oldlist.begin() + 1, oldlist.begin() + 2);
//			cout << "삽입한 후 : \n";
//
//			for (pr = books.begin(); pr != books.end(); pr++)
//				ShowReview(*pr);
//		}
//		books.swap(oldlist);
//		cout << "oldlist와 books를 교환한 후 : \n";
//		for (pr = books.begin(); pr != books.end(); pr++)
//			ShowReview(*pr);
//	}
//	else
//		cout << "입력한 것이 없어, 얻은것이 없습니다.\n";
//}
//
//bool FillReview(Review & rr)
//{
//	cout << "책 제목을 입력하십시오 (끝내려면 quit를 입력): ";
//	getline(cin, rr.title);
//	if (rr.title == "quit")
//		return false;
//	cout << "책 등급을 입력하십시오:";
//	cin >> rr.rating;
//	if (!cin)
//		return false;
//	while (cin.get() != '\n')
//		continue;
//	return true;
//}
//
//void ShowReview(const Review & rr)
//{
//	cout << rr.rating << "\t" << rr.title << endl;
//}

//const int NUM = 5;
//
//int main()
//{
//	vector<int> ratings(NUM);
//	vector<string> titles(NUM);
//	cout << NUM << "개의 책 제목과 책 등급(0-10)을 입력하시오.\n";
//	int i;
//
//	for (i = 0; i < NUM; i++)
//	{
//		cout << i + 1 << "번 책의 제목을 입력하시오.\n";
//		getline(cin, titles[i]);
//		cout << i + 1 << "번 책의 등급을 입력하시오.\n";
//		cin >> ratings[i];
//		cin.get();
//	}
//	cout << "감사합니다. 당신은 다음과같이 입력하셨습니다.\n" << "등급\t제목\n";
//
//	for (i = 0; i < NUM; i++)
//		cout << ratings[i] << "\t" << titles[i] << endl;
//}

//class Report
//{
//	string str;
//public:
//	Report(const string s) : str(s)
//	{
//		cout << "객체가 생성되었습니다!\n";
//	}
//	~Report()
//	{
//		cout << "객체가 삭제되었습니다.\n";
//	}
//	void comment() const { cout << str << '\n'; }
//};
//
//int main()
//{
//	{
//		auto_ptr<Report> ps(new Report("auto_ptr"));
//		ps->comment();
//	}
//
//	{
//		unique_ptr<Report> ps(new Report("unique_ptr"));
//		ps->comment();
//	}
//
//	{
//		shared_ptr<Report> ps(new Report("shared_ptr"));
//		ps->comment();
//	}
//}

//int main()
//{
//	ifstream fin;
//	fin.open("tobuy.txt");
//	if (fin.is_open() == false)
//	{
//		cerr << "파일을 열수 없습니다.\n";
//		exit(EXIT_FAILURE);
//	}
//	
//	string item;
//	int count = 0;
//	getline(fin, item, ':');
//
//	while (fin)
//	{
//		if (item[0] == '\n')
//			item.erase(0, 1);
//
//		++count;
//		cout << count << ": " << item << endl;
//		getline(fin, item, ':');
//	}
//
//	cout << "프로그램을 종료합니다.\n";
//	fin.close();
//}

//int main()
//{
//	string one("Lottery Winner!");
//	cout << one << endl;
//
//	string two(20, '$');
//	cout << two << endl;
//
//	string three(one);
//	cout << three << endl;
//	one += "Oops!";
//	cout << one << endl;
//
//	two = "Sorry! That was ";
//	three[0] = 'P';
//	
//	string four;
//	four = two + three;
//	cout << four << endl;
//
//	char alls[] = "All's well that ends well";
//	string five(alls, 20);
//	cout << five << "!\n";
//
//	string six(alls + 6, alls + 10);
//	cout << six << ", ";
//	
//	string seven(&five[6], &five[10]);
//	cout << seven << "...\n";
//
//	string eight(four, 7, 16);
//	cout << eight << " in motion!" << endl;
//}