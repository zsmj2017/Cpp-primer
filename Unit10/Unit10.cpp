#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <deque>
#include <Windows.h>

using namespace::std;

void exercise_0(void) {
	cout << "Please press into some numbers" << endl;
	vector<int> v;
	int num;
	while (cin >> num) {
		v.push_back(num);
	}
	cin.clear();//��Ϊctrl z�ȼ���EOF ������Ҫ������뻺���� �ڰ��µ�����get
	int value=0;
	cout << "Please press into which number you want to count : ";
	cin >> value;
	auto n = count(v.cbegin(), v.cend(), value);
	cout << value << " " << n << endl;
}

void exercise_1(void) {
	cout << "Please press into some words" << endl;
	vector<string> v;
	string word;
	while (cin >> word) {
		v.push_back(word);
	}
	cin.clear();
	string value;
	cout << "Please press into which word you want to count : ";
	cin >> value;
	auto n = count(v.cbegin(), v.cend(), value);
	cout << value << " " << n << endl;
}

int vectorSum(const vector<int> &v) {
	return accumulate(v.cbegin(), v.cend(), 0);
}

void exercise_2(void) {
	vector<int> v = { 0, 1, 2, 3, 4, 5 }, v1;
	fill_n(v.begin(), v.size(), 0);
	for (auto i : v) cout << i << " ";
	cout << endl;
	replace_copy(v.cbegin(), v.cend(), back_inserter(v1), 0, 6);
	for (auto i : v1) cout << i << " ";
	cout << endl;
}

bool isShorter(const string &s1, const string &s2) {
	return s1.size() < s2.size();
}

bool size_5(const string &s) {
	return s.size() < 5;
}

void elimDups( vector<string> &vstr) {
	stable_sort(vstr.begin(), vstr.end(),isShorter);
	auto end_unique = unique(vstr.begin(),vstr.end());
	vstr.erase(end_unique, vstr.end());
	for (auto s : vstr) cout << s << " ";
	cout << endl;
}

void exercise_3(vector<string> &v) {
	auto it = partition(v.begin(), v.end(), size_5);
	while (it != v.cend()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void exercise_4(void) {
	int n;
	auto lambda_0 = [](int a, int b) {return a + b; };
	auto lambda_1 = [n](int a) {return n + a; };
}

void biggles(vector<string> &v) {
	cout << "Please press into some words" << endl;
	string word;
	while (cin >> word) v.push_back(word);
	cin.clear();
	sort(v.begin(), v.end());
	auto end_unique = unique(v.begin(), v.end());
	v.erase(end_unique, v.end());
	//sort(v.begin(), v.end(), [](const string &s1, const string &s2) {return s1.size() < s2.size(); }); ʹ��partition�򲻱ذ��մ�С����
	cout << "how long words you need?" << endl;
	string::size_type length;
	cin >> length;
	//find_if(v.begin(), v.end(), [length](const string &s) {return s.size() >= length; });
	auto it = partition(v.begin(), v.end(), [length](const string &s) {return s.size() >= length; });//ֻ�������δ�ذ��մ�С���������Ҫ���� ����ǰ����б�Ҫ
	for_each(v.begin(), it, [](const string &s) {cout << s << " "; });
	cout << endl;
}

void findInt(vector<int> &v) {
	cout << "Please press into some numbers" << endl;
	int num;
	while (cin >> num) {
		v.push_back(num);
	}
	cin.clear();
	int value;
	cin >> value;
	/*auto pos = v.cbegin();
	while (pos != v.cend()) {
		pos = find_if(pos, v.cend(), [value](int i) {return i > value; });
		cout << *pos << " ";
		++pos;
	}*/
	//ʵ���϶������ֶ��������Ĳ��� ʹ��partitionЧ������ �ڴ�ֻ����ʾ��ʹ��find�ı�������
	cout << endl;
}

bool size_6(const string &s) {
	return s.size() > 6;
}

auto exercise_5(const vector<string> &s) {
	return count_if(s.cbegin(), s.cend(), size_6);
}

auto exercise_6(const vector<string> &s) {//lambda�汾
	return count_if(s.cbegin(), s.cend(), [](const string &s) {return s.size() > 6; });
}

void mutable_lambda(void) {
	int i = 5;
	auto f = [i]()mutable->bool {if (i > 0) { --i; return false; } else return true; };//�Ƿ������Ϊmutable����ֻ�ܶ�lambda�еľֲ��������� ʵ����i��ֵ��δ�ı�
	//����˵lambda�е�ֵ���������һ�������ı��� ����ʹ��mutableֻ�Ǹı�������������� ԭ�ȵı������ɸı� ����˵������const�ģ�
	for (int j = 0; j != 6; ++j) {
		cout << f() << " " << i << endl;
	}
}

bool check_size(const string &s, string::size_type sz) {
	return s.size() < sz;
}

void example_bind(void) {
	cout << "Please press into some words" << endl;
	string word;
	vector<string> v;
	while (cin >> word) v.push_back(word);
	cin.clear();
	string::size_type length;
	cout << "Please press into which length you want: ";
	cin >> length;
	auto check_length = bind(check_size,placeholders::_1, length);//ֵ��ע�����_1��placeholders���namespcae�� ����bind������ͷ�ļ�functional��
	auto pos = find_if(v.cbegin(), v.cend(), check_length);//ʹ��check_length �ȼ���ʹ��check_size(s,length)
	cout << *pos << endl;
}

bool check_num(const int i, string::size_type sz) {
	return i > sz;
}

void exercise_7(void) {
	cout << "press into one word." << endl;
	string word;
	cin >> word;
	cin.clear();
	string::size_type length = word.size();
	cout << "press into some numbers." << endl;
	vector<int> num;
	int temp;
	while (cin >> temp) {num.push_back(temp);}
	auto pos = find_if(num.cbegin(), num.cend(), bind(check_num, placeholders::_1, length));
	cout << *pos << endl;
}

void biggies_bind(void) {
	cout << "Please press into some words: ";
	string word;
	vector<string> sword;
	while (cin >> word) sword.push_back(word);
	cin.clear();
	sort(sword.begin(), sword.end());
	auto end_unique = unique(sword.begin(), sword.end());
	sword.erase(end_unique, sword.end());
	cout << "Please press into the length: ";
	string::size_type length;
	cin >> length;
	auto pos = partition(sword.begin(), sword.end(), bind(check_size, placeholders::_1, length));
	while (pos != sword.cend()) {
		cout << *pos << " ";
		++pos;
	}
	cout << endl;
}
void exercise_8(void) {
	cout << "Please press into some words: ";
	string word;
	vector<string> sword;
	while (cin >> word) sword.push_back(word);
	cin.clear();
	sort(sword.begin(), sword.end());//listû����sort����
	list<string> temp;
	unique_copy(sword.begin(), sword.end(), back_inserter(temp));
	for (auto str : temp) {
		cout << str << " ";
	}
	cout << endl;
}

void exercise_9(void) {
	vector<int> v0, v1, v2;
	deque<int> d0;
	for (int i = 1; i != 10; ++i)  v0.push_back(i); 
	copy(v0.cbegin(), v0.cend(), back_inserter(v1));
	copy(v0.cbegin(), v0.cend(), front_inserter(d0));
	copy(v0.cbegin(), v0.cend(), inserter(v2, v2.begin()));
	for (auto i : v0) cout << i << " ";
	cout << endl;
	for (auto i : v1) cout << i << " ";
	cout << endl;
	for (auto i : d0) cout << i << " ";
	cout << endl;
	for (auto i : v2) cout << i << " ";
	cout << endl;
}

void example_istream_iterator(void) {
	istream_iterator<int> in_int(cin);
	istream_iterator<int> eof;
	vector<int> v;
	while (in_int != eof) v.push_back(*in_int++);
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
	vector<int> vec(in_int, eof);//ֱ���õ�������������
	cout << accumulate(in_int, eof,0);//ֱ��ʹ���㷨������������
}

void example_ostream_iterator(void) {
	ostream_iterator<int> out_iter(cout, " ");
	vector<int> v = { 1,2,3,4,5 };
	for (auto i : v) {
		*out_iter++ = i;
	}
	cout << endl;
	copy(v.cbegin(), v.cend(), out_iter);//ʹ��copy��cout��ֵ���˴�������Ϊ�ǰ������������һ������
	cout << endl;
}

void exercise_10(void) {
	istream_iterator<int> in_int(cin), eof;
	vector<int> v(in_int, eof);
	sort(v.begin(), v.end());
	ostream_iterator<int> out_int(cout, " ");
	copy(v.cbegin(), v.cend(), out_int);
	cout << endl;
	unique_copy(v.cbegin(), v.cend(), out_int);
	cout << endl;
}

void example_riterator(void) {
	vector<int> v = { 1,2,3,4,5 };
	for (auto it = v.crbegin(); it != v.crend(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	sort(v.rbegin(), v.rend());
	ostream_iterator<int> out_int(cout, " ");
	copy(v.cbegin(), v.cend(), out_int);
	cout << endl;
}

void example_1(void) {
	string str = "hello,world";
	auto comma = find(str.cbegin(), str.cend(), ',');
	cout << string(str.cbegin(), comma) << endl;
	cout << string(++comma, str.cend()) << endl;
}

void exercise_11(void) {
	vector<int> v = { 1,2,3,4,5 };
	for (vector<int>::size_type index = 1; index<=v.size(); ++index) {//index�޷���
		cout << v[v.size()-index] << " ";
	}
	cout << endl;
}

void exercise_12(void) {
	list<int> l = { 0,1,1,2,5,4,3,0,2,1,0,4 };
	auto last = find(l.crbegin(), l.crend(), 0);
	cout << *last << endl;
}

void exercise_13(void) {
	vector<int> v = { 0,1,2,3,4,5,6,7,8,9 };
	list<int> l;
	for(auto pos=v.crbegin();;++pos){
		pos = find_if(pos, v.crend(), [](int i) {return i >= 3 && i <= 7; });//��find_if�ڲ�����ʱ�᷵��β�������
		if(pos!=v.crend()) l.push_back(*pos);//β��������޷�push����vector
		else break;
	}//�������ȷ�ı���д��
	ostream_iterator<int> out_int(cout, " ");
	copy(l.cbegin(), l.cend(), out_int);
	cout << endl;
}


int main(void) {
	exercise_13();
	system("pause");
}
