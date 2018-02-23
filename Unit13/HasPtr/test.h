#ifndef TEST_H
#define TEST_H

#include <string>
#include <memory>

using namespace::std;

class HasPtr {//��ֵ��Ϊ
friend void swap(HasPtr &, HasPtr &);
public:
	HasPtr(const string &s = string()) :ps(new string(s)), i(0) {};
	HasPtr(const string &s,int i) :ps(new string(s)), i(i) {};
	HasPtr(const HasPtr &);
	HasPtr(HasPtr &&p) noexcept:ps(p.ps), i(p.i) {p.ps = nullptr;}//�ƶ�����
	HasPtr & operator=(const HasPtr &);
	HasPtr & operator=(HasPtr &&);
	~HasPtr();//���һ�������ڲ���ָ��̬�ֲ������ָ�� һ��Ҫ�ǵ�delete
	bool operator<(const HasPtr &) const;
	string getps();
	int geti();
private:
	string *ps;
	int i;
};

HasPtr::HasPtr(const HasPtr & rhs) {//ָ��ͬ�ĵ�ַ ��Ȼ���պ�������л���ָ�ָ�뱻ɾ������
	ps = new string(*rhs.ps);
	i = rhs.i;
}

HasPtr & HasPtr::operator=(const HasPtr &rhs) {//����Ҫ���ͷ�ԭ�е��ڴ�ռ� �����ʼ����ͬ ��Ϊps�Ѿ�ָ����ĳ����ַ
	auto newps = new string(*rhs.ps);
	delete ps;
	ps = newps;
	i = rhs.i;
	return *this;
}

inline HasPtr & HasPtr::operator=(HasPtr &&rhs){//�ƶ���ֵ�����һ��Ҫ��ס����Ը�ֵ
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
