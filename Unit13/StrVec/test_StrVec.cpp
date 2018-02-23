#include <iostream>
#include <Windows.h>
#include <string>

using namespace::std;

int main(void) {
	string s("hello,world");
	auto it = s.begin();
	if (s.begin() != s.end()) *it = toupper(*it);
	cout << *it << endl;
	system("pause");
}
