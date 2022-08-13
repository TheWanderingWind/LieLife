#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>

#include "Widgets.h"
#include "Label.h"
#include "Button.h"
#include "Entry.h"

using namespace sf;

// Struct for settings window
struct winParam
{	
	// size window
	VideoMode videoMode{VideoMode(800, 600)};
	// name window (title)
	std::string name{""};
};

// Struct for send signals
struct winSignals
{
	// for forsed window close
	std::atomic<bool> closeNow{false};
	// for update settings window
	std::atomic<bool> updateParam{false};
	// for update game matrix
	std::atomic<bool> updateMatrix{false};
	// for get or set texture
	std::atomic<bool> readTexture{ true };
};

struct Resources
{
	Texture buttonReleased;
	Texture buttonPressed;
	Font font;
};

winParam param;
winSignals signals;
Resources resources;

// Main window cycle
int threadWindow(winParam* param, winSignals* signals, Resources* res)
{
	RenderWindow win((*param).videoMode, (*param).name); // Main window
	Event& event = Widget::getEvent();
	// event-object for handles events
	

	// Geting texture for button
	while (!signals->readTexture) {}
	signals->readTexture.store(false, std::memory_order_seq_cst);
	// Start load resouces from memory
	
	// set standard resources
	Button::setTextureReleased(res->buttonReleased);
	Button::setTexturePressed(res->buttonPressed);
	Label::setStandardFont(res->font);
	 
	// End load resouces from memory
	signals->readTexture.store(true, std::memory_order_seq_cst);
	
	// Initialization main widgets
	Button button1(&win, Size(180, 40), Position(10, 10), "Button #1");
	Button button2(&win, Size(180, 40), Position(200, 10), "Button #2");
	Button button3(&win, Size(180, 40), Position(420, 10), "Button #3");
	Button button4(&win, Size(180, 40), Position(6400, 10), "Button #4");
	
	button1.bind(LOST_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 1 lost focus\n";
		});
	button1.bind(GET_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 1 get focus\n";
		});
	button2.bind(LOST_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 2 lost focus\n";
		});
	button2.bind(GET_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 2 get focus\n";
		});
	button3.bind(LOST_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 3 lost focus\n";
		});
	button3.bind(GET_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 3 get focus\n";
		});
	button4.bind(LOST_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 4 lost focus\n";
		});
	button4.bind(GET_FOCUS, [](EventParam<Button> param) -> void {
		std::cout << "Button 4 get focus\n";
		});


	//Entry entry1(&win, Size(200, 30), Position(40, 200));

	while (win.isOpen())
	{
		// Forced window close
		if ((*signals).closeNow.load(std::memory_order_seq_cst)) {
			win.close();
			(*signals).closeNow.store(false, std::memory_order_seq_cst);
			return 1;
		};

		// Update window settiings
		if ((*signals).updateParam.load(std::memory_order_seq_cst)) {
			win.setSize(
				Vector2u(
					(*param).videoMode.width,
					(*param).videoMode.height
				));
			win.setTitle((*param).name);
			(*signals).updateParam.store(false, std::memory_order_seq_cst);
		}

		

		// Handles events
		while (win.pollEvent(event))
		{
			Widget::updateAllCalls();
			switch (event.type)
			{
			case Event::Closed:
				win.close();
				return 0;

			case Event::MouseEntered:
				break;

			case Event::MouseLeft:
				break;

			case Event::Resized:
				win.clear(Color(67, 67, 67, 33));
				win.display();
				break;

			case Event::SensorChanged:
				break;

			case Event::MouseButtonPressed:
				break;

			case Event::MouseButtonReleased:
				break;

			default:
				break;
			}
		}

		win.clear(Color(67, 67, 67, 33));
		Widget::updateAllDraws();
		win.display();
	}
}

// Main function
int main()
{
	std::cout << "Start program\n\n";
	
	std::cout << "Load resources...\n";
	signals.readTexture.store(false, std::memory_order_seq_cst);
	if (!resources.buttonReleased.loadFromFile("Resources/Button.png"))
	{
		std::cout << "Error read file (button texture_release).\n";
		std::cout << "Creating null texture.\n";
		resources.buttonReleased.create(120, 80);
	}
	if (!resources.buttonPressed.loadFromFile("Resources/ButtonPressed.png"))
	{
		std::cout << "Error read file (button texture_pressed).\n";
		std::cout << "Creating null texture.\n";
		resources.buttonPressed.create(120, 80);
	}

	if (!resources.font.loadFromFile("Resources/vgafixr.fon"))
	{
		std::cout << "Error read file (first text font).\n";
		std::cout << "Try read second font.\n";
		if (!resources.font.loadFromFile("Resources/19036.ttf"))
		{
			std::cout << "Error read file (second text font).\n";
			std::cout << "Cant find any font.\n";
			std::cout << "Close program.\n";
			return 1;
		}
	}
	
	signals.readTexture.store(true, std::memory_order_seq_cst);

	std::cout << "Create window thread...\n";
	std::thread thr(threadWindow, &param, &signals, &resources);

	std::cout << "Thread created.\n";


	// Forsed window close
	//signals.closeNow.store(true, std::memory_order_seq_cst);
	
	thr.join();

	std::cout << "End work. Close programm.\n";
	return 0;
}