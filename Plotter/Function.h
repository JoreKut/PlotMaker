#pragma once
#include <SFML/Graphics.hpp>
#include "Calculator.h"
#include <iostream>

class Function
{
public:
	std::string  expression;
	sf::Color graphColor;
	sf::VertexArray graphic;
	Function(std::string expression, sf::Color graphColor, int count);
	float ValueAt(float x);

};

