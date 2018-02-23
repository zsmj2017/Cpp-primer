#ifndef ANDQUERY_H
#define ANDQUERY_H

#include"BinaryQuery.h"
#include <algorithm>
#include <iterator>

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query &, const Query &);
	AndQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") {}
	QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
QueryResult AndQuery::eval(const TextQuery& text) const {
	auto left = lhs.eval(text), right = rhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	//标准库算法 合并两个set 并且最后一个是插入迭代器
	//前4个参数表示目标数据的范围，选出这两个范围中共同出现的元素
	//最后一个形参表示目的位置，这里是一个插入迭代器
	//inserter的第一个形参是一个容器 第二是指向该容器的一个迭代器 向其赋值等价于总把一个元素插入到这个指定位置之前
	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), left.get_file(), ret_lines);
}
#endif // !ANDQUERY_H

