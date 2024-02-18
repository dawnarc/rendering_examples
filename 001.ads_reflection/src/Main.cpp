
#pragma once

#include <iostream>
#include <windows.h>

#include <fstream>
#include <sstream>
#include <string>

//#include <GL/glew.h>
#include <KHR/khrplatform.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "VBOTorus.h"
#include "GLSLProgram.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

using std::string;
using std::ifstream;

GLFWwindow *window;

static HMODULE libGL;

GLuint vaoHandle;

int width, height;

GLSLProgram prog;

VBOTorus *torus;

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

float angle;

void update(float t);

void render();

void setMatrices();

void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) 
	{
		update(float(glfwGetTime()));
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void dumpGLInfo(bool dumpExtensions) {
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf("-------------------------------------------------------------\n");
	printf("GL Vendor    : %s\n", vendor);
	printf("GL Renderer  : %s\n", renderer);
	printf("GL Version   : %s\n", version);
	printf("GL Version   : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);
	printf("-------------------------------------------------------------\n");

	if (dumpExtensions) {
		GLint nExtensions;
		glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
		for (int i = 0; i < nExtensions; i++) {
			printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
		}
	}
}

void initScene()
{
	angle = 0.f;

	std::string vert_path = std::string(APP_WORK_DIR) + "/shader/phong.vert";
	bool rs = prog.CompileShader(vert_path.c_str(), GLSLShader::GLSLShaderType::VERTEX);
	if (!rs)
	{
		return;
	}
	
	std::string frag_path = std::string(APP_WORK_DIR) + "/shader/phong.frag";
	rs = prog.CompileShader(frag_path.c_str(), GLSLShader::GLSLShaderType::FRAGMENT);
	if (!rs)
	{
		return;
	}

	rs = prog.Link();
	if (!rs)
	{
		return;
	}

	rs = prog.Use();
	if (!rs)
	{
		return;
	}

	glEnable(GL_DEPTH_TEST);

	torus = new VBOTorus(0.7f, 0.3f, 50, 50);

	model = glm::mat4(1.0f);
	model *= glm::rotate(glm::radians(-35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model *= glm::rotate(glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::mat4(1.0f);
	glm::vec4 worldLight = glm::vec4(5.0f, 5.0f, 2.0f, 1.0f);

	prog.SetUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
	prog.SetUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
	prog.SetUniform("Light.Position", view * worldLight);
	prog.SetUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
	prog.SetUniform("Light.La", 0.4f, 0.4f, 0.4f);
	prog.SetUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	prog.SetUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
	prog.SetUniform("Material.Shininess", 100.0f);
}

void update(float t)
{
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model = glm::mat4(1.0f);
	model *= glm::rotate(glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model *= glm::rotate(glm::radians(-35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model *= glm::rotate(glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	setMatrices();
	torus->render();
}

void setMatrices()
{
	glm::mat4 mv = view * model;
	prog.SetUniform("ModelViewMatrix", mv);
	prog.SetUniform("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	prog.SetUniform("MVP", projection * mv);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}


void initializeGL() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	initScene();
}


int main(int argc, char* argv[])
{
	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

#ifdef __APPLE__
	// Select OpenGL 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
	// Select OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// Open the window
	string title = "OpenGLTest";
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	//glfwSetKeyCallback(window, key_callback);

	// Get framebuffer size
	int fbw, fbh;
	glfwGetFramebufferSize(window, &fbw, &fbh);

	// Load the OpenGL functions.
	if (!gladLoadGL()) { exit(-1); }

	dumpGLInfo(false);

	// Initialization
	initializeGL();

	resize(WIN_WIDTH, WIN_HEIGHT);

	// Enter the main loop
	mainLoop();

	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	exit(EXIT_SUCCESS);

	return 0;
}