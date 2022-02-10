#pragma once
#include <SFML/Graphics.hpp>
#include "Widgets.h"

/// <summary>
/// Standard button class
/// </summary>
class Button : public Widget
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win">-- Window in whith to display</param>
	/// <param name="texture">-- texture of button</param>
	/// <param name="size">-- size of button (in pixels)</param>
	/// <param name="position">-- position of button in window (in pixels)</param>
	/// <param name="col">-- widget color</param>
	/// <param name="text">-- text in button</param>
	Button(sf::RenderWindow* win, Size size, Position position, std::string text, sf::Color color);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win">-- Window in whith to display</param>
	/// <param name="texture">-- texture of button</param>
	/// <param name="size">-- size of button (in pixels)</param>
	/// <param name="position">-- position of button in window (in pixels)</param>
	/// <param name="text">-- text in button</param>
	Button(sf::RenderWindow *win, Size size, Position position, std::string text);

	/// <summary>
	/// Constructor without input settings
	/// 
	/// Standard settings:
	/// Position: X=0; Y=0.
	/// Size: width=120; height=80.
	/// without Color
	/// 
	/// </summary>
	/// <param name="win">-- Window in whith to display</param>
	/// <param name="texture">-- texture of button</param>
	Button(sf::RenderWindow *win);

	/// <summary>
	/// Widget texture getter
	/// </summary>
	static sf::Texture* getTexture();

	/// <summary>
	/// Widget texture setter
	/// </summary>
	static void setTexture(sf::Texture& texture);

	/// <summary>
	/// Widget texture getter
	/// </summary>
	static sf::Font* getFont();

	/// <summary>
	/// Widget texture setter
	/// </summary>
	static void setFont(sf::Font& font);

	/// <summary>
	/// Draw button
	/// </summary>
	void draw();

protected:
	/// <summary>
	/// Text in button
	/// (don't work yet)
	/// </summary>
	std::string text;

	static sf::Texture button_texture;

	static sf::Font button_font;

};