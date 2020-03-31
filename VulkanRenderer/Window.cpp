#include "Window.hpp"

void Window::Init(const std::string& title)
{
	const std::string fullTitle = "VulkanRenderer - " + title;

	if (!glfwInit()) {
		ABORT_F("Failed to init glfw");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Disable it until we have a change size function

	m_monitorGLFW = glfwGetPrimaryMonitor();
	m_vidmodeGLFW = glfwGetVideoMode(m_monitorGLFW);

	m_windowGLFW = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, fullTitle.c_str(), nullptr, nullptr);
	if (m_windowGLFW == nullptr) {
		ABORT_F("Failed to create GLFW window");
	}

	glfwSetWindowUserPointer(m_windowGLFW, this);

	LOG_F(INFO, "[WINDOW] successfully created glfw window");
}

void Window::Fini()
{
	glfwDestroyWindow(m_windowGLFW);
	glfwTerminate();

	LOG_F(INFO, "[WINDOW] destroyed glfw window / context");
}

GLFWwindow* Window::getGLFWWindow() const
{
	return m_windowGLFW;
}

GLFWmonitor* Window::getGLFWMonitor() const
{
	return m_monitorGLFW;
}

bool Window::shouldCloseWindow() const
{
	return false;
}

std::vector<const char*> Window::getRequiredGLFWExtensions()
{
	uint32_t extensionCount;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

	std::vector<const char*> extensions;
	extensions.reserve(extensionCount);
	for (uint32_t i = 0; i < extensionCount; i++) {
		extensions.push_back(glfwExtensions[i]);
	}

	return extensions;
}
