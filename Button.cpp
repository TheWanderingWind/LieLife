#include <string>

#include "Button.h"

using namespace sf;


//////////////////////////////////////////////////////////////////////////////
///// Static constants, values and functions /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Texture Button::textureReleased = Texture();
Texture Button::texturePressed = Texture();



//////////////////////////////////////////////////////////////////////////////
///// Constant functions for sys bind ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void butPres(EventParam<Button> param)
{
	Texture n = Button::getTexturePressed();
	//std::cout << "Press\n";
	param.widget.setTexture(n);
}
void butReles(EventParam<Button> param)
{
	Texture n = Button::getTextureReleased();
	//std::cout << "Release\n";
	param.widget.setTexture(n);
}



//////////////////////////////////////////////////////////////////////////////
///// Constructions //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Button::Button(RenderWindow* win, Size size, Position position, 
	std::string text, Color textColor, Color bgColor)
	: Label(win, size, position, text, textColor)
{
	Widget::setTexture(textureReleased);
	Widget::setColor(bgColor);

	binded = BindedFunction<Button>();
	
	bind(EventType::BUTTON_LEFT_PRESS, butPres);
	bind(EventType::BUTTON_LEFT_RELEASE, butReles);

	canBeFocus = true;
}



//////////////////////////////////////////////////////////////////////////////
///// Getters and Setters ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

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



//////////////////////////////////////////////////////////////////////////////
///// Functions //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Button::draw()
{
	window->draw(this->sprite);
	window->draw(textObj);
}



//////////////////////////////////////////////////////////////////////////////
///// Functions for bind and run binded functions ////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Button::bind(EventType type, void(*fun)(EventParam<Button>param))
{
	this->binded.addFunct(type, fun);
}

void Button::startEventUpdate()
{
	runEventCheking(EventParam<Button>(*this, event));
}

void Button::runBindedFunctions(EventType type)
{
	//std::cout << "Button binded. ID: " << id << std::endl;
	Label::runBindedFunctions(type);
	Button::binded.run(type, EventParam<Button>(*this, event));
}
