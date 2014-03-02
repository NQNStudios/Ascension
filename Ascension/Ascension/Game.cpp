#include "Game.h"

#include <SDL.h>

#include "Surface.h"
#include "FlagCondition.h"

const char* kWindowTitle = "...";
const char* kTitle = "ASCENSION";

const int kFPS = 60;
const int kMaxFrameTime = 5 * 1000 / 60;

Game::Game()
	: mRunning(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	LoadContent();
}

Game::~Game()
{
	SDL_Quit();
}

void Game::Run()
{
	ascii::Graphics graphics(kWindowTitle);
	ascii::Input input;

	mRunning = true;

	int lastUpdateTime = SDL_GetTicks();

	while (mRunning)
	{
		const int initialTime = SDL_GetTicks();

		input.beginNewFrame();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					Quit();
					return;
				case SDL_KEYDOWN:
					input.keyDownEvent(event);
					break;
				case SDL_KEYUP:
					input.keyUpEvent(event);
					break;
			}
		}

		HandleInput(input);

		const int currentTime = SDL_GetTicks();
		const int elapsedTime = currentTime - lastUpdateTime;

		Update(std::min(elapsedTime, kMaxFrameTime));
		lastUpdateTime = currentTime;

		Draw(graphics);

		const int msPerFrame = 1000 / kFPS;
		const int elapsedTimeMS = SDL_GetTicks() - initialTime;

		if (elapsedTimeMS < msPerFrame)
			SDL_Delay(msPerFrame - elapsedTimeMS);
	}
}

void Game::Quit()
{
	mRunning = false;
}

void Game::LoadContent()
{
	flags::init();

	Screen* scr = new Screen();

	Text txt("This text should display", FlagCondition(0, 0, 0));

	scr->add(txt);

	txt = Text("This text should not display", FlagCondition(0, 0, 1));

	scr->add(txt);

	txt = Text("This text should display 2 lines down", FlagCondition(1, 0, 0));

	scr->add(txt);

	mScreen.reset(scr);
}

void Game::Update(int deltaMS)
{
	mScreen->update(deltaMS);
}

void Game::HandleInput(ascii::Input& input)
{
	mScreen->handleInput(input);
}

void Game::Draw(ascii::Graphics& graphics)
{
	graphics.clear();

	graphics.drawBorder(' ', ascii::Color::Green, ascii::Color::White);
	graphics.blitString(kTitle, ascii::Color::Black, ascii::Graphics::kBufferWidth / 2 - strlen(kTitle) / 2, 0);

	mScreen->draw(graphics);

	graphics.update();
}