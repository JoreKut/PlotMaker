#include "Calculator.h"

double Calc::Calculate(std::string input) {
	input = CleanSpaces(input);
	std::string cur_num = "";
	int k = 0;
	for (int i = 0; i < input.size(); i++) {
		char el = input[i];
		if (IsOperation(el)) {
			if (el == '(') {
				operations.push(el);
				continue;
			}
			if (i == 0 && el == '-') {
				cur_num += el;
				continue;
			}
			if (el == '-' && IsOperation(input[i - 1])) {
				cur_num += el;
				continue;
			}
			if (cur_num != "") {
				nums.push(stod(cur_num));
				cur_num = "";
			}
			if (OperationStackIsEmpty()) {
				operations.push(el);
				continue;
			}
			while (IsFalling(el, operations.top())) {
				Fusion(operations.top());
				if (OperationStackIsEmpty()) break;
			}
			if (el == ')') {
				operations.pop();
				continue;
			}
			operations.push(el);
			continue;
		}
		if (el == ',') el = '.'; // Little correction ))
		cur_num += el;
	}
	if (cur_num != "") nums.push(stod(cur_num));
	while (operations.size() != 0) {
		Fusion(operations.top());
	}
	return nums.top();
}
std::string Calc::CleanSpaces(std::string s) {
	std::string ss = "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ') continue;
		ss += s[i];
	}
	return ss;
}
void Calc::Fusion(char c) {
	double n2 = nums.top();
	nums.pop();
	double n1 = nums.top();
	nums.pop();
	if (c == '+') nums.push(n1 + n2);
	if (c == '-') nums.push(n1 - n2);
	if (c == '*') nums.push(n1 * n2);
	if (c == '/') nums.push(n1 / n2);
	if (c == '^') nums.push(pow(n1, n2));

	operations.pop();
}
int Calc::Rank(char c) {
	if (c == '(') return -1;
	if (c == ')') return 1;
	if (c == '-' || c == '+') return 2;
	if (c == '*' || c == '/') return 3;
	if (c == '^') return 4;
	return 0;
}
bool Calc::IsFalling(char cur, char last) {
	return Rank(cur) <= Rank(last);
}
bool Calc::IsOperation(char c) {
	for (auto var : operation_signs)
		if (var == c) return true;
	return false;
}
bool Calc::OperationStackIsEmpty() {
	return operations.size() == 0;
}