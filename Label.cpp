#include <string>

#include "Label.h"

using namespace sf;

//////////////////////////////////////////////////////////////////////////////
///// Static constants, values and functions /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Font Label::standardFont = Font();



//////////////////////////////////////////////////////////////////////////////
///// Constructions //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Label::Label(RenderWindow* win, Size size, Position position, 
	std::string text, Color textColor, Color ñolor)
	: Widget(win, size, position, ñolor)
{
	this->text = text;
	this->textColor = textColor;
	font = standardFont;

	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
	textObj.setFillColor(this->textColor);

	FloatRect data = textObj.getGlobalBounds();
	std::cout << "top: " << data.top << " left: " << data.left << " height: " <<
		data.height << " width: " << data.width << std::endl;
	autoTextPosition();

	binded = BindedFunction<Label>();
}



//////////////////////////////////////////////////////////////////////////////
///// Getters and Setters ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Font Label::getFont()
{
	return Font(font);
}

void Label::setStandardFont(sf::Font& font)
{
	Label::standardFont = Font(font);
}

void Label::setFont(Font& font)
{
	this->font = Font(font);
}

std::string Label::getText()
{
	return text;
}

void Label::setText(std::string str)
{
	text = str;
	textObj.setString(str);
}

sf::Color Label::getTextColot()
{
	return sf::Color(textColor);
}

void Label::setTextColor(sf::Color col)
{
	textColor = Color(col);
	textObj.setFillColor(textColor);
}

int Label::getCharacterSize()
{
	return characterSize;
}

void Label::setCharacterSize(int size)
{
	characterSize = size;
	textObj.setCharacterSize(characterSize);
	autoTextPosition();
}

sf::Uint32 Label::getStyle()
{
	return textObj.getStyle();
}

void Label::setStyle(sf::Uint32 style)
{
	textObj.setStyle(style);
}



//////////////////////////////////////////////////////////////////////////////
///// Functions //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Label::draw()
{
	window->draw(textObj);
}

void Label::autoTextPosition()
{
	FloatRect data = textObj.getGlobalBounds();
	textPosition.X = (size.width - data.width) / 2;
	textPosition.Y = (size.height - data.height) / 2 - 5;

	textObj.setPosition(position.X + textPosition.X, position.Y + textPosition.Y);
}



//////////////////////////////////////////////////////////////////////////////
///// Functions for bind and run binded functions ////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Label::bind(EventType type, void(*fun)(EventParam<Label>param))
{
	this->binded.addFunct(type, fun);
}

void Label::startEventUpdate(sf::Event event) 
{
	Widget::startEventUpdate(event);
	runEventCheking(event, EventParam<Label>(*this, event), binded);
}

void Label::runBindedFunctions(EventType type, EventParam<Label> param)
{
	Label::binded.run(type, param);
}