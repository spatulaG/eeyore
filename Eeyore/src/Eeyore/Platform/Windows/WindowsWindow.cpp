#include "erpch.h"
#include "WindowsWindow.h"

#include "Eeyore/Events/KeyEvent.h"
#include "Eeyore/Events/MouseEvent.h"
#include "Eeyore/Events/ApplicationEvent.h"

#include "glad/glad.h"

namespace Eeyore {

	static bool s_GLFWInitialized = false;// we only want to initialize once, but tehre might be multiple windows

	static void GLFWErrorCallback(int error, const char* description) 
	{
		ER_CORE_ERROR("GLFW Error({0}):{1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() 
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ER_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			ER_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ER_CORE_ASSERT(status, "Failed to initialize glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) // set what happens when triggered this event
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //void* is a pointer that has no associated data type with it, can hold address of any type and can be typecasted to any type
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);// create a windows event
			data.EventCallback(event);// dispatch event

		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //void* is a pointer that has no associated data type with it, can hold address of any type and can be typecasted to any type

			WindowCloseEvent event;// create a windows event
			data.EventCallback(event);// dispatch event
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //void* is a pointer that has no associated data type with it, can hold address of any type and can be typecasted to any type

			switch (action) {
				case GLFW_PRESS:// cardi don't need more press!!!
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}			
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //void* is a pointer that has no associated data type with it, can hold address of any type and can be typecasted to any type

			switch (action) {
				case GLFW_PRESS:// cardi don't need more press!!!
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //void* is a pointer that has no associated data type with it, can hold address of any type and can be typecasted to any type
			
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //void* is a pointer that has no associated data type with it, can hold address of any type and can be typecasted to any type

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown() {
		//GLFW terminate
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);// wait for 1 frame to render
		else
			glfwSwapInterval(1);
	
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}