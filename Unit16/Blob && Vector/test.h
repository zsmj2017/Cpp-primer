#ifndef TEST_H
#define TEST_H

#include <utility>
#include <iostream>

template<typename T> int comapre(const T &lhs, const T &rhs) {
	if (less<T&>(lhs, rhs)) return 1;
	if (less<T&>(rhs, lhs)) return -1;
	return 0;
}

template<typename It, typename T> It tem_find(It beg,It end, const T &value) {
	while (beg==end && *beg!=value) ++beg;
	return beg;
}

template<typename T, unsigned N> void tem_print(const T(&r)[N]) {//�β���һ������N��T��Ԫ�ص���������� ʹ����������Ϊ�����޷�����
	for (const auto &e : r) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

template<typename T, unsigned N> T arr_begin(const T(&r)[N]) {
	return r[0];
}

template<typename T, unsigned N> T arr_end(const T(&r)[N]) {
	return r[N-1];
}

template<typename T, unsigned N> constexpr unsigned arr_size(const T(&r)[N]) {
	return N;
}

template<typename T,typename F=less<T>>
int compare(const T&lhs, const T&rhs, F f() = F()) {//�Һܻ������ܹ��������𡣡������ǿ�����һ����ʵ�� ���ж�����
	if (f(lhs, rhs)) return -1;
	if (f(rhs, lhs)) return 1; 
	return 0;
}

template<typename T>
void print_T(const T&t){//����������֧���������
	for (typename T::size_type index = 0; index != t.size(); ++index) {
		std::cout << t[index] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void print_t(const T&t) {
	for (auto it = t.cbegin(); it != t.cend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template<typename F,typename T1, typename T2>
void flip(F f,T1 &&t1,T2 &&t2) {
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}

template<typename T>
std::ostream& print(std::ostream &os,const T &t) {
	return os << t;
}

template<typename T,typename...Args>
std::ostream& print(std::ostream &os,const T &t,const Args...args) {
	os << t;
	return print(os, args...);
}

#endif // !TEST_H