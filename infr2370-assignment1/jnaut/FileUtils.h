#ifndef JNAUT_FILEUTILS_M
#define JNAUT_FILEUTILS_M

#include <vector>
#include <iostream>
#include "JnautStructs.h"
#include "../tiny_obj_loader.h"

namespace jnaut
{
	class J_FileUtils
	{
	public:
		static std::string ReadFile(const char *a_filepath)
		{
			FILE *file = fopen(a_filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char *data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}
		static Model *LoadOBJ(const char *a_filepath, GLuint a_shaderProgram)
		{
			Model *result = new Model;
			GLuint vao;
			GLint vPosition;
			GLint vNormal;
			
			GLfloat *vertices;
			GLfloat *normals;
			GLushort *indices;

			int tris;
			
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			result->vao = vao;

			std::string error = tinyobj::LoadObj(shapes, materials, a_filepath, 0);
			if (!error.empty())
			{
				std::cerr << error << std::endl;
				return nullptr;
			}

			// Retrieve the vertex data
			int numVerts = shapes[0].mesh.positions.size();
			vertices = new GLfloat[numVerts];
			for (int i = 0; i < numVerts; i++)
				vertices[i] = shapes[0].mesh.positions[i];
			
			// Retrieve vertex normals
			int numNorms = shapes[0].mesh.normals.size();
			normals = new GLfloat[numNorms];
			for (int i = 0; i < numNorms; i++)
				normals[i] = shapes[0].mesh.normals[i];

			// Retrieve triangle indices
			int numInds = shapes[0].mesh.indices.size();
			indices = new GLushort[numInds];
			result->indices = numInds;
			tris = numInds / 3;
			for (int i = 0; i < numInds; i++)
				indices[i] = shapes[0].mesh.indices[i];

			// Load the vertex data
			GLuint vBuffer;
			glGenBuffers(1, &vBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
			glBufferData(GL_ARRAY_BUFFER, (numVerts + numNorms)*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, numVerts*sizeof(GLfloat), vertices);
			glBufferSubData(GL_ARRAY_BUFFER, numVerts*sizeof(GLfloat), numNorms*sizeof(GLfloat), normals);

			// Load vertex indices
			GLuint iBuffer;
			glGenBuffers(1, &iBuffer);
			result->ibo = iBuffer;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInds * sizeof(GLushort), indices, GL_STATIC_DRAW);

			vPosition = glGetAttribLocation(a_shaderProgram, "vPosition");
			glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(vPosition);

			vNormal = glGetAttribLocation(a_shaderProgram, "vNormal");
			glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(vertices));
			glEnableVertexAttribArray(vNormal);

			return(result);
		}
		static GLuint LoadShader(const char *a_vShaderPath, const char *a_fShaderPath)
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSource = ReadFile(a_vShaderPath).c_str();
			std::string fragSource = ReadFile(a_fShaderPath).c_str();

			const char *v = vertSource.c_str();
			const char *f = fragSource.c_str();

			glShaderSource(vertex, 1, &v, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader! " << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}


			glShaderSource(fragment, 1, &f, NULL);
			glCompileShader(fragment);
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader! " << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}
	};
}

#endif //JNAUT_FILEUTILS_M