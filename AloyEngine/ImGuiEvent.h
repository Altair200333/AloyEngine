#pragma once
#include "Event.h"
#include "ImGuiEventSubscriber.h"

class ImGuiEvent final : public Event<ImGuiEventSubscriber>
{
public:
	void handle(ImGuiEventSubscriber* var) const override
	{
		var->onImGuiDraw();
	}
};
