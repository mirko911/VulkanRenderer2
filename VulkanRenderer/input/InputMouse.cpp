#include "InputMouse.hpp"

void InputMouse::Init(VulkanDevice& device)
{
	m_window = device.getWindow();

	glfwSetCursorPosCallback(m_window.getGLFWWindow(), [](GLFWwindow* window, const double xPos, const double yPos) {
		EventMouseMove eventMouseMove(xPos, yPos);
		HandlerEvent::instance().notify("mouseMove", eventMouseMove);
	});


	HandlerEvent::instance().registerEvent("mouseMove", [this](Event& event) {
		this->onMouseCallback(reinterpret_cast<EventMouseMove&>(event));
		});
}

void InputMouse::onMouseCallback(EventMouseMove& event)
{
//	LOG_F(INFO, "Mouse Callback: %f %f ", event.x, event.y);
}
