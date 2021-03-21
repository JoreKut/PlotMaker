#include <SFML/Graphics.hpp>

class Line
{
private:
	int index;
	sf::VertexArray line;
public:
	Line();
	Line(sf::Vertex v1, sf::Vertex v2);
	void setIndex(int index);
	int getIndex();
	int getX();
	int getY();
	void move(float dx, float dy);
	sf::VertexArray getLine();
};

