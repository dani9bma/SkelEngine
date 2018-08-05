/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assun��o
 * @Github https://github.com/dani9bma
 */

#include "Window.h"
#include "..\Utils\Input.h"

namespace Skel
{
	void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	Window::Window(int width, int height, const char* title)
		: m_width(width), m_height(height), m_title(title)
	{
#if defined(_WIN32)
		HWND hWin = GetForegroundWindow();
		ShowWindow(hWin, SW_HIDE);
#endif
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_window)
		{
			SK_LOG(Error, System, "Failed to Initialize Window");
			glfwTerminate();
			return;
		}
		glViewport(0.5, 0.0, m_width, m_height);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		glfwSetCursorPosCallback(m_window, mouse_callback);
		glfwSetScrollCallback(m_window, mouse_wheel_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwMakeContextCurrent(m_window);
		if (glewInit() != GLEW_OK)
		{
			SK_LOG(Error, Rendering, "Failed to Initialize GLEW");
			return;
		}

		SK_LOGP(Warning, System, "GLEW Initialized! Version: %s", glewGetString(GLEW_VERSION));
		SK_LOGP(Warning, System, "OpenGL Initialized! Version: %s", glGetString(GL_VERSION));
		
		Input::ShowMouseCursor(this, true);
		glfwSetWindowUserPointer(m_window, this);
		glfwSwapInterval(0); //V-Sync
		m_lastTime = glfwGetTime();
		m_fps = 0;

		//		Input* input = Input(this);
		//	m_input = input;
		//delete[] input;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::update()
	{


		// Measure speed
		double currentTime = glfwGetTime();
		m_fps++;
		if (currentTime - m_lastTime >= 1.0) // If last prinf() was more than 1 sec ago
		{
			SK_LOGP(Warning, System, "%d FPS", m_fps);
			m_fps = 0;
			m_lastTime += 1.0;
		}

		if (Input::isKeyPressed(this, KEY_K))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (Input::isKeyPressed(this, KEY_O))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (Input::isKeyPressed(this, KEY_ESCAPE))
			this->close();


		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	int Window::closed()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(m_window, 1);
	}

	void Window::setMousePosition(double x, double y)
	{
		m_x = x;
		m_y = y;
		glfwSetCursorPos(this->getGLFWwindow(), x, y);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0.5, 0.0, width, height);
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		auto* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_x = xpos;
		win->m_y = ypos;
	}

	void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Input::SetMouseScrollOffset(yoffset);
		glfwSetWindowShouldClose(window, 1);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{

	}
}