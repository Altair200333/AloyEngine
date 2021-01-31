#pragma once
#include <vector>

class ImGuiSeedGenerator final
{
	static constexpr int seedSize = 1000;
	std::vector<int> seeds;
	int currentSeed = 0;

	ImGuiSeedGenerator()
	{
		for (int i = 0; i < seedSize; ++i)
		{
			seeds.push_back(i);
		}
	}

	static ImGuiSeedGenerator& instance()
	{
		static ImGuiSeedGenerator generator;
		return generator;
	}

public:

	static int nextSeed()
	{
		if (instance().currentSeed >= seedSize)
			instance().currentSeed = 0;
		return instance().seeds[instance().currentSeed++];
	}
	static void reset()
	{
		instance().currentSeed = 0;
	}
};
