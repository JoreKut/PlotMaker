#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include "Point.h"
#include "Line.h"
#include "Function.h"

enum class Elements
{
	Backgroung,
	Net,
	RareNet,
	Text,
	MainAxe
};


class Plot
{
private:
	bool DarkTheme = true;
	Point center = Point(0,0);

	int width, height;
	float i_vector_size, j_vector_size;  //px
	float i_vector_value, j_vector_value;//своя система отсчета
	float i_scale, j_scale;
	float start_i_vector_size, start_j_vector_size;
	
	std::vector<Line> Horizontal, Vertical; // the Net
	
	std::vector<sf::Text> Horizontal_Text, Vertical_Text;

	std::vector<Function> Collection;

	sf::Color getColor(Elements element);


public:
	Plot(int width, int height);
	void move(float dx, float dy);
	void addFunction(Function f);
	void scale(float dx, float dy);
	void Display(sf::RenderWindow &window);
};

