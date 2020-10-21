#pragma once

#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "resourceManager.h"
#include "renderer.h"
#include "Snake.h"

enum GameState 
{
	GAME_ACTIVE,
	GAME_PAUSED,
	GAME_OVER
};

class Game
{
public:
	unsigned int WIDTH, HEIGHT;
	GameState State;
	bool Keys[1024];

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render(float globalRunTime);

	void Run(float deltaTime, float globalRunTime);
};

