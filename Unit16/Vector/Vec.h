#ifndef VEC_H
#define VEC_H

#include <memory>
#include <utility>
#include <iterator>
#include <algorithm>

template <typename T> class Vec;
template <typename T> bool operator!=(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator==(const Vec<T>&, const Vec<T>&);

template <typename T>
class Vec {
	friend bool operator!=<T>(const Vec<T>&, const Vec<T>&);
	friend bool operator==<T>(const Vec<T>&, const Vec<T>&);
public:
	Vec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
	Vec(std::initializer_list<T>);
	//���������ں���ģ�����
	Vec(const Vec&);
	Vec(const Vec&&) noexcept;
	Vec& operator=(const Vec&);
	Vec& operator=(const Vec&&) noexcept;
	Vec& operator=(std::initializer_list<T>);
	T& operator[](size_t n) { return elements[n]; }//�±������ͨ����Ҫ����const���const��
	T& operator[](size_t n) const { return elements[n]; }
	~Vec();
	void push_back(const T&);
	void push_back(T&&) noexcept;
	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const T&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T* begin() const { return elements; }//����������� �Ժ�����÷�Χfor
	T* end() const { return first_free; }
	template <class...Args> 
	void emplace_back(Args&&...args);
private:
	static std::allocator<T> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<T*, T*> alloc_n_copy(const T*, const T*);
	void free();
	void reallocate();
	void reallocate_n(size_t);
	T* elements;
	T* first_free;
	T* cap;
};

template<typename T> std::allocator<T> Vec<T>::alloc;

template<typename T>
inline std::pair<T*, T*> Vec<T>::alloc_n_copy(const T *b, const T *e)
{
	auto data = alloc.allocate(e - b);
	return{ data,std::uninitialized_copy(b,e,data) };
}

template<typename T>
inline void Vec<T>::free() {
	std::for_each(elements, first_free, [](T &t) {alloc.destroy(&t); });//for_each���������һ�¡��������bug���˰���
	alloc.deallocate(elements, capacity());
}

template<typename T>
inline void Vec<T>::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto last = std::uninitialized_copy(std::make_move_iterator(elements), std::make_move_iterator(cap), newdata);
	free();
	elements = newdata;
	first_free = last;
	cap = elements + newcapacity;
}

template<typename T>
inline void Vec<T>::reallocate_n(size_t n){
	auto newdata = alloc.allocate(n);
	auto num = size();
	std::uninitialized_copy_n(std::make_move_iterator(begin()), n, newdata);
	free();
	elements = newdata;
	first_free = elements + num;
	cap = elements + n;
}

template<typename T>
inline Vec<T>::Vec(std::initializer_list<T> il) {//ͨ���÷��������Vec��������
	auto p = alloc_n_copy(il.begin(), il.end());
	elements = p.first;
	first_free = cap = p.second;
}

template<typename T>
inline Vec<T>::Vec(const Vec &v) {//��δ�������չ��capacity
	auto p = alloc_n_copy(v.begin(), v.end());
	elements = p.first;
	first_free = cap = p.second;
}

template<typename T>
inline Vec<T>::Vec(const Vec &&v) noexcept {
	auto newdata = alloc.allocate(v.size());
	unitialized_copy(make_move_iterator(elements), make_move_iterator(first_free), newdata);
	elements = newdata;
	first_free = cap = elements + v.size();
}

template<typename T>
inline Vec<T> & Vec<T>::operator=(const Vec &rhs){
	//���ǲ���Ҫ�����Ը�ֵ�������
	//�ȼ�¼ ���ͷ�
	auto p = alloc_n_copy(rhs.begin(),rhs.end());
	free();
	elements = p.first;
	cap = first_free = p.second;
	return *this;
}

template<typename T>
inline Vec<T> & Vec<T>::operator=(const Vec &&rhs) noexcept{
	if (*this != rhs) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

template<typename T>
inline Vec<T> & Vec<T>::operator=(std::initializer_list<T>il)
{
	free();
	auto p = alloc_n_copy(il.begin(), il.end());
	elements = p.first;
	cap = first_free = p.second;
	return *this;
}

template<typename T>
inline Vec<T>::~Vec(){
	free();
}

template<typename T>
inline void Vec<T>::push_back(const T &t){
	chk_n_alloc();
	alloc.construct(first_free++, t);
}

template<typename T>
inline void Vec<T>::push_back(T &&t) noexcept{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(t));
}

template<typename T>
inline void Vec<T>::reserve(size_t n){//��capacity���
	if (n > capacity()) reallocate_n(n);
}

template<typename T>
inline void Vec<T>::resize(size_t n) {//��size��� ֮ǰ�ƶ���֮�����Ǹ���ָ����
	if (n < size()) {
		std::for_each(begin() + n, first_free, [](T &t) {alloc.destroy(&t); });
		first_free = elements + n;
	}
	else if (n >= size() && n <= capacity()) {
		std::for_each(first_free, elements + n, [](T &t) {alloc.construct(&t, T()); });
		first_free = elements + n;
	}
	else if (n > capacity()) {
		reallocate_n(n);
		std::for_each(first_free, cap, [](T &t) {alloc.construct(&t, T()); });
		first_free = elements + n;
	}
}

template<typename T>
inline void Vec<T>::resize(size_t n, const T &arg){
	if (n < size()) {
		std::for_each(begin() + n, first_free, [](T &t) {alloc.destroy(&t); });
		first_free = elements + n;
	}
	else if (n >= size() && n <= capacity()) {
		std::for_each(first_free, elements + n, [arg](T &t) {alloc.construct(&t, arg); });
		first_free = elements + n;
	}
	else if (n > capacity()) {
		reallocate_n(n);
		std::for_each(first_free, cap, [arg](T &t) {alloc.construct(&t, arg); });
		first_free = elements + n;
	}
}

template<typename T>
inline bool operator!=(const Vec<T>&lhs, const Vec<T>&rhs) {
	if (lhs.size() != rhs.size()) return true;
	for (size_t index = 0; index != lhs.size(); ++index) {
		if (lhs[index] != rhs[index]) return true;
	}
	return false;
}

template<typename T>
inline bool operator==(const Vec<T>&lhs, const Vec<T>&rhs)
{
	return !(lhs != rhs);
}

#endif // !VEC_H

template<typename T>
template<class ...Args>
inline void Vec<T>::emplace_back(Args&& ...args){
	chk_n_alloc();
	alloc.construct(*first_free++, std::forward<Args>(args)...);
}
