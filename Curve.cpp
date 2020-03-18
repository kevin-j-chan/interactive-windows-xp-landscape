#include "Curve.h"
#include "Window.h"

#include <iostream>
using namespace std;

Curve::Curve(int version)
{

    glm::mat4 B = glm::mat4(glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f), 
							glm::vec4(3.0f, -6.0f, 3.0f, 0.0f), 
							glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f), 
							glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));


	/* BOTTOM LEFT - BLUE */
	glm::mat4 G_x;
	G_x[0] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);
	G_x[1] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);
	G_x[2] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);
	G_x[3] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);

	glm::mat4 G_y;
	G_y[0] = glm::vec4(8.0f, 8.25f, 8.25f, 8.0f);
	G_y[1] = glm::vec4(8.3333f, 8.4833f, 8.4833f, 8.3333f);
	G_y[2] = glm::vec4(8.6667f, 8.8167f, 8.8167f, 8.6667f);
	G_y[3] = glm::vec4(9.0f, 9.15f, 9.15f, 9.0f);

	glm::mat4 G_z;
	if (version == 0) {
		
		G_z[0] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z[1] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z[2] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z[3] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
	}
	else {
		G_z[0] = glm::vec4(0.0f, 0.03f, 0.03f, 0.0f);
		G_z[1] = glm::vec4(0.0f, 0.13f, 0.13f, 0.0f);
		G_z[2] = glm::vec4(0.0f, 0.23f, 0.23f, 0.0f);
		G_z[3] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
	}

	glm::mat4 C_x = B * G_x * B;
	glm::mat4 C_y = B * G_y * B;
	glm::mat4 C_z = B * G_z * B;

	for (float t1 = 0; t1 < 200.0f; t1 += 1.0f)
	{
		for (float t2 = 0; t2 < 200.0f; t2 += 1.0f) {
			glm::vec4 U = glm::vec4(pow(t1 / 200.0f, 3), pow(t1 / 200.0f, 2), (t1 / 200.0f), 1);
			glm::vec4 V = glm::vec4(pow(t2 / 200.0f, 3), pow(t2 / 200.0f, 2), (t2 / 200.0f), 1);
			points.push_back(16.0f * glm::vec3(glm::dot((C_x * V), U), glm::dot((C_y * V), U), glm::dot((C_z * V), U)));
			//normals.push_back(glm::vec3(0.0f, 65.0f, 220.0f));
			if (t1 > 194.0f || t2 < 5.0f || t1 < 5.0f || t2 > 194.0f) {
				edge.push_back(50.0f);
			}
			else {
				edge.push_back(0.0f);
			}
			glm::vec4 U_2 = glm::vec4(pow(3 * t1, 2) / pow(200.0f, 3), pow(2 * t1, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			glm::vec4 V_2 = glm::vec4(pow(3 * t2, 2) / pow(200.0f, 3), pow(2 * t2, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			normals.push_back(glm::cross(glm::vec3(glm::dot((C_x * V), U_2), glm::dot((C_y * V), U_2), glm::dot((C_z * V), U_2)),
				glm::vec3(glm::dot((C_x * V_2), U), glm::dot((C_y * V_2), U), glm::dot((C_z * V_2), U))));
			sNum.push_back(1.0f);

		}
	} 

	/* BOTTOM RIGHT - YELLOW */
	glm::mat4 G_x2;
	G_x2[0] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	G_x2[1] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	G_x2[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	G_x2[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	glm::mat4 G_y2;
	G_y2[0] = glm::vec4(8.0f, 7.85f, 7.85f, 8.0f);
	G_y2[1] = glm::vec4(8.3333f, 8.2833f, 8.2833f, 8.3333f);
	G_y2[2] = glm::vec4(8.6667f, 8.5167f, 8.5167f, 8.6667f);
	G_y2[3] = glm::vec4(9.0f, 8.85f, 8.85f, 9.0f);

	glm::mat4 G_z2;
	if (version == 0) {
		G_z2[0] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z2[1] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z2[2] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z2[3] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
	}
	else {
		G_z2[0] = glm::vec4(0.0f, -0.03f, -0.03f, 0.0f);
		G_z2[1] = glm::vec4(0.0f, -0.13f, -0.13f, 0.0f);
		G_z2[2] = glm::vec4(0.0f, -0.23f, -0.23f, 0.0f);
		G_z2[3] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
	}

	glm::mat4 C_x2 = B * G_x2 * B;
	glm::mat4 C_y2 = B * G_y2 * B;
	glm::mat4 C_z2 = B * G_z2 * B;

	for (float t1 = 0; t1 < 200.0f; t1+= 1.0f)
	{
		for (float t2 = 0; t2 < 200.0f; t2+= 1.0f) {
			glm::vec4 U = glm::vec4(pow(t1 / 200.0f, 3), pow(t1 / 200.0f, 2), (t1 / 200.0f), 1);
			glm::vec4 V = glm::vec4(pow(t2 / 200.0f, 3), pow(t2 / 200.0f, 2), (t2 / 200.0f), 1);
			points.push_back(16.0f * glm::vec3(glm::dot((C_x2 * V), U), glm::dot((C_y2 * V), U), glm::dot((C_z2 * V), U)));
			//normals.push_back(glm::vec3(950.0f, 800.0f, 100.0f));
			if (t1 > 194.0f || t2 < 5.0f || t1 < 5.0f || t2 > 194.0f) {
				edge.push_back(50.0f);
			}
			else {
				edge.push_back(0.0f);
			}
			glm::vec4 U_2 = glm::vec4(pow(3 * t1, 2) / pow(200.0f, 3), pow(2 * t1, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			glm::vec4 V_2 = glm::vec4(pow(3 * t2, 2) / pow(200.0f, 3), pow(2 * t2, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			normals.push_back(glm::cross(glm::vec3(glm::dot((C_x2 * V), U_2), glm::dot((C_y2 * V), U_2), glm::dot((C_z2 * V), U_2)),
				glm::vec3(glm::dot((C_x2 * V_2), U), glm::dot((C_y2 * V_2), U), glm::dot((C_z2 * V_2), U))));
			sNum.push_back(2.0f);
		}
	} 

	/* TOP LEFT - RED */
	glm::mat4 G_x3;
	G_x3[0] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);
	G_x3[1] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);
	G_x3[2] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);
	G_x3[3] = glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f);

	glm::mat4 G_y3;
	G_y3[0] = glm::vec4(9.0f, 9.15f, 9.15f, 9.0f);
	G_y3[1] = glm::vec4(9.3333f, 9.4833f, 9.4833f, 9.3333f);
	G_y3[2] = glm::vec4(9.6667f, 9.8167f, 9.8167f, 9.6667f);
	G_y3[3] = glm::vec4(10.0f, 10.15f, 10.15f, 10.0f);

	glm::mat4 G_z3;
	if (version == 0) {
		G_z3[0] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z3[1] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z3[2] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z3[3] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
	}
	else {
		G_z3[0] = glm::vec4(0.0f, 0.33f, 0.33f, 0.0f);
		G_z3[1] = glm::vec4(0.0f, 0.43f, 0.43f, 0.0f);
		G_z3[2] = glm::vec4(0.0f, 0.53f, 0.53f, 0.0f);
		G_z3[3] = glm::vec4(0.0f, 0.63f, 0.63f, 0.0f);
	}
	


	glm::mat4 C_x3 = B * G_x3 * B;
	glm::mat4 C_y3 = B * G_y3 * B;
	glm::mat4 C_z3 = B * G_z3 * B;

	for (float t1 = 0; t1 < 200.0f; t1+= 1.0f)
	{
		for (float t2 = 0; t2 < 200.0f; t2+= 1.0f) {
			glm::vec4 U = glm::vec4(pow(t1 / 200.0f, 3), pow(t1 / 200.0f, 2), (t1 / 200.0f), 1);
			glm::vec4 V = glm::vec4(pow(t2 / 200.0f, 3), pow(t2 / 200.0f, 2), (t2 / 200.0f), 1);
			points.push_back(16.0f * glm::vec3(glm::dot((C_x3 * V), U), glm::dot((C_y3 * V), U), glm::dot((C_z3 * V), U)));
			//normals.push_back(glm::vec3(125.0f, 35.0f, -30.0f));
			if (t1 > 194.0f || t2 < 5.0f || t1 < 5.0f || t2 > 194.0f) {
				edge.push_back(50.0f);
			}
			else {
				edge.push_back(0.0f);
			}
			glm::vec4 U_2 = glm::vec4(pow(3 * t1, 2) / pow(200.0f, 3), pow(2 * t1, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			glm::vec4 V_2 = glm::vec4(pow(3 * t2, 2) / pow(200.0f, 3), pow(2 * t2, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			normals.push_back(glm::cross(glm::vec3(glm::dot((C_x3 * V), U_2), glm::dot((C_y3 * V), U_2), glm::dot((C_z3 * V), U_2)),
				glm::vec3(glm::dot((C_x3 * V_2), U), glm::dot((C_y3 * V_2), U), glm::dot((C_z3 * V_2), U))));
			sNum.push_back(3.0f);
		}
	}

	/* TOP RIGHT - GREEN */
	glm::mat4 G_x4;
	G_x4[0] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	G_x4[1] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	G_x4[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	G_x4[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	glm::mat4 G_y4;
	G_y4[0] = glm::vec4(9.0f, 8.85f, 8.85f, 9.0f);
	G_y4[1] = glm::vec4(9.3333f, 9.2833f, 9.2833f, 9.3333f);
	G_y4[2] = glm::vec4(9.6667f, 9.5167f, 9.5167f, 9.6667f);
	G_y4[3] = glm::vec4(10.0f, 9.85f, 9.85f, 10.0f);

	glm::mat4 G_z4;
	if (version == 0) {
		G_z4[0] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z4[1] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z4[2] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z4[3] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
	}
	else {
		G_z4[0] = glm::vec4(0.0f, -0.33f, -0.33f, 0.0f);
		G_z4[1] = glm::vec4(0.0f, -0.43f, -0.43f, 0.0f);
		G_z4[2] = glm::vec4(0.0f, -0.53f, -0.53f, 0.0f);
		G_z4[3] = glm::vec4(0.0f, -0.63f, -0.63f, 0.0f);
	}

	glm::mat4 C_x4 = B * G_x4 * B;
	glm::mat4 C_y4 = B * G_y4 * B;
	glm::mat4 C_z4 = B * G_z4 * B;

	for (float t1 = 0; t1 < 200.0f; t1+= 1.0f)
	{
		for (float t2 = 0; t2 < 200.0f; t2+= 1.0f) {
			glm::vec4 U = glm::vec4(pow(t1 / 200.0f, 3), pow(t1 / 200.0f, 2), (t1 / 200.0f), 1);
			glm::vec4 V = glm::vec4(pow(t2 / 200.0f, 3), pow(t2 / 200.0f, 2), (t2 / 200.0f), 1);
			points.push_back(16.0f * glm::vec3(glm::dot((C_x4 * V), U), glm::dot((C_y4 * V), U), glm::dot((C_z4 * V), U)));
			//normals.push_back(glm::vec3(40.0f, 69.0f, -105.0f));
			if (t1 > 194.0f || t2 < 5.0f || t1 < 5.0f || t2 > 194.0f) {
				edge.push_back(50.0f);
			}
			else {
				edge.push_back(0.0f);
			}
			glm::vec4 U_2 = glm::vec4(pow(3 * t1, 2) / pow(200.0f, 3), pow(2 * t1, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			glm::vec4 V_2 = glm::vec4(pow(3 * t2, 2) / pow(200.0f, 3), pow(2 * t2, 1) / pow(200.0f, 2), (1 / 200.0f), 0);
			glm::vec3 test = glm::cross(glm::vec3(glm::dot((C_x4 * V), U_2), glm::dot((C_y4 * V), U_2), glm::dot((C_z4 * V), U_2)),
			glm::vec3(glm::dot((C_x4 * V_2), U), glm::dot((C_y4 * V_2), U), glm::dot((C_z4 * V_2), U)));
			//cout << test.x << endl << test.y << endl << test.z << endl << endl;
			normals.push_back(glm::cross(glm::vec3(glm::dot((C_x4 * V), U_2), glm::dot((C_y4 * V), U_2), glm::dot((C_z4 * V), U_2)),
				glm::vec3(glm::dot((C_x4 * V_2), U), glm::dot((C_y4 * V_2), U), glm::dot((C_z4 * V_2), U))));
			sNum.push_back(4.0f);
		}	
	}



	curveShader = Window::getCurveShader();

	glGenVertexArrays(1, &curveVao);
	glGenBuffers(1, &curveVbo);

	glBindVertexArray(curveVao);
	glBindBuffer(GL_ARRAY_BUFFER, curveVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(),
		points.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);


	//Normals
	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(),
		normals.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0); 


	glGenBuffers(1, &otherVbo);
	glBindBuffer(GL_ARRAY_BUFFER, otherVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sNum.size(),
		sNum.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (void*)0);

	glGenBuffers(1, &otherVbo2);
	glBindBuffer(GL_ARRAY_BUFFER, otherVbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * edge.size(),
		edge.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (void*)0);
}

void Curve::draw(glm::mat4 C)
{
	glm::mat4 MV = Window::view;


	GLuint pcProj = glGetUniformLocation(curveShader, "projection");
	GLuint pcModelView = glGetUniformLocation(curveShader, "modelview");

	glUniformMatrix4fv(pcProj, 1, GL_FALSE, glm::value_ptr(Window::projection));
	glUniformMatrix4fv(pcModelView, 1, GL_FALSE, glm::value_ptr(MV));

	glBindVertexArray(curveVao);
	glPointSize(3.0f);
	glDrawArrays(GL_POINTS, 0, points.size());
	glBindVertexArray(0);
}

void Curve::update()
{
}

void Curve::addPoints(std::vector<glm::vec3> p)
{
	for (glm::vec3 point: p) {
		points.push_back(point);
	}
}
