#include "ngpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace nGene {

#define BIND_EVT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		// dispatching window close event to a specific function
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVT_FN(Application::OnWindowClose));

		NGN_CORE_TRACE("Event triggered: {0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		NGN_CORE_WARN("Engine shutting down...");
		m_IsRunning = false;
		NGN_CORE_INFO("Engine shutting success");
		return true;
	}

	void Application::Run() 
	{
		// intinitely running application 
		while (m_IsRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}