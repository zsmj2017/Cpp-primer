#ifndef BLOB_H
#define BLOB_H

#include <vector>
#include <string>
#include <memory>

//��ģ��ʵ�ֺ�������������ͬһ��ͷ�ļ���
//�޷�������������

template<typename T> class BlobPtr;
template<typename T> class Blob;
template<typename T> bool operator==(const Blob<T> &,const Blob<T> &);

template <typename T> class Blob {//���ñ�׼��vectorʵ�ֵ�һ��С����
	friend class BlobPtr<T>;//�Ѻù�ϵ���޶�����ͬ����ʵ������blob��blobptr֮��
	friend bool operator==<T>(const Blob<T> &, const Blob<T> &);//��������Ԫʱ��Ҫ����<T>����
public:
	typedef T value_type;
	//typename ��ʽ�ظ��߱����� std::vector<T> ��һ�������� ������һ��������
	typedef typename std::vector<T>::size_type size_type;
	Blob();
	Blob(std::initializer_list<T> il);
	template<typename It> Blob(It b, It e);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T&t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();
	T& begin();
	T& back();
	T& operator[](size_type);
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const std::string &msg) const;
};

template<typename T> 
Blob<T>::Blob() :data(std::make_shared<std::vector<T>>()) {}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}

template<typename T>
void Blob<T>::pop_back() {
	check(0, "There is no element in the blob!");
	data->pop_back();
}

template<typename T>
inline T & Blob<T>::begin(){
	return Blob<T>[0];
}

template<typename T>
T & Blob<T>::back() {
	return data->back();
}

template<typename T>
T & Blob<T>::operator[](size_type) {
	return (*data)[i];
}

template<typename T>
void Blob<T>::check(size_type i, const std::string & msg) const {
	if (i >= data->size())
		throw std::out_of_range(msg);
}

template<typename T>
inline bool operator==(const Blob<T>&lhs, const Blob<T>&rhs){
	if (lhs.size() == rhs.size()) return false;
	for (size_t index = 0; index != lhs.size(); ++index) {
		if (lhs[index] != rhs[index]) return false;//������Ҫ�����ڲ���Ԫ��֧��==
	}
	return true;
}

template<typename T>
template<typename It>
inline Blob<T>::Blob(It b, It e){
	data(std::make_shared(std::vector<T>(b, e)));
}

#endif // !BLOB_H
