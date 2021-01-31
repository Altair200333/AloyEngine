#pragma once
#include <vector>

//when rendering multiple fields with same names ImGui wants unique seeds
//so this class is just handy tool for that

class ImGuiSeedGenerator final
{
	int currentSeed = 0;
	
	static ImGuiSeedGenerator& instance()
	{
		static ImGuiSeedGenerator generator;
		return generator;
	}

public:

	static int nextSeed()
	{
		return instance().currentSeed++;
	}
	static void reset()
	{
		instance().currentSeed = 0;
	}
};
