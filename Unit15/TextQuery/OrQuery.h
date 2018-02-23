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
	//ͨ��Query��Աlhs��rhs���е������
	//����ÿ����������QueryResult
	auto right = rhs.eval(text), left = rhs.eval(text);
	//�½���һ��set,����������кſ��������set�У�����һ������ָ��ָ����
	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	//�ڴ�set�в����Ҳ������к�
	ret_lines->insert(right.begin(), right.end());
	//������ʱ������QueryResult
	return QueryResult(rep(), left.get_file(),ret_lines);//left��rightָ��ͬһ���ļ�
}
#endif // !ORQUERY_H

