#pragma once
#include <GLFW/glfw3.h>

namespace CursorMode
{
	using Cursor = int;
	enum : Cursor
	{
		CursorNormal = GLFW_CURSOR_NORMAL,
		CursorDisabled = GLFW_CURSOR_DISABLED,
		CursorHidden = GLFW_CURSOR_HIDDEN
	};
}
