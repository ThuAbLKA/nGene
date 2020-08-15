#pragma once

#include "nGene/Layer.h"
#include <nGene\Events\MouseEvent.h>
#include <nGene\Events\KeyEvent.h>
#include <nGene\Events\ApplicationEvent.h>

namespace nGene {
	class NGN_API ImGuiLayer: public Layer
	{
	private:
		float m_Time = 0.0f;

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnPush();
		void OnPop();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressEvent(MouseButtonPressEvent& e);
		bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e);
		bool OnMouseMoveEvent(MouseMoveEvent& e);
		bool OnMouseScrollEvent(MouseScrollEvent& e);
		bool OnKeyPressEvent(KeyPressEvent& e);
		bool OnKeyReleaseEvent(KeyReleaseEvent& e);
		bool OnKeyTypeEvent(KeyTypeEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};
}

