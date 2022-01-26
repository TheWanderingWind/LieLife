#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

using namespace sf;

void windowProcess(std::string nameWindow)
{
	Window win(VideoMode(800, 600), nameWindow);
	Event event;

	while (win.isOpen())
	{
		if (win.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				win.close();
			default:
				break;
			}
		}
	}
}

int main()
{
	std::cout << "Start program\n\n";

	std::cout << "Create window stream...\n";
	std::thread windowStream(windowProcess, "Test Window");

	std::cout << "Stream created.\n";
	windowStream.join();

	std::cout << "End work. Close programm.\n";
	return 0;
}