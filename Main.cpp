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
	std::atomic<VideoMode> videoMode;
	// name window (title)
	std::atomic<std::string> name;
};

// Struct for send signals
struct winSignals
{
	// for forsed window close
	std::atomic<bool> closeNow;
	// for update settings window
	std::atomic<bool> updateParam;
};

winParam param;
winSignals signals;

// Main window cycle
int threadWindow(winParam* param, winSignals* signals)
{
	Window win((*param).videoMode.load(std::memory_order_seq_cst), (*param).name.load(std::memory_order_seq_cst));
	Event event;

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
					(*param).videoMode.load(std::memory_order_seq_cst).width,
					(*param).videoMode.load(std::memory_order_seq_cst).height
				));
			win.setTitle((*param).name.load(std::memory_order_seq_cst));
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
			default:
				break;
			}
		}
	}
}

// Set standard settings for window
void standartParam() {
	param.name = "LieLife";
	param.videoMode = VideoMode(800, 600);

	signals.closeNow.store(false, std::memory_order_seq_cst);
}

// Main function
int main()
{
	std::cout << "Start program\n\n";
	standartParam();
	
	std::cout << "Create window thread...\n";
	std::thread thr(threadWindow, &param, &signals);

	std::cout << "Thread created.\n";


	// Forsed window close
	//signals.closeNow.store(true, std::memory_order_seq_cst);
	
	thr.join();

	std::cout << "End work. Close programm.\n";
	return 0;
}