#include "InputMouse.hpp"

void InputMouse::Init(VulkanDevice& device)
{
	m_window = device.getWindow();
	glfwSetInputMode(m_window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(m_window.getGLFWWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	//glfwSetCursorPosCallback(m_window.getGLFWWindow(), [](GLFWwindow* window, const double xPos, const double yPos) {
	//	HandlerEvent::instance().notify("mouseMove", eventMouseMove);
	//});


//	HandlerEvent::instance().registerEvent("mouseMove", [this](Event& event) {
//		this->onMouseCallback(reinterpret_cast<EventMouseMove&>(event));
//		});
}

void InputMouse::onMouseCallback(EventMouseMove& event)
{
//	LOG_F(INFO, "Mouse Callback: %f %f ", event.x, event.y);
}

void InputMouse::update(const float ftimeDelta, GameRoot& gameRoot)
{
	double x; double y;
	glfwGetCursorPos(m_window.getGLFWWindow(), &x, &y);

	double speed_x = x - m_xPrev;
	double speed_y = y - m_yPrev;

	if (speed_x == 0 && speed_y == 0) {
		return;
	}

	m_xPrev = x;
	m_yPrev = y;

	m_eventMouseMove = EventMouseMove(x, y, speed_x, speed_y);
	HandlerEvent::instance().notify("mouseMove", m_eventMouseMove);

	setCursorCenter();
}

void InputMouse::setCursorCenter()
{
	glfwSetCursorPos(m_window.getGLFWWindow(),
		SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_xPrev = SCREEN_WIDTH * 0.5f;
	m_yPrev = SCREEN_HEIGHT * 0.5f;
}
