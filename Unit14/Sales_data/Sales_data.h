#ifndef SALESDATA_H
#define SALESDATA_H

#include <iostream>
#include <string>

using namespace::std;


class Sales_data {
	friend istream &operator>>(istream &, Sales_data &);
	friend ostream &operator<<(ostream &, const Sales_data &);
	friend Sales_data operator+(const Sales_data &, const Sales_data &);//即使是出现a=a+a的情况也是使用const 因为先构造一个对象 然后对象返回后再对a进行赋值
	friend bool operator==(const Sales_data &, const Sales_data &);
public:
	Sales_data() = default;
	Sales_data(const string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(n*p) {};
	Sales_data(const string &s) :Sales_data(s, 0, 0.0) {};//委托构造
	Sales_data(istream &is) :Sales_data() { operator>>(is, *this); }//先执行默认构造函数 因为默认函数函数体为空 所以再执行read
	Sales_data &operator+=(const Sales_data &);
	string isbn() const { return bookNo; }
	operator string() const { return bookNo; }
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

inline istream & operator>>(istream &is, Sales_data &s) {
	is >> s.bookNo >> s.units_sold >> s.revenue;
	if (!is) s = Sales_data();//如果输入失败 保持对象的可使用
	return is;
}

inline ostream & operator<<(ostream &os, const Sales_data &s){
	os << s.isbn() << s.units_sold << s.revenue;
	return os;
}

inline Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) { //应该尽可能使用复合赋值来构造算术函数
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}

inline Sales_data & Sales_data::operator+=(const Sales_data &s) {
	if (this->bookNo == s.bookNo) {
		Sales_data s(s.bookNo);
		s.units_sold = this->units_sold + s.units_sold;
		s.revenue = this->revenue + s.revenue;
		return *this;
	}
	else 
		throw runtime_error("The two datas don't have the same isbn!");
}

inline bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.bookNo == rhs.bookNo &&
		lhs.units_sold == rhs.units_sold &&
		lhs.revenue == rhs.revenue;
}

inline bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
	return !(lhs == rhs);
}

#endif 

