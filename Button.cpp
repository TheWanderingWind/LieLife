#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"
#include "Label.h"

using namespace sf;

Texture Button::textureReleased = Texture();
Texture Button::texturePressed = Texture();

///// Constructs ///////////////////////////////////////////////////////////////////

//void butPres(EventParam<Button> param)
//{
//	Texture n = Button::getTexturePressed();
//	param.widget.setTexture(n);
//}
//void butReles(EventParam<Button> param)
//{
//	Texture n = Button::getTextureReleased();
//	param.widget.setTexture(n);
//}

///// Constructs ///////////////////////////////////////////////////////////////////

Button::Button(RenderWindow* win, Size size, Position position, 
	std::string text, Color textColor, Color bgColor)
	: Label(win, size, position, text, textColor)
{
	Widget::setTexture(textureReleased);
	Widget::setColor(bgColor);

	binded = BindedFunction<Button>();
	
	//bind(EventType::BUTTON_LEFT_PRESS, &butPres);
	//bind(EventType::BUTTON_LEFT_RELEASE, &butReles);
}

///// Getters and Setters //////////////////////////////////////////////////////////

void Button::setTextureReleased(Texture texture)
{
	Button::textureReleased = Texture(texture);
}

void Button::setTexturePressed(sf::Texture texture)
{
	Button::texturePressed = Texture(texture);
}

sf::Texture Button::getTextureReleased()
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

void Button::bind(EventType type, void(*fun)(EventParam<Button>param))
{
	this->binded.addFunct(type, fun);
}

EventParam<Button> Button::makeParam(sf::Event event)
{
	return EventParam<Button>(*this, event);
}
