#include "ngpch.h"
#include "WinWindow.h"

#include <nGene\Events\KeyEvent.h>
#include <nGene\Events\MouseEvent.h>

#include <glad\glad.h>

namespace nGene {
#define GLFW_USER_PTR(x) *(WindowData*)glfwGetWindowUserPointer(x)

	static bool s_GLFWInit = false;

	static void GLFWErrorCallback(int error, const char* desc) 
	{
		NGN_CORE_ERROR("GLFW Error:{0} - {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WinWindow(props);
	}

	WinWindow::WinWindow(const WindowProps& props)
	{
		Init(props);
	}

	WinWindow::~WinWindow()
	{
		Shutdown();
	}

	void WinWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NGN_CORE_INFO("Creating Win32 window with: {0} {1} {2}", props.Title, props.Height, props.Width);

		if (!s_GLFWInit)
		{
			int ok = glfwInit();
			NGN_CORE_ASSERT(ok, "GLFW init Failed!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInit = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// initialize glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NGN_CORE_ASSERT(status, "GLAD init Failed!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW windowPosition callback
		//glfwSetWindowPosCallback()

		// GLFW WindowSize callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = GLFW_USER_PTR(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		// GLFW WindowClose callback
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = GLFW_USER_PTR(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		// GLFW Key callback
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = GLFW_USER_PTR(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = GLFW_USER_PTR(window);
			KeyTypeEvent event(keycode);
			data.EventCallback(event);
		});

		// GLFW mouse callback
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = GLFW_USER_PTR(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		// GLFW MousePosition callback
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = GLFW_USER_PTR(window);
			MouseMoveEvent event(xpos, ypos);
			data.EventCallback(event);
		});

		// GLFW MouseScroll callback
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = GLFW_USER_PTR(window);
			MouseScrollEvent event(xoffset, yoffset);
			data.EventCallback(event);
		});
	}

	void WinWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WinWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}