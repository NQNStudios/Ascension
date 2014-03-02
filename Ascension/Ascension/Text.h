#pragma once

#include <string>

#include "FlagCondition.h"

struct Text
{
	public:
		Text(const char* text, FlagCondition condition)
			: text(text), condition(condition)
		{
		}

		const char* getText() { return text.c_str(); }
		bool isVisible() { return condition(); }
	private:
		std::string text;
		FlagCondition condition;
};