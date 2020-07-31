#pragma once
#include <stdio.h>

#ifdef NGN_PLATFORM_WINDOWS

extern nGene::Application* nGene::CreateApp();

	int main(int argc, char** argv)
	{
		nGene::Log::Init("sandbox");
		NGN_CORE_TRACE("nGene starting...");

		auto app = nGene::CreateApp();
		NGN_CLIENT_INFO("Sandbox starting...");
		app->Run();
		delete app;
	}
#else
	#error nGene only supports windows!
#endif // NGN_PLATFORM_WINDOWS
