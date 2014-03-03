#pragma once

#include "FlagCondition.h"
#include "FlagSet.h"
#include "Flags.h"

struct Action
{
	public:
		Action(const char* text, FlagCondition condition, FlagSet flagSet, char* nextRoom)
			: text(text), condition(condition), flagSet(flagSet), nextRoom(nextRoom)
		{
		}

		Action()
			: condition(-1, -1, 0), flagSet(-1, -1, 0)
		{
		}

		bool isEnabled() { return condition(); }
		void operator()()
		{
			flagSet();
			flags::setNextRoom(nextRoom);
		}

		const char* getText()
		{
			return text;
		}
	private:
		const char* text;
		FlagCondition condition;
		FlagSet flagSet;
		char* nextRoom;
};