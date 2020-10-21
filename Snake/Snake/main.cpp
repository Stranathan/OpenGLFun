/*
	Main program is just instantiates a game class and has a connected windowing system.
*/

#include "Game.h"
#include "utils.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 800;

Game Snake(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Something something snake", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	centerWindow(window, primary);

	// ----------- glad: load all OpenGL function pointers -----------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ----------- Init Game -----------
	Snake.Init();

	// ----------- Init Time -----------
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float globalRunTime = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// ----------- Time Update -----------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		globalRunTime += deltaTime;
		// ----------- # -----------
		glfwPollEvents();
		// ----------- Run Game -----------
		Snake.Run(deltaTime, globalRunTime);
		// ----------- # -----------
		glfwSwapBuffers(window);
	}
	ResourceManager::clear();
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose(window, true);
	if ( key < 1024 && key >= 0 )
	{	
		if ( action == GLFW_PRESS )
			Snake.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Snake.Keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

