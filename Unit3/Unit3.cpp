#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <Windows.h>

using namespace::std;

int exercise_1(void) {
	string line;
	while (getline(cin, line)) {
		cout << line << endl;
	}
	return 0;
}

int exercise_2(void) {
	string word;
	while (cin >> word) {
		cout << word<< endl;
	}
	return 0;
}

int exercise_3(void) {
	string s1, s2;
	cin >> s1 >> s2;
	if (s1 == s2) {
		cout << "The two strings are same." << endl;
	}
	else {
		if (s1 > s2) cout << s1 << endl;
		else cout << s2 << endl;
	}
	return 0;
}

int exercise_4(void) {
	string s1, s2;
	cin >> s1 >> s2;
	if (s1 == s2) {
		cout << "The two strings are same." << endl;
	}
	else {
		if (s1.size() > s2.size()) cout << s1 << endl;
		else cout << s2 << endl;
	}
	return 0;
}

int exercise_5(void) {
	string word,longstring;
	while (cin >> word) {
		longstring += word;
	}
	cout << longstring << endl;
	return 0;
}

int exercise_6(void) {
	string word;
	while (cin >> word) {
		cout << word + "    ";
	}
	return 0;
}

int example_1(void) {
	string str("Hello,world!!!");
	decltype(str.size()) punct_cnt = 0;//string::size_type size_t punct_cnt
	for (auto c : str) {
		if (ispunct(c)) punct_cnt++;
	}
	cout << punct_cnt << " punctuation characters in " << str << endl;
	return 0;
}

int example_2(void) {
	string str("Hello,world!!!");
	for (auto &c : str) {
		c = toupper(c);
	}
	cout << str << endl;
	return 0;
}

int example_3(void) {
	string str("Hello world!!!");
	for (decltype(str.size()) index = 0; index != str.size() && !iswspace(str[index]); ++index) {
		str[index] = toupper(str[index]);
	}
	cout << str << endl;
	return 0;
}

int example_4(void) {
	const string hexdigits("0123456789ABCDEF");
	cout << "Press into a series of numbers between 0 and 15 "
		<< " separated by spaces.Hit CTRL+Z when finished: "
		<< endl;
	string result;
	decltype(result.size()) n = 0;
	while (cin >> n) {
		if (n < hexdigits.size()) {
			result += hexdigits[n];
			result += " ";
		}
	}
	cout << result << endl;
	return 0;
}

int exercise_7(void) {
	string str("hhhwwwooo");
	for (auto &c : str) {
		c = 'x';
	}
	cout << str << endl;
	return 0;
}

int exercise_8(void) {
	string str("Hello, world!!");
	string result1,result2;
	for (auto c : str) {
		if (!ispunct(c)) result1 += c;
	}
	cout << result1 << endl;
	for (decltype(str.size()) index = 0; index < str.size(); ++index) {
		if (!ispunct(str[index])) {
			result2 += str[index];
		}
	}
	cout << result2 << endl;
	return 0;
}

int exercise_9(void) {
	vector<int> v1;
	int n;
	while (cin >> n) {
		v1.push_back(n);
	}
	for (auto i : v1) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

int exercise_10(void) {
	vector<string> v1;
	string str;
	while (cin >> str) {
		v1.push_back(str);
	}
	for (auto c : v1) {
		cout << c << " ";
	}
	cout << endl;
	return 0;
}

int example_5(void) {
	vector<int> v1{ 1,3,5,7,9 };
	for (auto &i : v1) {
		i *= i;
		cout << i << " ";
	}
	cout << endl;
	return 0;

}

int example_6(void) {
	vector<int> scores(11);
	int n;
	while (cin >> n) {
		if (n <= 100) ++scores[n / 10];
	}
	for (auto i : scores) cout << i << " ";
	cout << endl;
	return 0;
}

int exercise_11(void) {
	vector<string> toupper_word;
	string word;
	while (cin >> word) {
		for (auto &c : word) {
			c = toupper(c);
		}
		toupper_word.push_back(word);
	}
	for (auto str : toupper_word) {
		cout << str << endl;
	}
	return 0;
}

int exercise_12(void) {
	vector<int> number;
	int n;
	while (cin >> n) {
		number.push_back(n);
	}
	for (decltype(number.size()) index = 0; index < number.size() - 1; ++index)
		cout << number[index] + number[index + 1] << " ";
	cout << endl;
	for (decltype(number.size()) index = 0; index < number.size()/2; ++index)
		cout << number[index] + number[number.size()-1-index] << " ";
	cout << endl;
	return 0;
}

int exercise_13(void) {
	vector<string> text;
	string line;
	while (getline(cin,line)) {
		text.push_back(line);
	}
	for (auto it = text.begin(); it != text.end() && !it->empty(); ++it) {
		for (auto &c : *it) {
			c = toupper(c);
		}
	}
	for (auto str : text) {
		cout << str;
	}
	cout << endl;
	return 0;
}

int exercise_14(void) {
	vector <int> number;
	int n;
	while (cin >> n) {
		number.push_back(n);
	}
	for (auto it = number.begin(); it != number.end(); it++) {
		*it *= 2;
	}
	for (auto i : number) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

int exercise_15(void) {
	vector<int> number;
	vector<int> sumv;
	int n, sum;
	while (cin >> n) {
		number.push_back(n);
	}
	for (auto it = number.cbegin(); it != number.cend()-1; it++) {
		sum = (*it) + *(it + 1);
		sumv.push_back(sum);
	}
	for (auto i : sumv) cout << i << " ";
	cout << endl;
	return 0;
}

int exercise_16(void) {
	vector<int> number;
	vector<int> sumv;
	int n, sum;
	while (cin >> n) {
		number.push_back(n);
	}
	for (auto beg=number.begin(),end=number.end()-1;beg<end; beg++,end--) {//end��ָ�����Ԫ�ص���һ��λ�ã�����
		sum = (*beg)+(*end);
		sumv.push_back(sum);
	}
	for (auto i : sumv) cout << i << " ";
	cout << endl;
	return 0;
}

int exercise_17(void) {
	vector<int> scores(11);
	int n;
	auto it = scores.begin();
	while (cin >> n) {
		if (n <= 100) {
			(*(it + n / 10))++;
		}
	}
	for (auto i : scores) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

int exercise_18(void) {
	int a[10] = {};
	int b[10] = {};
	for (size_t index = 0; index != 10; index++) {
		a[index] = int (index);
	}
	for (size_t index = 0; index != 10; index++) {
		b[index] = a[index];
	}
	for (auto i : b) {
		cout << i << " ";
	}
	cout << endl;
	vector<int> number_a(10), number_b(10);
	for (auto iter = number_a.begin(); iter != number_a.end(); iter++) {//������ʵ��
		(*iter) = int(iter - number_a.begin());
	}
	for (decltype(number_a.size()) index = 0; index < number_a.size(); index++) {//�±�ʵ��
		number_a[index] = int(index);
	}
	number_b = number_a;//vector������ֵ��ʱ����Ҫ���������Ĵ�С�� Ӧ�ò��ÿ��ǰ� ���b����������a �������ǰ10��
	for (auto i : number_b) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

int exercise_19(void) {
	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
	int *p = a;
	for (int i = 0; i < 10; i++) {
		*(p + i) = 0;
	}
	for (auto i : a) cout << i << " ";
	cout << endl;
	return 0;
}

int exercise_20(void) {
	int a[] = { 1,2,3,4,5 };
	int b[] = { 1,2,3,4,5 };
	bool flag = 0; 
	int number_a = sizeof(a) / sizeof(a[0]), number_b = sizeof(b) / sizeof(b[0]);
    if(number_a==number_b){
		for (int i = 0; i < number_a; ++i) {
			if (a[i] == b[i]) continue;
			else { flag = 1; break; }
		}
	}
	else flag = 1;
	if (flag == 1) cout << "NOT SAME" << endl;
	else cout << "SAME" << endl;
	return 0;
}

int exercise_21(void) {//vector���±�ʵ��
	vector<int> v1{ 1,2,3,4,5 }, v2{ 1,2,3,4,5 };
	bool flag = 0;
	auto number_a = v1.size(), number_b = v2.size();
	if (number_a == number_b) {
		for (decltype(v1.size()) index = 0; index < number_a; ++index) {
			if (v1[index] == v2[index]) continue;
			else { flag = 1; break; }
		}
	}
	else flag = 1;
	if (flag == 1) cout << "NOT SAME" << endl;
	else cout << "SAME" << endl;
	return 0;
}

int exercise_22(void) {//vector�ĵ�����ʵ��
	vector<int> v1{ 1,2,3,4,5 }, v2{ 1,2,3,4,5 };
	bool flag = 0;
	auto number_a = v1.size(), number_b = v2.size();
	if (number_a == number_b) {
		auto iter1 = v1.cbegin(), iter2 = v2.cbegin();
		while (iter1 != v1.cend() && ((*iter1) == (*iter2))) {//��������ԱȵĻ����һ����ʵ��ָ����δ����Ԫ�أ��������ж��Ƿ���ĩβ �����������������ұߵı��ʽ
			++iter1; ++iter2;
		}
		if (iter1 == v1.cend()) flag = 0;
		else flag = 1;
	}
	else flag = 1;
	if (flag == 1) cout << "NOT SAME" << endl;
	else cout << "SAME" << endl;
	return 0;
}

int exercise_23(void) {
	char a[] = "HELLO,WORLD";
	string str = a;
	cout << str << endl;
	int num[] = { 1,2,3,4,5 };
	vector<int> v(begin(num), end(num));
	for (auto i : v) cout << i << " ";
	cout << endl;
	auto iter = v.cbegin();
	int b[5] = {};
	for (auto &i : b) {//ע�����ʹ�õ���������Χfor
		i = *iter;
		iter++;
	}
	return 0;
}

int example_7(void) {
	int a[3][4];
	for (auto &r : a) {//����r�󶨵�һ������  ע�⼴ʹ�����������ݽ��и���Ҳ��Ҫ���� ��Ϊ��ʹ�����÷��ᵼ��r��һ��ָ�������ָ��
		for (auto i : r) {//r�е�Ԫ����������
			cout << i << " ";
		}
	}
	return 0;
}

int example_8(void) {
	int a[3][4] = {};
	for (auto p = a; p != a + 3; p++) {//p��������int (*p)[4] ��һ��ָ����4�����������ָ�� ��int *p[4] ָ����һ������4������ָ�������
		for (auto q = *p; q != *p + 4; q++) {//������p �õ���һ������ ��q��һ��ָ��������λԪ�ص�ָ��
			cout << *q << " ";
		}
	}
	return 0;
}

int example_9(void) {
	int a[3][4] = {};
	for (auto p = begin(a); p != end(a); p++) {
		for (auto q = begin(*p); q != end(*p); q++) {
			cout << *q << " ";
		}
	}
	return 0;
}

int example_10(void) {
	using int_array = int[4];//�÷����� �����˵һ������4������Ԫ�ص������
	typedef int int_array[4];//��͸������� �����˵intarray��һ������4������Ԫ�ص����� �о������������� ����һ�ֲ���˵��
	int a[3][4] = {};
	for (int_array *p = a; p != a + 3; p++) {//p��һ��ָ�� ָ��һ������4������Ԫ�ص�����
		for (int *q = *p; q != *p + 4; q++) {
			cout << *q << " ";
		}
	}
}

int main(void) {
	exercise_23();
	system("pause");
	return 0;
}