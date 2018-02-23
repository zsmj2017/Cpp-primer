#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <Windows.h>

using namespace::std;

void example_0(void) {
	map<string, size_t> word_count;
	set<string> exclude;
	string word;
	while (cin >> word) {
		if(exclude.find(word)==exclude.end())
		++word_count[word];
	}
	for (const auto &w : word_count) {
		cout << w.first << " occurs " << w.second << " times." << endl;
	}
}

void transmit_word(string &s) {
	for (string::size_type index = 0; index != s.size(); ++index) {
		if (ispunct(s[index])) s.erase(index,1), --index;
		if (isupper(s[index])) s[index] = tolower(s[index]);
	}
}


void exercise_0(void) {
	map<string, size_t> word_count;
	string word;
	while (cin >> word) {
		transmit_word(word);
		++word_count[word];
		}
	for (const auto &w : word_count) {
		cout << w.first << " occurs " << w.second << " times." << endl;
	}
}

//�ó��������հ汾
/*void add_familymembers(map<string, vector<string>> &m, const string &s1,const string &s2) {
		m[s1].push_back(s2);
}

void print_family(const map<string, vector<string>> &m) {
	for (const auto &w : m) {
		for (const auto &s : w.second) {
			cout << w.first << s << endl;
		}
	}
}*/

void add_vector_member(vector<int> &v,const int i) {
	if (find(v.cbegin(), v.cend(), i) == v.end()) {
		v.push_back(i);
		cout << "��ӳɹ�~" << endl;
	}
	else cout << "���ʧ�ܣ�" << endl;
	for (auto i : v) cout << i << " ";
	cout << endl;
}

void add_family(map<string, vector<pair<string, string>>> &m, 
				const string &surname, const string &name, const string &date) {
	m[surname].push_back({ name,date });
}

void print_family(const map<string, vector<pair<string, string>>> &m) {
	for (const auto &w : m) {
		for (const auto &i : w.second) {
			cout << w.first << i.first <<" " << i.second << endl;
		}
	}
}

void print_family_iter(const map<string, vector<pair<string, string>>> &m) {
	auto map_it = m.cbegin();
	while (map_it != m.cend()) {
		for (const auto &i : map_it->second) {
			cout << map_it->first << i.first << " " << i.second;
			cout << endl;
		}
		++map_it;
	}
}

void exercise_1(void) {
	map<int, int> map_int;
	map<int, int>::iterator map_iter;
	map_iter = map_int.begin();
	map_iter->second = 0;//ֻ���޸�value�������޸�key Ҳ����˵map_iter->first������Ϊ��ֵ
}

void exercisse_2(void) {
	map<string, size_t> word_count;
	string word;
	while (cin >> word) {
		/*auto ret = word_count.insert({ word,1 });
		if (!ret.second) {
			++(*ret.first).second;//ret��һ��pair������first��һ��������ָ����word���ڵ�pair������ʹ�ý����� Ҫ˵�������ҷ��ֹ�������������Ҳ�ǿ�����*�İ�
		}*/
		//�����޵м򻯰�
		++word_count.insert({ word,0 }).first->second;//�������Ԫ�أ�ֱ�ӽ�0����Ϊ��1������Ļ�������ָ����ԭ�е���key��Ӧ��value������
	}
}

//�Ҵ�δ������˴�������֪�ĳ���
pair<map<string, vector<int>>::iterator, bool> insert_map(map<string, vector<int>> &m,
														  const string &str,const vector<int> &v) {
	return m.insert({ str,v });
}

void add_familymember(multimap<string, vector<string>> &m,
					  const string &surname,const string &name) {
	//m[surname].push_back(name); ��ϧmultimap����ʹ���±�
	m.insert({ surname,vector<string>{name} });//ǿ�й�����һ��vector �ô�
}

void find_count_multimap(const multimap<string, string> &m, const string &search) {
	auto entries = m.count(search);
	auto iter = m.find(search);
	while (entries--) {
		cout << iter++->second << endl;
	}
}

void iter_multimap(const multimap<string, string> &m, const string &search) {
	auto beg = m.lower_bound(search);
	auto end = m.upper_bound(search);
	while (beg != end) {
		cout << beg->second << endl;
		++beg;
	}
}

void equal_range_multimap(const multimap<string, string> &m, const string &search) {
	auto pos = m.equal_range(search);
	while (pos.first != pos.second) {
		cout << pos.first->second << endl;
		++pos.first;
	}
}

map<string, int>::const_iterator map_find(const map<string, int> &m, const string &s) {//����β���const map ��ôfind���ص���һ��const_iterator
	return m.find(s);
}

void erase_multimap(multimap<string, string> &m, const string &s) {
	auto pos = m.equal_range(s);
	if (pos.first == pos.second)//�����δ���ҵ��Ŀշ�Χ equal_range���ص�pos��first��second����ָ��end������һ����ȫ�Ĳ���λ�� 
		cerr << "there is no element you want to find." << endl;
	else {
		while (pos.first != pos.second) {
			pos.first = m.erase(pos.first);
		}
	}
}

void print_multimap(const multimap<string, string> &m) {
	for (auto w : m) {
		cout << w.first << w.second << endl;
	}
}

map<string, string> & buildMap(ifstream &map_file) {
	map<string, string> trans_map;
	string key, value;
	while (map_file >> key&&getline(map_file, value)) {//getline����ȡ����key֮��Ĳ��� 
		if (value.size() > 1) trans_map[key] = value.substr(1);//�������ת������ ��������ȡ��ǰ�ÿո�
		else throw runtime_error("no rule for" + key);
	}
	return trans_map;
}

const string & transform(string &str, const map<string, string> &m) {
	auto iter = m.find(str);
	if (iter != m.cend()) {
		return str = iter->second;
	}
	else return str;
}

void word_transform(ifstream &map_file, ifstream &input_file) {
	map<string, string> trans_map = buildMap(map_file);
	string line;//�����ȡ����ÿһ��
	while (getline(input_file, line)) {
		istringstream stream(line);//��lineתΪһ��string��
		bool firstword = true;
		string word;
		while (stream >> word) {//��ȡÿһ���ڵĵ��� ʹ��string���������Ӵ�string����ȡ����ҧ����
			if (firstword) firstword = false;//����Ƿ�Ϊ��һλ
			else cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

void unordered_map_count(void) {
	unordered_map<string, size_t> word_count;
	string word;
	while (cin >> word) {
		++word_count[word];
	}
	for (const auto &w : word_count) {
		cout << w.first << " occurs " << w.second << " times." << endl;
	}
}



int main(void) {
	system("pause");
}