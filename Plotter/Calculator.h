#pragma once
#include <iostream>
#include <stack>
#include <string>

class Calc
{
private:
	std::stack <char> operations;
	std::stack <double> nums;
	char operation_signs[7]{ '+', '-', '*', '/', '^', '(', ')' };

	bool IsOperation(char c);
	bool IsFalling(char cur, char last);
	int Rank(char c);
	bool OperationStackIsEmpty();
	void Fusion(char c);
	std::string CleanSpaces(std::string s);
public:
	// TO REVERSE POLISH NOTATION 
	double Calculate(std::string input);
};

