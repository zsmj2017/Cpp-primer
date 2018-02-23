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
	//return�����ʽ��ʹ����һ��Query���캯��
	//��Ȼ��������д��
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const {
	auto result = query.eval(text);
	auto ret_lines = make_shared<set<line_no>>();//ָ���set������ָ��
	auto beg = result.begin(), end = result.end();//ָ�򱣴����кŵ�set��begin��end
	//���������ÿһ�� ������в���result�� �������һ��
	auto sz = result.get_file()->size();//��ȡ��text������
	for (size_t n = 0; n != sz; ++n) {//����
		if (beg == end || n != *beg) ret_lines->insert(n); //��δ�鵽���ݻ��ߵ�ǰ�в�δ������result����
		else if (beg != end) ++beg;
	}
	return QueryResult(rep(), result.get_file(), ret_lines);
}

#endif // !NOTQUERY_H

