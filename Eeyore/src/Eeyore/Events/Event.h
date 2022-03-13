#pragma once
#include "Eeyore/Core.h"

namespace Eeyore {
	//blocking, will buffer events in event bus in the future
	enum class EventType {
		//0 for none, then each assigned with a number
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,		   //ApplicationEvents.h
		AppTick, AppUpdate, AppRender,												   //ApplicationEvents.h
		KeyPressed, KeyReleased,  													   //KeyEvent.h
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled			   //MouseEvents.h
	};
	enum EventCategory {
		//mask bit field to filter event
		None = 0,
		EventCategoryApplication   = BIT(0),
		EventCategoryInput		   = BIT(1),
		EventCategoryKeyboard	   = BIT(2),
		EventCategoryMouse		   = BIT(3),
		EventCategoryMouseButton   = BIT(4)
	};

//##type return: EventType::KeyPressed
// 
//#type return "KeyPressed"
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::##type;}\
								virtual	EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}				

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;} // return: bit(n)

	class EEYORE_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)// inline: for optimization, only expand when called
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool n_Handled = false;
	};

	class EventDispatcher 
	{ 
		// dispatch event base on type
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public: 
			EventDispatcher(Event& event)
				: m_Event(event) 
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// Check what eventtype are we trying to dispatch, if it matches the template
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
			Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}