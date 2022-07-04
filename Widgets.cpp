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

//// Functions ////////////////////////////////////////////////////////////////////

void Widget::draw()
{
	this->window->draw(this->sprite);
}

EventParam Widget::makeParam(sf::Event event)
{
	EventParam eve;
	eve.mousePosition = Position(event.mouseMove.x, event.mouseMove.y);
	eve.widget = this;

	return eve;
}

///// Binded function //////////////////////////////////////////////////////////////

BindedFunction::TypeAndFunc::TypeAndFunc(EventType type, void(*fun)(EventParam param))
{
	mainType = type;
	func = fun;
}

BindedFunction::TypeAndFunc::TypeAndFunc()
{
	/// nothing
}

void BindedFunction::addFunct(EventType type, void(*fun)(EventParam param))
{
	TypeAndFunc* newArray = new TypeAndFunc[size + 1];

	for (int i = 0; i < size; i++)	newArray[i] = arrayFunc[i];
	newArray[size] = TypeAndFunc(type, fun);
	size++;

	arrayFunc = newArray;
}

void BindedFunction::run(EventType type, EventParam param)
{
	for (int i = 0; i < size; i++)
	{
		if (arrayFunc[i].mainType == type)
			arrayFunc->func(param);
	}
}

void BindedFunction::deleteFunct(EventType type, void(*fun)(EventParam param))
{
	int num = -1;
	for (int i = 0; i < size; i++) // try find function to be remove
	{
		if (arrayFunc[i].mainType == type)
			if (arrayFunc[i].func == fun)
			{
				num = i;
				break;
			}

	}

	if (num == -1) return; // if we don`t find

	TypeAndFunc* newArray = new TypeAndFunc[size - 1];
	for (int i = 0; i < num; i++)
		newArray[i] = arrayFunc[i];
	for (int i = num + 1; i < size; i++)
		newArray[i - 1] = arrayFunc[i];

	arrayFunc = newArray;
}
