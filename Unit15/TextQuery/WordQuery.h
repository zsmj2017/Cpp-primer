#ifndef WORDQUERY_H
#define WORDQUERY_H

#include "Query.h"

class WordQuery:public Query_base {
	friend class Query;
	WordQuery(const string &s):query_word(s) {}//˽�еĹ��캯�� �Է���query����
	QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
	std::string rep() const { return query_word; }
	std::string query_word;
};

#endif

