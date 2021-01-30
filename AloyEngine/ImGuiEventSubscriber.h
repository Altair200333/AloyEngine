#pragma once
#include "EventSubscriber.h"

class ImGuiEventSubscriber : virtual public EventSubscriber
{
public:
	virtual ~ImGuiEventSubscriber() = default;
	virtual void onImGuiDraw() = 0;
};
