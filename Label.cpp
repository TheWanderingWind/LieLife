#include <SFML/Graphics.hpp>
#include <string>

#include "Label.h"
#include "Widgets.h"

using namespace sf;

///// Static fields ////////////////////////////////////////////////////////////////

Font Label::standardFont = Font();

///// Constructs ///////////////////////////////////////////////////////////////////

Label::Label(RenderWindow* win, Size size, Position position, std::string text, Color color)
	: Widget(win, size, position)
{
	this->text = text;
	textColor = color;
	font = standardFont;

	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
	textObj.setFillColor(color);
}

Label::Label(RenderWindow *win, Size size, Position position, std::string text)
	: Widget(win, size, position)
{
	this->text = text;
	textColor = Color(Color::Black);
	font = standardFont;

	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
	textObj.setFillColor(textColor);
}

Label::Label(RenderWindow* win, std::string text) 
	: Widget(win)
{
	this->text = text;
	textColor = Color(Color::Black);
	font = standardFont;

	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
	textObj.setFillColor(textColor);
}


Label::Label(RenderWindow *win) : Widget(win)
{
	this->text = "";
	textColor = Color(Color::Black);
	font = standardFont;

	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
	textObj.setFillColor(textColor);
}

///// Getters and Setters //////////////////////////////////////////////////////////

void Label::setStandardFont(sf::Font& font)
{
	Label::standardFont = Font(font);
}

void Label::setFont(Font& font)
{
	this->font = Font(font);
}

Font Label::getFont()
{
	return Font(font);
}

void Label::setText(std::string str)
{
	text = str;
	textObj.setString(str);
}

std::string Label::getText()
{
	return text;
}

void Label::setTextColor(sf::Color col)
{
	textColor = Color(col);
	textObj.setFillColor(textColor);
}

sf::Color Label::getTextColot()
{
	return sf::Color(textColor);
}

void Label::setCharacterSize(int size)
{
	characterSize = size;
	textObj.setCharacterSize(characterSize);
}

int Label::getCharacterSize()
{
	return characterSize;
}

void Label::setStyle(sf::Uint32 style)
{
	textObj.setStyle(style);
}

sf::Uint32 Label::getStyle()
{
	return textObj.getStyle();
}

///// Functions ////////////////////////////////////////////////////////////////////

void Label::draw()
{
	window->draw(textObj);
}
