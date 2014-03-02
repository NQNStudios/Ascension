#include "Screen.h"

void Screen::add(Text text)
{
	this->text.push_back(text);
}

void Screen::update(int deltaMS)
{
}

void Screen::handleInput(ascii::Input& input)
{
}

void Screen::draw(ascii::Graphics& graphics)
{
	ascii::Rectangle destination(3, 2, 74, 21);

	for (std::vector<Text>::iterator it = text.begin(); it != text.end(); ++it)
	{
		if (it->isVisible())
		{
			graphics.blitStringMultiline(it->getText(), ascii::Color::Green, destination);

			destination.y += graphics.measureStringMultiline(it->getText(), destination);

			destination.y++;
		}
	}
}