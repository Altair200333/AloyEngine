#pragma once
#include <array>
#include <string>
#include <utility>

class WindowProps final
{
public:
	std::array<int, 2> position { 0, 0 };
	std::string name{};
	int width{};
	int height{};
	WindowProps(std::string windowName = "Untitled", size_t w = 1600, size_t h = 900) : name(std::move(windowName)), width(w), height(h)
	{}
};
