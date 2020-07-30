#pragma once

#include "Core.h"

namespace nGene {

	class NGN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// to be defined in the client
	Application* CreateApp();
}

