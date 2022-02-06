#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"
#include "Widgets.h"

using namespace sf;


Button::Button(RenderWindow *win, Texture &texture, Size size, Position position, std::string text)
	: Widget(win, size, position)
{
	this->texture = Texture(texture);
	this->setTexture(this->texture);

	this->text = text;
}

Button::Button(RenderWindow *win, Texture &texture, Size size, Position position, std::string text, Color color)
	: Widget(win, size, position, color)
{
	this->Button::setTexture(this->texture);

	this->text = text;
}

Button::Button(RenderWindow *win, Texture &texture) : Widget(win)
{
	this->Button::setTexture(this->texture);

	this->text = "";
}

void Button::draw()
{
	this->window->draw(this->sprite);
}
