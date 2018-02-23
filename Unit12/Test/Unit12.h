#ifndef CHAPTER12_H
#define CHAPTER12_H

#include<string>
#include<vector>
#include<memory>
#include <iostream>

using namespace::std;

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> i1);
	StrBlob(const StrBlob &);//类值行为
	StrBlob& operator=(const StrBlob &);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const string &str) { data->push_back(str);}
	void pop_back();
	string &front();
	const string & front() const;//因为this是一个指向非常量对象的常量指针 为了指向一个常量 必须加以const修饰为 const StrBlob const* this
	string &back();
	const string & back() const;
	StrBlobPtr & begin();
	StrBlobPtr & end();
private:
	shared_ptr<vector<string>> data;
	void check(size_type i,const string &msg) const;
};

StrBlob::StrBlob():data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> i1):data(make_shared<vector<string>>(i1)) {}

StrBlob::StrBlob(const StrBlob &s):data(make_shared<vector<string>>(*s.data)) {}//此种写法只存在于初始化中 如果在函数框体内部写等价于给data赋值 data已被初始化

StrBlob& StrBlob::operator=(const StrBlob &s) {
	data = make_shared<vector<string>>(*s.data);
	//data.reset(s.data.get());  可以认为二者是等价的吧 
	//然而并不是 get返回的指针无法被delete 最好不用它来初始化或者给智能指针赋值
	//get仅仅用于当某一个函数不能使用指针指针的情况
	return *this;
}


void StrBlob::check(StrBlob::size_type i,const string &msg) const {
	if (i >= this->size()) throw out_of_range(msg);//无法写成*this.size()
}

string & StrBlob::front() {
	check(0, "there is no element in the bolb");
	return data->front();
}

const string &StrBlob::front() const {
	check(0, "there is no element in the bolb");
	return data->front();
}

string & StrBlob::back() {
	check(0, "there is no element in the bolb");
	return data->back();
}

const string & StrBlob::back() const {
	check(0, "there is no element in the bolb");
	return data->back();
}

void StrBlob::pop_back() {
	check(0, "there is no element in the bolb");
	data->pop_back();
}

bool neq(StrBlobPtr &,StrBlobPtr &);

class StrBlobPtr {
friend bool neq(StrBlobPtr &, StrBlobPtr &);
public:
	StrBlobPtr() :curr(0) {};
	StrBlobPtr(StrBlob &a, size_t sz = 0) :wptr(a.data), curr(sz) {};
	StrBlobPtr& operator++();
	string& operator*() const;
	string* operator->() const;//箭头运算符返回一个指针
	StrBlobPtr operator++(int);
private:
	weak_ptr<vector<string>> wptr;
	shared_ptr<vector<string>> check(size_t, const string &) const;
	size_t curr;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
	auto ret = wptr.lock();
	if (ret) {
		if (i >= ret->size()) throw out_of_range(msg);
	}
	else throw runtime_error("unbound strblobptr");
	return ret;
}


inline StrBlobPtr & StrBlobPtr::operator++(){
	check(curr, "dereference past end");//检测是否越界
	++curr;
	return *this;
}

inline string & StrBlobPtr::operator*() const{
	auto p = check(curr, "dereference past end.");
	return (*p)[curr];//*p是一个存放了string的vector
}

inline string * StrBlobPtr::operator->() const{
	return &(**this);//*this得到目前对象 调用解引用运算符 再次进行取址
}

inline StrBlobPtr StrBlobPtr::operator++(int){
	auto ret = *this;//保存当前状态
	++*this;//完成对this的前置递增 
	return ret;
}


StrBlobPtr & StrBlob::begin() {
	check(0, "there is no element in the bolb");
	return StrBlobPtr(*this);
}

StrBlobPtr & StrBlob::end() {
	check(0, "there is no element in the bolb");
	return StrBlobPtr(*this, data->size());
}

bool neq(StrBlobPtr &a, StrBlobPtr &b) {
	if (a.wptr.lock() == nullptr || b.wptr.lock()== nullptr) {
		throw runtime_error("there is no vector!");
	}
	else if (a.wptr.lock() != b.wptr.lock()) {
		throw runtime_error("they are not bound to the same vector.");
	}
	else if (a.wptr.lock() == b.wptr.lock()) {
		if (a.curr == b.curr) return false;
		else return true;
	}
}

/*class ConstStrBlobPtr {
public:
	ConstStrBlobPtr() :curr(0) {};
	ConstStrBlobPtr(const StrBlob &a, size_t i) :wptr(a.data), curr(i) {};
	string & deref() const;
	

private:
	size_t curr;
	const shared_ptr<vector<string>>  &check(size_t, const string &msg) const;
	weak_ptr<vector<string>> wptr;
};*/

#endif
