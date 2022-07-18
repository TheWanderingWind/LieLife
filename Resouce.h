#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

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
//class Widget;

/// <summary>
/// Struct with parametrs of event (for making functions)
/// </summary>
template <typename T>
struct EventParam
{
	T& widget;
	Position mousePosition;

	EventParam(T& wid, sf::Event event) : widget(wid)
	{
		RenderWindow* window = wid.getWindow();

		if ((window->getPosition().x < Mouse::getPosition().x - 8 &&
			Mouse::getPosition().x - 8 < window->getPosition().x + window->getSize().x)
			&&
			(window->getPosition().y < Mouse::getPosition().y - 30 &&
				Mouse::getPosition().y - 30 < window->getPosition().y + window->getSize().y))

			mousePosition = Position(Mouse::getPosition().x - window->getPosition().x - 8,
				Mouse::getPosition().y - window->getPosition().y - 30);
		else
			mousePosition = Position(-1, -1);
	}
};

/// <summary>
/// Struct with function and type event when run this function
/// </summary>
template <typename T>
struct BindedFunction
{
private:
	/// <summary>struct with just function and type</summary>
	struct TypeAndFunc
	{
		EventType mainType;
		void (*func) (EventParam<T> param);

		TypeAndFunc(EventType type, void(*fun)(EventParam<T> param))
		{
			mainType = type;
			func = fun;
		}
		TypeAndFunc()
		{
			/// nothing
		}
	};

	/// <summary>array of functions</summary>
	TypeAndFunc* arrayFunc = new TypeAndFunc[0];
	/// <summary> size of array </summary>
	int size = 0;
public:

	/// <summary>
	/// Getter size of function array
	/// </summary>
	/// <returns></returns>
	int getSize()
	{
		return size;
	}

	/// <summary>
	/// Add new function
	/// </summary>
	/// <param name="type">type of event when function must run</param>
	/// <param name="fun">function to be run</param>
	void addFunct(EventType type, void(*fun)(EventParam<T> param))
	{
		TypeAndFunc* newArray = new TypeAndFunc[size + 1];

		for (int i = 0; i < size; i++) {
			newArray[i] = arrayFunc[i];//TypeAndFunc(arrayFunc[i].mainType, arrayFunc[i].func);
		}
		newArray[size] = TypeAndFunc(type, fun);
		size++;

		//delete arrayFunc;
		arrayFunc = newArray;
	}

	/// <summary>
	/// Run function
	/// </summary>
	/// <param name="type">type of event that are binded</param>
	/// <param name="param">parameters of event</param>
	void run(EventType type, EventParam<T> param)
	{
		for (int i = 0; i < size; i++)
		{
			if (arrayFunc[i].mainType == type)
				arrayFunc[i].func(param);
		}
	}

	/// <summary>
	/// Delete function
	/// </summary>
	/// <param name="type">type of event when function must run</param>
	/// <param name="fun">function to be removed</param>
	void deleteFunct(EventType type, void(*fun)(EventParam<T> param))
	{
		int num = -1;
		for (int i = 0; i < size; i++) // try find function to be remove
		{
			if (arrayFunc[i].mainType == type)
				if (arrayFunc[i].func == fun)
				{
					num = i;
					break;
				}

		}

		if (num == -1) return; // if we don`t find

		TypeAndFunc* newArray = new TypeAndFunc[size - 1];
		for (int i = 0; i < num; i++)
			newArray[i] = arrayFunc[i];
		for (int i = num + 1; i < size; i++)
			newArray[i - 1] = arrayFunc[i];

		size--;
		arrayFunc = newArray;
	}
};

