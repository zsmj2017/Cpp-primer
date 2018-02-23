#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace::std;

int exercise_1(void) {
	int score;
	vector<string> grade{ "E","D","C","B","A" };
	auto iter = grade.begin();
	string finalgrade;
	cin >> score;
	if (score > 100 || score < 0) return -1;
	if (score < 60) finalgrade = *iter;
	else {
		finalgrade = *(iter + (score - 50) / 10);//注意不必穷举情况 是有关联的
		if (score % 10 > 7) finalgrade += "+";
		else if (score % 10 < 3) finalgrade += "-";
	}
	cout << finalgrade << endl;
	return 0;
}

int exercise_2(void) {
	int score;
	vector<string> grade{ "E","D","C","B","A" };
	auto iter = grade.begin();
	string finalgrade;
	cin >> score;
	if (score > 100 || score < 0) return -1;
	finalgrade = (score < 60)? *iter :*(iter + (score - 50) / 10);
	cout << finalgrade << endl;
	return 0;
}

int exercise_3(void) {//只能说保存了各个元素的数据 过于臃肿
	vector<string> v;
	vector<int> num;
	vector<decltype(v.size())> index;
	string str;
	int n=1;
	while (cin >> str) {
		v.push_back(str);
	}
	auto iter = v.cbegin();
	while (iter!=v.cend()) {
		while (iter != v.cend() - 1 && *iter == *(iter + 1)) {
			++n;
			++iter;
		}
		num.push_back(n); n = 1;
		index.push_back(iter - v.cbegin());
		++iter;
	}
	int max = 0;
	decltype(num.size()) max_index;
	auto iter1 = num.cbegin();
	while (iter1 != num.cend()) {
		if (max < *iter1) {
			max = *iter1;
			max_index = iter1 - num.cbegin();
		}
		++iter1;
	}
	cout << *(v.cbegin() + *(index.cbegin() + max_index)) << " " << *(num.cbegin() + max_index) << endl;
	return 0;
}

int exercise_4(void) {//答案提供的更好的思路
	int max_num = 0, n = 1;
	string current_str, pre_str = " ", max_str;
	while (cin >> current_str) {
		if (current_str == pre_str) ++n;
		else n = 1;
		if (n > max_num) {
			max_num = n;
			max_str = current_str;
		}
		pre_str = current_str;
	}
	cout << max_str << " " << max_num << endl;
	return 0;
}

int exercise_5(void) {
	vector<int> v1{ 1,2,3,4,5 };
	vector<int> v2{ 1,2,3,4,5,6,7 };
	auto size1 = v1.size(), size2 = v2.size();
	bool flag = true;
	if (size1 <= size2) {
		auto iter = v2.cbegin();
		for (auto i : v1) {
			if (i == *iter) iter++;
			else { flag = false; break; }
		}
	}
	else {
		auto iter = v1.cbegin();
		for (auto i : v2) {
			if (i == *iter) iter++;
			else { flag = false; break;}
		}
	}
	if (flag) cout << "从属关系" << endl;
	else cout << "并非如此" << endl;
	return 0;
}

int exercise_6(void) {
	string str1, str2, res;
	do {
		cout << "Please input two string:";
		cin >> str1 >> str2;
		if (str1.size() >= str2.size()) cout << str1 << endl;
		else cout << str2 << endl;
		cout << "Y/N?";
		cin >> res;
	} while (res[0] == 'Y');
	return 0;
}

int exercise_7(void) {
	int a, b;
	while (cin >> a >> b) {
		try {
			if (b == 0) throw runtime_error("Please pressinto a number not zero!");
			cout << a / b << endl;
		}
		catch (runtime_error err) {
			cout << err.what() << endl;
			cout << "do u want to try again?";
			char c; cin >> c;
			if (c == 'n' || !c) break;
		}
	}
	return 0;
}

int main(void) {
	exercise_7();
	system("pause");
	return 0;
}
