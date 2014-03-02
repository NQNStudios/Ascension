#pragma once

#include <vector>

#include "Input.h"
#include "Graphics.h"

#include "Text.h"

class Screen
{
	public:
		void add(Text text);

		void update(int deltaMS);
		void handleInput(ascii::Input& input);
		void draw(ascii::Graphics& graphics);
	private:
		std::vector<Text> text;
};