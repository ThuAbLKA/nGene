#include "ngpch.h"
#include "WinInput.h"

#include "nGene/Application.h"
#include <GLFW\glfw3.h>

namespace nGene {

	Input* Input::s_Instance = new WinInput();

	bool WinInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WinInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	/*float WinInput::GetMouseXImpl()
	{
		double x, y;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &x, &y);

		return x;
	}
	float WinInput::GetMouseYImpl()
	{
		double x, y;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &x, &y);

		return y;
	}*/

	std::pair<float, float> WinInput::GetMousePosImpl()
	{
		double x, y;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}
}