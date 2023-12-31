
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "ocalib.h"

using std::string;

const static unsigned int QUAD_INDICES[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

template<typename T>
void initializeShaders(unsigned int &vertexShader, vector<T> &shapes) {

	// 1) Create shader string
	string mainVertexShaderFile = ocaReadTextFile("vert.glsl");
	const char* mainVertexShaderSource = mainVertexShaderFile.c_str();

	//2) Create shader ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 3) Compile shader
	glShaderSource(vertexShader, 1, &mainVertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 4) Check if successful

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Vertex shader compiled successfully\n";
	}

	// Load and read fragment shaders for each mesh:

	for (auto& t : shapes) {
		// 1) Create shader string
		string fragShaderFile = ocaReadTextFile(t.shaderPath);
		const char* fragShaderSource = fragShaderFile.c_str();

		//2) Create shader ID
		t.fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		
		// 3) Compile shader
		glShaderSource(t.fragShader, 1, &fragShaderSource, NULL);
		glCompileShader(t.fragShader);

		// 4) Check if successful
		glGetShaderiv(t.fragShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(t.fragShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else {
			std::cout << "Fragment shader compiled successfully\n";
		}

		// Create shader program
		t.shaderProgram = glCreateProgram();

		glAttachShader(t.shaderProgram, vertexShader);
		glAttachShader(t.shaderProgram, t.fragShader);
		glLinkProgram(t.shaderProgram);

		// Check if successful
		glGetProgramiv(t.shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(t.shaderProgram, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else {
			std::cout << "Shader program created successfully\n";
		}

		glDeleteShader(t.fragShader);
	}

	glDeleteShader(vertexShader);
}

void loadQuads(vector<Quad>& quads) {
	STATE.quads = quads;

	initializeShaders(STATE.mainVertexShader, STATE.quads);

	for (auto& t : STATE.quads) {
		vector<float> v = t.vertices;

		glGenVertexArrays(1, &t.VAO);
		glBindVertexArray(t.VAO);

		glGenBuffers(1, &t.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, t.VBO);
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), &v[0], GL_STATIC_DRAW);

		glGenBuffers(1, &t.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}

void loadTriangles(vector<Triangle>& triangles) {
	STATE.triangles = triangles;

	initializeShaders(STATE.mainVertexShader, STATE.triangles);

	for (auto& t : STATE.triangles) {
		vector<float> v = t.vertices;

		glGenVertexArrays(1, &t.VAO);
		glBindVertexArray(t.VAO);

		glGenBuffers(1, &t.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, t.VBO);
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), &v[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}


void initWindow(int w, int h, const char* title) {
	if (!glfwInit()) {
		std::cerr << "Could not initialize OpenGL.\n";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	STATE.windowWidth = w;
	STATE.windowHeight = h;

	STATE.mainWindow = glfwCreateWindow(STATE.windowWidth, STATE.windowHeight, title, NULL, NULL);

	if (!STATE.mainWindow) {
		std::cerr << "Failed to create OpenGL window.\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(STATE.mainWindow);

	// Set resize callback
	glfwSetFramebufferSizeCallback(STATE.mainWindow, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, STATE.EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, STATE.EBO);
}

bool windowShouldClose() {
	return glfwWindowShouldClose(STATE.mainWindow);
}

void beginDrawing() {
	glUseProgram(STATE.mainShaderProgram);
}

void endDrawing() {
	glfwSwapBuffers(STATE.mainWindow);
	glfwPollEvents();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawQuad() {
	for (auto& q : STATE.quads) {
		glUseProgram(q.shaderProgram);
		glBindVertexArray(q.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}	
}

void drawTriangle() {
	for (auto& t : STATE.triangles) {
		glUseProgram(t.shaderProgram);
		glBindVertexArray(t.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void clearBackground(RGBA c) {
	glClearColor(c.r, c.g, c.b, c.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void closeWindow() {
	for (auto& q : STATE.quads) {
		glDeleteVertexArrays(1, &q.VAO);
		glDeleteBuffers(1, &q.VBO);
		glDeleteBuffers(1, &q.EBO);
		glDeleteProgram(q.shaderProgram);
	}	
	for (auto& t : STATE.triangles) {
		glDeleteVertexArrays(1, &t.VAO);
		glDeleteBuffers(1, &t.VBO);
		glDeleteProgram(t.shaderProgram);
	}

	glfwTerminate();
}
