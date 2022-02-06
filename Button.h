#pragma once
#include <SFML/Graphics.hpp>
#include "Widgets.h"

class Button : public Widget
{
protected:
	std::string text;

public:

	Button(sf::RenderWindow *win, sf::Texture &texture, Size size, Position position, std::string text);

	Button(sf::RenderWindow *win, sf::Texture &texture, Size size, Position position, std::string text, sf::Color color);

	Button(sf::RenderWindow *win, sf::Texture &texture);


	void draw();

};