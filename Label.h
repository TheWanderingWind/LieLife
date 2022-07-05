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
	Label(sf::RenderWindow* win, Size size = Size(0, 0), Position position = Position(0, 0),
		std::string text = "", sf::Color textColor = sf::Color::Black);

	/// <summary>
	/// Setter standart font
	/// </summary>
	/// <param name="font">new font</param>
	static void setStandardFont(sf::Font& font);

	/// <summary>
	/// Setter font for this widget
	/// </summary>
	/// <param name="font">new font</param>
	void setFont(sf::Font& font);

	/// <summary>
	/// Getter font (from this widget)
	/// </summary>
	/// <returns>sf::Font of text in this widget</returns>
	sf::Font getFont();

	/// <summary>
	/// Setter text
	/// </summary>
	/// <param name="str">new text</param>
	void setText(std::string str);

	/// <summary>
	/// Getter text
	/// </summary>
	/// <returns>std::string - text in widget</returns>
	std::string getText();

	/// <summary>
	/// Setter for text color
	/// </summary>
	/// <param name="col">new color for text</param>
	void setTextColor(sf::Color col);

	/// <summary>
	/// Getter color of text
	/// </summary>
	/// <returns>sf::Color - color of text in widget</returns>
	sf::Color getTextColot();
	
	/// <summary>
	/// Setter character size.
	/// Note, that not all font can be seted any size! 
	/// </summary>
	/// <param name="size">new character size (in pixels)</param>
	void setCharacterSize(int size);

	/// <summary>
	/// Getter character size
	/// </summary>
	/// <returns>int - size of character in pixels</returns>
	int getCharacterSize();

	/// <summary>
	/// Setter style for text
	/// (see more in sf::Text)
	/// </summary>
	/// <param name="style">new style</param>
	void setStyle(sf::Uint32 style);

	/// <summary>
	/// Getter text style
	/// </summary>
	/// <returns>Uint32 - style text in widget</returns>
	sf::Uint32 getStyle();

	/// <summary>
	/// Draw label
	/// </summary>
	void draw();

protected:
	/// <summary> text that show in window</summary>
	std::string text;
	/// <summary> text-object</summary>
	sf::Text textObj;
	/// <summary> standart font (style) of text</summary>
	static sf::Font standardFont;
	/// <summary> font (style) of text for this widget</summary>
	sf::Font font;
	/// <summary> Color of text</summary>
	sf::Color textColor;
	/// <summary> size of character</summary>
	int characterSize;
};

