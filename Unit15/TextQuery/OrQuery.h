#ifndef ORQUERY_H
#define ORQUERY_H

#include "BinaryQuery.h"

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query &, const Query &);
	OrQuery(const Query &l, const Query &r):BinaryQuery(l, r, "|") {}
	QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const {
	//通过Query成员lhs与rhs进行的虚调用
	//返回每个运算对象的QueryResult
	auto right = rhs.eval(text), left = rhs.eval(text);
	//新建了一个set,将左侧对象的行号拷贝到结果set中，并用一个智能指针指向它
	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	//在此set中插入右侧对象的行号
	ret_lines->insert(right.begin(), right.end());
	//返回临时创建的QueryResult
	return QueryResult(rep(), left.get_file(),ret_lines);//left和right指向同一个文件
}
#endif // !ORQUERY_H

