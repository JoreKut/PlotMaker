#include "Plot.h"

Plot::Plot(int width, int height) {
	this->width = width;
	this->height = height;
	//делаем векторы равными
	i_vector_size = 50.f;
	j_vector_size = i_vector_size;
	//задаем единичные отрезки
	i_vector_value = 1.f;
	j_vector_value = 1.f;
	//scale values
	i_scale = 1.f;
	j_scale = 1.f;
	//center position
	center.x = 0;
	center.y = 0;
	//исходя из всего формируем сетку с значениями
	move(width / 2.f, -height / 2.f);

	start_i_vector_size = i_vector_size;
	start_j_vector_size = j_vector_size;
}

void Plot::scale(float dx, float dy) {
	i_vector_size += dx;
	j_vector_size += dy;

	if (i_vector_size >= 2 * start_i_vector_size && dx != 0) {
		i_vector_size = start_i_vector_size;
		i_scale /= 2;
	}if (j_vector_size >= 2 * start_j_vector_size && dx != 0) {
		j_vector_size = start_j_vector_size;
		j_scale /= 2;
	}

	if (i_vector_size <= start_i_vector_size / 2 && dy != 0) {
		i_vector_size = start_i_vector_size;
		i_scale *= 2;
	}if (j_vector_size <= start_j_vector_size / 2 && dy != 0) {
		j_vector_size = start_j_vector_size;
		j_scale *= 2;
	}

}

void Plot::move(float dx, float dy) {
	center.move(dx, dy);
}

void Plot::addFunction(Function f) {
	Collection.push_back(f);
}

void Plot::Display(sf::RenderWindow &window) {
	Horizontal.clear();
	Vertical.clear();
	Horizontal_Text.clear();
	Vertical_Text.clear();
	
	window.clear(getColor(Elements::Backgroung));

	sf::Text tx;
	sf::Font font;
	font.loadFromFile("Dosis-ExtraLight.ttf");
	tx.setFont(font);
	tx.setCharacterSize(20);

	float x0 = center.x;
	//выравниваем до экрана
	if (x0 < 0) {
		x0 += width;
	}
	if (x0 > width) {
		x0 -= width;
	}
	//находим остаток от деления
	while (x0 > i_vector_size) {
		x0 -= i_vector_size;
	}
	//строим
	while (x0 < width)
	{
		sf::Vertex v1 = sf::Vertex(sf::Vector2f(x0, 0));
		sf::Vertex v2 = sf::Vertex(sf::Vector2f(x0, height));
		int i = (x0 - center.x) / i_vector_size;
		if (i % 5 != 0) {
			v1.color = getColor(Elements::RareNet);
		}
		else if (i == 0) {
			v1.color = getColor(Elements::MainAxe);
		}
		else
		{
			v1.color = getColor(Elements::Net);
		}
		if (i % 5 == 0) {
			std::string text = std::to_string(i * i_scale);
			text = text.substr(0, text.find(".")+2);

			tx.setString(text);
			tx.setPosition(sf::Vector2f(x0, center.y));
			//Horizontal_Text.push_back(tx);
			window.draw(tx);
		}
		v2.color = v1.color;

		Line line = Line(v1, v2);
		line.setIndex(i);
		window.draw(line.getLine());
		//Vertical.push_back(line);

		x0 += i_vector_size;
	}

	// The same operation for Y
	float y0 = center.y;
	//выравниваем до экрана
	if (y0 < 0) {
		y0 += j_vector_size;
	}
	if (y0 > height) {
		y0 -= height;
	}
	//находим остаток от деления
	while (y0 > j_vector_size) {
		y0 -= j_vector_size;
	}
	//строим
	while (y0 < height)
	{
		sf::Vertex v1 = sf::Vertex(sf::Vector2f(0, y0));
		sf::Vertex v2 = sf::Vertex(sf::Vector2f(width, y0));

		int j = (y0 - center.y) / j_vector_size;

		if (j % 5 != 0) {

			v1.color = getColor(Elements::RareNet);
		}
		else if (j == 0) {

			v1.color = getColor(Elements::MainAxe);

		}
		else
		{
			v1.color = getColor(Elements::Net);
		}

		if (j % 5 == 0) {
			std::string text = std::to_string(-j * j_scale);
			text = text.substr(0, text.find(".")+2);
			
			tx.setString(text);
			tx.setPosition(sf::Vector2f(center.x, y0));
			//Vertical_Text.push_back(tx);
			window.draw(tx);
		}
		v2.color = v1.color;
		Line line = Line(v1, v2);
		line.setIndex(j);
		//Horizontal.push_back(line);
		window.draw(line.getLine());
		y0 += i_vector_size;
	}
	sf::Vertex v1;
	float x, y, v;
	for (int i = 0; i < Collection.size(); i++) {
		Function f = Collection[i];
		for (float x = 0; x < f.graphic.getVertexCount(); x++) {
			v = (x - center.x) / i_vector_size * i_scale;
			y = -(f.ValueAt(v) * j_vector_size / j_scale - center.y);
			v1 = sf::Vertex(sf::Vector2f(x, y), f.graphColor);
			f.graphic[x] = v1;

		}
		Collection[i] = f;
		window.draw(f.graphic);
	}

	window.display();
}


sf::Color Plot::getColor(Elements element) {
	switch (element)
	{
	case Elements::Backgroung:
		if (DarkTheme) {
			return sf::Color(20, 20, 20);
		}
		else {
			return sf::Color(240, 240, 240);
		}
		break;
	case Elements::Net:
		if (DarkTheme) {
			return sf::Color(230, 230, 230);
		}
		else {
			return sf::Color(120, 120, 120);
		}
		break;
	case Elements::RareNet:
		if (DarkTheme) {
			return sf::Color(90, 90, 90);
		}
		else {
			return sf::Color(180, 180, 180);
		}
		break;
	case Elements::MainAxe:
		if (DarkTheme) {
			return sf::Color(240, 0, 0);
		}
		else {
			return sf::Color(0, 0, 0);
		}
		break;
	case Elements::Text:
		if (DarkTheme) {
			return sf::Color(220, 220, 220);
		}
		else {
			return sf::Color(0, 0, 0);
		}
		break;

	default:
		break;
	}
}