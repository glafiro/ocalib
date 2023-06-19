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

#define N_QUADS				1
#define VERTICES_IN_QUAD	12
#define INDICES_IN_QUAD		6

static vector<string> SHADERS{ "fragOrange.glsl", "fragYellow.glsl" };

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

int main() {

	initWindow(DEFAULT_W, DEFAULT_H, "Hello world");

	vector<Quad> quads;

	for (int i = 0; i < N_QUADS; i++) {
		Quad q;
		for (int j = 0; j < VERTICES_IN_QUAD; j++) {
			q.vertices.push_back(vertices[j]);
		}
		for (int j = 0; j < INDICES_IN_QUAD; j++) {
			q.indices.push_back(indices[j]);
		}
		q.shaderPath = "fragYellow.glsl";
		quads.push_back(q);
	}

	loadQuads(quads);

	RGBA c{ 0.1f, 0.3f, 0.7f, 1.0f };

	while (!windowShouldClose()) {

		beginDrawing();
		
		clearBackground(c);
		drawQuad();

		endDrawing();
	}

	closeWindow();
	return 0;
}
