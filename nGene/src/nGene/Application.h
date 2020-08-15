#pragma once

#include "Core.h"
#include "Window.h"
#include <nGene\Events\ApplicationEvent.h>
#include <nGene\LayerStack.h>


namespace nGene {

	class NGN_API Application
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;

	public:
		Application();
		virtual ~Application();
		void Run();
		
		void OnEvent(Event& e);

		// layers 
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() {
			return *m_Window;
		};

	};


	// to be defined in the client
	Application* CreateApp();
}

