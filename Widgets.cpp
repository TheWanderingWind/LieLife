#include <string>
#include <iostream>

#include "Widgets.h"


using namespace sf;

//////////////////////////////////////////////////////////////////////////////
///// Static constants, values and functions /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int Widget::numWidgets = 0;

Widget** Widget::allWidgets = new Widget * [0];

void Widget::addWidget(Widget* wid)
{
	numWidgets++;

	Widget** newWidgets = new Widget * [numWidgets];
	for (int i = 0; i < numWidgets - 1; i++)
		newWidgets[i] = allWidgets[i];
	newWidgets[numWidgets - 1] = wid;

	allWidgets = newWidgets;
}

void Widget::updateAll(Event event)
{
	for (int i = 0; i < numWidgets; i++)
	{
		allWidgets[i]->draw();
		allWidgets[i]->startUpdate(event);
	}
}



//////////////////////////////////////////////////////////////////////////////
///// Constructions //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Widget::Widget(RenderWindow* win, Size siz, Position pos, Color color)
{
	this->window = win;
	this->setCreateTexture();

	this->setSize(siz);

	this->setPosition(pos);

	this->setColor(color);

	Widget::addWidget(this);

	binded = BindedFunction<Widget>();
}

Widget::Widget()
{
	// just null widget
}



//////////////////////////////////////////////////////////////////////////////
///// Getters and Setters ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

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

void Widget::setColor(Color col)
{
	this->color = col;

	this->sprite.setColor(col);
}

void Widget::setColor(int r, int g, int b, int w = 225) { this->setColor(Color(r, g, b, w)); }


Texture* Widget::getTexture() { return &this->texture; }

void Widget::setTexture(Texture &tex) 
{ 
	this->texture = Texture(tex);
	this->sprite.setTexture(this->texture);
}

void Widget::setCreateTexture()
{
	Texture tex;
	tex.create(120, 80);
	this->setTexture(tex);
}

sf::RenderWindow* Widget::getWindow() { return window; }



//////////////////////////////////////////////////////////////////////////////
///// Functions //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Widget::draw()
{
	this->window->draw(this->sprite);
}



//////////////////////////////////////////////////////////////////////////////
///// Functions for bind and run binded functions ////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Widget::bind(EventType type, void(*fun)(EventParam<Widget> param))
{
	binded.addFunct(type, fun);
}

void Widget::startUpdate(sf::Event event)
{
	runFunctions(event, EventParam<Widget>(*this, event), binded);
}