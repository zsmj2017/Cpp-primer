#ifndef TEST_H
#define TEST_H

#include<iostream>
#include<string>

using namespace::std;

class readString {
public:
	readString(istream &is = cin):is(is) {};
	string line;
	string operator()() {
		if (!getline(is, line)) {//����ȡ���
			return " ";
		}
		else return line;
	}
private:
	istream &is;//ע��������������ʽ is�޷�����ֵ����
};

class equalInt {
public:
	equalInt(int a) :val(a) {};
	bool operator()(int a) const {
		return (a == val);
	}
private:
	int val;
};

class checkStringLen {
public:
	//checkStringLen(size_t length) :len(length) {};
	bool operator()(const string &s) {
		return s.size() >=1&&s.size()<=9;
	}
private:
	//size_t len;
};

#endif 