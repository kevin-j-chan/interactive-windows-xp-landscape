#include "Window.h"

/*
 * Declare your variables below. Unnamed namespace is used here to avoid
 * declaring global or static variables.
 */
namespace
{
	int width, height;
	std::string windowTitle("GLFW Project");

	Object* currentObj1;
	Cube* cube;
	
	Terrain* terrain;

	glm::vec3 eye(0, 150, 100); // Camera position.
	glm::vec3 center(0, 150, 0); // The point we are looking at.
	glm::vec3 up(0, 1, 0); // The up direction of the camera.
	float fovy = 60;
	float near = 1;
	float far = 2000;
	glm::mat4 view = glm::lookAt(eye, center, up); // View matrix, defined by eye, center and up.
	glm::mat4 projection; // Projection matrix.

	float yaw = -90.0f;
	float pitch = 0.0f;

	GLuint program; // The shader program id.
	GLuint programSkybox;

	GLuint projectionLoc; // Location of projection in shader.
	GLuint viewLoc; // Location of view in shader.
	GLuint modelLoc; // Location of model in shader.
	GLuint colorLoc; // Location of color in shader.

	bool moveForward;
	bool moveBack;
	bool moveLeft;
	bool moveRight;

	bool firstMouse;

	bool drawTerrain = true;
}

bool Window::initializeProgram()
{
	// Create a shader program with a vertex shader and a fragment shader.
	program = LoadShaders("shaders/shader.vert", "shaders/shader.frag");

	// Check the shader programs.
	if (!program)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}

	// Activate the shader program.
	glUseProgram(program);
	// Get the locations of uniform variables.
	projectionLoc = glGetUniformLocation(program, "projection");
	viewLoc = glGetUniformLocation(program, "view");
	modelLoc = glGetUniformLocation(program, "model");
	colorLoc = glGetUniformLocation(program, "color");

	programSkybox = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
	glUniform1f(glGetUniformLocation(programSkybox, "skybox"), 0);

	return true;
}

bool Window::initializeObjects()
{
	cube = new Cube(50.0f);
	currentObj1 = cube;

	terrain = new Terrain();
	terrain->generate();

	return true;
}

void Window::cleanUp()
{
	// Deallcoate the objects.
	delete cube;

	delete terrain;
	// Delete the shader programs.
	glDeleteProgram(program);
	glDeleteProgram(programSkybox);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int w, int h)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height);
#endif
	width = w;
	height = h;

	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	projection = glm::perspective(glm::radians(fovy),
		(float)width / (float)height, near, far);
}

void Window::idleCallback()
{
	// Perform any updates as necessary. 
	currentObj1->update();

	glm::vec3 dir;
	if (moveForward) {
		dir = center - eye;
		dir = glm::normalize(dir);
		dir *= 0.01;
		eye += dir;
		center += dir;
		view = glm::lookAt(eye, center, up);
	}
	if (moveBack) {
		dir = center - eye;
		dir = glm::normalize(dir);
		dir *= 0.01;
		eye -= dir;
		center -= dir;
		view = glm::lookAt(eye, center, up);
	}
	if (moveLeft) {
		dir = center - eye;
		dir = glm::normalize(glm::cross(dir, up));
		dir *= 0.01;
		eye -= dir;
		center -= dir;
		view = glm::lookAt(eye, center, up);
	}
	if (moveRight) {
		dir = center - eye;
		dir = glm::normalize(glm::cross(dir, up));
		dir *= 0.01;
		eye += dir;
		center += dir;
		view = glm::lookAt(eye, center, up);
	}
}

void Window::displayCallback(GLFWwindow* window)
{

	glUseProgram(program);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	if (drawTerrain) {
		glm::mat4 model = glm::mat4(1);
		model = glm::scale(glm::vec3(256.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		terrain->draw();
	}

	glUseProgram(programSkybox);
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	currentObj1->draw();

	// Gets events, including input such as keyboard and mouse or window resizing.
	glfwPollEvents();
	// Swap buffers.
	glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press.
	if (action == GLFW_PRESS)
	{
		// Uppercase key presses (shift held down + key press)
		if (mods == GLFW_MOD_SHIFT) {
			switch (key) {
			default:
				break;
			}
		}

		// Deals with lowercase key presses
		else {
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				// Close the window. This causes the program to also terminate.
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;


			case GLFW_KEY_W:
				moveForward = true;
				break;
			case GLFW_KEY_S:
				moveBack = true;
				break;
			case GLFW_KEY_A:
				moveLeft = true;
				break;
			case GLFW_KEY_D:
				moveRight = true;
				break;
			case GLFW_KEY_T:
				terrain->generate();
				break;
			case GLFW_KEY_0:
				drawTerrain = !drawTerrain;
				break;
			default:
				break;
			}
		}
	}
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			moveForward = false;
			break;
		case GLFW_KEY_S:
			moveBack = false;
			break;
		case GLFW_KEY_A:
			moveLeft = false;
			break;
		case GLFW_KEY_D:
			moveRight = false;
			break;
		default:
			break;
		}
	}
}

void Window::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	static glm::vec3 lastPoint = glm::vec3(0.0f, 0.0f, 0.0f);

	if (firstMouse) {
		lastPoint.x = xpos;
		lastPoint.y = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastPoint.x;
	float yoffset = lastPoint.y - ypos; // reversed since y-coordinates go from bottom to top
	lastPoint.x = xpos;
	lastPoint.y = ypos;

	float sensitivity = 0.5f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	center = eye + glm::normalize(front);

	view = glm::lookAt(eye, center, up);

}