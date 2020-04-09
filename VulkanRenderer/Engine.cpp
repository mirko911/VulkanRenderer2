#include "Engine.hpp"


void Engine::Init()
{
	m_window.Init("Test");
	m_device.createInstance(m_window.getRequiredGLFWExtensions());
	m_device.createSurface(m_window.getGLFWWindow());
	m_device.createDevice();


	m_game.Init(m_device, m_window);

	//renderer.Destroy();
	LOG_F(INFO, "[Engine] successfully initialized");
	m_gameState.setState(GameState::STATE::Running);
}

void Engine::Loop()
{
	while (m_gameState.isRunning()) {
		if (m_window.shouldCloseWindow() != 0) {
			m_gameState.setState(GameState::STATE::Stopped);
		}
		glfwPollEvents();

		m_game.Tick();
		m_game.Draw();
	}
}

void Engine::Fini()
{
	m_game.Fini();

	//m_device.destroyDevice();
	m_window.Fini();
	
}
