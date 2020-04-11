#include "InputKeyboard.hpp"

void InputKeyboard::Init(VulkanDevice& device)
{
	m_window = device.getWindow();

	glfwSetKeyCallback(m_window.getGLFWWindow(), [](GLFWwindow* window,  int key,  int scan,  int action,  int mods) {
		EventKeyPress keyPressEvent(key, scan, action, mods);
		HandlerEvent::instance().notify("keyPress", keyPressEvent);
	//	this->onKeyCallback(window, key, scan, action, mods);
	});

	HandlerEvent::instance().registerEvent("keyPress", [this](Event& event){
		this->onKeyCallback(reinterpret_cast<EventKeyPress&>(event));
	});
}

void InputKeyboard::onKeyCallback(EventKeyPress& event)
{
	const char* key = glfwGetKeyName(event.key, event.scancode);
	LOG_F(INFO, "Keyboard Callback: %s ", key);
}
