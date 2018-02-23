#ifndef BINARYQUERY_H
#define BINARTQUERY_H

#include "Query.h"

class BinaryQuery:public Query_base{//³éÏó»ùÀà
protected:
	BinaryQuery(const Query &l,const Query &r,const std::string &s):
		lhs(s),rhs(r),opSym(s) {}
	std::string rep() const {
		return "(" + lhs.rep() + " " + opSym + " " + rhs.rep + ")";
	}
	Query lhs, rhs;
	std::string opSym;
};

#endif // !BINARYQUERY

