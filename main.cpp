#pragma once

// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "ocalib.h"

#define DEFAULT_W	640
#define DEFAULT_H	480

int main() {

	initWindow(DEFAULT_W, DEFAULT_H, "Hello world");

	RGBA c{ 0.9f, 0.3f, 0.0f, 1.0f };

	while (!windowShouldClose()) {

		beginDrawing();
		
		// RENDER HERE
		clearBackground(c);
		drawTriangle();

		endDrawing();
	}

	closeWindow();
	return 0;
}
