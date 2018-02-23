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
	//һ����� ����ʹ��һ����ģ��ʱ�����ṩģ��ʵ��
	//������һ������ ������һ����ģ����������п���ֱ��ʹ��ģ���������ṩʵ��
	//�����ﷵ�ص���BlobPtr& ������BlobPtr<T>& �����ǵȼ۵�
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
inline BlobPtr BlobPtr<T>::operator++(int){//���÷���һ����������������
	BlobPtr ret = *this;//������һ�������������������ʱ���ɿ���Ϊ����������
	++*this;//����������Ķ���Ӧ��ʹ��ǰ��������Ľӿڣ������˼�����
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
