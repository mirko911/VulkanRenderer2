#include "Engine.hpp"


void Engine::Init()
{
	m_window.Init("Test");
	m_device.createInstance(m_window.getRequiredGLFWExtensions());
	m_device.createSurface(m_window.getGLFWWindow());

	LOG_F(INFO, "[Engine] successfully initialized");
}

void Engine::Loop()
{
}

void Engine::Fini()
{
	m_device.destroyDevice();
	m_window.Fini();
	
}
