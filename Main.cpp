#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>

#include "Widgets.h"
#include "Button.h"


// Далі, що треба зробити:
// Як виявилось, після натискання кнопки, event не обновлюється
// Тому якщо після натисканні кнопки нічого не було, то 1) натискання зараховується багато разів,
// 2) воно постійно думає, що виникає подія натискання
// Треба ввести додаткову змінну, яка буде слідкувати за цим
// 
// Треба розробити класс Base (чи щось подібне), щоб в ньому збирати усі екземпляри Widget-ів 
// та через нього оновлювати віджети та перевіряти події, щоб не засирати головний код
//


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

void test1(EventParam param) {
	std::cout << "MOUSE_ENTER_1" << std::endl;
}
void test2(EventParam param) {
	std::cout << "MOUSE_ENTER_2" << std::endl;
}
void test3(EventParam param) {
	std::cout << "MOUSE_EXIT_3" << std::endl;
}
void test4(EventParam param) {
	std::cout << "MOUSE_EXIT_4" << std::endl;
}

// Main window cycle
int threadWindow(winParam* param, winSignals* signals, Resources* res)
{
	RenderWindow win((*param).videoMode, (*param).name); // Main window
	Event event;			// event-object for handles events
	

	// Geting texture for button
	while (!signals->readTexture) {}
	signals->readTexture.store(false, std::memory_order_seq_cst);
	Texture texture(res->button);	// texture for button
	Texture& texture_button = texture;
	signals->readTexture.store(true, std::memory_order_seq_cst);
	
	//Sprite sprite(texture_button);
	//sprite.setColor(Color(160, 160, 160, 225));

	Button::setTexture(texture_button);
	Button button1(&win, Size(100, 40), Position(10, 10), "");
	Button button2(&win, Size(100, 40), Position(120, 10), "");
	Button button3(&win, Size(100, 40), Position(230, 10), "");

	button1.bind(EventType::BUTTON_RIGTH_RELEASE, test1);
	button1.bind(EventType::MOUSE_ENTER, test2);
	button1.bind(EventType::MOUSE_EXIT, test3);
	button1.bind(EventType::BUTTON_LEFT_PRESS, test4);
	button2.bind(EventType::MOUSE_ENTER, [](EventParam param) -> void {
		std::cout << "button2!" << std::endl;
		});
	button3.bind(EventType::MOUSE_EXIT, [](EventParam param) -> void {
		std::cout << "button3!" << std::endl;
		});

	//button1.setTexture(texture_butt);

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
		
		//win.draw(sprite);

		button1.draw();
		button2.draw();
		button3.draw();

		button1.runFunctions(event);
		//button2.runFunctions(event);
		//button3.runFunctions(event);

		win.display();
	}
}

// Main function
int main()
{
	std::cout << "Start program\n\n";
	
	std::cout << "Load resources...\n";
	signals.readTexture.store(false, std::memory_order_seq_cst);
	if (!resources.button.loadFromFile("Resources/Button.png"))
	{
		std::cout << "Error read file.\n";
		resources.button.create(120, 80);
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