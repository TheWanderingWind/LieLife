#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Widgets.h"

using namespace sf;

///// Constructs ///////////////////////////////////////////////////////////////////

Widget::Widget(RenderWindow *win)
{
	this->window = win;
	this->setTexture();

	this->setSize(120, 80);

	this->setPosition(0.0, 0.0);
}

Widget::Widget(RenderWindow *win, Size siz, Position pos, Color col)
{
	this->window = win;
	this->setTexture();

	this->setSize(siz);

	this->setPosition(pos);

	this->setColor(col);
}

Widget::Widget(RenderWindow *win, Size siz, Position pos)
{
	this->window = win;
	this->setTexture();

	this->setSize(siz);

	this->setPosition(pos);
}

///// Getters and Setters //////////////////////////////////////////////////////////

Size Widget::getSize() { return Size(this->size); }

void Widget::setSize(Size siz) { this->setSize(siz.width, siz.height); }

void Widget::setSize(int width, int height)
{
	this->size.width = width;
	this->size.height = height;

	this->sprite.setScale(
		(float) width / this->sprite.getTexture()->getSize().x,
		(float) height / this->sprite.getTexture()->getSize().y
	);
}


Position Widget::getPosition() { return Position(this->position); }

void Widget::setPosition(Position pos) { this->setPosition(pos.X, pos.Y); }

void Widget::setPosition(float X, float Y)
{
	this->position.X = X;
	this->position.Y = Y;

	this->sprite.setPosition(X, Y);
}


Color Widget::getColor() { return Color(this->color); }

void Widget::setColor(int r, int g, int b, int w = 225) { this->setColor(Color(r, g, b, w)); }

void Widget::setColor(Color col) 
{
	this->color = col;

	this->sprite.setColor(col);
}


Texture* Widget::getTexture() { return &this->texture; }

void Widget::setTexture() 
{ 
	Texture tex;
	tex.create(120, 80);
	this->setTexture(tex);
}

void Widget::setTexture(Texture &tex) 
{ 
	this->texture = Texture(tex);
	this->sprite.setTexture(this->texture);
}

///// Functions ////////////////////////////////////////////////////////////////////

void Widget::draw()
{
	this->window->draw(this->sprite);
}