#include <iostream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <cstring>
#include "chapter12.h"

using namespace::std;

vector<int> * new_vector(void) {
	return new vector<int>;
}

vector<int> * input_vector(void) {
	auto p = new_vector();
	int input;
	while (cin >> input) {
		p->push_back(input);
	}
	return p;
}

void print_vector(vector<int> *p) {
	for (auto i : *p) {
		cout << i << " ";
	}
	cout << endl;
	delete p;
}

void exercise_0(void) {
	auto sptr = make_shared<vector<int>>();
	int input;
	while (cin >> input) {
		sptr->push_back(input);
	}
	for (auto i : *sptr) {
		cout << i << " ";
	}
	cout << endl;//sptr�뿪�������ָ����ڴ汻�Զ��ͷ�
}

void test(void) {//�˳�����ǰ������size��С���ڴ� �����޷�����ʵ��������ڻ���С�ڷ����������
	int size;
	cin >> size;
	string *const p = new string[size];
	string *q = p;
	string s;
	while (cin >> s && q != p + size) {
		*q++ = s;//��Ȼ ÿһ��string������ֵ������ һ���ǳ�ʼ�� һ���Ǵ˴���ֵ ����
	}
	const auto real_size = q - p;
	q = p;//��q����
	while (q != p + real_size) {
		cout << *q++ << " ";
	}
	cout << endl;
}

void test_1(void) {
	vector<string> vstr({ "hello","world","miemie" });
	allocator<string> alloc;
	auto const p = alloc.allocate(vstr.size()*2);
	auto q = uninitialized_copy(vstr.cbegin(), vstr.cend(), p);
	uninitialized_fill_n(q, vstr.size(), "t");
	string *beg = p;
	while (beg != p + vstr.size() * 2) {
		cout << *beg << " ";
		alloc.destroy(beg++);
	}
	cout << endl;
	alloc.deallocate(p, vstr.size() * 2);
}

int main(void) {
	test_1();
	system("pause");
}