#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Widgets.h"

using namespace sf;

///// Constructs ///////////////////////////////////////////////////////////////////

Widget::Widget(RenderWindow* win, Size siz, Position pos, Color color)
{
	this->window = win;
	this->setTexture();

	this->setSize(siz);

	this->setPosition(pos);

	this->setColor(color);

	Widget::addWidget(this);
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

void Widget::bind(EventType type, void(*fun)(EventParam param))
{
	binded.addFunct(type, fun);
}

void Widget::runFunctions(sf::Event events)
{
	EventParam eve = EventParam(*this, events);

	if ((eve.mousePosition.X == lastMousePosition.X) &&
		(eve.mousePosition.Y == lastMousePosition.Y))
	{	// Position of mouse was not changed
		
	}
	else
	{	// Position of mouse was changed
		if ((eve.mousePosition.X > position.X) &&
			(eve.mousePosition.Y > position.Y) &&
			(eve.mousePosition.X < position.X + size.width) &&
			(eve.mousePosition.Y < position.Y + size.height))
		{	// mouse in widget now
			if ((lastMousePosition.X > position.X) &&
				(lastMousePosition.Y > position.Y) &&
				(lastMousePosition.X < position.X + size.width) &&
				(lastMousePosition.Y < position.Y + size.height))
				// mouse was in widget before
			{ }
			else // mouse was not in widget before
				binded.run(MOUSE_ENTER, eve);

		} else { // mouse not in widget now
			if ((lastMousePosition.X > position.X) &&
				(lastMousePosition.Y > position.Y) &&
				(lastMousePosition.X < position.X + size.width) &&
				(lastMousePosition.Y < position.Y + size.height))
				// mouse was in widget before
				binded.run(MOUSE_EXIT, eve);
		}
	}

	/// Not matter if mouse move
	if ((events.type == sf::Event::MouseButtonPressed) && (buttonIsPresed == false))
	{ // Mouse button presed
		buttonIsPresed = true;
		if ((eve.mousePosition.X > position.X) &&
			(eve.mousePosition.Y > position.Y) &&
			(eve.mousePosition.X < position.X + size.width) &&
			(eve.mousePosition.Y < position.Y + size.height))
		{	// mouse in widget now
			if (events.mouseButton.button == 0)
				binded.run(BUTTON_LEFT_PRESS, eve);
			if (events.mouseButton.button == 1)
				binded.run(BUTTON_RIGTH_PRESS, eve);
		}	
	}
	if ((events.type == sf::Event::MouseButtonReleased) && (buttonIsPresed == true))
	{ // Mouse button presed
		buttonIsPresed = false;
		if ((eve.mousePosition.X > position.X) &&
			(eve.mousePosition.Y > position.Y) &&
			(eve.mousePosition.X < position.X + size.width) &&
			(eve.mousePosition.Y < position.Y + size.height))
		{	// mouse in widget now
			if (events.mouseButton.button == 0)
				binded.run(BUTTON_LEFT_RELEASE, eve);
			if (events.mouseButton.button == 1)
				binded.run(BUTTON_RIGTH_RELEASE, eve);
		}
	}

	lastMousePosition = eve.mousePosition;
}

sf::RenderWindow* Widget::getWindow()
{
	return window;
}

int Widget::numWidgets = 0;
Widget** Widget::allWidgets = new Widget*[0];

void Widget::updateAll(Event event)
{
	for (int i = 0; i < numWidgets; i++)
	{
		allWidgets[i]->draw();
		allWidgets[i]->runFunctions(event);
	}
}

void Widget::addWidget(Widget* wid)
{
	numWidgets++;
	
	Widget** newWidgets = new Widget*[numWidgets];
	for (int i = 0; i < numWidgets - 1; i++)
		newWidgets[i] = allWidgets[i];
	newWidgets[numWidgets - 1] = wid;

	allWidgets = newWidgets;
}

//EventParam Widget::makeParam(sf::Event event)
//{
//	EventParam eve = EventParam(*this, event);
//	Vector2i vector = sf::Mouse::getPosition((Window)window);
//
//	eve.mousePosition = Position(event.mouseMove.x, event.mouseMove.y);
//
//	return eve;
//}

///// Binded function //////////////////////////////////////////////////////////////

Widget::BindedFunction::TypeAndFunc::TypeAndFunc(EventType type, void(*fun)(EventParam param))
{
	mainType = type;
	func = fun;
}

Widget::BindedFunction::TypeAndFunc::TypeAndFunc()
{
	/// nothing
}

void Widget::BindedFunction::addFunct(EventType type, void(*fun)(EventParam param))
{
	TypeAndFunc* newArray = new TypeAndFunc[size + 1];

	for (int i = 0; i < size; i++) { 
		newArray[i] = TypeAndFunc(arrayFunc[i].mainType, arrayFunc[i].func);
	}
	newArray[size] = TypeAndFunc(type, fun);
	size++;

	delete arrayFunc;
	arrayFunc = newArray;
}

void Widget::BindedFunction::run(EventType type, EventParam param)
{
	for (int i = 0; i < size; i++)
	{
		if (arrayFunc[i].mainType == type)
			arrayFunc[i].func(param);
	}
}

void Widget::BindedFunction::deleteFunct(EventType type, void(*fun)(EventParam param))
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

	size--;
	arrayFunc = newArray;
}

EventParam::EventParam(Widget &wid, sf::Event event) : widget(wid)
{
	RenderWindow* window = wid.getWindow();

	if ((window->getPosition().x < Mouse::getPosition().x - 8 && 
		Mouse::getPosition().x - 8 < window->getPosition().x + window->getSize().x)
		&& 
		(window->getPosition().y < Mouse::getPosition().y - 30 &&
		Mouse::getPosition().y - 30 < window->getPosition().y + window->getSize().y))
		
		mousePosition = Position(Mouse::getPosition().x - window->getPosition().x - 8, 
								Mouse::getPosition().y - window->getPosition().y - 30);
	else
		mousePosition = Position(-1, -1);
}
