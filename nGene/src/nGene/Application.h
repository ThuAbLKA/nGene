#pragma once

#include "Core.h"
#include "Window.h"
#include <nGene\Events\ApplicationEvent.h>

namespace nGene {

	class NGN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};


	// to be defined in the client
	Application* CreateApp();
}

