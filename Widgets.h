#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/// <summary>
/// Struct for storage position data (in pixels)
/// </summary>
struct Position
{
	float X, Y;

	Position(float X, float Y)
	{
		this->X = X;
		this->Y = Y;
	}

	Position()
	{
		this->X = 0;
		this->Y = 0;
	}
};

/// <summary>
/// Struct for storage sie data (in pixels)
/// </summary>
struct Size
{
	int width, height;

	Size(int wid, int hei)
	{
		this->width = wid;
		this->height = hei;
	}

	Size()
	{
		this->height = 80;
		this->width = 120;
	}
};

/// <summary>
/// Enum with types of events
/// </summary>
enum EventType
{
	BUTTON_LEFT_PRESS,
	BUTTON_LEFT_RELEASE,
	BUTTON_RIGTH_PRESS,
	BUTTON_RIGTH_RELEASE,
	MOUSE_ENTER,
	MOUSE_EXIT,
	KEY_PRESS,
	KEY_RELEASE
};

// for correct making struct
class Widget;

/// <summary>
/// Struct with parametrs of event (for making functions)
/// </summary>
struct EventParam
{
	Widget& widget;
	Position mousePosition;

	EventParam(Widget& wid, sf::Event event);
};

/// <summary>
/// Base class for widgets
/// </summary>
class Widget
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="win">-- Window in whith to display</param>
	/// <param name="siz">-- size of widget (in pixels)</param>
	/// <param name="pos">-- position of widget in window (in pixels)</param>
	/// <param name="col">-- widget color</param>
	Widget(sf::RenderWindow* win, Size siz = Size(0, 0), 
		Position pos = Position(0, 0), sf::Color color = sf::Color(225, 225, 225, 225));

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
	void setColor(int r, int g, int b, int w);

	/// <summary>
	/// Widget color setter
	/// </summary>
	void setColor(sf::Color col);

	/// <summary>
	/// Widget texture getter
	/// </summary>
	sf::Texture* getTexture();

	/// <summary>
	/// Widget texture setter
	/// </summary>
	void setTexture();

	/// <summary>
	/// Widget texture setter
	/// </summary>
	void setTexture(sf::Texture &tex);

	/// <summary>
	/// Draw widget
	/// </summary>
	virtual void draw();

	/// <summary>
	/// Struct with function and type event when run this function
	/// </summary>
	struct BindedFunction
	{
	private:
		/// <summary>struct with just function and type</summary>
		struct TypeAndFunc
		{
			EventType mainType;
			void (*func) (EventParam param);

			TypeAndFunc(EventType type, void (*fun)(EventParam param));
			TypeAndFunc();
		};

		/// <summary>array of functions</summary>
		TypeAndFunc* arrayFunc = new TypeAndFunc[0];
		/// <summary> size of array </summary>
		int size = 0;
	public:

		/// <summary>
		/// Add new function
		/// </summary>
		/// <param name="type">type of event when function must run</param>
		/// <param name="fun">function to be run</param>
		void addFunct(EventType type, void (*fun)(EventParam param));

		/// <summary>
		/// Run function
		/// </summary>
		/// <param name="type">type of event that are binded</param>
		/// <param name="param">parameters of event</param>
		void run(EventType type, EventParam param);

		/// <summary>
		/// Delete function
		/// </summary>
		/// <param name="type">type of event when function must run</param>
		/// <param name="fun">function to be removed</param>
		void deleteFunct(EventType type, void (*fun)(EventParam param));
	};

	/// <summary>
	/// Bind function
	/// </summary>
	/// <param name="type">Event type (when function must run)</param>
	/// <param name="fun"></param>
	void bind(EventType type, void (*fun)(EventParam param));

	/// <summary>
	/// Checks the event type that occurred and run functions
	/// </summary>
	void runFunctions(sf::Event event);

	// must be delete in future!
	sf::RenderWindow* getWindow();

	static void updateAll(sf::Event event);

protected:
	/// <summary>
	/// Make parameters for using in dinded functions
	/// </summary>
	/// <param name="event">Event object from SF, for getting some parameters</param>
	/// <returns>EventParam object</returns>
	EventParam makeParam(sf::Event event);

	/// <summary> sprite of widget </summary>
	sf::Sprite sprite;
	/// <summary> texture of widget </summary>
	sf::Texture texture;
	/// <summary> link to the window in wich the widget is located </summary>
	sf::RenderWindow* window;

	/// <summary> size of widget </summary>
	Size size;
	/// <summary> position of widget in window </summary>
	Position position;
	/// <summary> color of widget </summary>
	sf::Color color;
	/// <summary> binded function with this widget </summary>
	BindedFunction binded;
	/// <summary> Last position of mouse </summary>
	Position lastMousePosition;
	/// <summary> If button pressed now </summary>
	bool buttonIsPresed = false;

private:
	Widget();

	static Widget** allWidgets;
	static int numWidgets;

	static void addWidget(Widget *wid);


};