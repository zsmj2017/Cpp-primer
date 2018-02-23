#include <iostream>
#include <Windows.h>

using namespace::std;

istream& func(istream & is) {
	int v;
	while (is>>v,!is.eof()) {
		if (is.bad()) throw runtime_error("IO流错误");
		else if (is.fail()) {
			cout << "请输入int型数据";
			is.clear();
			is.ignore(100, '\n');//清除缓冲区，如果字符容量达到100活着遇到'\n'则终止，消除上一次输入对下一次输入的影响
			continue;
		}
		cout << v << endl;
	}
	is.clear();
	return is;
}

int main(void) {
	func(cin);
	system("pause");
	return 0;
}