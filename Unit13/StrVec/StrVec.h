#ifndef StrVec_H
#define StrVec_H

#include <memory>
#include <string>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace::std;

class StrVec {
	friend bool operator==(const StrVec &, const StrVec &);
	friend bool operator!=(const StrVec &, const StrVec &);
public:
	StrVec() :elements(nullptr),first_free(nullptr),cap(nullptr) {};
	StrVec(initializer_list<string>);//为啥不能用引用类型 因为initializer_list并不拷贝元素 而是实现底层共享
	StrVec(const StrVec &);//显然vector是类值拷贝
	StrVec(StrVec &&) noexcept;//移动构造函数不应该抛出任何异常
	StrVec& operator=(const StrVec &);
	StrVec& operator=(initializer_list <string>);
	StrVec& operator=(StrVec &&) noexcept; 
	string& operator[](size_t n) { return elements[n]; }//下标运算符通常会定义const版本和非常量版
	string& operator[](size_t n) const { return elements[n]; }//对一个指针直接使用下标运算符等价于*（elements+n）
	~StrVec();
	void push_back(const string &);
	void push_back(string &&);
	void reserve(size_t);
	void resize(size_t);//很明显resize和reserve应该调用某个生成并移动n个元素的reallocate（） 但是我懒得重构了
	void resize(size_t, const string &);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin() const { return elements; }
	string* end() const { return first_free; }
private:
	static allocator<string> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	pair<string*, string*> alloc_n_copy(const string *, const string *);
	void free();//销毁元素 释放内存
	void reallocate();//重新分配内存 并且拷贝已有元素
	string * elements;
	string * first_free;
	string * cap;
};

allocator<string> StrVec::alloc;

inline StrVec::StrVec(initializer_list<string> l){
	auto newdata = alloc_n_copy(l.begin(),l.end());
	elements = newdata.first;
	cap = first_free = newdata.second;
}

StrVec::StrVec(const StrVec &rhs) {//我们并没有分配同样大的capacity 因为无法定位到first_free的原因
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());//将rhs复制 newdata为一个pair
	elements = newdata.first;
	first_free = cap = newdata.second;
}

inline StrVec::StrVec(StrVec && s) noexcept	:elements(s.elements),first_free(s.first_free),cap(s.cap){
	s.elements = s.first_free = s.cap = nullptr;//将指针置为空，确保移后源对象能够被正常析构
}

inline StrVec & StrVec::operator=(const StrVec &rhs)
{
	free();
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

inline StrVec & StrVec::operator=(initializer_list<string> il){//initializer不需要自赋值检测
	free();
	auto p = alloc_n_copy(il.begin(), il.end());
	elements = p.first;
	cap = first_free = p.second;
	return *this;
}

inline StrVec & StrVec::operator=(StrVec &&rhs) noexcept{
	if (this != &rhs) {//直接检测是不是自赋值
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

inline StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const string &s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

inline void StrVec::push_back(string &&s){
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));//construct默认采用拷贝方式构造 此处我们使用move进行构造 优化性能
}

inline void StrVec::reserve(size_t n){
	if (n > capacity()) {
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i) {
			alloc.construct(dest++, std::move(*elem++));
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = newdata + n;
	}
}

inline void StrVec::resize(size_t n){//值得注意的是resize在n不大于capacity的情况下不会改变capacity
	if (n <= size()) {
		for (auto p = elements + n; p != first_free; ++p) {
			alloc.destroy(p);//仅仅detroy对象而不释放内存
		}
	}
	else if (n > size() && n <= capacity()) {
		for (auto p = first_free; p != elements + n; ++p) {
			alloc.construct(p, string());//构造空string
		}
	}
	else if (n > capacity()) {
		auto newcapacity = n;
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i) {
			alloc.construct(dest++, std::move(*elem++));
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
		for (auto p = first_free; p != cap; ++p) {
			alloc.construct(p, string());
		}
	}
}

inline void StrVec::resize(size_t n, const string &s) {
	if (n <= size()) {
		for (auto p = elements + n; p != first_free; ++p) {
			alloc.destroy(p);//仅仅detroy对象而不释放内存
		}
	}
	else if (n > size() && n <= capacity()) {
		for (auto p = first_free; p != elements + n; ++p) {
			alloc.construct(p, s);//构造空string
		}
	}
	else if (n > capacity()) {
		auto newcapacity = n;
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i) {
			alloc.construct(dest++, std::move(*elem++));
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
		for (auto p = first_free; p != cap; ++p) {
			alloc.construct(p, s);
		}
	}
}

void StrVec::free() {//首先destroy所有元素 然后释放内存
	/*for (auto beg = elements; beg != first_free; ++beg) {
		alloc.destroy(beg);
	}
	alloc.deallocate(elements, capacity());*/
	for_each(elements, first_free, [](string &s) {alloc.destroy(&s); });//lambda在使用时实现了解引用 它的形参其实是字符串 所以destory要取其地址
	alloc.deallocate(elements, capacity());
}

inline void StrVec::reallocate()//显然，对string对象进行拷贝然后销毁是一笔很大的空间和时间开销
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	/*auto last = newdata;//指向新数组中的下一个空闲位置
	auto elem = elements;//指向旧数组中的下一个元素
	for (size_t i = 0; i != size(); ++i) {
		//调用move返回的结果会导致construct使用string的移动构造函数
		//string管理的内存不会被拷贝
		//我们构造的每一个string都会从elem所指的string那里接管内存所有权
		alloc.construct(dest++, std::move(*elem++));//注意一定要std::move 通过string的移动构造函数来construct
	}*/
	auto last = uninitialized_copy(make_move_iterator(elements), make_move_iterator(cap), newdata);//make_move_iterator将普通迭代器转为移动迭代器
	free();
	elements = newdata;
	first_free = last;
	cap = elements + newcapacity;
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
	//pair内保存了指向新空间的首地址和拷贝尾后地址
	auto data = alloc.allocate(e - b);
	return { data,uninitialized_copy(b,e,data) };
}

inline bool operator==(const StrVec &lhs, const StrVec &rhs) {
	bool flag = true;
	if (lhs.size() == rhs.size()) {
		for (size_t index = 0;index!=lhs.size();++index) {//马上定义个下标运算符 这儿真是麻烦死了
			if (*(lhs.elements + index) != *(rhs.elements + index)) {//这里目测是使用string类的==
				flag = false;
				break;
			}
		}
	}
}

inline bool operator!=(const StrVec &lhs, const StrVec &rhs){
	return !(lhs==rhs);
}

class Str {//初步断定私有成员和函数不能取同样的名字
	friend ostream& operator<<(ostream &,const Str &);
	friend bool operator==(const Str &, const Str &);
public:
	Str() :elements(nullptr), cap(nullptr) {};
	Str(const char *);
	Str(const Str &);
	Str& operator=(const Str &);
	~Str();
	size_t size() const { return cap - elements; }
	char * begin() const { return elements; }
	char * end() const { return cap; }
private:
	static allocator<char> alloc;
	pair<char *, char *> allocate_n_copy(const char *,const char *);
	void free();
	char * elements;
	char * cap;
};

allocator<char> Str::alloc;

Str::Str(const char *c) {
	auto p =allocate_n_copy(c, c + strlen(c));
	elements = p.first;
	cap = p.second;
}

inline Str::Str(const Str &rhs){
	auto p = allocate_n_copy(rhs.begin(), rhs.end());
	elements = p.first;
	cap = p.second;
}

inline Str & Str::operator=(const Str &rhs)
{
	free();
	auto p = allocate_n_copy(rhs.elements, rhs.begin);
	elements = p.first;
	cap = p.second;
	return *this;
}

Str::~Str() {
	free();
}

void Str::free() {
	for_each(elements, cap, [](char &c) { alloc.destroy(&c); });
	alloc.deallocate(elements, size());
}

pair<char *, char *> Str::allocate_n_copy(const char *b,const char *e) {
	auto data = alloc.allocate(e - b);
	return { data,uninitialized_copy(b,e,data) };
}

ostream& operator<<(ostream &os,const Str &s){
	/*for (auto &c : s) {
		os << c;
	}*/
	cout << s;
	return os;
}
inline bool operator==(const Str &lhs, const Str &rhs){
	bool flag = true;
	if (lhs.size() == rhs.size()) {
		for (auto p = lhs.begin(), q = rhs.begin(); p != lhs.end(); ++p, ++q) {//马上我再写个下标运算符。。。
			if (*p != *q) {
				flag = false;
				break;
			}
		}
	}
	return flag;
}
#endif