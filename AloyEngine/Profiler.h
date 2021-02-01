#pragma once
#include <chrono>

class Profiler final: public ImGuiEventSubscriber
{

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	float frameTimems;
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
		instance().frameTimems = (instance().end - instance().start) / std::chrono::milliseconds(1);
	}

	static auto frameTime()
	{
		return instance().frameTimems;
	}
	
	static float currentFrameTime()
	{
		return (std::chrono::high_resolution_clock::now() - instance().start) / std::chrono::milliseconds(1);
	}

	void onImGuiDraw() override
	{
		DebugGui::beginWindow("Profiler");
		DebugGui::text("Frame time: " + std::to_string(frameTime()) + " ms");
		DebugGui::text("FPS       : " + std::to_string(1000.0f/frameTime()));
		DebugGui::endWindow();
	}
};
