#include "ngpch.h"
#include "Application.h"
#include "nGene/./Input.h"

#include <glad/glad.h>


namespace nGene {

#define BIND_EVT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		NGN_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
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

			// update all layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			auto [x, y] = Input::GetMousePos();
			NGN_CORE_TRACE("Mouse Pos: {0}, {1}", x, y);

			auto pressed = Input::IsMouseButtonPressed(1);
			NGN_CORE_TRACE("Mouse 1 pressed: {0}", pressed);

			m_Window->OnUpdate();
		}
	}

	// Layers
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnPush();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnPush();
	}
}