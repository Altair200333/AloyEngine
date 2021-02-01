#pragma once
#include <deque>
#include <mutex>
#include <string>
#include <fstream>
#include <sstream>


#include "DebugGui.h"
#include "ImGuiEventSubscriber.h"

class Logger final: public ImGuiEventSubscriber
{
	inline static std::string loggerFileName = "log.txt";
	std::ofstream stream;

	std::deque<std::string> logs;
	std::mutex mtx;

	void logMsg(const std::string& msg)
	{
		mtx.lock();

		if (logs.size() > 20)
			logs.pop_front();
		logs.push_back(msg);

		if (stream)
			stream << msg << "\n";
		mtx.unlock();
	}
	Logger() : stream(std::ofstream(loggerFileName, std::ios::app))
	{
	}
public:
	static Logger& instance()
	{
		static Logger instance{};
		return instance;
	}

	static void log(const std::string& msg)
	{
		instance().logMsg(msg);
	}

	static std::string getLatestLogs()
	{
		std::stringstream out;
		auto& inst = instance();

		if (inst.logs.empty())
			return "";

		for (auto& msg : inst.logs)
		{
			out << msg << "\n";
		}
		return out.str();
	}	

	void onImGuiDraw() override
	{
		DebugGui::beginWindow("Logs");
		DebugGui::text(getLatestLogs());
		DebugGui::endWindow();
	}
};
