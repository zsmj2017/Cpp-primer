#include <iostream>
#include <Windows.h>
#include "Sales_item.h"

int example_1(void) {
	std::cout << "Please press into two number." << std::endl;
	int a, b;
	std::cin >> a >> b;
	std::cout << "The sum of a + b is: " << a + b << std::endl;
	return 0;
}
int exercise_1(void) {
	std::cout << "Hello.world!" << std::endl;
	return 0;
}
int exercise_2(void) {
	std::cout << "Please press into two number." << std::endl;
	int a, b;
	std::cin >> a >> b;
	std::cout << "a * b is: " << a * b << std::endl;
	return 0;
}
int example_2(void) {
	int sum = 0, value;
	while (std::cin >> value) {//judge cin is ended
		sum += value;
	}
	std::cout << "The sum is " << sum;
	return 0;
}
int exercise_3(void) {
	std::cout << "Please press into two number,then we can tell you every number between them." << std::endl;
	int a, b;
	std::cout << "a:"; std::cin >> a;
	std::cout << "b:"; std::cin >> b;
	int num; num = a + 1;
	while (num < b) {
		std::cout << num << " ";
		num++;
	}
	std::cout << std::endl;
	return 0;
}
int exercise_4(void) {
	std::cout << "Please press into two number,then we can tell you every number between them." << std::endl;
	int a, b;
	std::cout << "a:"; std::cin >> a;
	std::cout << "b:"; std::cin >> b;
	int num = a + 1;
	int n = 0;
	while (num < b) {
		std::cout << num << " ";
		num++; n++;
		if (n == 10) {
			std::cout << std::endl;
			n = 0;
		}
	}
	std::cout << std::endl;
	return 0;
}
int exercise_5(void) {
	std::cout << "Please press into two number,then we can tell you the sum of every number between them." << std::endl;
	int a, b, sum=0;
	std::cout << "a:"; std::cin >> a;
	std::cout << "b:"; std::cin >> b;
	if(a<b){
		int num; num = a ;
		while (num <= b) {
			sum += num;
			num++;
		}
		std::cout <<"The sum is "<<sum<< std::endl;
    }
	else {
		int num; num = b;
		while (num <= a) {
			sum += num;
			num++;
		}
		std::cout << "The sum is " << sum << std::endl;
	}
	return 0;
}
int example_3(void) {
	Sales_item book;
	std::cout << "Please press into the books' ISBN,number and price:";
	std::cin >> book;
	std::cout << book << std::endl;
	return 0;
}
int example_4(void) {
	Sales_item item1, item2;
	std::cout << "Please press into the book_1s' ISBN,number and price:";
	std::cin >> item1;
	std::cout << "Please press into the book_2s' ISBN,number and price:";
	std::cin >> item2;
	std::cout << item1+item2 << std::endl;//
	return 0;
}
int example_5(void) {
	Sales_item item1, item2;
	std::cout << "Please press into the book_1s' ISBN,number and price:";
	std::cin >> item1;
	std::cout << "Please press into the book_2s' ISBN,number and price:";
	std::cin >> item2;
	if (item1.isbn == item2.isbn) {
		std::cout << item1 + item2 << std::endl;
		return 0;
	}
	else {
		std::cerr << "Data should refer to same ISBN!" << std::endl;
		return - 1;
	}
}
int example_6(void) {
	Sales_item total;
	if (std::cin >> total) {
		Sales_item trans;
		while (std::cin >> trans) {
			if (trans.isbn == total.isbn) {
				total += trans;
			}
			else {
				std::cout << total << std::endl;
				total = trans;
			}
			std::cout << total << std::endl;
		}
	}
	else {
		std::cerr << "No data?!" << std::endl;
		return -1;
	}
	return 0;
}
int main(void) {
	example_6();
	system("pause");
}