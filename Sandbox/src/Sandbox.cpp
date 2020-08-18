#include "nGene.h"

class TestLayer : public nGene::Layer
{
public:
	TestLayer(): Layer("Test")
	{

	}

	void OnUpdate() override
	{
		if (nGene::Input::IsKeyPressed(NGN_KEY_TAB))
			NGN_CORE_TRACE("TAB is pressed");
	}

	void OnEvent(nGene::Event& event) override
	{
		NGN_CLIENT_INFO("TestLayer::EVENT- {0}", event.ToString());
	}
};

class Sandbox : public nGene::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
		PushOverlay(new nGene::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

nGene::Application* nGene::CreateApp()
{
	return new Sandbox();
}