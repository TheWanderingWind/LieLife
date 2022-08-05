#pragma once
#include <iostream>

#include "Label.h"

class Entry : public Label
{
public:
	//////////////////////////////////////////////////////////////////////////////
	// Constructions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win"> Window in whith to display</param>
	/// <param name="size"> size widget-box (in pixels)</param>
	/// <param name="position"> position of entry in window (in pixels)</param>
	/// <param name="textColor"> text color</param>
	Entry(sf::RenderWindow* win, Size size = Size(0, 0), Position position = Position(0, 0),
		sf::Color textColor = sf::Color::Black);



	//////////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Draw widget
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
	void bind(EventType type, void (*fun)(EventParam<Entry> param));

	/// <summary>
	/// Start cheking event and setup event-functions
	/// </summary>
	/// <param name="event">Event object from SF, for getting some parameters</param>
	void startEventUpdate(sf::Event event) override;

	/// <summary>
	/// Run binded functions
	/// </summary>
	void runBindedFunctions(EventType type, EventParam<Entry> param);



	//////////////////////////////////////////////////////////////////////////////
	// Fields and constants 
	//////////////////////////////////////////////////////////////////////////////

protected:
	/// <summary> binded function with this widget </summary>
	BindedFunction<Entry> binded;
};

