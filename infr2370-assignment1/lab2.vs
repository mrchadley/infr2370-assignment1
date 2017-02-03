#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 model;
uniform mat4 viewPers;
uniform mat3 normalMat;
out vec3 normal;

void main() {

	gl_Position = viewPers * model * vPosition;
	normal = normalMat* vNormal;
}