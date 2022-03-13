#include "erpch.h" 
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "log.h"

namespace Eeyore {
	Application::Application() {}
	Application::~Application() {}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
			ER_TRACE(e);
		if (e.IsInCategory(EventCategoryInput))
			ER_TRACE(e);

		while(true);
	}

}