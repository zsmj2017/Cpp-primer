#ifndef TextQuery_H
#define TextQuery_H

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string> 
#include <fstream>
#include <memory>
#include <sstream>

using namespace::std;
class QueryResult;

class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery() = default;
	TextQuery(ifstream &);
	QueryResult query(const string &) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &input) {
	string line;
	line_no number=0;
	while (getline(input, line)) {
		file->push_back(line);
		istringstream linestream(line);
		string word;
		while (linestream >> word) {
			auto &lines = wm[word];//lines��һ��shared_ptr
			if (!lines) {//��һ������wordʱ��ָ��Ϊ��
				lines.reset(new set<line_no>);//����һ�θ�set���ڴ棬������linesָ��ö��ڴ�
				(*lines).insert(number);
			}
		}
	}
	++number;
}

QueryResult TextQuery::query(const string &s) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(s);
	if (loc == wm.cend()) {
		return QueryResult(s, file, nodata);
	}
	else return QueryResult(s, file, loc->second);
}

class QueryResult {
friend void print(ostream &os, QueryResult &q);
public:
	QueryResult() = default;
	QueryResult(const string & s, shared_ptr<vector<string>> f,
		shared_ptr<set<TextQuery::line_no>> l) :
		sought(s), file(f), line(l) {};
	shared_ptr<vector<string>> get_file() { return file; }
	set<TextQuery::line_no>::iterator begin();
	set<TextQuery::line_no>::iterator end();

private:
	string sought;
	shared_ptr<vector<string>> file;
	shared_ptr<set<TextQuery::line_no>> line;
};

set<TextQuery::line_no>::iterator QueryResult::begin() {
	return line->begin();
}

set<TextQuery::line_no>::iterator QueryResult::end() {
	return line->end();
}

void print(ostream &os, QueryResult &q) {
	os << q.sought << " occurs" << q.line->size() << " times." << endl;
	for (auto num : *q.line) {
		os << "\t" << "(line " << num + 1 << ")" << " " << (*q.file)[num] << endl;
	}
}

#endif

