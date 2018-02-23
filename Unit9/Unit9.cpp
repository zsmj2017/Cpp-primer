#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <Windows.h>

using namespace::std;

bool find_int(vector<int>::const_iterator beg,vector<int>::const_iterator end,int i) {
	bool flag = false;
	while (beg != end) {
		if (*beg == i) { flag = true; return flag; }
		beg++;
	}
	return flag;
}

int findInt(vector<int>::const_iterator beg, vector<int>::const_iterator end, int i) {
	while (beg != end) {
		if (*beg == i) return *beg;
		beg++;
	}
	cout << "There is nothing that you want to find.";
	return -1;
}

bool equInt(vector<int> &v1, list<int> &l1) {
	if (v1.size() != l1.size()) return false;
	else {
		auto vbeg = v1.cbegin();
		auto lbeg = l1.cbegin();
		while (vbeg != v1.cend()) {
			if (*vbeg != *lbeg) return false;
			vbeg++, lbeg++;
		}
	}
	return true;
}

void exercise_0(void) {
	deque<string> d;
	string word;
	while (cin >> word) {
		d.push_back(word);
	}
	for (auto iter=d.cbegin();iter!=d.cend();++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}

void exercise_1(void) {
	list<string> l;
	string word;
	while (cin >> word) {
		l.push_back(word);
	}
	for (auto iter = l.cbegin(); iter != l.cend(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}

void copyNum(const list<int>  &l, deque<int> &d1, deque<int> &d2) {
	for (auto lbeg = l.cbegin(); lbeg != l.cend(); ++lbeg) {
		if (*lbeg % 2) d1.push_back(*lbeg);
		else d2.push_back(*lbeg);
	}
}

void exercise_2(const vector<int> &r) {
	cout << *r.cbegin() << endl;
	cout << r.front() << endl;
	cout << r[0] << endl;
	cout << r.at(0) << endl;
}

void exercise_3(int a[], list<int> &l, vector<int> &v) {
	l.assign(&a[0], &a[10]);//顺序拷贝数组的好方法，不过要数一下数组大小
	v.assign(&a[0], &a[10]);
	auto lbeg = l.begin();
	while (lbeg != l.end()) {
		if (*lbeg % 2) lbeg = l.erase(lbeg);
		else ++lbeg;
	}
	auto vbeg = v.begin();
	while (vbeg != v.end()) {
		if (*vbeg % 2) ++vbeg;
		else vbeg = v.erase(vbeg);
	}
}

void  exercise_4(forward_list<int> &flst) {
	auto prev = flst.before_begin();
	auto curr = flst.begin();
	while (curr != flst.end()) {
		if (*curr % 2) {
			++curr;
			++prev;
		}
		else {
			curr = flst.erase_after(prev);
		}
	}
	for (auto i : flst) cout << i << " ";
	cout << endl;
}

void insertStr(forward_list<string> &flst, const string &a, const string &b) {
	auto prev = flst.before_begin();
	auto curr = flst.begin();
	while (curr != flst.end()) {
		if (*curr == a) {
			flst.insert_after(curr, b);
			break;
		}
		++curr;
		++prev;
	}
	if(curr==flst.end()) flst.insert_after(prev, b);
	for (auto str : flst) cout << str << " ";
	cout << endl;
}

void wordReplace(string &s, const string &oldValue,const string &newValue) {
	string::size_type index = 0;
	string::iterator  posbeg, posend;
	for (auto beg = s.begin(); beg != s.end()-(oldValue.size()-1); ++beg) {//最后小于oldvalue长度的元素不需要检测
		for (; index != oldValue.size(); ++index) {
			if (*(beg + index) == oldValue[index]) continue;
			else {
				index = 0;
				break;
			}
		}
		if (index == oldValue.size()) {
			posbeg = beg;
			posend = posbeg + oldValue.size()-1;
			auto insertit = s.erase(posbeg, posend + 1);//删除了oldValue 因为左闭右开所以+1 要注意erase之后posbeg posend均已经无效 所以返回值指向删除后的第一个元素
			beg=s.insert(insertit, newValue.cbegin(), newValue.cend())+newValue.size();//将迭代器移动到插入元素后的第一个元素
			index = 0;
		}
	}	
}

string exercise_5(string &s, const string &prefix, const string & suffix) {
	s.insert(s.cbegin(),prefix.cbegin(),prefix.cend());
	s.append(suffix);
	return s;
}

void findNums(const string &str, string &s1, string &s2) {
	vector<string::size_type> vnum, vword;
	string::size_type pos=0;
	string nums = "0123456789";
	while ((pos = str.find_first_of(nums,pos)) != string::npos) {
		vnum.push_back(pos);
		++pos;
	}
	pos = 0;
	while ((pos = str.find_first_not_of(nums, pos)) != -1) {
		vword.push_back(pos);
		++pos;
	}
	for (auto i : vnum) {
		s1.push_back(str[i]);
	}
	for (auto i : vword) {
		s2.push_back(str[i]);
	}
}

void exercise_6(void) {
	vector<string> vstr;
	string word;
	while (cin >> word) {
		vstr.push_back(word);
	}
	string nums = "0123456789";
	string::size_type pos = 0, maxlen = 0;
	string maxlenstr;
	for (auto str : vstr) {
		if ((pos = str.find_first_of(nums, pos)) != string::npos) {
			pos = 0;
			continue;
		}
		else {
			if (maxlen < str.size()) {
				maxlen = str.size();
				maxlenstr = str;
		   }
			pos = 0;
		}
	}
	cout << maxlen <<" " << maxlenstr << endl;
}

void sumStr(const vector<string> &v) {
	bool intflag = true;
	string::size_type pos = 0;
	int intSum = 0;
	double doubleSum = 0;
	for (auto str : v) {
		if ((pos = str.find(".")) != string::npos) {
			intflag = false;
			break;
		}
	}
	if (intflag) {
		for (auto str : v) intSum += stoi(str);
		cout << intSum << endl;
	}
	else {
		for (auto str : v) doubleSum += stod(str);
		cout << doubleSum << endl;
	}
}

int main(void) {
	vector<string> v = { "1","2.2","3","4.1" };
	sumStr(v);
	system("pause");
}
