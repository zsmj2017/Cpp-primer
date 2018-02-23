#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "test.h"


int main(void) {
	HasPtr a("hello world", 3), b("fuck you", 2), c("haha", 1);
	vector<HasPtr> vh;
	vh.push_back(a);
	vh.push_back(b);
	vh.push_back(c);
	for (auto &has : vh) {
		cout << has.getps() << "";
	}
	cout << endl;
	sort(vh.begin(), vh.end());//其中调用了=操作
	for (auto &has : vh) {
		cout << has.getps() << " ";
	}
	cout << endl;
	system("pause");
}