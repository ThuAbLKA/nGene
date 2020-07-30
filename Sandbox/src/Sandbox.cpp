#include "nGene.h"

class Sandbox : public nGene::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

nGene::Application* nGene::CreateApp()
{
	return new Sandbox();
}