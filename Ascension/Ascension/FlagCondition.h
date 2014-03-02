#pragma once

#include "Flags.h"

struct FlagCondition
{
	public:
		FlagCondition(int row, int col, int val)
			: row(row), col(col), val(val)
		{
		}

		bool operator()()
		{
			return flags::getFlag(row, col) == val;
		}

	private:
		int row, col, val;
};