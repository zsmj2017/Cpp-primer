#include <iostream>
#include <Windows.h>
int example_1(void) {
	int value = 2;
	int pow = 10;
	int result = 1;
	for (int i = 0; i < pow; i++) {
		result *= value;
	}
	std::cout << result << std::endl;
	return 0;
}
int exercise_1(void) {
	int value, pow;
	int result = 1;
	std::cout << "Please press into the value: ";
	std::cin >> value;
	std::cout << "Please press into the power: ";
	std::cin >> pow;
	for (int i = 0; i < pow; i++) {
		result *= value;
	}
	std::cout << "The result is: " << result << std::endl;
	return 0;
}
int exercise_2(void) {
	int i = 56; int j = 64;
	int *p = &i, *lp = &j;
	std::cout << *p << std::endl;
	p = lp; std::cout << *p<<std::endl;
	*p = 49; std::cout << j << std::endl;
	return 0;
}
int example_3(void) {
	int i = 42;
	const int ci = i;
	auto &r = ci;
	i = 43;
	std::cout << r;
	return 0;
}
int main(void) {
	example_3();
	system("pause");
}