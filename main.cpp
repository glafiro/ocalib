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

vector<vector<float>> vertices = {
	{
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	},
	{
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	}
};

int main() {

	initWindow(DEFAULT_W, DEFAULT_H, "Hello world");
	vector<Triangle> triangles;
	loadTriangles(vertices);

	RGBA c{ 0.1f, 0.3f, 0.7f, 1.0f };

	while (!windowShouldClose()) {

		beginDrawing();
		
		clearBackground(c);
		drawTriangle();

		endDrawing();
	}

	closeWindow();
	return 0;
}
