#pragma once

#include "Flags.h"

struct FlagSet
{
	public:
		FlagSet(int row, int col, int val)
			: row(row), col(col), val(val)
		{
		}

		void operator()()
		{
			if (row >= 0 && col >= 0)
				flags::setFlag(row, col, val);
		}
	private:
		int row, col, val;
};