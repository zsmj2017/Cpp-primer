#include <iostream>
#include <Windows.h>

using namespace::std;

istream& func(istream & is) {
	int v;
	while (is>>v,!is.eof()) {
		if (is.bad()) throw runtime_error("IO������");
		else if (is.fail()) {
			cout << "������int������";
			is.clear();
			is.ignore(100, '\n');//���������������ַ������ﵽ100��������'\n'����ֹ��������һ���������һ�������Ӱ��
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