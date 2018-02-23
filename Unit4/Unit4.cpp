#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace::std;

int exercise_1(void) {
	int n;
	while (cin >> n && n != 42) {};
	cout << "shut down!" << endl;
	return 0;
}

int exercise_2(void) {
	vector<int> v{1,2,3,4,5};
	for (auto &i : v) {
		i = ((i % 2) ? i * 2 : i);
	}
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

int exercise_3(void) {
	int score;
	cin >> score;
	string finalgrade = (score >= 90) ? "high_grade" : (score >= 60 && score <= 75) ? "middle_grade" : (score < 60) ? "fail" : "pass";//passÖ¸µÄÊÇ75-90
	cout << finalgrade << endl;
	return 0;
}
int main(void) {
	exercise_3();
	system("pause");
	return 0;
}