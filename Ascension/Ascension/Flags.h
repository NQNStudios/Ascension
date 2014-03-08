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
			nextRoom = "";
		}

		static inline void setFlag(int r, int c, int val)
		{
			gFlags[r][c] = val;
		}

		static inline int getFlag(int r, int c)
		{
			return gFlags[r][c];
		}

		static inline void resetFlags()
		{
			for (int r = 0; r < kFlagRows; ++r)
			{
				for (int c = 0; c < kFlagColumns; ++c)
				{
					gFlags[r][c] = 0;
				}
			}
		}

		static const char* getNextRoom() { return nextRoom.c_str(); }
		static void setNextRoom(char* val) { nextRoom = std::string(val); }
	private:
		static std::vector<std::vector<int> > gFlags;

		static std::string nextRoom;
};