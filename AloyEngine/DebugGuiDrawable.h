#pragma once

class DebugGuiDrawable
{
public:
	virtual ~DebugGuiDrawable() = default;
	
	virtual void onDebugGuiDraw() = 0;
};