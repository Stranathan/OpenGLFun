// std includes
#include <iostream>
#include <vector>
#include <string>

// windowing
#include <SFML/Window.hpp>

// OpenGL loader
#include <glad/glad.h>

// Math library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Rendering
#include "Rendering/shader.h"
#include "Rendering/texture.h"
#include "Rendering/shapeMaker.hpp"

// BLAH
#include "constants.h"

// Testing
#include <random>

using namespace std;

// SHAPES
namespace wabi
{
	template <int N>
	struct Polygon
	{
		glm::vec2 position;
		glm::vec2 vertices[N];
		glm::vec2 texCoords[N];
		glm::vec2 model[N];
		int size = N;
		float rotation = 0.f;
	};

	struct Rectangle : Polygon<4>
	{
		Rectangle() {}
		Rectangle(glm::vec2 p, float w, float h, float r = 0.f);

		GLushort indices[6];

		float width = 0.f;
		float height = 0.f;
	};
}

struct Renderable
{
	GLuint* vao;
	GLuint* buffer;
	GLuint* indexBuffer;
	GLushort indexCount;
	GLuint* shader;

	// textures should be set globablly wherever as texture atlas, right now I'm setting one in PLATFORM LAYER
};

struct QueueRenderer
{
	std::vector<Renderable*> renderables;

	string iTime = "iTime";
	string leWaveTimer = "waveTimer";
	string iMouse = "iMouse";
	string iResolution = "iResolution";

	void render(float time, float waveTimer, glm::vec2 mousePos)
	{
		// ------ UNIFORMS ------

		// PROJECTION MATRIX --> NDC
		string projectionString = "projection";
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::ortho(0.0f, static_cast<GLfloat>(STAGE_WIDTH),
			0.0f, static_cast<GLfloat>(STAGE_HEIGHT), -1.0f, 1.0f);

		// QUEUE RENDER
		//for (int i = 0; i < renderables.size(); i++)
		for (int i = 0; i < renderables.size(); i++)
		{
			glUseProgram(*renderables[i]->shader);
			glUniformMatrix4fv(glGetUniformLocation(*renderables[i]->shader, projectionString.c_str()), 1, GL_FALSE, &projection[0][0]);
			glUniform1f(glGetUniformLocation(*renderables[i]->shader, iTime.c_str()), time);
			glUniform1f(glGetUniformLocation(*renderables[i]->shader, leWaveTimer.c_str()), waveTimer);
			glUniform2f(glGetUniformLocation(*renderables[i]->shader, iMouse.c_str()), mousePos.x, mousePos.y);
			glUniform2f(glGetUniformLocation(*renderables[i]->shader, iResolution.c_str()), (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);


			glBindVertexArray(*renderables[i]->vao);
			glDrawElements(GL_TRIANGLES, renderables[i]->indexCount, GL_UNSIGNED_SHORT, 0);
		}
	}
	void clear()
	{
		glClearColor(0.78f, 0.62f, 0.78f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void resize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}
};

// OWEN OBJECTS
struct Platform
{
	wabi::Rectangle shape;
	//Rendering::Shape shape;
};
struct Sea
{
	glm::vec2 vertices[100];
	// number of steps/ rects = (vertexCount - 2) / 2;
	// for each step, there are 6 indices
	GLushort indices[294];
};
struct Rock
{
	Rendering::Shape shape;
};

struct Stage
{
	// Rendering:
	QueueRenderer renderer;

	// Owen
	std::vector<Platform> platforms;
	//std::vector<Sea> seas;
	Sea seas[1];
};

// MOCK FUNCTION PROTOTYPES
void initLevelRenderData(Stage* stage);
void drawStage(Stage* stage, float time, float waveTimer, glm::vec2 mousePos);

int main()
{
	//INIT SFML & OpenGL
	sf::ContextSettings settings;

	settings.antialiasingLevel = 8;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 1;
	settings.attributeFlags = sf::ContextSettings::Core;

	sf::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "VV A V E S", sf::Style::Default, settings);
	window.setFramerateLimit((int)(1.0f / FRAME_RATE));

	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}
	// INIT SFML OBJECTS & VARIABLES
	sf::Clock drawClock; // starts the clock
	float drawDelta;
	sf::Event event;
	sf::Clock shaderClock; // starts the clock
	sf::Clock shaderClock2; // starts the clock
	float deltaTime = 0;
	glm::vec2 mousePos;

	// MOCK UP OF OWEN STUFF
	//  STAGE --> PLATFORMS, SEA
	Stage aStage;

	// PLATFORM INDEX WINDING ORDER
	/* (3)-------(2)
		-----------
		-----------
		-----------
	   (0)-------(1)
	*/

	// RNG FOR TESTING
	std::random_device rd;  // seed for the random number engine
	std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 100);

	// ------ PLATFORM LAYER ------
	// ---MAKING SOME PLATFORMS ---
	// ----------------------------
	unsigned short offset = 0;
	for (int j = 0; j < 10; j++)
	{
		Platform platform;
		wabi::Rectangle rect;

		rect.width = 0.4f * (float)dis(gen);
		rect.height = 0.2f * (float)dis(gen);
		rect.position = glm::vec2(dis(gen), dis(gen));
		rect.vertices[0] = rect.position;
		rect.vertices[1] = glm::vec2(rect.position.x + rect.width, rect.position.y);
		rect.vertices[2] = glm::vec2(rect.position.x + rect.width, rect.position.y + rect.height);
		rect.vertices[3] = glm::vec2(rect.position.x, rect.position.y + rect.height);

		rect.texCoords[0] = glm::vec2(0.0f, 0.0f);
		rect.texCoords[1] = glm::vec2(1.0f, 0.0f);
		rect.texCoords[2] = glm::vec2(1.0f, 1.0f);
		rect.texCoords[3] = glm::vec2(0.0f, 1.0f);

		rect.indices[0] = offset + 0;
		rect.indices[1] = offset + 1;
		rect.indices[2] = offset + 2;
		rect.indices[3] = offset + 2;
		rect.indices[4] = offset + 3;
		rect.indices[5] = offset + 0;

		platform.shape = rect;
		aStage.platforms.push_back(platform);

		offset += 4;
	}

	// --------- SEA LAYER --------
	// --------MAKING A SEA -------
	// ----------------------------
	// PLATFORM INDEX WINDING ORDER
	/*	(0)----(2)-----(4)....(n-1)
		--------------------------
		--------------------------
		(1)----(3)-----(5)......(n)
	*/
	Sea aSea;
	int vertexCount = 100;
	int numSteps = (vertexCount - 2) / 2;
	float stepLength = (float)STAGE_WIDTH / (float)numSteps;

	// kinda hardcoded numSteps == num quads == (vertexCount - 2) / 2;
	//				  vertexCount == the size of the vertices array in a sea struct
	for (int i = 0; i < numSteps + 1; i++)
	{
		// even vertices
		aSea.vertices[2 * i] = glm::vec2(i * stepLength, SEA_HEIGHT);
		// odd vertices
		aSea.vertices[2 * i + 1] = glm::vec2(i * stepLength, 0.0f);
	}

	GLuint seaIndexOffset = 0;
	for (int j = 0; j < 6 * (vertexCount - 2) / 2; j += 6)
	{
		aSea.indices[j] = seaIndexOffset;
		aSea.indices[j + 1] = seaIndexOffset + 1;
		aSea.indices[j + 2] = seaIndexOffset + 2;
		aSea.indices[j + 3] = seaIndexOffset + 2;
		aSea.indices[j + 4] = seaIndexOffset + 1;
		aSea.indices[j + 5] = seaIndexOffset + 3;

		seaIndexOffset += 2;

		// cout
		/*cout << "quad " << j / 6 << " : " << aSea.indices[j] << ","
			<< aSea.indices[j + 1] << ","
			<< aSea.indices[j + 2] << ","
			<< aSea.indices[j + 3] << ","
			<< aSea.indices[j + 4] << ","
			<< aSea.indices[j + 5] << endl;*/
	}
	aStage.seas[0] = aSea;

	//--------------------------------------
	initLevelRenderData(&aStage);
	//--------------------------------------

	// APPLICATION LOOP
	while (window.isOpen())
	{
		// EVENT HANDLING
		while (window.pollEvent(event))
		{
			//NDC mouse Coords:
			/*mousePos = glm::vec2((2.0f * (float)(sf::Mouse::getPosition(window).x / (float)SCREEN_WIDTH)) - 1.0f,
				-1.0f * ((2.0f * (float)sf::Mouse::getPosition(window).y / (float)SCREEN_HEIGHT) - 1.0f));*/

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mousePos = glm::vec2((2.0f * (float)(sf::Mouse::getPosition(window).x / (float)SCREEN_WIDTH)) - 1.0f,
					-1.0f * ((2.0f * (float)sf::Mouse::getPosition(window).y / (float)SCREEN_HEIGHT) - 1.0f));

				shaderClock2.restart();
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				aStage.renderer.resize(event.size.width, event.size.height);
				SCREEN_WIDTH = event.size.width;
				SCREEN_HEIGHT = event.size.height;
			}
		}
		// DRAW LOOP
		drawDelta = drawClock.getElapsedTime().asSeconds();
		if (drawDelta >= FRAME_RATE)
		{

			drawStage(&aStage, shaderClock.getElapsedTime().asSeconds(), shaderClock2.getElapsedTime().asSeconds(), mousePos);
			window.display();
			drawClock.restart();

			GLenum leError = glGetError();
			if (leError != GL_NO_ERROR)
			{
				cout << leError << endl;
			}
		}
	}
}

void drawStage(Stage* stage, float time, float waveTimer, glm::vec2 mousePos)
{
	// Note: this is only meaningful if we're not using every pixel each frame, using a background makes this a waste
	//stage->renderer.clear();
	stage->renderer.render(time, waveTimer, mousePos);
}

void initLevelRenderData(Stage* stage)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ------------------------------------------
	// --------- BACKGROUND IMAGE LAYER ---------
	// ------------------------------------------

	Shader backgroundShader("Shaders/backgroundVert.glsl", "Shaders/backgroundFrag.glsl");

	GLfloat vertices[] =
	{
		 0.0f, STAGE_HEIGHT,
		 0.0f, 0.0f,
		 STAGE_WIDTH,  STAGE_HEIGHT,
		 STAGE_WIDTH,  0.0f
	};
	GLushort indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	GLuint backgroundVao, backgroundBuffer, backgroundIndexBuffer;

	glGenVertexArrays(1, &backgroundVao);
	glGenBuffers(1, &backgroundBuffer);
	glGenBuffers(1, &backgroundIndexBuffer);

	glBindVertexArray(backgroundVao);

	glBindBuffer(GL_ARRAY_BUFFER, backgroundBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backgroundIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// save stuff to render
	Renderable* background = new Renderable();

	GLuint* backgroundShaderID = new GLuint(backgroundShader.objectID);
	GLuint* vaoID = new GLuint(backgroundVao);
	GLuint* bufferID = new GLuint(backgroundBuffer);
	GLuint* indexBufferID = new GLuint(backgroundIndexBuffer);

	background->shader = backgroundShaderID;
	background->vao = vaoID;
	background->buffer = bufferID;
	background->indexBuffer = indexBufferID;
	background->indexCount = 6;
	stage->renderer.renderables.push_back(background);

	////------------------ PLATFORM LAYER----------------------
	////--------------BATCHING PLATFORM DATA---------------------

	Shader platformsShader("Shaders/platformsVert.glsl", "Shaders/platformsFrag.glsl");

	Texture platformTexture;
	platformTexture.generate("Textures/shippingContainer.jpg");
	GLuint* platformTextureID = new GLuint(platformTexture.objectID);
	glBindTexture(GL_TEXTURE_2D, platformTexture.objectID);

	GLuint theBuffer, platformsVAO, theIndexBuffer;
	glGenVertexArrays(1, &platformsVAO);
	glGenBuffers(1, &theBuffer);
	glGenBuffers(1, &theIndexBuffer);

	glBindVertexArray(platformsVAO);
	glBindBuffer(GL_ARRAY_BUFFER, theBuffer);
	// each platform has 4 vertices which has 2 floats & 4 vertices with 2 texture coordinates --> 16
	// define size of vertices, tex coords, colors etc once you settle on implementation with O-dawg
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stage->platforms.size() * 16, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBuffer);
	// each platform has 6 indices which has 1 ushort --> 6
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * stage->platforms.size() * 6, NULL, GL_STATIC_DRAW);

	GLushort indexCount = 0; // save this for making the correct argument in the draw call
	for (int i = 0; i < stage->platforms.size(); i++)
	{
		/*glBufferSubData(GLenum target,
			GLintptr offset,
			GLsizeiptr size,
			const GLvoid * data);*/
		glBufferSubData(GL_ARRAY_BUFFER, i * (sizeof(GLfloat) * 16), sizeof(GLfloat) * 8, stage->platforms[i].shape.vertices); // vertex data
		glBufferSubData(GL_ARRAY_BUFFER, i * (sizeof(GLfloat) * 16) + sizeof(GLfloat) * 8, sizeof(GLfloat) * 8, stage->platforms[i].shape.texCoords); // tex coords
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i * sizeof(GLushort) * 6, sizeof(GLushort) * 6, stage->platforms[i].shape.indices);
		indexCount += 6;
	}

	// set attribs for shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // vertex attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(GLfloat) * 8)); // texture attribute
	glEnableVertexAttribArray(1);

	// save stuff to render
	Renderable* platforms = new Renderable();

	GLuint* platformsShaderID = new GLuint(platformsShader.objectID);
	GLuint* platformsVaoID = new GLuint(platformsVAO);
	GLuint* platformsBufferID = new GLuint(theBuffer);
	GLuint* platformsIboID = new GLuint(theIndexBuffer);

	platforms->shader = platformsShaderID;
	platforms->vao = platformsVaoID;
	platforms->buffer = platformsBufferID;
	platforms->indexBuffer = platformsIboID;
	platforms->indexCount = indexCount;

	stage->renderer.renderables.push_back(platforms);

	// -------------------------------------------------------
	// --------- SEA FULL SCREEN FRAG REFACTOR LAYER ---------
	// -------------------------------------------------------

	Shader seaRefactorShader("Shaders/seaVert.glsl", "Shaders/seaFrag.glsl");

	GLfloat vertices2[] =
	{
		 0.0f, STAGE_HEIGHT,
		 0.0f, 0.0f,
		 STAGE_WIDTH,  STAGE_HEIGHT,
		 STAGE_WIDTH,  0.0f
	};
	GLushort indices2[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	GLuint seaRefactorVao, seaRefactorBuffer, seaRefactorIndexBuffer;

	glGenVertexArrays(1, &seaRefactorVao);
	glGenBuffers(1, &seaRefactorBuffer);
	glGenBuffers(1, &seaRefactorIndexBuffer);

	glBindVertexArray(seaRefactorVao);

	glBindBuffer(GL_ARRAY_BUFFER, seaRefactorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, seaRefactorIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	// 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// unbinding is unnecessary I think, but to be safe
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Save stuff to render
	Renderable* sea = new Renderable();
	GLuint* seaRefactorShaderID = new GLuint(seaRefactorShader.objectID);
	GLuint* seaRefactorVaoID = new GLuint(seaRefactorVao);
	GLuint* seaRefactorBufferID = new GLuint(seaRefactorVao);
	GLuint* seaRefactorIndexBufferID = new GLuint(seaRefactorVao);

	sea->shader = seaRefactorShaderID;
	sea->vao = seaRefactorVaoID;
	sea->buffer = seaRefactorBufferID;
	sea->indexBuffer = seaRefactorIndexBufferID;
	sea->indexCount = 6;

	stage->renderer.renderables.push_back(sea);

}
