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

void init()
{
	program = jnaut::J_FileUtils::LoadShader("lab2.vs", "lab2.fs");
	glUseProgram(program);
	soundSrcModel = jnaut::J_FileUtils::LoadOBJ("head.obj", program);
	listenerModel = jnaut::J_FileUtils::LoadOBJ("head.obj", program);
	projection = glm::perspective(45.0f, (float)800 / (float)600, 1.0f, 800.0f);
	glViewport(0, 0, 800, 600);
	ssModelPos = glm::mat4(1.0f);
	lModelPos = glm::mat4(1.0f);
	ssModelPos = glm::translate(ssModelPos, glm::vec3(0, 0, -10));
	glEnable(GL_DEPTH_TEST);
}


/*void init() {
	GLuint vbuffer;
	GLuint ibuffer;
	GLint vPosition;
	GLint vNormal;
	int vs;
	int fs;
	GLfloat *vertices;
	GLfloat *normals;
	GLushort *indices;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	int nv;
	int nn;
	int ni;
	int i;
	float xmin, ymin, zmin;
	float xmax, ymax, zmax;

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	//  Load the obj file 

	std::string err = tinyobj::LoadObj(shapes, materials, "head.obj", 0);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	/*  Retrieve the vertex coordinate data *

	nv = shapes[0].mesh.positions.size();
	vertices = new GLfloat[nv];
	for (i = 0; i<nv; i++) {
		vertices[i] = shapes[0].mesh.positions[i];
	}

	/*
	*  Find the range of the x, y and z
	*  coordinates.
	*
	xmin = ymin = zmin = 1000000.0;
	xmax = ymax = zmax = -1000000.0;
	for (i = 0; i<nv / 3; i++) {
		if (vertices[3 * i] < xmin)
			xmin = vertices[3 * i];
		if (vertices[3 * i] > xmax)
			xmax = vertices[3 * i];
		if (vertices[3 * i + 1] < ymin)
			ymin = vertices[3 * i + 1];
		if (vertices[3 * i + 1] > ymax)
			ymax = vertices[3 * i + 1];
		if (vertices[3 * i + 2] < zmin)
			zmin = vertices[3 * i + 2];
		if (vertices[3 * i + 2] > zmax)
			zmax = vertices[3 * i + 2];
	}
	/* compute center and print range *
	cx = (xmin + xmax) / 2.0f;
	cy = (ymin + ymax) / 2.0f;
	cz = (zmin + zmax) / 2.0f;
	printf("X range: %f %f\n", xmin, xmax);
	printf("Y range: %f %f\n", ymin, ymax);
	printf("Z range: %f %f\n", zmin, zmax);
	printf("center: %f %f %f\n", cx, cy, cz);

	/*  Retrieve the vertex normals *

	nn = shapes[0].mesh.normals.size();
	normals = new GLfloat[nn];
	for (i = 0; i<nn; i++) {
		normals[i] = shapes[0].mesh.normals[i];
	}

	/*  Retrieve the triangle indices *

	ni = shapes[0].mesh.indices.size();
	triangles = ni / 3;
	indices = new GLushort[ni];
	for (i = 0; i<ni; i++) {
		indices[i] = shapes[0].mesh.indices[i];
	}

	/*
	*  load the vertex coordinate data
	*
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, (nv + nn)*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nv*sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, nv*sizeof(GLfloat), nn*sizeof(GLfloat), normals);

	/*
	*  load the vertex indexes
	*
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ni*sizeof(GLushort), indices, GL_STATIC_DRAW);

	/*
	*  compile and build the shader program
	*
	//vs = buildShader(GL_VERTEX_SHADER, "lab2.vs");
	//fs = buildShader(GL_FRAGMENT_SHADER, "lab2.fs");
	program = jnaut::J_FileUtils::LoadShader("lab2.vs", "lab2.fs");

	/*
	*  link the vertex coordinates to the vPosition
	*  variable in the vertex program.  Do the same
	*  for the normal vectors.
	*
	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(vertices));
	glEnableVertexAttribArray(vNormal);

	projection = glm::perspective(45.0f, (float)800 / (float)600, 1.0f, 800.0f);
	glViewport(0, 0, 800, 600);
}*/

void display()
{
	glm::mat4 view;
	glm::mat4 viewPerspective;


	int modelLoc;
	int vpLoc;
	int normalLoc;

	
	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
		glm::vec3(0, 0, -1),
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

	/*
	std::cout << "Please enter the name of a .wav file: ";

	std::cin.get(soundFile, 256);
	*/

	
	sound.Load(soundFile);

	using namespace jnaut;
	using namespace graphics;
	Window window("INFR 2370 - Assignment One", 800, 600);

	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

	eyex = 5.0;
	eyey = 2.0;
	eyez = 9.0;

	init();
	sound.Play();
	
	float start, delta = 0;

	float timer = 0;
	int step = 0;

	while (!window.Closed())
	{
		window.Clear();

		start = clock();

		//draw opengl stuff
		display();

		if (timer >= 0.5f)
		{
			RotateSound();
			timer = 0.0f;
		}

		Sound::SystemUpdate();
		window.Update();

		delta = (clock() - start) / 1000;
		timer += delta;
	}
	return EXIT_SUCCESS;
}