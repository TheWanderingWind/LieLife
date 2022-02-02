#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>


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
	Texture button;
};

winParam param;
winSignals signals;
Resources resources;

// Main window cycle
int threadWindow(winParam* param, winSignals* signals, Resources* res)
{
	RenderWindow win((*param).videoMode, (*param).name);
	Event event;
	Sprite spriteTest;
	Texture tex_button;
	
	while (!signals->readTexture) {}
	signals->readTexture.store(false, std::memory_order_seq_cst);
	tex_button = res->button;
	signals->readTexture.store(true, std::memory_order_seq_cst);
	
	spriteTest.setTexture(tex_button);
	spriteTest.setPosition(Vector2f(20, 50));
	spriteTest.setColor(Color(0, 225, 225, 225));

	win.clear(Color(67, 67, 67, 33));

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
				std::cout << "sensor change\n";
				break;

			case Event::MouseButtonPressed:
				std::cout << "+";
				break;

			case Event::MouseButtonReleased:
				std::cout << "-\n";
				break;

			default:
				break;
			}
		}

		win.clear(Color(67, 67, 67, 33));
		
		win.draw(spriteTest);

		win.display();
	}
}

// Main function
int main()
{
	std::cout << "Start program\n\n";
	
	std::cout << "Load resources...\n";
	Texture tex;
	signals.readTexture.store(false, std::memory_order_seq_cst);
	if (!tex.loadFromFile("Resources/Button.png"))
	{
		std::cout << "Error read file.\n";
		tex.create(120, 80);
	}
	resources.button = tex;
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