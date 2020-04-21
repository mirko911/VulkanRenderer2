#include "Engine.hpp"


void Engine::Init()
{
	m_window.Init("Test");
	m_device.createInstance(m_window.getRequiredGLFWExtensions());
	m_device.createSurface(m_window.getGLFWWindow());
	m_device.createDevice();
	m_device.setWindow(m_window);

	m_game.Init(m_device, m_window);

	//renderer.Destroy();
	LOG_F(INFO, "[Engine] successfully initialized");
	m_gameState.setState(GameState::STATE::Running);
}

void Engine::Loop()
{
	timePoint m_t0;
	timePoint m_t1;
	uint32_t m_FPS = 0;
	float timeCounter = 0.0f;
	float timeDelta = 0.0f;
	m_t0 = m_t1 = std::chrono::high_resolution_clock::now();

	do {
		if (m_window.shouldCloseWindow() != 0) {
			m_gameState.setState(GameState::STATE::Stopped);
		}
		glfwPollEvents();

		m_FPS++;
		m_t1 = std::chrono::high_resolution_clock::now();
		timeDelta = static_cast<float>(std::chrono::duration_cast<ms>(m_t1 - m_t0).count());
		timeCounter += timeDelta;
		m_t0 = m_t1;

		m_game.Tick(timeDelta);
		m_game.Draw();

		if (timeCounter > 1000000000) {
			LOG_F(INFO, "FPS: %i", m_FPS);
			m_FPS = 0;
			timeCounter = 0.0f;
		}
	} while (m_gameState.isRunning());
}

void Engine::Fini()
{
	m_game.Fini();

	//m_device.destroyDevice();
	m_window.Fini();
	
}
