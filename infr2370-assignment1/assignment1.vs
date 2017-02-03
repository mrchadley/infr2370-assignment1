/*
 *  Simple vertex shader
 */

in vec4 vPosition;
uniform mat4 model;
uniform mat4 viewPerspective;

void main() {

	gl_Position = viewPerspective * model * vPosition;
	//gl_Position = vPosition;
	
}