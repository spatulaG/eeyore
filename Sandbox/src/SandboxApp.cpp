#include "Eeyore.h"

class ExampleLayer : public Eeyore::Layer {
public:
	ExampleLayer()
		: Layer("Example") // first: core layer, then example layer
	{
	}

	void OnUpdate() override
	{
		ER_INFO("ExampleLayer::Update");
	}

	void OnEvent(Eeyore::Event& event) override
	{
		ER_TRACE("{0}", event);
	}
};

class Sandbox : public Eeyore::Application 
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Eeyore::ImGuiLayer());
	}
	~Sandbox() {
	}
};

Eeyore::Application* Eeyore::CreateApplication() {
	return new Sandbox();
}