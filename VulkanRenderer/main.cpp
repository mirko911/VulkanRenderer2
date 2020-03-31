#include <loguru.hpp>

#include "Engine.hpp"
int main(int argc, char* argv[]) {

	// Optional, but useful to time-stamp the start of the log.
	// Will also detect verbosity level on command line as -v.
	loguru::init(argc, argv);

	LOG_F(INFO, "Init Vulkan Renderer");

	Engine engine;
	engine.Init();
	engine.Loop();
	engine.Fini();

	return 0;
}