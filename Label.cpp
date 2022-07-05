#include <SFML/Graphics.hpp>
#include <string>

#include "Label.h"
#include "Widgets.h"

using namespace sf;

///// Static fields ////////////////////////////////////////////////////////////////

Font Label::font = Font();

///// Constructs ///////////////////////////////////////////////////////////////////

Label::Label(RenderWindow* win, Size size, Position position, std::string text, Color color)
	: Widget(win, size, position, color)
{
	this->text = text;
	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
}

Label::Label(RenderWindow *win, Size size, Position position, std::string text)
	: Widget(win, size, position)
{
	this->text = text;
	std::cout << text << std::endl;
	textObj = Text();
	textObj.setFont(font);
	textObj.setString(text);	
	textObj.setCharacterSize(24);
	textObj.setStyle(sf::Text::Regular);
	textObj.setPosition(position.X, position.Y);
}

Label::Label(RenderWindow* win, std::string text) 
	: Widget(win)
{
	this->text = text;
	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
}


Label::Label(RenderWindow *win) : Widget(win)
{
	this->text = "";
	textObj = Text(text, font);
	textObj.setPosition(position.X, position.Y);
}

void Label::setFont(Font& font)
{
	Label::font = Font(font);
}

void Label::draw()
{
	window->draw(textObj);
}
