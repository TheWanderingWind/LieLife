#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>

#include "Widgets.h"
#include "Label.h"
#include "Button.h"

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

//void test1(EventParam param) {
//	std::cout << "MOUSE_ENTER_1" << std::endl;
//}
//void test2(EventParam param) {
//	std::cout << "MOUSE_ENTER_2" << std::endl;
//}
//void test3(EventParam param) {
//	std::cout << "MOUSE_EXIT_3" << std::endl;
//}
//void test4(EventParam param) {
//	std::cout << "MOUSE_EXIT_4" << std::endl;
//}

// Main window cycle
int threadWindow(winParam* param, winSignals* signals, Resources* res)
{
	RenderWindow win((*param).videoMode, (*param).name); // Main window
	Event event;			// event-object for handles events
	

	// Geting texture for button
	while (!signals->readTexture) {}
	signals->readTexture.store(false, std::memory_order_seq_cst);
	Texture texture(res->buttonReleased);	// texture for button
	Texture& texture_button_release = texture;
	texture = Texture(res->buttonReleased);	// texture for button
	Texture& texture_button_pressed = texture;
	Font font(res->font);	// texture for button
	Font& font_text= font;
	signals->readTexture.store(true, std::memory_order_seq_cst);
	
	// set standard resources
	Button::setTextureReleased(texture_button_release);
	Button::setTexturePressed(texture_button_pressed);
	Label::setStandardFont(font_text);
	
	// Initialization main widgets
	Button button1(&win, Size(180, 40), Position(10, 10), "Very-very long-long string");
	button1.setCharacterSize(16);
	//button1.bind(EventType::BUTTON_LEFT_RELEASE, [](EventParam<Button> param) {
	//	Texture n = Button::getTextureReleased();
	//	std::cout << "Reset\n";
	//	param.widget.setTexture(n);
	//	});


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
		if (win.pollEvent(event))
		{
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
		
		button1.updateAll(event);
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