#ifndef SALESDATA_H
#define SALESDATA_H

#include <iostream>
#include <string>

using namespace::std;


class Sales_data {
	friend istream &operator>>(istream &, Sales_data &);
	friend ostream &operator<<(ostream &, const Sales_data &);
	friend Sales_data operator+(const Sales_data &, const Sales_data &);//��ʹ�ǳ���a=a+a�����Ҳ��ʹ��const ��Ϊ�ȹ���һ������ Ȼ����󷵻غ��ٶ�a���и�ֵ
	friend bool operator==(const Sales_data &, const Sales_data &);
public:
	Sales_data() = default;
	Sales_data(const string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(n*p) {};
	Sales_data(const string &s) :Sales_data(s, 0, 0.0) {};//ί�й���
	Sales_data(istream &is) :Sales_data() { operator>>(is, *this); }//��ִ��Ĭ�Ϲ��캯�� ��ΪĬ�Ϻ���������Ϊ�� ������ִ��read
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
	if (!is) s = Sales_data();//�������ʧ�� ���ֶ���Ŀ�ʹ��
	return is;
}

inline ostream & operator<<(ostream &os, const Sales_data &s){
	os << s.isbn() << s.units_sold << s.revenue;
	return os;
}

inline Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) { //Ӧ�þ�����ʹ�ø��ϸ�ֵ��������������
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

