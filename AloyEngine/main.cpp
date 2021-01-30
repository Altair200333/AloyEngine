#include <iostream>
#include "Engine.h"
#include "AloyDemoApp.h"

int main()
{
	Engine::init("Aloy engine");
	AloyDemoApp app;
	Engine::run();

	return 0;
}
