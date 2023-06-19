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

#define N_TRIS				1
#define VERTICES_IN_TRI		9

static vector<string> SHADERS{ "fragOrange.glsl", "fragYellow.glsl" };

float quad_vertices[] = {
	0.8f,  0.2f, 0.0f,  // top right
	0.8f,  0.8f, 0.0f,  // bottom right
	0.0f,  0.8f, 0.0f,  // bottom left
	0.0f,  0.2f, 0.0f   // top left 
};

float tri_vertices[] = {
	-0.8f, -0.3f, 0.0f,
	-0.2f, -0.3f, 0.0f,
	-0.5f, 0.3f, 0.0f
};

int main() {

	initWindow(DEFAULT_W, DEFAULT_H, "Hello world");

	vector<Quad> quads;
	vector<Triangle> triangles;

	for (int i = 0; i < N_QUADS; i++) {
		Quad q;
		for (int j = 0; j < VERTICES_IN_QUAD; j++) {
			q.vertices.push_back(quad_vertices[j]);
		}
		q.shaderPath = SHADERS[0];
		quads.push_back(q);
	}

	for (int i = 0; i < N_TRIS; i++) {
		Triangle t;
		for (int j = 0; j < VERTICES_IN_TRI; j++) {
			t.vertices.push_back(tri_vertices[j]);
		}
		t.shaderPath = SHADERS[1];
		triangles.push_back(t);
	}

	loadQuads(quads);
	loadTriangles(triangles);

	RGBA c{ 0.1f, 0.3f, 0.7f, 1.0f };

	while (!windowShouldClose()) {

		beginDrawing();
		
		clearBackground(c);
		drawQuad();
		drawTriangle();

		endDrawing();
	}

	closeWindow();
	return 0;
}
