#pragma once
#include "core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Eeyore {
	class EEYORE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	//to be defined in client
	Application* CreateApplication();
}
