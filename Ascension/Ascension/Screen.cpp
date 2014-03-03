#include "Screen.h"

const int kRevealMS = 30;

Screen::Screen()
	: revealedChars(0), elapsedMS(0)
{
}

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
	elapsedMS += deltaMS;

	if (elapsedMS >= kRevealMS)
	{
		elapsedMS -= kRevealMS;
		revealedChars++;
	}
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
					if (idx >= actions.size()) return;

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

	int charsLeft = revealedChars;
	for (std::vector<Text>::iterator it = text.begin(); it != text.end(); ++it)
	{
		if (it->isVisible())
		{
			std::string tempstr(it->getText());

			std::string cutstr(tempstr.substr(0, charsLeft));
			charsLeft -= cutstr.size();

			graphics.blitStringMultiline(cutstr.c_str(), ascii::Color::Green, destination);

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
			if (charsLeft)
			{
				graphics.setCharacterColor(destination.x, destination.y, ascii::Color::Green);
				graphics.setCharacter(destination.x, destination.y, num);
				--charsLeft;
			}
			if (charsLeft)
			{
				graphics.setCharacterColor(destination.x + 1, destination.y, ascii::Color::Green);
				graphics.setCharacter(destination.x + 1, destination.y, '-');
				charsLeft--;
			}

			destination.x += 2;

			std::string tempstr(it->getText());
			std::string cutstr = tempstr.substr(0, charsLeft);

			graphics.blitStringMultiline(cutstr.c_str(), ascii::Color::Green, destination);

			charsLeft -= cutstr.size();

			++num;

			destination.x -= 2;
			destination.y += graphics.measureStringMultiline(it->getText(), destination);
		}
	}
}

void Screen::resetAnim()
{
	revealedChars = 0;
	elapsedMS = 0;
}