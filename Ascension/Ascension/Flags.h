#pragma once

#include <vector>

const int kFlagRows = 50;
const int kFlagColumns = 50;

class flags
{
	public:
		static inline void init()
		{
			gFlags = std::vector<std::vector<int> >(kFlagRows, std::vector<int>(kFlagColumns, 0));
		}

		static inline void setFlag(int r, int c, int val)
		{
			gFlags[r][c] = val;
		}

		static inline int getFlag(int r, int c)
		{
			return gFlags[r][c];
		}
	private:
		static std::vector<std::vector<int> > gFlags;
};