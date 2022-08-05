#pragma once

#include <iostream>

#include "Resouce.h"


/// <summary>
/// Base class for widgets
/// </summary>
class Widget
{
public:
	//////////////////////////////////////////////////////////////////////////////
	// Constructions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win"> Window in whith to display</param>
	/// <param name="siz"> size of widget (in pixels)</param>
	/// <param name="pos"> position of widget in window (in pixels)</param>
	/// <param name="col"> widget color</param>
	Widget(sf::RenderWindow* win, Size siz = Size(0, 0), 
		Position pos = Position(0, 0), sf::Color color = sf::Color(225, 225, 225, 225));

	/// <summary>
	/// Destructor
	/// </summary>
	~Widget();

private:
	/// <summary>
	/// Special constructor for making null-widget in arrays
	/// </summary>
	Widget();



	//////////////////////////////////////////////////////////////////////////////
	// Setters and Getters
	//////////////////////////////////////////////////////////////////////////////

public:
	/// <summary>
	/// Widget size getter
	/// </summary>
	Size getSize();

	/// <summary>
	/// Widget size setter
	/// </summary>
	void setSize(Size siz);

	/// <summary>
	/// Widget size setter
	/// </summary>
	void setSize(int x, int y);

	/// <summary>
	/// Widget position getter
	/// </summary>
	Position getPosition();

	/// <summary>
	/// Widget position setter
	/// </summary>
	void setPosition(Position pos);

	/// <summary>
	/// Widget position setter
	/// </summary>
	void setPosition(float X, float Y);

	/// <summary>
	/// Widget color getter
	/// </summary>
	sf::Color getColor();

	/// <summary>
	/// Widget color setter
	/// </summary>
	void setColor(sf::Color col);

	/// <summary>
	/// Widget color setter
	/// </summary>
	void setColor(int r, int g, int b, int w);

	/// <summary>
	/// Widget texture getter
	/// </summary>
	sf::Texture* getTexture();

	/// <summary>
	/// Widget texture setter
	/// </summary>
	void setTexture(sf::Texture& tex);

	/// <summary>
	/// Make new textrure 120x80 pixels and set
	/// </summary>
	void setCreateTexture();

	/// <summary>
	/// Return window wherein this widget
	/// </summary>
	sf::RenderWindow* getWindow();

	/// <summary>
	/// Getter widget focus
	/// </summary>
	bool getFocus();

	/// <summary>
	/// Setter widget focus
	/// </summary>
	void setFocus(bool focus);
	
	/// <summary>
	/// Getter can be widget focus
	/// </summary>
	bool getCanBeFocus();

	/// <summary>
	/// Setter can be widget focus
	/// </summary>
	void setCanBeFocus(bool canBe);

	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary>
	/// Getter focused widget link
	/// </summary>
	static Widget& getFocused();
	/// 
	//////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Draw widget
	/// </summary>
	virtual void draw();

private:
	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary>
	/// Add new widget (link) to array
	/// </summary>
	/// <param name="wid">new widget</param>
	static void addWidget(Widget* wid);
	///
	/// <summary>
	/// delete widget from array
	/// </summary>
	/// <param name="id">id of widget that shoud delete</param>
	static void deleteWidget(int id);
	/// 
	//////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////
	// Functions for bind and run binded functions
	//////////////////////////////////////////////////////////////////////////////
public:
	/// <summary>
	/// Bind function
	/// </summary>
	/// <param name="type">Event type (when function must run)</param>
	/// <param name="fun">function worth run</param>
	void bind(EventType type, void (*fun)(EventParam<Widget> param));

	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary>
	/// Draw and run event function all widgets
	/// </summary>
	/// <param name="event">sf::Event - event-object</param>
	static void updateAll(sf::Event event);
	///
	//////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Start cheking event and setup event-functions
	/// </summary>
	/// <param name="event">Event object from SF, for getting some parameters</param>
	virtual void startEventUpdate(sf::Event event);

protected:
	/// <summary>
	/// Checks the event type that occurred and run functions
	/// (only for this widget!)
	/// </summary>
	template <typename T>
	void runEventCheking(sf::Event event, EventParam<T> eve, BindedFunction<T> binded);

	/// <summary>
	/// Run binded functions
	/// </summary>
	virtual void runBindedFunctions(EventType type, EventParam<Widget> param);

	template <typename T>
	void testFuncRuner(EventType type, EventParam<T> param);



protected:
	//////////////////////////////////////////////////////////////////////////////
	// Fields and constants 
	//////////////////////////////////////////////////////////////////////////////

	/// <summary> link to the window in wich the widget is located </summary>
	sf::RenderWindow* window;

	/// <summary> sprite of widget </summary>
	sf::Sprite sprite;
	/// <summary> texture of widget </summary>
	sf::Texture texture;

	/// <summary> size of widget </summary>
	Size size;
	/// <summary> position of widget in window </summary>
	Position position;
	/// <summary> color of widget </summary>
	sf::Color color;

	/// <summary> binded function with this widget </summary>
	BindedFunction<Widget> binded;
	/// <summary> last position of mouse</summary>
	Position lastMousePosition;
	/// <summary> If button pressed now </summary>
	bool buttonIsPresed = false;

	/// <summary> this widget in focus?</summary>
	bool isFocus;
	/// <summary> this widget can be focus?</summary>
	bool canBeFocus;

	/// Static ///////////////////////////////////////////////////////////////////
	/// 
	/// <summary> Widget that in focus now </summary>
	static Widget& focused;
	/// 
private:
	/// <summary> array whith all widgets (links)</summary>
	static Widget** allWidgets;
	/// <summary> number of widgets in array</summary>
	static int numWidgets;
	///
	//////////////////////////////////////////////////////////////////////////////
	
	// Id of widget
	int id;
};

template <typename T>
void testFuncRuner(EventType type, EventParam<T> param)
{
	T::binded.run(type, param);
}


template <typename T>
void Widget::runEventCheking(sf::Event events, EventParam<T> eve, BindedFunction<T> binded)
{
	if ((eve.mousePosition.X == lastMousePosition.X) &&
		(eve.mousePosition.Y == lastMousePosition.Y))
	{	// Position of mouse was not changed
	// for now no events, when it matter
	}
	else
	{	// Position of mouse was changed
		if ((eve.mousePosition.X > position.X) &&
			(eve.mousePosition.Y > position.Y) &&
			(eve.mousePosition.X < position.X + size.width) &&
			(eve.mousePosition.Y < position.Y + size.height))
		{	// mouse in widget now
			if ((lastMousePosition.X > position.X) &&
				(lastMousePosition.Y > position.Y) &&
				(lastMousePosition.X < position.X + size.width) &&
				(lastMousePosition.Y < position.Y + size.height))
			{	// mouse was in widget before
			// for now no events, when it matter
			}
			else // mouse was not in widget before
				testFuncRuner(MOUSE_ENTER, eve);
				//binded.run(MOUSE_ENTER, eve);

		}
		else 
		{	// mouse not in widget now
			if ((lastMousePosition.X > position.X) &&
				(lastMousePosition.Y > position.Y) &&
				(lastMousePosition.X < position.X + size.width) &&
				(lastMousePosition.Y < position.Y + size.height))
			{ 	// mouse was in widget before
				testFuncRuner(MOUSE_EXIT, eve);
				//binded.run(MOUSE_EXIT, eve);
			}
		}

		// set new last mouse position
		lastMousePosition = eve.mousePosition;
	}


	// Not matter if mouse move
	if ((events.type == sf::Event::MouseButtonPressed) && (buttonIsPresed == false))
	{ // Mouse button presed
		buttonIsPresed = true;
		if ((eve.mousePosition.X > position.X) &&
			(eve.mousePosition.Y > position.Y) &&
			(eve.mousePosition.X < position.X + size.width) &&
			(eve.mousePosition.Y < position.Y + size.height))
		{	// mouse in widget now
			if (events.mouseButton.button == 0)
			{	// pressed button # 0 (left button)
				testFuncRuner(BUTTON_LEFT_PRESS, eve);
				//binded.run(BUTTON_LEFT_PRESS, eve);

				if (eve.widget.getCanBeFocus() == true)
				{
					if (eve.widget.getFocus() == false)
					{
						//focused.
					}
				}
			}
			if (events.mouseButton.button == 1)
			{	// pressed button # 1 (ridth button)
				testFuncRuner(BUTTON_RIGTH_PRESS, eve);
				//binded.run(BUTTON_RIGTH_PRESS, eve);
			}
		}
	}
	if ((events.type == sf::Event::MouseButtonReleased) && (buttonIsPresed == true))
	{ // Mouse button presed
		buttonIsPresed = false;
		if ((eve.mousePosition.X > position.X) &&
			(eve.mousePosition.Y > position.Y) &&
			(eve.mousePosition.X < position.X + size.width) &&
			(eve.mousePosition.Y < position.Y + size.height))
		{	// mouse in widget now
			if (events.mouseButton.button == 0)
			{	// released button # 0 (left button)
				testFuncRuner(BUTTON_LEFT_RELEASE, eve);
				//binded.run(BUTTON_LEFT_RELEASE, eve);
			}
			if (events.mouseButton.button == 1)
			{	// released button # 1 (rigth button)
				testFuncRuner(BUTTON_RIGTH_RELEASE, eve);
				//binded.run(BUTTON_RIGTH_RELEASE, eve);
			}
		}
	}
}

