#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
using std::string;

#include <iostream>
#include <vector>
using std::vector;

struct Triangle {
	unsigned int VBO;
	unsigned int VAO;
	vector<float> vertices;
	string shaderPath;
	unsigned int fragShader;
	unsigned int shaderProgram;
};

struct Quad {
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	vector<float> vertices;
	string shaderPath;
	unsigned int fragShader;
	unsigned int shaderProgram;
};

struct AppState {

	GLFWwindow* mainWindow;
	int windowWidth;
	int windowHeight;

	unsigned int mainShaderProgram;
	unsigned int mainVertexShader;
	unsigned int mainFragmentShader;
	
	unsigned int EBO;

	vector<Triangle> triangles;
	vector<Quad> quads;
};

struct RGBA {
	float r;
	float g;
	float b;
	float a;
};

static AppState STATE{};

/** Read a text file given a specified path.
*
* @param path path to the file (relative path can be used).
* @return string a string containing the content of the text file.
*/
string ocaReadTextFile(std::string path);

/** Initialize a window, OpenGL context and default shaders.
*
* Requires a call to closeWindow() once the program terminates.
* 
* @param w window width.
* @param h window height.
* @param title window title.
*/
void initWindow(int w, int h, const char* title);

/** Load an array of vertices into memory, which will be interpreted as quads.
*
* @param quads a vector of quads.
*/
void loadQuads(vector<Quad>& quads);

/** Load an array of vertices into memory, which will be interpreted as triangles.
*
* @param quads a vector of triangles.
*/
void loadTriangles(vector<Triangle>& triangles);

// TODO Write documentation for this
bool windowShouldClose();
void beginDrawing();
void endDrawing();
void drawQuad();
void drawTriangle();
void clearBackground(RGBA c);
void closeWindow();

