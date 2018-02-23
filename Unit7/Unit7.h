#ifndef UNIT7_H
#define UNIT7_H

#include <iostream>
#include <vector>
#include <string>

using namespace::std;

class Sales_data;
class Person;
class Window_mgr;
class Screen;//声明Screen 否则window_mgr的addScreen函数认为是一个error_type;

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
	Sales_data(const string &s) :Sales_data(s,0,0.0) {};//委托构造
	Sales_data(istream &is) :Sales_data() {read(is, *this);}//先执行默认构造函数 因为默认函数函数体为空 所以再执行read
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
	vector<Screen> screens{ Screen(24,80,' ') };//构造一个Screen对象  构造函数其实返回值是一个对象？
};

void Window_mgr::clear(ScreenIndex i) {
	Screen &s = screens[i];
	s.contents = string(s.width*s.height, ' ');
}

inline 
Window_mgr::ScreenIndex //因为返回值在类型名之前 不属于类的作用域 所以必须声明从属某个类
Window_mgr::addScreen(const Screen &s)
{
	screens.push_back(s);
	return screens.size() - 1;
}

class Screen {
	friend void Window_mgr::clear(ScreenIndex);//在声明友元时需要注意，需要先定义这个成员函数所在的类 然后再声明该成员函数 然后再声明友元 最后定义该成员函数
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
	const Screen &display(ostream &) const;//等价于使用了两个参数const Screen *this与ostream & 所以形参与下一个不一样
	Screen &display(ostream &);//仅在返回类型相同的情况下无法重载
private:
	pos cursor = 0;
	pos width = 0, height = 0;
	string contents;
	void do_display(ostream &os) const { os << contents; }//常量成员函数，如果不加以const，则指向一个非常量对象，那么返回const Screen& 的函数无法编译
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