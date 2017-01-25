//Marc Tremblay 01/24/2017
//100555250

#pragma comment(lib, "GLEW/glew32.lib")
#pragma comment(lib, "GLFW/glfw3dll.lib")

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include"FMOD/SoundEngine.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

const GLint WIDTH = 800, HEIGHT = 600;

float startTime = 0, deltaTime = 0;

int main()
{
	char soundFile[256] = "media/drumloop.wav";
	/*
	std::cout << "Please enter the name of a .wav file: ";

	std::cin.get(soundFile, 256);
	*/

	Sound sound = Sound({ 0.0, 0.0, 0.0});
	sound.Load(soundFile);

	if (glfwInit())
	{
		//GLFW initialization failed
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "INFR 2370 - Assignment One", NULL, NULL);
	
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window)
	{
		std::cout << "GLFW window or OpenGL context creation failed!" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	sound.Play();
	
	double start;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw opengl stuff

		Sound::SystemUpdate();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}