#ifndef NOTQUERY_H
#define NOTQUERY_H

#include "Query.h"

class NotQuery :public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q):query(q) {}
	std::string rep() const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const;
	Query query;
};

inline Query operator~(const Query &operand) {
	//shared_ptr<Query_base> tmp(new NotQuery(expr));
	//return Query(tmp)
	//return语句隐式地使用了一个Query构造函数
	//居然还能这样写？
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const {
	auto result = query.eval(text);
	auto ret_lines = make_shared<set<line_no>>();//指向空set的智能指针
	auto beg = result.begin(), end = result.end();//指向保存有行号的set的begin与end
	//对于输入的每一行 如果该行不在result中 则加入这一行
	auto sz = result.get_file()->size();//读取的text的行数
	for (size_t n = 0; n != sz; ++n) {//遍历
		if (beg == end || n != *beg) ret_lines->insert(n); //并未查到数据或者当前行并未出现在result当中
		else if (beg != end) ++beg;
	}
	return QueryResult(rep(), result.get_file(), ret_lines);
}

#endif // !NOTQUERY_H

