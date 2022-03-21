#pragma once

#include "Eeyore/Core.h"
#include "Eeyore/Events/Event.h"


namespace Eeyore {
	class EEYORE_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		
		inline const std::string& GetName() const { return m_DebugName; }
	protected: //accessible within the same class and within the derived/sub/child class
		std::string m_DebugName;
	};
}