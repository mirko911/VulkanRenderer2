#include "Engine.hpp"


void Engine::Init()
{
	m_window.Init("Test");
	m_device.createInstance(m_window.getRequiredGLFWExtensions());
	m_device.createSurface(m_window.getGLFWWindow());
	m_device.createDevice();


	m_game.Init();

	LOG_F(INFO, "[Engine] successfully initialized");
	m_gameState.setState(GameState::STATE::Running);
}

void Engine::Loop()
{
	while (m_gameState.isRunning()) {
		m_game.Tick();
		m_game.Draw();
	}
}

void Engine::Fini()
{
	m_game.Fini();

	m_device.destroyDevice();
	m_window.Fini();
	
}