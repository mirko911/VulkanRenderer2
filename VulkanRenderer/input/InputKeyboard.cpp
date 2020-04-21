#include "InputKeyboard.hpp"

void InputKeyboard::Init(VulkanDevice& device)
{
	m_window = device.getWindow();

	glfwSetKeyCallback(m_window.getGLFWWindow(), [](GLFWwindow* window,  int key,  int scan,  int action,  int mods) {
		EventKeyPress keyPressEvent(key, scan, action, mods);
		HandlerEvent::instance().notify("keyPress", keyPressEvent);
	//	this->onKeyCallback(window, key, scan, action, mods);
	});

//	HandlerEvent::instance().registerEvent("keyPress", [this](Event& event){
//		this->onKeyCallback(reinterpret_cast<EventKeyPress&>(event));
//	});
}

void InputKeyboard::onKeyCallback(EventKeyPress& event)
{
//	const char* key = glfwGetKeyName(event.key, event.scancode);
	//LOG_F(INFO, "Keyboard Callback: %s ", key);
}

void InputKeyboard::update(const float fTimeDelta, GameRoot& gameRoot)
{
	uint32_t action = 0x0;

	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		action |= ActionType::FORWARD;
	}
	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		action |= ActionType::LEFT;
	}
	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		action |= ActionType::BACKWARD;
	}
	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		action |= ActionType::RIGHT;
	}
	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
		action |= ActionType::DOWN;
	}
	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_E) == GLFW_PRESS) {
		action |= ActionType::UP;
	}
	if (glfwGetKey(m_window.getGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		action |= ActionType::SPACE;
	}

	m_eventAction = EventAction(action);

	if(action != 0x0)
		HandlerEvent::instance().notify("action", m_eventAction);
}

