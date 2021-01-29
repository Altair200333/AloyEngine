#include <iostream>
#include "Engine.h"
#include "AloyTestApp.h"

int main()
{
	Engine::init("Aloy engine");
	AloyTestApp app;
	Engine::run();

	return 0;
}
