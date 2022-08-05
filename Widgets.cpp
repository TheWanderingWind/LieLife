#include <string>
#include <iostream>

#include "Widgets.h"


using namespace sf;

//////////////////////////////////////////////////////////////////////////////
///// Static constants, values and functions /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int Widget::numWidgets = 0;

// make first element null-widget for focus
Widget** Widget::allWidgets = new Widget * [1];

Widget& Widget::focused = *Widget::allWidgets[0];

void Widget::addWidget(Widget* wid)
{
	numWidgets++;
	int id = 0;

	Widget** newWidgets = new Widget * [numWidgets];
	for (int i = 0; i < numWidgets - 1; i++)
	{
		newWidgets[i] = allWidgets[i];
		if (allWidgets[i]->id == id)
			id++;
	}
	newWidgets[numWidgets - 1] = wid;
	wid->id = id;

	allWidgets = newWidgets;
}

void Widget::deleteWidget(int id)
{
	for (int d = 0; d < numWidgets; d++)
	{
		if (allWidgets[d]->id == id)
		{
			numWidgets--;

			Widget** newWidgets = new Widget * [numWidgets];
			
			for (int i = 0;		i < d;	i++)
				newWidgets[i] = allWidgets[i];

			for (int i = d+1;	i < numWidgets+1;	i++)
				newWidgets[i - 1] = allWidgets[i];

			allWidgets = newWidgets;
		}
	}
}

void Widget::updateAll(Event event)
{
	for (int i = 0; i < numWidgets; i++)
	{
		allWidgets[i]->draw();
		allWidgets[i]->startEventUpdate(event);
	}
}

Widget& Widget::getFocused()
{
	return focused;
}



//////////////////////////////////////////////////////////////////////////////
///// Constructions //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Widget::Widget(RenderWindow* win, Size siz, Position pos, Color color)
{
	window = win;
	setCreateTexture();

	setSize(siz);
	setPosition(pos);
	setColor(color);

	Widget::addWidget(this);
	binded = BindedFunction<Widget>();
	isFocus = false;
	canBeFocus = false;
}

Widget::Widget()
{
	Widget::addWidget(this);
	// just null widget
}

Widget::~Widget()
{
	deleteWidget(this->id);
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

bool Widget::getFocus() { return isFocus; }

void Widget::setFocus(bool focus)
{
	if (focus)
	{	// set this widget in focus
		isFocus = true;
		focused = *this;
	}
	else
	{	// set this widget out of focus
		if (focused.id == id)	
		{ // this widget is focused now
			focused = *allWidgets[0]; // set null widget in focus
			isFocus = false;
		}
		// else this widget not in focus, so no action is required
	}
}

bool Widget::getCanBeFocus() { return canBeFocus; }

void Widget::setCanBeFocus(bool canBe)
{
	canBeFocus = canBe;
	if (canBe == false) setFocus(false);
}




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

void Widget::startEventUpdate(sf::Event event)
{
	runEventCheking(event, EventParam<Widget>(*this, event), binded);
}

void Widget::runBindedFunctions(EventType type, EventParam<Widget> param)
{
	Widget::binded.run(type, param);
}