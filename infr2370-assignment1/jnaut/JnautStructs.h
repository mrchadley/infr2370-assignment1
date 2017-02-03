#ifndef JNAUT_STRUCTS_M
#define JNAUT_STRUCTS_M

#include "graphics/GL/glew.h"

namespace jnaut
{
	struct Model
	{
		GLuint vao; //vertex array object
		GLuint ibo; //index buffer object
		int indices;//number of indices
	};
}

#endif //JNAUT_STRUCTS_M
