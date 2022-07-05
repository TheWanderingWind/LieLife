#pragma once
#include <SFML/Graphics.hpp>
#include "Widgets.h"



class Label : public Widget
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win">-- Window in whith to display</param>
	/// <param name="size">-- size of text (in pixels?)</param>
	/// <param name="position">-- position of text in window (in pixels)</param>
	/// <param name="col">-- widget color (color text?)</param>
	/// <param name="text">-- text </param>
	Label(sf::RenderWindow* win, Size size, Position position, std::string text, sf::Color color);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win">-- Window in whith to display</param>
	/// <param name="texture">-- texture of button</param>
	/// <param name="size">-- size of text (in pixels?)</param>
	/// <param name="position">-- position of text in window (in pixels)</param>
	/// <param name="text">-- text</param>
	Label(sf::RenderWindow* win, Size size, Position position, std::string text);

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
	/// <param name="text">-- text</param>
	Label(sf::RenderWindow* win, std::string text);

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
	Label(sf::RenderWindow* win);

	static void setFont(sf::Font& font);

	/// <summary>
	/// Draw button
	/// </summary>
	void draw();

protected:
	/// <summary> text that show in window</summary>
	std::string text;
	/// <summary> text-object</summary>
	sf::Text textObj;
	/// <summary> font (style) of text</summary>
	static sf::Font font;
};

