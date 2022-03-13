#include "erpch.h" 
#include "Eeyore.h"

class Sandbox : public Eeyore::Application 
{
public:
	Sandbox() {
	}
	~Sandbox() {
	}

};

Eeyore::Application* Eeyore::CreateApplication() {
	return new Sandbox();
}