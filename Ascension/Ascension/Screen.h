#pragma once

#include <vector>

#include "Input.h"
#include "Graphics.h"

#include "Text.h"
#include "Action.h"

class Screen
{
	public:
		Screen();

		void add(Text text);
		void addAction(Action action);

		void update(int deltaMS);
		void handleInput(ascii::Input& input);
		void draw(ascii::Graphics& graphics);

		void resetAnim();
		void skipAnim();
	private:
		std::vector<Text> text;
		std::vector<Action> actions;

		int revealedChars;
		int elapsedMS;
		int totalMS;
		bool takeInput;
};