#pragma once
#include <SFML/Graphics.hpp>
#include "Label.h"

/// <summary>
/// Standard button class
/// </summary>
class Button : public Label
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
	Button(sf::RenderWindow* win, Size size = Size(0,0), Position position = Position(0, 0),
		std::string text = "", sf::Color textColor = sf::Color::Black,
		sf::Color bgColor = sf::Color(225, 225, 225, 225));

	/// <summary>
	/// Setter button texture in general
	/// </summary>
	static void setTextureRelease(sf::Texture texture);

	/// <summary>
	/// Setter button texture when pressed
	/// </summary>
	static void setTexturePressed(sf::Texture texture);

	/// <summary>
	/// Getter button texture in general
	/// </summary>
	static sf::Texture getTextureRelease();

	/// <summary>
	/// Getter button texture when pressed
	/// </summary>
	static sf::Texture getTexturePressed();

	/// <summary>
	/// Draw button
	/// </summary>
	void draw();

protected:
	static sf::Texture textureReleased;
	static sf::Texture texturePressed;
};