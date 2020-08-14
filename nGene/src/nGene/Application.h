#pragma once

#include "Core.h"
#include "Window.h"

namespace nGene {

	class NGN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};


	// to be defined in the client
	Application* CreateApp();
}

