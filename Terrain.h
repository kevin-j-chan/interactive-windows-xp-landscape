#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <random>
#include <tuple>

#include "Object.h"

constexpr auto ROWS = 129;
constexpr auto COLS = 129;

class Chunk {
private:
	const int ITERATIONS = 20;

	std::vector<std::vector<float>> heightMap;
	std::vector<glm::vec3> points;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texCoords;
	GLuint vao, vbo[3], ebo;

	GLuint textureID;

	void diamond(int x, int y, int d);
	void generateHeight();
	void generateFakeHeight();

public:
	Chunk();
	~Chunk();

	void generate();

	void draw();
};

class Terrain
{
private:
	Chunk chunk;

public:
	Terrain();
	~Terrain();

	void generate();

	void draw();
};

#endif
