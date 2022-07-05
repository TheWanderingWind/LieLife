#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"
#include "Label.h"

using namespace sf;

Texture Button::textureReleased = Texture();
Texture Button::texturePressed = Texture();

///// Constructs ///////////////////////////////////////////////////////////////////

Button::Button(RenderWindow* win, Size size, Position position, 
	std::string text, Color textColor, Color bgColor)
	: Label(win, size, position, text, textColor)
{
	Widget::setTexture(textureReleased);
	Widget::setColor(bgColor);
}

///// Getters and Setters //////////////////////////////////////////////////////////

void Button::setTextureRelease(Texture texture)
{
	Button::textureReleased = Texture(texture);
}

void Button::setTexturePressed(sf::Texture texture)
{
	Button::texturePressed = Texture(texture);
}

sf::Texture Button::getTextureRelease()
{
	return Texture(Button::textureReleased);
}

sf::Texture Button::getTexturePressed()
{
	return Texture(Button::texturePressed);
}

///// Functions ////////////////////////////////////////////////////////////////////

void Button::draw()
{
	window->draw(this->sprite);
	window->draw(textObj);
}
