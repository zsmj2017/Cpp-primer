#ifndef QUERY_H
#define QUERY_H

#include "Query_base.h"
//尽可能不要在h中使用using namespace：：std 这样可能会造成污染
class Query {//管理query_base的接口类
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);
public:
	Query(const std::string &);
	QueryResult eval(const TextQuery &t) const  { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query):q(query) {}
	std::shared_ptr<Query_base> q;
};

inline Query::Query(const std::string &s):q(new WordQuery(s)) {}//该构造函数分配一个wordquery 令其smartptr指向该对象

std::ostream & operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
}

#endif

