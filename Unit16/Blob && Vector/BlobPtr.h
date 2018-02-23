#ifndef BLOBPTR_H
#define BLOBPTR_H

#include "Blob.h"

template <typename T> class BlobPtr {
public:
	BlobPtr():curr(0) {}
	BlobPtr(Blob<T> &a,size_t sz=0):wptr(a.data),curr(sz) {}
	T & operator*() const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	//一般而言 我们使用一个类模板时必须提供模板实参
	//但是有一个例外 就是在一个类模板的作用域中可以直接使用模板名而不提供实参
	//在这里返回的是BlobPtr& 而非是BlobPtr<T>& 它们是等价的
	BlobPtr& operator++();
	BlobPtr& operator--();
	BlobPtr operator++(int);
	BlobPtr operator--(int);
private:
	std::shared_ptr<std::vector<T>>
		check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};

template<typename T>
inline BlobPtr & BlobPtr<T>::operator++()
{
	check(curr, "dereference past end");
	++curr;
	return *this;
}

template<typename T>
inline BlobPtr & BlobPtr<T>::operator--(){
	check(--curr, "It is the first element!");
	return *this;
}

template<typename T>
inline BlobPtr BlobPtr<T>::operator++(int){//后置返回一个拷贝而非是引用
	BlobPtr ret = *this;//当遇到一个类型名及作用域符号时即可看作为进入作用域
	++*this;//后置运算符的定义应该使用前置运算符的接口，避免了检查操作
	return ret;
}

template<typename T>
inline BlobPtr BlobPtr<T>::operator--(int)
{
	auto ret = *this;
	--*this;
	return ret;
}

template<typename T>
inline std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string &msg) const {
	if (i >= wptr->size()) throw std::out_of_range(msg);
	return wptr.lock();
}

#endif
