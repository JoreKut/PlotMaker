#include "Line.h"

Line::Line() {
	line = sf::VertexArray(sf::Lines, 2);

	sf::Vertex v1 = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	sf::Vertex v2 = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	line[0] = v1;
	line[1] = v2;
}

Line::Line(sf::Vertex v1, sf::Vertex v2) {
	line = sf::VertexArray(sf::Lines, 2);
	line[0] = v1;
	line[1] = v2;
}
int Line::getIndex() {
	return index;
}

void Line::setIndex(int index) {
	this->index = index;
}
sf::VertexArray Line::getLine() {
	return line;
}

int Line::getX() {
	return line[0].position.x;
}

int Line::getY() {
	return line[0].position.y;
}

void Line::move(float dx, float dy) {
	line[0].position.x += dx;
	line[0].position.y -= dy;
	line[1].position.x += dx;
	line[1].position.y -= dy;
}