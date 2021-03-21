#include "Function.h"

Function::Function(std::string expression, sf::Color graphColor, int count) {
	this->expression = expression;
	this->graphColor = graphColor;
	graphic = sf::VertexArray(sf::LinesStrip, count);
}
float Function::ValueAt(float x) {
	std::string new_expression = "";
	if (expression[0] == '-') new_expression += "0"; // для обработки ситуаций : -(2)^2 [-4] а без этого [4]
	for (int i = 0; i < expression.size(); i++) {
		if (expression[i] == '(' && expression[i + 1] == '-') {
			new_expression += "(0";
			continue;
		}
		if (expression[i] == 'x') {
			if (x < 0) {
				new_expression += "(0";
				new_expression += std::to_string(x);
				new_expression += ")";
			}
			else {
				new_expression += std::to_string(x);
			}
			continue;
		}
		new_expression += expression[i];
	}
	Calc calc;
	return calc.Calculate(new_expression);
}