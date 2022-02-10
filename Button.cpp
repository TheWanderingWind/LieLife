#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"
#include "Widgets.h"

using namespace sf;

Texture Button::button_texture = Texture();
Font Button::button_font = Font();

///// Constructs ///////////////////////////////////////////////////////////////////

Button::Button(RenderWindow *win, Size size, Position position, std::string text)
	: Widget(win, size, position)
{
	this->Widget::setTexture(button_texture);

	this->text = text;
}

Button::Button(RenderWindow *win, Size size, Position position, std::string text, Color color)
	: Widget(win, size, position, color)
{
	this->Widget::setTexture(button_texture);

	this->text = text;
}

Button::Button(RenderWindow *win) : Widget(win)
{
	this->Widget::setTexture(button_texture);

	this->text = "";
}

///// Getters and Setters //////////////////////////////////////////////////////////

Texture* Button::getTexture()
{
	return &button_texture;
}

void Button::setTexture(Texture& texture)
{
	button_texture = Texture(texture);
}

Font* Button::getFont()
{
	return &button_font;
}

void Button::setFont(Font& font)
{
	button_font = Font(font);
}

///// Functions ////////////////////////////////////////////////////////////////////

void Button::draw()
{
	this->window->draw(this->sprite);
}
