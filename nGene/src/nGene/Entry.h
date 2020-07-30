#pragma once
#include <stdio.h>

#ifdef NGN_PLATFORM_WINDOWS

extern nGene::Application* nGene::CreateApp();

	int main(int argc, char** argv)
	{
		printf("Starting nGene");
		auto app = nGene::CreateApp();
		app->Run();
		delete app;
	}
#else
	#error nGene only supports windows!
#endif // NGN_PLATFORM_WINDOWS
