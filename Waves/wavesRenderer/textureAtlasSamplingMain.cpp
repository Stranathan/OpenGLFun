//// std includes
//#include <iostream>
//#include <vector>
//#include <string>
//
//// windowing
//#include <SFML/Window.hpp>
//
//// OpenGL loader
//#include <glad/glad.h>
//
//// Math library
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//// Rendering
//#include "Rendering/shader.h"
//#include "Rendering/texture.h"
//#include "Rendering/textureAtlas.h"
//#include "Rendering/shapeMaker.hpp"
//
//// BLAH
//#include "constants.h"
//
//// Testing
//#include <random>
//
//using namespace std;
//
//// SHAPES
//namespace wabi
//{
//	template <int N>
//	struct Polygon 
//	{
//		glm::vec2 position;
//		glm::vec2 vertices[N];
//		glm::vec2 texCoords[N];
//		glm::vec2 model[N];
//		int size = N;
//		float rotation = 0.f;
//	};
//
//	struct Rectangle : Polygon<4> 
//	{
//		Rectangle() {}
//		Rectangle(glm::vec2 p, float w, float h, float r = 0.f);
//
//		GLushort indices[6];
//
//		float width = 0.f;
//		float height = 0.f;
//	};
//}
//
//struct Renderable
//{
//	GLuint vao;
//	GLuint buffer;
//	GLuint indexBuffer;
//	GLushort indexCount;
//	GLuint shader;
//};
//
//struct QueueRenderer
//{
//	GLuint textures[2];
//	Renderable renderables[1];
//
//	string iTime = "iTime";
//	string leWaveTimer = "waveTimer";
//	string iMouse = "iMouse";
//	string iResolution = "iResolution";
//	string projectionString = "projection";
//
//	string animationIndex = "index";
//
//	void render(float time, float waveTimer, glm::vec2 mousePos)
//	{
//		
//		glm::mat4 projection = glm::mat4(1.0f);
//		projection = glm::ortho(0.0f, static_cast<GLfloat>(STAGE_WIDTH),
//			0.0f, static_cast<GLfloat>(STAGE_HEIGHT), -1.0f, 1.0f);
//
//		// RENDER
//		for(int i = 0; i< 1; i++)
//		{
//			
//			// uniforms
//			glUseProgram(renderables[i].shader);
//			glUniformMatrix4fv(glGetUniformLocation(renderables[i].shader, projectionString.c_str()), 1, GL_FALSE, &projection[0][0]);
//			glUniform1f(glGetUniformLocation(renderables[i].shader, iTime.c_str()), time);
//			glUniform1f(glGetUniformLocation(renderables[i].shader, leWaveTimer.c_str()), waveTimer);
//			glUniform2f(glGetUniformLocation(renderables[i].shader, iMouse.c_str()), mousePos.x, mousePos.y);
//			glUniform2f(glGetUniformLocation(renderables[i].shader, iResolution.c_str()), (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
//			// animation testing:
//			//glUniform1f(glGetUniformLocation(renderables[i].shader, animationIndex.c_str()), (time + );
//
//
//			glBindVertexArray(renderables[i].vao);
//			glDrawElements(GL_TRIANGLES, renderables[i].indexCount, GL_UNSIGNED_SHORT, 0);
//		}
//	}
//	void clear()
//	{
//		glClearColor(0.78f, 0.62f, 0.78f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//	}
//	void resize(int width, int height)
//	{
//		glViewport(0, 0, width, height);
//	}
//};
//
//// OBJECTS
//struct Platform
//{
//	wabi::Rectangle shape;
//	//Rendering::Shape shape;
//};
//struct Sea
//{
//	glm::vec2 vertices[100];
//	// number of steps/ rects = (vertexCount - 2) / 2;
//	// for each step, there are 6 indices
//	GLushort indices[294];
//};
//struct Rock
//{
//	Rendering::Shape shape;
//};
//
//struct Boat
//{
//	wabi::Rectangle shape;
//};
//
//struct Stage
//{
//	QueueRenderer renderer;
//	Boat boat;
//};
//
//// MOCK FUNCTION PROTOTYPES
//void initLevelRenderData(Stage& stage);
//void drawStage(Stage& stage, float time, float waveTimer, glm::vec2 mousePos);
//
//int main()
//{
//	//INIT SFML & OpenGL
//	sf::ContextSettings settings;
//
//	settings.antialiasingLevel = 8;
//	settings.depthBits = 24;
//	settings.stencilBits = 8;
//	settings.majorVersion = 4;
//	settings.minorVersion = 1;
//	settings.attributeFlags = sf::ContextSettings::Core;
//
//	sf::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "VV A V E S", sf::Style::Default, settings);
//
//	window.setFramerateLimit((int)(1.0f / FRAME_RATE));
//
//	if (!gladLoadGL())
//	{
//		std::cout << "Failed to initialize OpenGL context" << std::endl;
//		return -1;
//	}
//	// INIT OBJECTS & VARIABLES
//	sf::Clock drawClock; // starts the clock
//
//	sf::Event event;
//	sf::Clock shaderClock;
//	sf::Clock shaderClock2;
//	float deltaTime = 0;
//	float drawDelta;
//
//	glm::vec2 mousePos;
//
//	Stage aStage;
//	
//	// RNG FOR TESTING
//	std::random_device rd;  // seed for the random number engine
//	std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
//	std::uniform_int_distribution<> dis(1, 100);
//
//	// LOAD LEVEL
//	initLevelRenderData(aStage);
//
//	// APPLICATION LOOP
//	while (window.isOpen())
//	{
//		// EVENT HANDLING
//		while (window.pollEvent(event))
//		{
//			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//			{
//				mousePos = glm::vec2((2.0f * (float)(sf::Mouse::getPosition(window).x / (float)SCREEN_WIDTH)) - 1.0f,
//					-1.0f * ((2.0f * (float)sf::Mouse::getPosition(window).y / (float)SCREEN_HEIGHT) - 1.0f));
//
//				shaderClock2.restart();
//			}
//
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//			else if (event.type == sf::Event::Resized)
//			{
//				aStage.renderer.resize(event.size.width, event.size.height);
//				SCREEN_WIDTH = event.size.width;
//				SCREEN_HEIGHT = event.size.height;
//			}
//		}
//		// DRAW LOOP
//		drawDelta = drawClock.getElapsedTime().asSeconds();
//		if (drawDelta >= FRAME_RATE) 
//		{
//			drawStage(aStage, shaderClock.getElapsedTime().asSeconds(), shaderClock2.getElapsedTime().asSeconds(), mousePos);
//			window.display();
//			drawClock.restart();
//
//			GLenum leError = glGetError();
//			if(leError != GL_NO_ERROR)
//			{
//				cout << leError << endl;
//			}
//		}
//	}
//}
//
//// send in a struct with uniforms probably
//void drawStage(Stage& stage, float time, float waveTimer, glm::vec2 mousePos)
//{
//	stage.renderer.clear();
//	stage.renderer.render(time, waveTimer, mousePos);
//}
//
//void initLevelRenderData(Stage& stage)
//{
//	Shader boatShader("Shaders/boatAnimationVert.glsl", "Shaders/boatAnimationFrag.glsl");
//	boatShader.bind();
//
//	
//	TextureAtlas boatTexture1;
//	boatTexture1.generate("Textures/horseJumpSpriteSheet.png");
//
//	TextureAtlas boatTexture2;
//	boatTexture2.generate("Textures/horseRunSpriteSheet.png");
//	
//	glUniform1i(glGetUniformLocation(boatShader.objectID, "texture1"), 0);
//	glUniform1i(glGetUniformLocation(boatShader.objectID, "texture2"), 1);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, boatTexture1.objectID);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, boatTexture2.objectID);
//
//	GLfloat vertices[] =
//	{
//		// positions          // colors           // texture coords
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//	};
//	GLushort indices[] = 
//	{
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//	unsigned int VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	// texture coord attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	
//	// save stuff to render:
//	Renderable aBoat;
//
//	aBoat.vao = VAO;
//	aBoat.buffer = VBO;
//	aBoat.indexBuffer = EBO;
//	aBoat.indexCount = 6;
//	aBoat.shader = boatShader.objectID;
//
//	stage.renderer.renderables[0] = aBoat;
//}