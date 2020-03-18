#include "Terrain.h"

unsigned char* loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

// load image file into texture object
void loadTexture(const char* file)
{
	GLuint texture[1];     // storage for one texture
	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data

	// Load image file
	tdata = loadPPM(file, twidth, theight);
	if (tdata == NULL) return;

	// Create ID for texture
	glGenTextures(1, &texture[0]);

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Chunk::Chunk()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = loadPPM("grass.ppm", width, height);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

		std::cout << "Loaded grass.ppm" << std::endl;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << "grass.ppm" << std::endl;
	}
	
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

void Chunk::diamond(int x, int y, int d) {
	std::vector<std::tuple<int, int, int, int, float>> queue;

	queue.push_back(std::make_tuple(0, x, y, d, 1.f));

	bool visited[ROWS][COLS] = { false };

	while (queue.size() != 0) {
		std::tuple<int, int, int, int, float> t = queue[0];
		queue.erase(queue.begin());

		x = std::get<1>(t);
		y = std::get<2>(t);
		d = std::get<3>(t);
		float i = std::get<4>(t);

		if (x < 0 || x >= COLS || y < 0 || y >= ROWS) continue;
		if (visited[x][y]) continue;

		float f = static_cast <float> (rand()) / static_cast<float> (RAND_MAX) * (0.3 * i);

		int count = 0;
		float avg = 0.0f;

		if (std::get<0>(t) == 0) {
			if (x - d >= 0 && x - d < COLS && y - d >= 0 && y - d < ROWS) {
				avg += heightMap[x - d][y - d];
				count++;
			}
			if (x - d >= 0 && x - d < COLS && y + d >= 0 && y + d < ROWS) {
				avg += heightMap[x - d][y + d];
				count++;
			}
			if (x + d >= 0 && x + d < COLS && y - d >= 0 && y - d < ROWS) {
				avg += heightMap[x + d][y - d];
				count++;
			}
			if (x + d >= 0 && x + d < COLS && y + d >= 0 && y + d < ROWS) {
				avg += heightMap[x + d][y + d];
				count++;
			}

			if (count == 0) continue;

			avg /= (float)count;

			heightMap[x][y] = avg + f;

			queue.push_back(std::make_tuple(1, x, y - d, d, i));
			queue.push_back(std::make_tuple(1, x, y + d, d, i));
			queue.push_back(std::make_tuple(1, x - d, y, d, i));
			queue.push_back(std::make_tuple(1, x + d, y, d, i));
		}
		else {
			if (x - d >= 0 && x - d < COLS && y >= 0 && y < ROWS) {
				avg += heightMap[x - d][y];
				count++;
			}
			if (x + d >= 0 && x + d < COLS && y >= 0 && y < ROWS) {
				avg += heightMap[x + d][y];
				count++;
			}
			if (x >= 0 && x < COLS && y - d >= 0 && y - d < ROWS) {
				avg += heightMap[x][y - d];
				count++;
			}
			if (x >= 0 && x < COLS && y + d >= 0 && y + d < ROWS) {
				avg += heightMap[x][y + d];
				count++;
			}

			if (count == 0) continue;

			avg /= (float) count;

			heightMap[x][y] = avg + f;
			
			d = d / 2;
			queue.push_back(std::make_tuple(0, x - d, y - d, d, i / 2.2));
			queue.push_back(std::make_tuple(0, x - d, y + d, d, i / 2.2));
			queue.push_back(std::make_tuple(0, x + d, y - d, d, i / 2.2));
			queue.push_back(std::make_tuple(0, x + d, y + d, d, i / 2.2));
		}
		visited[x][y] = true;
	}

	// parse through the heightmap and fill in large holes
	bool filled = true;
	while (filled) {
		filled = false;
		for (int i = 1; i < ROWS - 1; i++) {
			for (int j = 1; j < COLS - 1; j++) {
				float h = heightMap[i][j];

				float h1 = heightMap[i - 1][j];
				float h2 = heightMap[i + 1][j];
				float h3 = heightMap[i][j - 1];
				float h4 = heightMap[i][j + 1];

				if (h < h1 && h < h2 && h < h3 && h < h4) {
					heightMap[i][j] = (h1 + h2 + h3 + h4) / 4.f;
					filled = true;
				}
			}
		}
	}
}

// Diamond square algorithm
void Chunk::generateHeight() {
	std::vector<std::vector<float>> heightData(ROWS, std::vector<float>(COLS, 0.0f));
	heightMap = heightData;

	float f0 = static_cast <float> (rand()) / static_cast<float> (RAND_MAX) * 0.3;
	float f1 = static_cast <float> (rand()) / static_cast<float> (RAND_MAX) * 0.3;
	float f2 = static_cast <float> (rand()) / static_cast<float> (RAND_MAX) * 0.3;
	float f3 = static_cast <float> (rand()) / static_cast<float> (RAND_MAX) * 0.3;
	heightMap[0][0] = f0;
	heightMap[0][COLS - 1] = f1;
	heightMap[ROWS - 1][0] = f2;
	heightMap[ROWS - 1][COLS - 1] = f3;

	diamond((COLS / 2), (ROWS / 2), (COLS / 2));
}

void Chunk::generate()
{
	indices = std::vector<unsigned int>();
	points = std::vector<glm::vec3>();
	normals = std::vector<glm::vec3>();

	std::vector<std::vector<glm::vec3>> _points;
	std::vector<std::vector<glm::vec3>> _normals;
	std::vector<std::vector<glm::vec2>> _texCoords;

	//generateFakeHeight();
	generateHeight();

	for (int i = 0; i < ROWS; i++) {
		std::vector<glm::vec3> row;
		for (int j = 0; j < COLS; j++) {
			const auto factorRow = float(i) / float(ROWS - 1);
			const auto factorCol = float(j) / float(COLS - 1);

			row.push_back(glm::vec3(-0.5f + factorCol, heightMap[i][j], -0.5f + factorRow));
		}
		_points.push_back(row);
	}

	for (std::vector<glm::vec3> r : _points) {
		for (glm::vec3 p : r) {
			points.push_back(p);
		}
	}

	const auto textureStepU = 0.1f;
	const auto textureStepV = 0.1f;

	for (int i = 0; i < ROWS; i++)
	{
		std::vector<glm::vec2> row;
		for (int j = 0; j < COLS; j++) {
			row.push_back(glm::vec2(textureStepU * j, textureStepV * i));
		}
		_texCoords.push_back(row);
	}

	for (std::vector<glm::vec2> r : _texCoords) {
		for (glm::vec2 p : r) {
			texCoords.push_back(p);
		}
	}

	std::vector< std::vector<glm::vec3> > tempNormals[2];
	for (int i = 0; i < 2; i++) {
		tempNormals[i] = std::vector<std::vector<glm::vec3>>(ROWS - 1, std::vector<glm::vec3>(COLS - 1));
	}

	for (int i = 0; i < ROWS - 1; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			const auto& vertexA = _points[i][j];
			const auto& vertexB = _points[i][j + 1];
			const auto& vertexC = _points[i + 1][j + 1];
			const auto& vertexD = _points[i + 1][j];

			const auto triangleNormalA = glm::cross(vertexB - vertexA, vertexA - vertexD);
			const auto triangleNormalB = glm::cross(vertexD - vertexC, vertexC - vertexB);

			tempNormals[0][i][j] = glm::normalize(triangleNormalA);
			tempNormals[1][i][j] = glm::normalize(triangleNormalB);
		}
	}

	for (int i = 0; i < ROWS; i++) {
		std::vector<glm::vec3> row;
		for (int j = 0; j < COLS; j++) {
			const bool isFirstRow = i == 0;
			const bool isFirstColumn = j == 0;
			const bool isLastRow = i == ROWS - 1;
			const bool isLastColumn = j == COLS - 1;

			glm::vec3 finalVertexNormal = glm::vec3(0.0f, 0.0f, 0.0f);

			// Look for triangle to the upper-left
			if (!isFirstRow && !isFirstColumn) {
				finalVertexNormal += tempNormals[0][i - 1][j - 1];
			}

			// Look for triangles to the upper-right
			if (!isFirstRow && !isLastColumn) {
				for (auto k = 0; k < 2; k++) {
					finalVertexNormal += tempNormals[k][i - 1][j];
				}
			}

			// Look for triangle to the bottom-right
			if (!isLastRow && !isLastColumn) {
				finalVertexNormal += tempNormals[0][i][j];
			}

			// Look for triangles to the bottom-right
			if (!isLastRow && !isFirstColumn) {
				for (auto k = 0; k < 2; k++) {
					finalVertexNormal += tempNormals[k][i][j - 1];
				}
			}

			// Store final normal of j-th vertex in i-th row
			row.push_back(glm::normalize(finalVertexNormal));
			//printf("%f %f %f\n", row[j].x, row[j].y, row[j].z);
		}
		_normals.push_back(row);
	}

	for (std::vector<glm::vec3> r : _normals) {
		for (glm::vec3 p : r) {
			normals.push_back(p);
		}
	}

	for (int i = 0; i < ROWS - 1; i++) {
		for (int j = 0; j < COLS; j++) {
			for (int k = 0; k < 2; k++) {
				int index = (i + k) * COLS + j;
				indices.push_back(index);
			}
		}
		indices.push_back(ROWS * COLS);
	}

	//printf("%d, %d %d %d\n", ROWS * COLS, points.size(), normals.size(), indices.size());

	glDeleteBuffers(1, vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);

	// Generate a vertex array (VAO) and a vertex buffer objects (VBO).
	glGenVertexArrays(1, &vao);
	glGenBuffers(3, vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(),
		points.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(),
		normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoords.size(),
		texCoords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
		indices.data(), GL_STATIC_DRAW);

	// Unbind from the VBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind from the VAO.
	glBindVertexArray(0);
}

void Chunk::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(vao);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(ROWS * COLS);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_PRIMITIVE_RESTART);
}

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

void Terrain::generate()
{	
	chunk.generate();
}

void Terrain::draw()
{
	chunk.draw();
}