#include <string>

#include "Entry.h"

using namespace sf;


//////////////////////////////////////////////////////////////////////////////
///// Constructions //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Entry::Entry(RenderWindow* win, Size size, Position position,
	Color textColor)
	:Label(win, size, position, "", textColor)
{
	//bind(KEY_PRESS, [](EventParam<Entry> param) {
	//	if (param.isFocus) {
	//		std::string tex = param.widget.getText();
	//		tex += param.sumbol;
	//		param.widget.setText(tex);
	//	}
	//	});
}



//////////////////////////////////////////////////////////////////////////////
///// Functions //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Entry::draw()
{
	window->draw(this->textObj);
	window->draw(this->sprite);
}



//////////////////////////////////////////////////////////////////////////////
///// Functions for bind and run binded functions ////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void Entry::bind(EventType type, void(*fun)(EventParam<Entry>param))
{
	binded.addFunct(type, fun);
}

void Entry::startUpdate(sf::Event event)
{
	Label::startUpdate(event);
	runFunctions(event, EventParam<Entry>(*this, event), binded);
}

