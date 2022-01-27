#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>


using namespace sf;

struct winParam
{
	VideoMode videoMode;
	std::string name;
};

struct winSignals
{
	std::atomic<bool> closeNow;
	std::atomic<bool> updateParam;
};

winParam param;
winSignals signals;

int threadWindow(winParam* param, winSignals* signals)
{
	Window win((*param).videoMode, (*param).name);
	Event event;

	while (win.isOpen())
	{
		if ((*signals).closeNow.load(std::memory_order_seq_cst)) {
			win.close();
			return 1;
		};

		if (win.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				win.close();
				return 0;
			default:
				break;
			}
		}
	}
}

void standartParam() {
	param.name = "LieLife";
	param.videoMode = VideoMode(800, 600);

	signals.closeNow.store(false, std::memory_order_seq_cst);
}

int main()
{
	std::cout << "Start program\n\n";
	standartParam();
	
	std::cout << "Create window stream...\n";
	std::thread thr(threadWindow, &param, &signals);

	std::cout << "Stream created.\n";

	std::cout << "Press 'Enter' to close window";
	std::cin >> param.name;

	signals.closeNow.store(true, std::memory_order_seq_cst);
	thr.join();

	std::cout << "End work. Close programm.\n";
	return 0;
}