#pragma once
#include "ComponentManager.h"

class Object final
{
	ComponentManager componentManager;
public:
	
	Object* parent = nullptr;

	std::vector<std::shared_ptr<Object>> children;
	
	template<typename T>
	void addComponent(std::shared_ptr<T> component)
	{
		componentManager.addComponent(component, this);
	}
	
	template<typename T>
	[[nodiscard]] auto getComponent() const
	{
		return componentManager.getComponent<T>();
	}

	void addChild(const std::shared_ptr<Object>& child)
	{
		children.push_back(child);
		child->parent = this;
	}
	
	void removeChild(const std::shared_ptr<Object>& child)
	{
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
		child->parent = nullptr;
	}

	auto componentsBegin()
	{
		return componentManager.begin();
	}
	auto componentsEnd()
	{
		return componentManager.end();
	}
};
