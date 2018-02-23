#ifndef TEST_H
#define TEST_H

#include <string>
#include <memory>

using namespace::std;

class HasPtr {//类值行为
friend void swap(HasPtr &, HasPtr &);
public:
	HasPtr(const string &s = string()) :ps(new string(s)), i(0) {};
	HasPtr(const string &s,int i) :ps(new string(s)), i(i) {};
	HasPtr(const HasPtr &);
	HasPtr(HasPtr &&p) noexcept:ps(p.ps), i(p.i) {p.ps = nullptr;}//移动构造
	HasPtr & operator=(const HasPtr &);
	HasPtr & operator=(HasPtr &&);
	~HasPtr();//如果一个对象内部有指向动态分布对象的指针 一定要记得delete
	bool operator<(const HasPtr &) const;
	string getps();
	int geti();
private:
	string *ps;
	int i;
};

HasPtr::HasPtr(const HasPtr & rhs) {//指向不同的地址 不然在日后的析构中会出现该指针被删除两次
	ps = new string(*rhs.ps);
	i = rhs.i;
}

HasPtr & HasPtr::operator=(const HasPtr &rhs) {//必须要先释放原有的内存空间 这与初始化不同 因为ps已经指向了某个地址
	auto newps = new string(*rhs.ps);
	delete ps;
	ps = newps;
	i = rhs.i;
	return *this;
}

inline HasPtr & HasPtr::operator=(HasPtr &&rhs){//移动赋值运算符一定要记住检查自赋值
	if (this != &rhs) {
		delete ps;
		ps = rhs.ps;
		i = rhs.i;
		rhs.ps = nullptr;
		rhs.i = 0;
	}
	return *this;
}

HasPtr::~HasPtr() {
	delete ps;
}

bool HasPtr::operator<(const HasPtr &rhs) const {
	return i < rhs.i;
}

string HasPtr::getps() {
	return *ps;
}

int HasPtr::geti() {
	return i;
}

inline void swap(HasPtr &lhs, HasPtr &rhs) {
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}

#endif
