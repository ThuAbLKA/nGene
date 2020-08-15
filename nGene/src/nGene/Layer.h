#pragma once
#include <nGene\Events\Event.h>

namespace nGene {
	class NGN_API Layer
	{
	protected: 
		std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		// when the layer is added to the stack
		virtual void OnPush() {}
		// when the layer is removeed form the stack
		virtual void OnPop() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string GetName() const { return m_DebugName; }
	};
}

