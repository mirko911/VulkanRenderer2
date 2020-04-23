#!/bin/bash

glslc main.vert -o main.vert.spv
glslc main.frag -o main.frag.spv
glslc skybox.vert -o skybox.vert.spv
glslc skybox.frag -o skybox.frag.spv
glslc depth.vert -o depth.vert.spv
glslc depth.frag -o depth.frag.spv
