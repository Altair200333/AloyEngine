#pragma once
#include <chrono>

class Profiler final
{

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
public:
	static Profiler& instance()
	{
		static Profiler instance;
		return instance;
	}
	static void startFrame()
	{
		instance().start = std::chrono::high_resolution_clock::now();
	}

	static void endFrame()
	{
		instance().end = std::chrono::high_resolution_clock::now();
	}

	static float frameTime()
	{
		return (instance().end - instance().start) / std::chrono::milliseconds(1);
	}
	
	static float currentFrameTime()
	{
		return (std::chrono::high_resolution_clock::now() - instance().start) / std::chrono::milliseconds(1);
	}
};
