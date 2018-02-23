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
	//find_ifֻ����һԪν��
	//auto it = find_if(vstr.cbegin(), vstr.cend(), bind2nd(not_equal_to<string>(),"poss"));//bind2nd����c11������ ������bind����
	//����ʹ��bind
	auto newcallable = bind(not_equal_to<string>(), placeholders::_1, "poss");
	auto it = find_if(vstr.cbegin(), vstr.cend(), newcallable);//newcallable�ȼ��� not_qual_to("poss");��find_if��֧������ν��
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