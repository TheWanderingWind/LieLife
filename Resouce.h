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

// if pressed key now?
static bool isKeyPressed = false;

/// <summary>
/// Struct with parametrs of event (for making functions)
/// </summary>
template <typename T>
struct EventParam
{
	// Widget that run this function
	T& widget;
	// Position of mouse now
	Position mousePosition;
	// Symbol that presed (otherwise it will be zero)
	char sumbol = 0;
	// Index key that presed (if it can`t be sumbol, example 'Backspace')
	int key = -1;
	
public:
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

		// for now pressing the key will not allow to enter multiple characters
		// (you need pressed and released some times for this)
		if (event.KeyPressed == event.type && !isKeyPressed)
		{
			isKeyPressed = true;
			sumbol = getSumbol(event.key.code, event.key.shift);
			if (sumbol == 0) 
				key = event.key.code;
		}
		if (event.KeyReleased == event.type && isKeyPressed)
		{
			isKeyPressed = false;
			std::cout << std::endl;
		}
	}

	/// <summary>
	/// Check the key code and return the sumbol (if it can be sumbol)
	/// </summary>
	/// <param name="code">code of key</param>
	/// <param name="shift">if pressed Shift?</param>
	/// <returns>Returnt sumbol, if it can be sumbol return null-sumbol (char 0)</returns>
	char getSumbol(int code, bool shift)
	{
		if (Keyboard::A <= code && code <= Keyboard::Z)
		{
			if (shift)
				return code + 65;
			else
				return code + 97;
		}
		if (Keyboard::Num0 <= code && code <= Keyboard::Num9)
		{
			if (shift)
				switch (code)
				{
				case Keyboard::Num0:
					return 41;
				case Keyboard::Num1:
					return 33;
				case Keyboard::Num2:
					return 64;
				case Keyboard::Num3:
					return 35;
				case Keyboard::Num4:
					return 36;
				case Keyboard::Num5:
					return 37;
				case Keyboard::Num6:
					return 94;
				case Keyboard::Num7:
					return 38;
				case Keyboard::Num8:
					return 42;
				case Keyboard::Num9:
					return 40;
				default:
					break;
				} 
			else
				return code + 22;
		}

		if (!shift)
			switch (code)
			{
			case Keyboard::LBracket:
				return 91;
			case Keyboard::RBracket:
				return 93;
			case Keyboard::Semicolon:
				return 59;
			case Keyboard::Comma:
				return 44;
			case Keyboard::Period:
				return 46;
			case Keyboard::Quote:
				return 39;
			case Keyboard::Slash:
				return 47;
			case Keyboard::Backslash:
				return 92;
			case Keyboard::Tilde:
				return 126;
			case Keyboard::Equal:
				return 61;
			case Keyboard::Hyphen:
				return 45;
			case Keyboard::Space:
				return 32;
			case Keyboard::Add:
				return 43;
			case Keyboard::Subtract:
				return 45;
			case Keyboard::Multiply:
				return 42;
			case Keyboard::Divide:
				return 47;
			default:
				break;
			}
		if (shift)
			switch (code)
			{
			case Keyboard::LBracket:
				return 123;
			case Keyboard::RBracket:
				return 125;
			case Keyboard::Semicolon:
				return 58;
			case Keyboard::Comma:
				return 60;
			case Keyboard::Period:
				return 62;
			case Keyboard::Quote:
				return 34;
			case Keyboard::Slash:
				return 63;
			case Keyboard::Backslash:
				return 124;
			case Keyboard::Tilde:
				return 196;
			case Keyboard::Equal:
				return 43;
			case Keyboard::Hyphen:
				return 95;
			case Keyboard::Space:
				return 32;
			case Keyboard::Add:
				return 43;
			case Keyboard::Subtract:
				return 45;
			case Keyboard::Multiply:
				return 42;
			case Keyboard::Divide:
				return 47;
			default:
				break;
			}

		return 0;
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

