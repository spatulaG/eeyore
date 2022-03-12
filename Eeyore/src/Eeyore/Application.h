#pragma once
#include "core.h"
namespace Eeyore {
	class EEYORE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	//to be defined in client
	Application* CreateApplication();
}
