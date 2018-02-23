#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <Windows.h>
#include "tset.h"

using namespace::std;

int exercise_0(void) {
	vector<string> vstr = { "hello","fuck" };
	//find_if只接受一元谓词
	//auto it = find_if(vstr.cbegin(), vstr.cend(), bind2nd(not_equal_to<string>(),"poss"));//bind2nd并非c11的特性 类似于bind函数
	//以下使用bind
	auto newcallable = bind(not_equal_to<string>(), placeholders::_1, "poss");
	auto it = find_if(vstr.cbegin(), vstr.cend(), newcallable);//newcallable等价于 not_qual_to("poss");但find_if不支持这种谓词
	cout << *it << endl;
	return 0;
}

bool exercise_1(int a) {
	vector<int> v = { 1,2,4,5 };
	modulus<int> mod;
	bool flag = true;
	for (auto i : v) {
		if (mod(a, i) != 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

void exercise_2(void) {
	map<string, function<int(int, int)>> binops = {
		{"+",plus<int>()},
		{"-",minus<int>()},
		{"*",multiplies<int>()},
		{"/",divides<int>()},
		{"%",modulus<int>()}
	};
	int a, b;
	string op;
	cin >> a >> op >> b;
	cout << binops[op](a, b) << endl;
}

int main(void) {
	exercise_2();
	system("pause");
};