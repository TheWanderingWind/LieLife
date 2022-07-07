#include <string>

#include "Label.h"

using namespace sf;

///// Static fields ////////////////////////////////////////////////////////////////

Font Label::standardFont = Font();

///// Constructs ///////////////////////////////////////////////////////////////////

Label::Label(RenderWindow* win, Size size, Position position, 
	std::string text, Color textColor)
	: Widget(win, size, position)
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
	autoSizeProcess();

	binded = BindedFunction<Label>();
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
	autoSizeProcess();
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

void Label::autoSizeProcess()
{
	FloatRect data = textObj.getGlobalBounds();
	textPosition.X = (size.width - data.width) / 2;
	textPosition.Y = (size.height - data.height) / 2 - 5;

	textObj.setPosition(position.X + textPosition.X, position.Y + textPosition.Y);
}

void Label::bind(EventType type, void(*fun)(EventParam<Label>param))
{
	this->binded.addFunct(type, fun);
}

void Label::startUpdate(sf::Event event)
{
	runFunctions(event, EventParam<Label>(*this, event), binded);
}

//EventParam<Label> Label::makeParam(sf::Event event)
//{
//	return EventParam<Label>(*this, event);;
//}
