#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>
#include <set>
#include <utility>

using namespace::std;

class Quote {
public:
	Quote() = default;
	Quote(const string &str, double d) :bookNo(str), price(d) {};
	Quote(const Quote&);
	Quote(Quote &&) noexcept;//�ƶ���ʼ��
	Quote& operator=(const Quote &);
	Quote& operator=(Quote &&) noexcept;//�ƶ���ֵ
	bool operator!=(const Quote &);
	virtual ~Quote() = default;
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return n*price; }
	virtual Quote* clone() const & { return new Quote(*this); }//ֻ����thisΪ��ֵʱ����
	//��Ȼ�ƶ���֮����������������
	virtual Quote* clone() && noexcept{return new Quote(std::move(*this)); }//��ʾ�������ֻ��this���󱻵��õ�ʱ�����ⲿ��ֵ���õ�ʱ����Ч��������������ֵ����ء�
private:
	string bookNo;
protected:
	double price = 0.0;
};

inline Quote::Quote(const Quote &q){
	bookNo = q.bookNo;
	price = q.price;
}

inline Quote::Quote(Quote &&q) noexcept{
		bookNo = std::move(q.bookNo);
		price = std::move(q.price);
}

inline Quote & Quote::operator=(const Quote &rhs)
{
	//��������
	bookNo = rhs.bookNo;
	price = rhs.price;
}

inline Quote & Quote::operator=(Quote &&rhs) noexcept{//�ƶ�������������ƶ���������
	//��������
	if (*this != rhs) {
		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);
	}
	return *this;
}

inline bool Quote::operator!=(const Quote &rhs)
{
	bool flag = true;
	if (bookNo != rhs.bookNo || price != rhs.price) flag = false;
	return flag;
}

double print_total(ostream &os, const Quote &item, size_t n) {//����Ϊprint������Ӧ�ü��Ը�ʽ�� �������û����ж���
	//������ʵ��basket��ʹ���˸ýӿ� ����Ӧ��������з�Ϊ��
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold:" << n << "total due: " << ret << endl;
}

class Disc_quote :public Quote {//Disc_quote�����޷�����һ������ ��˲���Ҫ�������Ƴ�Ա
public:
	Disc_quote() = default;
	Disc_quote(const string &str, double p, size_t qty, double disc) :
		Quote(str, p), quantity(qty), discount(disc) {};//ʹ��Quote�Ĺ��캯������ɶԼ̳��Ի����Ա�ĳ�ʼ
	virtual ~Disc_quote() = default;
	virtual double net_price(size_t) const = 0;//���麯��
protected:
	size_t quantity;
	double discount;
};

class Bulk_Quote :public Disc_quote {
public:
	using Disc_quote::Disc_quote;//�̳й��캯��
	Bulk_Quote() = default;
	Bulk_Quote(const string &str, double p, size_t qty, double disc) :
		Disc_quote(str,p,qty,disc) {};
	Bulk_Quote(const Bulk_Quote&);//��Щ��ôд�أ���
	Bulk_Quote(Bulk_Quote &&);
	Bulk_Quote& operator=(const Bulk_Quote&);
	Bulk_Quote& operator=(Bulk_Quote &&);
	~Bulk_Quote() = default;
	double net_price(size_t) const override;//���ǻ���汾
	Bulk_Quote* clone() const & override { return new Bulk_Quote(*this); }
	Bulk_Quote* clone() && noexcept override {return new Bulk_Quote(std::move(*this)); }
};


inline double Bulk_Quote::net_price(size_t n) const {
	if (n >= quantity) 
		return n*(1 - discount)*price;
	else
		return n*price;
}

class Basket {
public:
	void add_item(const Quote&sale);
	void add_item(Quote &&sale);
	double total_receipt(ostream&) const;
private:
	static bool compare(const shared_ptr<Quote> &lhs,const shared_ptr<Quote> &rhs) {
		return lhs->isbn() < rhs->isbn();
	}
	//������һ��װ��ָ��quote���Ͷ����smartptr��mutiset
	//��mutisetʹ��compare������������ decltype(compare)�õ����Ǻ������� ����*��ʾ����ָ��
	//mutiset��Ա��������items ���Ƕ�����г�ʼ������ʹ��compare����
	//Ҳ����дΪitems(compare) || items(&compare)
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
};

inline void Basket::add_item(const Quote & sale){
	items.insert(shared_ptr<Quote>(sale.clone()));
}

inline void Basket::add_item(Quote && sale){
	items.insert(shared_ptr<Quote>(std::move(sale).clone()));
}

inline double Basket::total_receipt(ostream &os) const{//�����ǰ�Ĺ��ﳵ�����Ҽ��㹺�ﳵ�ܼ�
	double sum = 0.0;
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {//iter��ת����һ����С������λ�� �������ؼ�����ͬ��Ԫ��
		sum += print_total(os, **iter, items.count(*iter));//*iter��һ������ָ�룬**iter��һ��
	}
	os << "Total Sale: " << sum << endl;
	return sum;
}

#endif