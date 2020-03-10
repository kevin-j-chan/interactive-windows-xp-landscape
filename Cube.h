#ifndef _CUBE_H_
#define _CUBE_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "Object.h"

class Cube : public Object
{
private:
	GLuint vao;
	GLuint vbos[2];
	GLuint textureID;

public:
	Cube(float size);
	~Cube();

	void draw();
	void update();

	void spin(float deg);
	unsigned int loadCubemap(std::vector<std::string> faces);
};

#endif

