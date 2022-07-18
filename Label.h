#pragma once
#include "Widgets.h"

template <typename T>
struct BindedFunction;

class Label : public Widget
{
public:
	//////////////////////////////////////////////////////////////////////////////
	// Constructions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win"> Window in whith to display</param>
	/// <param name="size"> size of widget-box (in pixels)</param>
	/// <param name="position"> position of label in window (in pixels)</param>
	/// <param name="text"> text in label </param>
	/// <param name="textColor"> color text</param>
	/// <param name="ñolor"> color background</param>
	Label(sf::RenderWindow* win, Size size = Size(0, 0), Position position = Position(0, 0),
		std::string text = "", sf::Color textColor = sf::Color::Black, 
		sf::Color color = sf::Color(225, 225, 225, 225));



	//////////////////////////////////////////////////////////////////////////////
	// Setters and Getters
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Getter font (from this widget)
	/// </summary>
	/// <returns>sf::Font of text in this widget</returns>
	sf::Font getFont();

	/// <summary>
	/// Setter font for this widget
	/// </summary>
	/// <param name="font">new font</param>
	void setFont(sf::Font& font);

	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary>
	/// Setter standart font
	/// </summary>
	/// <param name="font">new font</param>
	static void setStandardFont(sf::Font& font);
	///
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Getter text
	/// </summary>
	/// <returns>std::string - text in widget</returns>
	std::string getText();

	/// <summary>
	/// Setter text
	/// </summary>
	/// <param name="str">new text</param>
	void setText(std::string str);

	/// <summary>
	/// Getter color of text
	/// </summary>
	/// <returns>sf::Color - color of text in widget</returns>
	sf::Color getTextColot();

	/// <summary>
	/// Setter for text color
	/// </summary>
	/// <param name="col">new color for text</param>
	void setTextColor(sf::Color col);

	/// <summary>
	/// Getter character size
	/// </summary>
	/// <returns>int - size of character in pixels</returns>
	int getCharacterSize();

	/// <summary>
	/// Setter character size.
	/// Note, that not all font can be seted any size! 
	/// </summary>
	/// <param name="size">new character size (in pixels)</param>
	void setCharacterSize(int size);

	/// <summary>
	/// Getter text style
	/// </summary>
	/// <returns>Uint32 - style text in widget</returns>
	sf::Uint32 getStyle();

	/// <summary>
	/// Setter style for text
	/// (see more in sf::Text)
	/// </summary>
	/// <param name="style">new style</param>
	void setStyle(sf::Uint32 style);



	//////////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////////
	
	/// <summary>
	/// Draw label
	/// </summary>
	void draw() override;

	/// <summary>
	/// Set position character to center of widget-box (size widget)
	/// </summary>
	void autoTextPosition();
	


	//////////////////////////////////////////////////////////////////////////////
	// Functions for bind and run binded functions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Bind function
	/// </summary>
	/// <param name="type">Event type (when function must run)</param>
	/// <param name="fun">function worth run</param>
	void bind(EventType type, void (*fun)(EventParam<Label> param));

	/// <summary>
	/// Make parameters for using in binded functions and setup runFunction()
	/// </summary>
	/// <param name="event">Event object from SF, for getting some parameters</param>
	void startUpdate(sf::Event event) override;



	//////////////////////////////////////////////////////////////////////////////
	// Fields and constants 
	//////////////////////////////////////////////////////////////////////////////

protected:
	/// <summary> binded function with this widget </summary>
	BindedFunction<Label> binded;

	/// <summary> text that show in window</summary>
	std::string text;
	/// <summary> text-object</summary>
	sf::Text textObj;
	/// <summary> text position in widget-box</summary>
	Position textPosition;
	/// <summary> size of character</summary>
	int characterSize;
	/// <summary> font (style) of text for this widget</summary>
	sf::Font font;
	/// <summary> Color of text</summary>
	sf::Color textColor;
	
	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary> standart font (style) of text</summary>
	static sf::Font standardFont;
	///
	//////////////////////////////////////////////////////////////////////////////
};

