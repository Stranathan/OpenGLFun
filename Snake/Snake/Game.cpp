#include "Game.h"

Renderer* renderer;
Snake* theSnake;

Game::Game(unsigned int width, unsigned int height)
	: WIDTH(width), HEIGHT(height), Keys(), State(GAME_ACTIVE)
{
}
Game::~Game()
{
	delete renderer;
	delete theSnake;
}
void Game::Init()
{
	glm::vec2 screenDimensions = glm::vec2(WIDTH, HEIGHT);
	renderer = new Renderer(screenDimensions);
	theSnake = new Snake(renderer->renderables, screenDimensions);
}
void Game::ProcessInput(float deltaTime)
{
	if (this->Keys[GLFW_KEY_A])
	{
		if(renderer->renderables.size() != 0)
		{
			theSnake->moveLeft();
		}
	}
	if (this->Keys[GLFW_KEY_D])
	{
		if (renderer->renderables.size() != 0)
		{
			theSnake->moveRight();
		}
	}
	if (this->Keys[GLFW_KEY_W])
	{
		if (renderer->renderables.size() != 0)
		{
			theSnake->moveUp();
		}
	}
	if (this->Keys[GLFW_KEY_S])
	{
		if (renderer->renderables.size() != 0)
		{
			theSnake->moveDown();
		}
	}
}
void Game::Update(float deltaTime)
{
	theSnake->update(deltaTime, renderer->renderables);
}
void Game::Render(float globalRunTime)
{
	if (this->State == GAME_ACTIVE)
	{
		renderer->render(globalRunTime);
	}
}
void Game::Run(float deltaTime, float globalRunTime)
{
	ProcessInput(deltaTime);
	Update(deltaTime);
	Render(globalRunTime);
}
