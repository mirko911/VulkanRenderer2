#!/bin/bash

INCLUDE_LIBS="-I ../../Libs/glm -I ../../Libs/loguru -I ../../Libs/stb -I ../../Libs/tinyobjloader -I ../../Libs/glfw-3.3.2/include"
LIB_FILES="-L Libs/loguru/ -lloguru -lvulkan -lglfw3 -lpthread -lm -ldl -lX11 -lstdc++"
BUILD_OPTIONS="-std=c++17" #-Wall

echo "Compile Shaders"
cd VulkanRenderer/shaders/
./compile.sh

echo "Compiling C++ Code"

cd ../x64

g++ $BUILD_OPTIONS $INCLUDE_LIBS -c ../*.cpp
g++ $BUILD_OPTIONS $INCLUDE_LIBS -c ../demos/*.cpp
g++ $BUILD_OPTIONS $INCLUDE_LIBS -c ../handler/*.cpp
g++ $BUILD_OPTIONS $INCLUDE_LIBS -c ../input/*.cpp
g++ $BUILD_OPTIONS $INCLUDE_LIBS -c ../modules/*.cpp

cd ../../

echo "Linking"

gcc -o VulkanRenderer/vulkanrenderer_x64 VulkanRenderer/x64/*.o $LIB_FILES
