#include "Game.h"

#include <SDL.h>

#include "Surface.h"

const char* kTitle = "Ascension";
const char* kTitleCaps = "ASCENSION";

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
	ascii::Graphics graphics(kTitle);
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
	
}

void Game::Update(int deltaMS)
{
}

void Game::HandleInput(ascii::Input& input)
{
	
}

void Game::Draw(ascii::Graphics& graphics)
{
	graphics.clear();

	ascii::Surface* renderSurface = new ascii::Surface(ascii::Graphics::kBufferWidth, ascii::Graphics::kBufferHeight);

	renderSurface->drawBorder(' ', ascii::Color::Green, ascii::Color::White);
	renderSurface->blitString(kTitleCaps, ascii::Color::Black, ascii::Graphics::kBufferWidth / 2 - strlen(kTitleCaps) / 2, 0);

	ascii::Rectangle rect(5, 5, 30, 5);
	renderSurface->fillRect(rect, ' ', ascii::Color::Green, ascii::Color::White);
	renderSurface->blitStringMultiline("This is quite a long string. I think I'll have to wrap it to multiple lines to get it to display properly. Now, how do I do that?", ascii::Color::Black, rect);

	graphics.blitSurface(renderSurface, 0, 0);

	delete renderSurface;

	graphics.update();
}