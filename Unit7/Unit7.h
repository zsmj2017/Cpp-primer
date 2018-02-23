#ifndef UNIT7_H
#define UNIT7_H

#include <iostream>
#include <vector>
#include <string>

using namespace::std;

class Sales_data;
class Person;
class Window_mgr;
class Screen;//����Screen ����window_mgr��addScreen������Ϊ��һ��error_type;

class Sales_data {
	friend istream &read(istream &, Sales_data &);
	friend ostream &print(ostream &, const Sales_data &);
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
public:
	Sales_data() = default;
	Sales_data(const string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(n*p) {};
	Sales_data(const string &s) :Sales_data(s,0,0.0) {};//ί�й���
	Sales_data(istream &is) :Sales_data() {read(is, *this);}//��ִ��Ĭ�Ϲ��캯�� ��ΪĬ�Ϻ���������Ϊ�� ������ִ��read
	string isbn() const { return bookNo; }
	Sales_data &combine(const Sales_data &rhs) {
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
};

istream &read(istream &is, Sales_data &item) {
	double price = 0.0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price*item.units_sold;
	return is;
}

ostream &print(ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue;
	return os;
}

class Person {
	friend istream &read(istream &, Person &);
	friend ostream &print(ostream &, const Person &);
private:
	string strName;
	string strAddress;
public:
	Person() = default;
	Person(const string &s1, const string &s2) :strName(s1), strAddress(s2) {};
	string getName() const { return strName; }
	string getAddress() const { return strAddress; }
};

istream &read(istream &is, Person &item) {
	is >> item.strName >> item.strAddress;
	return is;
}

ostream &print(ostream &os, const Person &item) {
	os << item.getName() << item.getAddress();
	return os;
}

class Window_mgr {
public:
	using ScreenIndex = vector<Screen>::size_type;
	void clear(ScreenIndex);
	ScreenIndex addScreen(const Screen &);
private:
	vector<Screen> screens{ Screen(24,80,' ') };//����һ��Screen����  ���캯����ʵ����ֵ��һ������
};

void Window_mgr::clear(ScreenIndex i) {
	Screen &s = screens[i];
	s.contents = string(s.width*s.height, ' ');
}

inline 
Window_mgr::ScreenIndex //��Ϊ����ֵ��������֮ǰ ��������������� ���Ա�����������ĳ����
Window_mgr::addScreen(const Screen &s)
{
	screens.push_back(s);
	return screens.size() - 1;
}

class Screen {
	friend void Window_mgr::clear(ScreenIndex);//��������Ԫʱ��Ҫע�⣬��Ҫ�ȶ��������Ա�������ڵ��� Ȼ���������ó�Ա���� Ȼ����������Ԫ �����ó�Ա����
public:
	using pos = string::size_type;
	Screen() = default;
	Screen(pos wd, pos ht) :width(wd), height(ht) {};
	Screen(pos wd, pos ht, char c) :width(wd), height(ht), contents(wd*ht, c) {};
	Screen &move(pos, pos);
	char get();
	char get(pos, pos);
	Screen &set(char c);
	Screen &set(pos, pos,char c);
	const Screen &display(ostream &) const;//�ȼ���ʹ������������const Screen *this��ostream & �����β�����һ����һ��
	Screen &display(ostream &);//���ڷ���������ͬ��������޷�����
private:
	pos cursor = 0;
	pos width = 0, height = 0;
	string contents;
	void do_display(ostream &os) const { os << contents; }//������Ա���������������const����ָ��һ���ǳ���������ô����const Screen& �ĺ����޷�����
};

inline
Screen& Screen::move(pos x, pos y) {
	cursor = y*height + x;
	return *this;
}

char Screen::get() {
	return contents[cursor];
}

char Screen::get(pos x, pos y) {
	return contents[y*height + x];
}

Screen& Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

Screen& Screen::set(pos x,pos y,char c) {
	contents[y*height+x] = c;
	return *this;
}

const Screen& Screen::display(ostream &os) const {
	do_display(os);
	return *this;
}

Screen& Screen::display(ostream &os) {
	do_display(os);
	return *this;
}

#endif