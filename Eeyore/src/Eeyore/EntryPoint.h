#pragma once
#ifdef ER_PLATFORM_WINDOWS
extern Eeyore::Application* Eeyore::CreateApplication();

int main(int argc, char**argv) {
	auto app = Eeyore::CreateApplication();
	app->Run();
	delete app;
}
#endif