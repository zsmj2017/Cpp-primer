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
	StrVec(initializer_list<string>);//Ϊɶ�������������� ��Ϊinitializer_list��������Ԫ�� ����ʵ�ֵײ㹲��
	StrVec(const StrVec &);//��Ȼvector����ֵ����
	StrVec(StrVec &&) noexcept;//�ƶ����캯����Ӧ���׳��κ��쳣
	StrVec& operator=(const StrVec &);
	StrVec& operator=(initializer_list <string>);
	StrVec& operator=(StrVec &&) noexcept; 
	string& operator[](size_t n) { return elements[n]; }//�±������ͨ���ᶨ��const�汾�ͷǳ�����
	string& operator[](size_t n) const { return elements[n]; }//��һ��ָ��ֱ��ʹ���±�������ȼ���*��elements+n��
	~StrVec();
	void push_back(const string &);
	void push_back(string &&);
	void reserve(size_t);
	void resize(size_t);//������resize��reserveӦ�õ���ĳ�����ɲ��ƶ�n��Ԫ�ص�reallocate���� �����������ع���
	void resize(size_t, const string &);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin() const { return elements; }
	string* end() const { return first_free; }
private:
	static allocator<string> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	pair<string*, string*> alloc_n_copy(const string *, const string *);
	void free();//����Ԫ�� �ͷ��ڴ�
	void reallocate();//���·����ڴ� ���ҿ�������Ԫ��
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

StrVec::StrVec(const StrVec &rhs) {//���ǲ�û�з���ͬ�����capacity ��Ϊ�޷���λ��first_free��ԭ��
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());//��rhs���� newdataΪһ��pair
	elements = newdata.first;
	first_free = cap = newdata.second;
}

inline StrVec::StrVec(StrVec && s) noexcept	:elements(s.elements),first_free(s.first_free),cap(s.cap){
	s.elements = s.first_free = s.cap = nullptr;//��ָ����Ϊ�գ�ȷ���ƺ�Դ�����ܹ�����������
}

inline StrVec & StrVec::operator=(const StrVec &rhs)
{
	free();
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

inline StrVec & StrVec::operator=(initializer_list<string> il){//initializer����Ҫ�Ը�ֵ���
	free();
	auto p = alloc_n_copy(il.begin(), il.end());
	elements = p.first;
	cap = first_free = p.second;
	return *this;
}

inline StrVec & StrVec::operator=(StrVec &&rhs) noexcept{
	if (this != &rhs) {//ֱ�Ӽ���ǲ����Ը�ֵ
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
	alloc.construct(first_free++, std::move(s));//constructĬ�ϲ��ÿ�����ʽ���� �˴�����ʹ��move���й��� �Ż�����
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

inline void StrVec::resize(size_t n){//ֵ��ע�����resize��n������capacity������²���ı�capacity
	if (n <= size()) {
		for (auto p = elements + n; p != first_free; ++p) {
			alloc.destroy(p);//����detroy��������ͷ��ڴ�
		}
	}
	else if (n > size() && n <= capacity()) {
		for (auto p = first_free; p != elements + n; ++p) {
			alloc.construct(p, string());//�����string
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
			alloc.destroy(p);//����detroy��������ͷ��ڴ�
		}
	}
	else if (n > size() && n <= capacity()) {
		for (auto p = first_free; p != elements + n; ++p) {
			alloc.construct(p, s);//�����string
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

void StrVec::free() {//����destroy����Ԫ�� Ȼ���ͷ��ڴ�
	/*for (auto beg = elements; beg != first_free; ++beg) {
		alloc.destroy(beg);
	}
	alloc.deallocate(elements, capacity());*/
	for_each(elements, first_free, [](string &s) {alloc.destroy(&s); });//lambda��ʹ��ʱʵ���˽����� �����β���ʵ���ַ��� ����destoryҪȡ���ַ
	alloc.deallocate(elements, capacity());
}

inline void StrVec::reallocate()//��Ȼ����string������п���Ȼ��������һ�ʺܴ�Ŀռ��ʱ�俪��
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	/*auto last = newdata;//ָ���������е���һ������λ��
	auto elem = elements;//ָ��������е���һ��Ԫ��
	for (size_t i = 0; i != size(); ++i) {
		//����move���صĽ���ᵼ��constructʹ��string���ƶ����캯��
		//string������ڴ治�ᱻ����
		//���ǹ����ÿһ��string�����elem��ָ��string����ӹ��ڴ�����Ȩ
		alloc.construct(dest++, std::move(*elem++));//ע��һ��Ҫstd::move ͨ��string���ƶ����캯����construct
	}*/
	auto last = uninitialized_copy(make_move_iterator(elements), make_move_iterator(cap), newdata);//make_move_iterator����ͨ������תΪ�ƶ�������
	free();
	elements = newdata;
	first_free = last;
	cap = elements + newcapacity;
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
	//pair�ڱ�����ָ���¿ռ���׵�ַ�Ϳ���β���ַ
	auto data = alloc.allocate(e - b);
	return { data,uninitialized_copy(b,e,data) };
}

inline bool operator==(const StrVec &lhs, const StrVec &rhs) {
	bool flag = true;
	if (lhs.size() == rhs.size()) {
		for (size_t index = 0;index!=lhs.size();++index) {//���϶�����±������ ��������鷳����
			if (*(lhs.elements + index) != *(rhs.elements + index)) {//����Ŀ����ʹ��string���==
				flag = false;
				break;
			}
		}
	}
}

inline bool operator!=(const StrVec &lhs, const StrVec &rhs){
	return !(lhs==rhs);
}

class Str {//�����϶�˽�г�Ա�ͺ�������ȡͬ��������
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
		for (auto p = lhs.begin(), q = rhs.begin(); p != lhs.end(); ++p, ++q) {//��������д���±������������
			if (*p != *q) {
				flag = false;
				break;
			}
		}
	}
	return flag;
}
#endif