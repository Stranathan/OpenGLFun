
// std
#include <iostream>
// middleware
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// my stuff
#include "geometry.hpp"
#include "shaderManager.hpp"
#include "vaoManager.hpp"
#include "settings.hpp"
#include "renderable.hpp"
#include "renderer.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Let's go", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);	
	glfwSetCursorPosCallback(window, cursor_position_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ObjectManager start up
	// physics manager start up
	// renderer start up

	renderer theRenderer = renderer(camPos);
	theRenderer.makeARectangle(glm::vec2(5.0f, 0.0f));

	float processTimeAccumulator = 0.0f;
	float frameTimeAccumulator = 0.0f;
	float currentTime = 0.0f;
	float renderTime = 0.0f;
	float physicsTime = 0.0f;
	// float timeForRenderLoop = 0.0f; // cout for fps check

	while (!glfwWindowShouldClose(window))
	{
		float newTime = float(glfwGetTime());
		float processTime = newTime - currentTime;
		currentTime = newTime;
		processTimeAccumulator += processTime;

		// Render Loop -- only render every frameDeltaTime
		while (processTimeAccumulator >= frameDeltaTime)
		{
			// cout for fps check
			/*float newRenderTime = float(glfwGetTime());
			float renderProcessTime = newRenderTime - timeForRenderLoop;
			timeForRenderLoop = newRenderTime;
			std::cout << 1.0f / renderProcessTime << std::endl;*/

			processTimeAccumulator -= frameDeltaTime;
			frameTimeAccumulator += frameDeltaTime;
			renderTime += frameDeltaTime;

			// input
			processInput(window);

			// physics Loop
			while (frameTimeAccumulator >= physicsDeltaTime)
			{
				frameTimeAccumulator -= physicsDeltaTime;
				physicsTime += physicsDeltaTime;
				// physicsWorld.update(physicsTime)
			}

			theRenderer.render(renderTime);

			// glfw stuff
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		//std::cout << "pressed dawg" << std::endl;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xPos = 2.0f * float(xpos) / float(SCR_WIDTH) - 1.0f; // scale to ndc
	float yPos = -2.0f * float(ypos) / float(SCR_HEIGHT) + 1.0f;

	xPos *= orthoWidth / 2.0f;
	yPos *= orthoHeight / 2.0f; // scale to world
	//std::cout << "(" << xPos << ",  " << yPos << ")" << std::endl;
}

