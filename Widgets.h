#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

struct Position
{
	float X, Y;

	Position(float X, float Y)
	{
		this->X = X;
		this->Y = Y;
	}

	Position()
	{
		this->X = 0;
		this->Y = 0;
	}
};

struct Size
{
	int width, height;

	Size(int wid, int hei)
	{
		this->width = wid;
		this->height = hei;
	}

	Size()
	{
		this->height = 80;
		this->width = 120;
	}
};

class Widget
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow *window;

	Size size;
	Position position;
	sf::Color color;

public:

	Widget(sf::RenderWindow *win);

	Widget(sf::RenderWindow *win, Size siz, Position pos, sf::Color col);

	Widget(sf::RenderWindow *win, Size siz, Position pos);

	Size getSize();

	void setSize(Size siz);

	void setSize(int x, int y);

	Position getPosition();

	void setPosition(Position pos);

	void setPosition(float X, float Y);

	sf::Color getColor();

	void setColor(int r, int g, int b, int w);

	void setColor(sf::Color col);

	sf::Texture* getTexture();

	void setTexture();

	void setTexture(sf::Texture &tex);

	void draw();
};