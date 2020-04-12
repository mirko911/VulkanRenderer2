#pragma once
#include <string>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "loguru.hpp"

constexpr int SCREEN_WIDTH = 2560;
constexpr int SCREEN_HEIGHT = 1440;

class Window
{
private:
	//GLFW Window Object Pointer
	GLFWwindow* m_windowGLFW = nullptr;

	//GLFW Monitor Object Pointer
	GLFWmonitor* m_monitorGLFW = nullptr;

	//GLFW Videomode Pointer
	const GLFWvidmode* m_vidmodeGLFW = nullptr;
public:
	//Initializes GLFW Window context
	void Init(const std::string& title = "");

	//Destroys GLFW Window context
	void Fini();

	//Returns the GLFW Window Pointer
	GLFWwindow* getGLFWWindow() const;

	//Returns the GLFW Monitor Pointer
	GLFWmonitor* getGLFWMonitor() const;

	//Was the cross icon clicked?
	int shouldCloseWindow() const;

	//Returns a vector of required GLFW extensions
	std::vector<const char*> getRequiredGLFWExtensions();

	void getFrameBufferSize(uint32_t& width, uint32_t& height);
};

