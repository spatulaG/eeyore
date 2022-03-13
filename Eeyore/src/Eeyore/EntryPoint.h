#pragma once
#ifdef ER_PLATFORM_WINDOWS
extern Eeyore::Application* Eeyore::CreateApplication();

int main(int argc, char**argv) {
	Eeyore::Log::Init();
	ER_CORE_WARN("Initialized Log!");
	int a=5;
	ER_INFO("Hello! Var={0}", a);

	auto app = Eeyore::CreateApplication();
	app->Run();
	delete app;
}
#endif