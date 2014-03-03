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
			if (row < 0 || col < 0)
			{
				return true;
			}
			return flags::getFlag(row, col) == val;
		}

	private:
		int row, col, val;
};