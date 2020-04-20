#pragma once
#include <loguru.hpp>

#include "VulkanDevice.hpp"
#include "Window.hpp"

#include "Renderer.hpp"
#include "GameRoot.hpp"
#include "GeoCube.hpp"
#include "GeoWavefront.hpp"
#include "GeoPlane.hpp"

#include "input/InputKeyboard.hpp"
#include "input/InputMouse.hpp"

#include "Handler/HandlerEvent.hpp"

#include "demos/DemoBlueUniverse.hpp"
#include "demos/DemoBlue.hpp"
#include "demos/DemoMaterial.hpp"

class Game
{
private:
	VulkanDevice m_device;
	Window m_window;
	Renderer m_renderer;
	GameRoot m_gameRoot;
	DemoMaterial m_activeDemo;
public:
	void Init(VulkanDevice& device, Window& window);
	void Tick();
	void Draw();
	void Fini();
	void Test(EventKeyPress& event) { LOG_F(WARNING, "GAME TEST CALLBACK"); };
};

