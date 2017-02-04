//Marc Tremblay 01/24/2017
//100555250


#include "FMOD/SoundEngine.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "jnaut/graphics/Window.h"
#include "jnaut/FileUtils.h"


#include <time.h>
#include <math.h>
#include <stack>

#define PI 3.14159265

GLuint program;			// shader programs
GLuint objVAO;
int triangles;
int window;

glm::mat4 projection;	// projection matrix
float eyex, eyey, eyez;	// eye position
glm::mat4 ssModelPos;
glm::mat4 lModelPos;
Sound sound = Sound({ 0.0, 0.0, 0.0 });
int angle = 90;

bool dir = true;
float posMax = 10.0f, posMin = 2.0f;
float posCur = 2.0f;

jnaut::Model *soundSrcModel;
jnaut::Model *listenerModel;

void RotateSound()
{
	angle += 5;
	FMOD_VECTOR newPos = {2*cosf(angle*PI / 180.0f), 2*sinf(angle*PI / 180.0f), 0};
	sound.SetPos(newPos);
	ssModelPos = glm::mat4(1.0f);
	ssModelPos = glm::translate(ssModelPos, glm::vec3(5 * newPos.x, newPos.z, -5 * newPos.y));
}

void SlideSound()
{
	FMOD_VECTOR newPos = sound.GetPos();
	if (dir) newPos.y += 1;
	else newPos.y -= 1;
	sound.SetPos(newPos);
	ssModelPos = glm::mat4(1.0f);
	ssModelPos = glm::translate(ssModelPos, glm::vec3(0, 0, -5 * newPos.y));
	if (sound.GetPos().y >= posMax || sound.GetPos().y <= posMin) dir = !dir;
}

void init()
{
	program = jnaut::J_FileUtils::LoadShader("lab2.vs", "lab2.fs");
	glUseProgram(program);
	soundSrcModel = jnaut::J_FileUtils::LoadOBJ("icosphere_small.obj", program);
	listenerModel = jnaut::J_FileUtils::LoadOBJ("icosphere.obj", program);
	projection = glm::perspective(45.0f, (float)800 / (float)600, 1.0f, 800.0f);
	glViewport(0, 0, 800, 600);
	ssModelPos = glm::mat4(1.0f);
	lModelPos = glm::mat4(1.0f);
	ssModelPos = glm::translate(ssModelPos, glm::vec3(0, 0, -10));
	glEnable(GL_DEPTH_TEST);
	sound.SetPos(FMOD_VECTOR{ 0, 2, 0 });
}


void display()
{
	glm::mat4 view;
	glm::mat4 viewPerspective;


	int modelLoc;
	int vpLoc;
	int normalLoc;

	
	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
		glm::vec3(0, 0, -5),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view)));
	viewPerspective = projection * view;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(ssModelPos));
	vpLoc = glGetUniformLocation(program, "viewPers");
	glUniformMatrix4fv(vpLoc, 1, 0, glm::value_ptr(viewPerspective));
	normalLoc = glGetUniformLocation(program, "normalMat");
	glUniformMatrix3fv(normalLoc, 1, 0, glm::value_ptr(normal));

	glBindVertexArray(soundSrcModel->vao);
	glDrawElements(GL_TRIANGLES, soundSrcModel->indices, GL_UNSIGNED_SHORT, NULL);

	modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(lModelPos));
	glBindVertexArray(listenerModel->vao);
	glDrawElements(GL_TRIANGLES, listenerModel->indices, GL_UNSIGNED_SHORT, NULL);
}

int main()
{
	char soundFile[256] = "media/drumloop.wav";

	std::cout << "Controls:" << std::endl;
	std::cout << "p - pan around listener" << std::endl;
	std::cout << "d - move away from/towards listener" << std::endl;
	std::cout << "r - toggle logarithmic/linear rolloff modes" << std::endl;
	std::cout << "q - quit" << std::endl;
	std::cout << "Please enter the name of a .wav file: ";

	std::cin.get(soundFile, 256);
	

	
	sound.Load(soundFile);

	using namespace jnaut;
	using namespace graphics;
	Window window("INFR 2370 - Assignment One", 800, 600);

	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

	eyex = 10.0;
	eyey = 6.0;
	eyez = 16.0;

	init();
	sound.Play();
	
	float start, delta = 0;

	float timer = 0;
	unsigned short mode = 0;

	while (!window.Closed())
	{
		window.Clear();

		start = clock();


		if (window.GetKey(GLFW_KEY_P)) //rotate around listener
		{
			mode = 1;
			angle = 90;
			sound.SetPos(FMOD_VECTOR{ 0, 2, 0 });
			ssModelPos = glm::mat4(1.0f);
			ssModelPos = glm::translate(ssModelPos, glm::vec3(0, 0, -10));
		}
		if (window.GetKey(GLFW_KEY_D)) //move away and to listener
		{
			mode = 2;
			sound.SetPos(FMOD_VECTOR{ 0, 2, 0 });
			ssModelPos = glm::mat4(1.0f);
			ssModelPos = glm::translate(ssModelPos, glm::vec3(0, 0, -10));

		}
		if (window.GetKey(GLFW_KEY_R)) //toggle rolloff
		{

		}
		if (window.GetKey(GLFW_KEY_Q)) //quit
		{
			break;
		}

		//draw opengl stuff
		display();

		if (timer >= 0.5f)
		{
			timer = 0.0f;
			switch (mode)
			{
			case 1:
				RotateSound();
				break;
			case 2:
				SlideSound();
				break;
			default:
				break;
			}
		}

		Sound::SystemUpdate();
		window.Update();

		delta = (clock() - start) / 1000;
		timer += delta;
	}
	return EXIT_SUCCESS;
}