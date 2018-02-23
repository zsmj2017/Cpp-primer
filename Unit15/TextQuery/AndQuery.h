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
	//��׼���㷨 �ϲ�����set �������һ���ǲ��������
	//ǰ4��������ʾĿ�����ݵķ�Χ��ѡ����������Χ�й�ͬ���ֵ�Ԫ��
	//���һ���βα�ʾĿ��λ�ã�������һ�����������
	//inserter�ĵ�һ���β���һ������ �ڶ���ָ���������һ�������� ���丳ֵ�ȼ����ܰ�һ��Ԫ�ز��뵽���ָ��λ��֮ǰ
	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), left.get_file(), ret_lines);
}
#endif // !ANDQUERY_H

