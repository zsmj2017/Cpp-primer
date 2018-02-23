#include <iostream>
#include <string>
#include <vector>
#include "Chapter6.h"
#include <cctype>
#include <Windows.h>

using namespace::std;

int exercise_1(void) {
	cout << "Please press into one number:";
	int n; cin >> n;
	int res = 1;
	while (n) {
		res *= n--;
	}
	cout << res << endl;
	return 0;
}

int exercise_2(int n) {
	if (n >= 0) return n;
	else return -n;
}

int exercise_3(void) {
	static int n=0;
	return n++;
}
 
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

string::size_type findchar(const string &s, char c, 
	                       string::size_type &occurs) {
	auto ret = s.size();
	auto iter = s.cbegin();
	occurs = 0;
	while (iter != s.cend()) {
		if (*iter == c) {
			if (ret == s.size()) ret = iter - s.cbegin()+1;//因为是与第一个的间隔
			++occurs;
		}
		++iter;
	}
	return ret;
}

bool find_upper_char(const string &s) {
	bool flag = false;
	for (auto c : s) {
		if (isupper(c)) flag = true;
	}
	return flag;
}

void change_upper_char(string &s) {
	for (auto &c : s) {
		if (isupper(c)) c=tolower(c);
	}
}

int exercise_3(int a, int* b) {
	if (a > *b) return a;
	else return *b;
}

void swap_point_w(int* a, int* b) {//这种做法是错误的，所有的交换仅仅局限于函数内部
	int* temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_point_r(int* &a, int* &b) {//a,b是指向指针类型的引用
	int* temp;
	temp = a;
	a = b;
	b = temp;
}

void exercise_4(initializer_list<int> i1) {
	int sum = 0;
	for (auto i : i1) {
		sum += i;
	}
	cout << sum << endl;
}

void print(vector<int> const &v1, vector<int>::const_iterator iter) {//迭代器必须指向同一个容器才可以比较,而如果初始化值传递则等于拷贝了一个vector 所以必须使用引用vector
	if (iter != v1.cend()) {
		cout << *iter << " ";
		print(v1, iter + 1);
	}
}

void print(vector<int> v1, decltype(v1.size()) index) {
	if (index < v1.size()) {
		cout << v1[index] << " ";
		print(v1, index + 1);
	}

}

string make_plural(size_t ctr, const string &word , const string &ending="s") {
	return (ctr > 1) ? word + ending : word;
}

inline int plusInt(int a, int b) {
	return a + b;
}

inline int substractInt(int a, int b) {
	return (a > b) ? a - b : b - a;
}

inline int multiInt(int a, int b) {
	return a*b;
}

inline int divisionInt(int a, int b) {
	return (a > b) ? a / b : b / a;
}

inline int compute(int i, int j, int(*p)(int, int)) {
	return p(i, j);
}

int main(void) {
	typedef decltype(plusInt) *pf;//多用类型别名吧 真的写全太恶心了；
	pf p1 = plusInt, p2 = substractInt, p3 = multiInt, p4 = divisionInt;
	vector<pf> v1 = { p1,p2,p3,p4 };
	for (auto p : v1) {
		cout << compute(1, 2, p) << endl;
	}
	system("pause");
	return 0;
}