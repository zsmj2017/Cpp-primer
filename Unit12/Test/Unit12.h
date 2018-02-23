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
	StrBlob(const StrBlob &);//��ֵ��Ϊ
	StrBlob& operator=(const StrBlob &);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const string &str) { data->push_back(str);}
	void pop_back();
	string &front();
	const string & front() const;//��Ϊthis��һ��ָ��ǳ�������ĳ���ָ�� Ϊ��ָ��һ������ �������const����Ϊ const StrBlob const* this
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

StrBlob::StrBlob(const StrBlob &s):data(make_shared<vector<string>>(*s.data)) {}//����д��ֻ�����ڳ�ʼ���� ����ں��������ڲ�д�ȼ��ڸ�data��ֵ data�ѱ���ʼ��

StrBlob& StrBlob::operator=(const StrBlob &s) {
	data = make_shared<vector<string>>(*s.data);
	//data.reset(s.data.get());  ������Ϊ�����ǵȼ۵İ� 
	//Ȼ�������� get���ص�ָ���޷���delete ��ò���������ʼ�����߸�����ָ�븳ֵ
	//get�������ڵ�ĳһ����������ʹ��ָ��ָ������
	return *this;
}


void StrBlob::check(StrBlob::size_type i,const string &msg) const {
	if (i >= this->size()) throw out_of_range(msg);//�޷�д��*this.size()
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
	string* operator->() const;//��ͷ���������һ��ָ��
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
	check(curr, "dereference past end");//����Ƿ�Խ��
	++curr;
	return *this;
}

inline string & StrBlobPtr::operator*() const{
	auto p = check(curr, "dereference past end.");
	return (*p)[curr];//*p��һ�������string��vector
}

inline string * StrBlobPtr::operator->() const{
	return &(**this);//*this�õ�Ŀǰ���� ���ý���������� �ٴν���ȡַ
}

inline StrBlobPtr StrBlobPtr::operator++(int){
	auto ret = *this;//���浱ǰ״̬
	++*this;//��ɶ�this��ǰ�õ��� 
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
