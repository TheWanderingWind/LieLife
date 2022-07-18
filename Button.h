#pragma once
#include "Label.h"

template <typename T>
struct BindedFunction;

/// <summary>
/// Standard button class
/// </summary>
class Button : public Label
{
public:
	//////////////////////////////////////////////////////////////////////////////
	// Constructions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win"> Window in whith to display</param>
	/// <param name="texture"> texture of button</param>
	/// <param name="size"> size of button (in pixels)</param>
	/// <param name="position"> position of button in window (in pixels)</param>
	/// <param name="text"> text in button</param>
	/// <param name="textColor"> text color</param>
	/// <param name="bgColor"> background color</param>
	Button(sf::RenderWindow* win, Size size = Size(0,0), Position position = Position(0, 0),
		std::string text = "", sf::Color textColor = sf::Color::Black,
		sf::Color bgColor = sf::Color(225, 225, 225, 225));



	//////////////////////////////////////////////////////////////////////////////
	// Setters and Getters
	//////////////////////////////////////////////////////////////////////////////

	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary>
	/// Getter button texture in general
	/// </summary>
	static sf::Texture getTextureReleased();
	///
	/// <summary>
	/// Getter button texture when pressed
	/// </summary>
	static sf::Texture getTexturePressed();
	///
	/// <summary>
	/// Setter button texture in general
	/// </summary>
	static void setTextureReleased(sf::Texture texture);
	///
	/// <summary>
	/// Setter button texture when pressed
	/// </summary>
	static void setTexturePressed(sf::Texture texture);
	///
	//////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Draw button
	/// </summary>
	void draw() override;



	//////////////////////////////////////////////////////////////////////////////
	// Functions for bind and run binded functions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Bind function
	/// </summary>
	/// <param name="type">Event type (when function must run)</param>
	/// <param name="fun">function worth run</param>
	void bind(EventType type, void (*fun)(EventParam<Button> param));

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
	BindedFunction<Button> binded;

	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary> Standatd texture, when button released</summary>
	static sf::Texture textureReleased;
	/// <summary> Standatd texture, when button pressed</summary>
	static sf::Texture texturePressed;
	///
	//////////////////////////////////////////////////////////////////////////////
};