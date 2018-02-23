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
	Quote(Quote &&) noexcept;//移动初始化
	Quote& operator=(const Quote &);
	Quote& operator=(Quote &&) noexcept;//移动赋值
	bool operator!=(const Quote &);
	virtual ~Quote() = default;
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return n*price; }
	virtual Quote* clone() const & { return new Quote(*this); }//只允许this为左值时调用
	//显然移动完之后这个对象就析构了
	virtual Quote* clone() && noexcept{return new Quote(std::move(*this)); }//表示这个函数只对this对象被调用的时候在外部右值引用的时候有效，可以用来做奇怪的重载。
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
	//析构自身
	bookNo = rhs.bookNo;
	price = rhs.price;
}

inline Quote & Quote::operator=(Quote &&rhs) noexcept{//移动运算符必须检查移动自身的情况
	//析构自身
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

double print_total(ostream &os, const Quote &item, size_t n) {//我认为print函数不应该加以格式化 而是让用户进行定制
	//但是事实上basket中使用了该接口 还是应该输出换行符为宜
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold:" << n << "total due: " << ret << endl;
}

class Disc_quote :public Quote {//Disc_quote根本无法创建一个对象 因此不需要拷贝控制成员
public:
	Disc_quote() = default;
	Disc_quote(const string &str, double p, size_t qty, double disc) :
		Quote(str, p), quantity(qty), discount(disc) {};//使用Quote的构造函数来完成对继承自基类成员的初始
	virtual ~Disc_quote() = default;
	virtual double net_price(size_t) const = 0;//纯虚函数
protected:
	size_t quantity;
	double discount;
};

class Bulk_Quote :public Disc_quote {
public:
	using Disc_quote::Disc_quote;//继承构造函数
	Bulk_Quote() = default;
	Bulk_Quote(const string &str, double p, size_t qty, double disc) :
		Disc_quote(str,p,qty,disc) {};
	Bulk_Quote(const Bulk_Quote&);//这些怎么写呢？？
	Bulk_Quote(Bulk_Quote &&);
	Bulk_Quote& operator=(const Bulk_Quote&);
	Bulk_Quote& operator=(Bulk_Quote &&);
	~Bulk_Quote() = default;
	double net_price(size_t) const override;//覆盖基类版本
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
	//定义了一个装有指向quote类型对象的smartptr的mutiset
	//该mutiset使用compare函数进行排序 decltype(compare)得到的是函数类型 加上*表示函数指针
	//mutiset成员的名字是items 我们对其进行初始化并且使用compare函数
	//也可以写为items(compare) || items(&compare)
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
};

inline void Basket::add_item(const Quote & sale){
	items.insert(shared_ptr<Quote>(sale.clone()));
}

inline void Basket::add_item(Quote && sale){
	items.insert(shared_ptr<Quote>(std::move(sale).clone()));
}

inline double Basket::total_receipt(ostream &os) const{//输出当前的购物车，并且计算购物车总价
	double sum = 0.0;
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {//iter跳转到下一个不小于它的位置 即跳过关键词相同的元素
		sum += print_total(os, **iter, items.count(*iter));//*iter是一个智能指针，**iter是一个
	}
	os << "Total Sale: " << sum << endl;
	return sum;
}

#endif