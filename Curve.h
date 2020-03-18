#ifndef _CURVE_H_
#define _CURVE_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <vector>

class Curve
{
private:
	std::vector<glm::vec3> points;
	std::vector<glm::vec3> normals;
	std::vector<float> sNum, edge;


	std::vector<Curve*> curves;
	GLuint curveVao, curveVbo, normalVbo, otherVbo, otherVbo2;
	GLuint curveShader;
public:
	Curve(int version);
	void draw(glm::mat4 C);
	void update();
	void addPoints(std::vector<glm::vec3> p);
};

#endif

