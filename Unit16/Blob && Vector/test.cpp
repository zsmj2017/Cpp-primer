#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "test.h"
#include "Blob.h"
#include "Vec.h"

int exercise_0(void) {
	std::vector<int> v1 = { 1,2,3,4,5 };
	auto it = tem_find(v1.cbegin(), v1.cend(), 3);
	std::cout << *it << std::endl;
	system("pause");
	return 0;
}

int exercise_1(void) {
	int a[] = { 1,2,3,4,5 };
	std::cout << arr_end(a);
	system("pause");
	return 0;
}

void test(void) {
	Blob<int> b = { 1,2,3,4,5 };
	std::cout <<b.back()<< std::endl;
	system("pause");
}

void test_vec(void) {
	Vec<int> v1 = { 1,2,3,4,5 };
	v1.push_back(6);
	/*for (auto i:v1) std::cout << i << " ";
	std::cout << std::endl;
	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl;
	v1.reserve(20);*/
	Vec<int> v2 = v1;
	std::cout <<(v2!=v1)<< std::endl;
	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl;
}

int main(void) {
	std::cout << compare<std::string>("hello","fuck") << std::endl;;
	system("pause");
	return 0;
}