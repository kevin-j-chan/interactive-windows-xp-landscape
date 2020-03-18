#ifndef _CLOUD_H_
#define _CLOUD_H_

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

class Cloud : public Object
{
private:
	GLuint vao;
	GLuint vbos[2];
	
	GLuint projectionLoc, viewLoc, modelLoc, texLoc, timeLoc;

	unsigned int texture;
	
	bool pityPoints = false;

	std::vector<glm::vec3> vertices;
	unsigned int layouts;

public:
	Cloud();
	~Cloud();

	void draw();
	void update();

	void setPityPoints(bool p);
};

#endif