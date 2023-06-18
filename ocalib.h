#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
using std::string;

#include <iostream>

#include "ocafile.h"

struct AppState {
	GLFWwindow* mainWindow;
	int windowWidth;
	int windowHeight;
	unsigned int mainShaderProgram;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};

struct RGBA {
	float r;
	float g;
	float b;
	float a;
};

AppState STATE{};

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void initializeShaders(unsigned int& vertexShader, unsigned int& fragShader, unsigned int& shaderProgram) {

	// 1) Create shader string
	string vertexShaderFile = ocaReadTextFile("vert.glsl");
	const char* vertexShaderSource = vertexShaderFile.c_str();

	//2) Create shader ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 3) Compile shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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

	// Load and read fragment shader:

	// 1) Create shader string
	string fragShaderFile = ocaReadTextFile("frag.glsl");
	const char* fragShaderSource = fragShaderFile.c_str();

	//2) Create shader ID
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 3) Compile shader
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	// 4) Check if successful
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Fragment shader compiled successfully\n";
	}

	// Create shader program
	STATE.mainShaderProgram = glCreateProgram();

	glAttachShader(STATE.mainShaderProgram, vertexShader);
	glAttachShader(STATE.mainShaderProgram, fragShader);
	glLinkProgram(STATE.mainShaderProgram);

	// Check if successful
	glGetProgramiv(STATE.mainShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(STATE.mainShaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Shader program created successfully\n";
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
	glfwSetFramebufferSizeCallback(STATE.mainWindow, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glGenVertexArrays(1, &STATE.VAO);
	glGenBuffers(1, &STATE.VBO);

	glGenBuffers(1, &STATE.EBO);

	glBindBuffer(GL_ARRAY_BUFFER, STATE.VBO);
	glBindVertexArray(STATE.VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, STATE.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, STATE.EBO);



	unsigned int vertexShader;
	unsigned int fragShader;
	initializeShaders(vertexShader, fragShader, STATE.mainShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	glUseProgram(STATE.mainShaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

void drawTriangle() {
	glBindVertexArray(STATE.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void clearBackground(RGBA c) {
	glClearColor(c.r, c.g, c.b, c.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void closeWindow() {
	glfwTerminate();
}