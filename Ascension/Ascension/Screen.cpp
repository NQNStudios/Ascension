#include "Screen.h"

void Screen::add(Text text)
{
	this->text.push_back(text);
}

void Screen::addAction(Action action)
{
	this->actions.push_back(action);
}

void Screen::update(int deltaMS)
{
}

void Screen::handleInput(ascii::Input& input)
{
	for (int i = (int)SDLK_1; i < (int)SDLK_9; ++i)
	{
		if (input.wasKeyPressed((SDL_Keycode)i))
		{
			int n = i - (int)SDLK_0;

			Action act;
			int idx = 0;
			for (int j = 0; j < n; ++j)
			{
				do
				{
					act = actions[idx];
					++idx;
				} while (!act.isEnabled());
			}

			act();
		}
	}
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

	destination.x += 2;

	char num = 49;
	for (std::vector<Action>::iterator it = actions.begin(); it != actions.end(); ++it)
	{
		if (it->isEnabled())
		{
			graphics.setCharacterColor(destination.x, destination.y, ascii::Color::Green);
			graphics.setCharacter(destination.x, destination.y, num);
			graphics.setCharacterColor(destination.x + 1, destination.y, ascii::Color::Green);
			graphics.setCharacter(destination.x + 1, destination.y, '-');

			destination.x += 2;

			graphics.blitStringMultiline(it->getText(), ascii::Color::Green, destination);

			++num;

			destination.x -= 2;
			destination.y += graphics.measureStringMultiline(it->getText(), destination);
		}
	}
}