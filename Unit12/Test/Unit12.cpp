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
	cout << endl;//sptr离开作用域后指向的内存被自动释放
}

void test(void) {//此程序提前分配了size大小的内存 但是无法处理实际输入大于或者小于分配量的情况
	int size;
	cin >> size;
	string *const p = new string[size];
	string *q = p;
	string s;
	while (cin >> s && q != p + size) {
		*q++ = s;//显然 每一个string都被赋值了两次 一次是初始化 一次是此处赋值 冗余
	}
	const auto real_size = q - p;
	q = p;//将q重置
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