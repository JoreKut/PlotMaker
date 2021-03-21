#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plot.h"
#include "Function.h"
#include <deque>

using namespace sf;

int Width = 1200, Height = 900;

RenderWindow window(VideoMode(Width, Height), "Plotter");

int main() {

	window.setFramerateLimit(60);

	Function f1 = Function("2*x+4", sf::Color::Green, Width);
	Function f2 = Function("-0.1*x^2+4", sf::Color::Blue, Width);
	Function f3 = Function("x^3-3*x^2 - x+2", sf::Color::Cyan, Width);
	Function f4 = Function("1/(x+2)", sf::Color::Yellow, Width);
	Function f5 = Function("(-2+x)^(-1)", sf::Color::Magenta, Width);

	Plot p = Plot(Width, Height);
	p.addFunction(f1);
	p.addFunction(f2);
	p.addFunction(f3);
	p.addFunction(f4);
	p.addFunction(f5);
	p.Display(window);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered && event.text.unicode == 43) {
				// '+'
				p.scale(10, 10);
				p.Display(window);
			}
			else if (event.type == Event::TextEntered && event.text.unicode == 45) {
				// '-'
				p.scale(-10, -10); 
				p.Display(window);
			}

			if (Mouse::isButtonPressed(Mouse::Left)) { // Перемещение с помощью мышки
				float x, y;
				//начальное положение при нажатии
				float x0 = Mouse::getPosition().x;
				float y0 = Mouse::getPosition().y;
				while (Mouse::isButtonPressed(Mouse::Left)) // тянем мышку
				{
					//каждый раз конечное положение изменяется
					x = Mouse::getPosition().x;
					y = Mouse::getPosition().y;

					float dx = x - x0, dy = y - y0;
					// Подсчитываем разницу и смещаем всю систему
					p.move(dx, -dy);
					p.Display(window);
					//сдвигаем начальное значение на конечное. Затем весь цикл повторяется
					x0 += dx;
					y0 += dy;
				}
			}
		}

	}

}
