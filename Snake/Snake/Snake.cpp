#include "Snake.h"

Snake::Snake(std::vector<Renderable>& renderersRenderables, glm::vec2 viewPort)
	: screenDimensions(viewPort)
{
	reset();
	init(renderersRenderables);
}

/*
	Resource of Renderable is always moved to renderer, this in turn is freed when renderer is destroyed
	
	Not scalable design choice, but renderables and positions talk about the same objects up to the intial offset of the background
	renderables[0] -> background
	renderables[1] -> food
	positions[0] -> food
*/

void Snake::init(std::vector<Renderable>& renderersRenderables)
{
	// ------------------ Food Circle ------------------
	// seed pseudo rng
	std::srand(std::time(0));
	float randomPosX = 2.0f * (float)(std::rand() % 15) - 15.0f; // magic number needs to be changed -- game width/ dimensions w/e
	float randomPosY = 2.0f * (float)(std::rand() % 15) - 15.0f; // magic number needs to be changed -- game height

	// make a renderable & push into renderables
	glm::vec4 foodCircle = glm::vec4(randomPosX, randomPosY, 0.0f, 1.0);
	positions.push_back(foodCircle);
	glm::mat4 foodTransform = glm::mat4(1.0f);
	foodTransform = glm::translate(foodTransform, glm::vec3(randomPosX, randomPosY, 0.0f));
	Shader foodShader = ResourceManager::getShader("food"); // made in renderer init
	Renderable food(foodTransform, circle, GL_TRIANGLES, foodShader, screenDimensions);

	// set uniform value for food shader
	food.m_uniforms.pos = glm::vec3(randomPosX, randomPosY, 0.0f);
	renderersRenderables.push_back(std::move(food));

	// update last renderable index count for eating logic
	lastRenderableIndex += 1;

	// ------------------ Snake Head Circle ------------------
	// make a renderable & push into renderables
	Shader snakeHeadShader = ResourceManager::getShader("snakeHead"); // made in renderer init
	Renderable snakeHead(glm::mat4(1.0f), circle, GL_TRIANGLES, snakeHeadShader, screenDimensions);
	snakeHead.m_uniforms.index = lastRenderableIndex;
	renderersRenderables.push_back(std::move(snakeHead));
	// mirror in position
	glm::vec4 firstCirclePos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0);
	positions.push_back(firstCirclePos);

	lastRenderableIndex += 1;


	for(int i = 1; i < baseLength; i++)
	{
		// make a renderable & push into renderables
		Shader snakeBodyShader = ResourceManager::getShader("snakeBody"); // made in renderer init
		Renderable snakeBody(glm::mat4(1.0f), circle, GL_TRIANGLES, snakeBodyShader, screenDimensions);
		snakeBody.m_uniforms.index = lastRenderableIndex;
		renderersRenderables.push_back(std::move(snakeBody));
		// mirror in position
		glm::vec4 secondCirclePos = glm::vec4(-2.0f * i * radius, 0.0f, 0.0f, 1.0);
		positions.push_back(secondCirclePos);
		// offset its model transform by two of its radius
		glm::mat4 secondCircleTranslation = glm::mat4(1.0f);
		secondCircleTranslation = glm::translate(secondCircleTranslation, glm::vec3(secondCirclePos.x, secondCirclePos.y, secondCirclePos.z));
		renderersRenderables[2 + i].model *= secondCircleTranslation;
		// update last renderable index count for eating logic
		lastRenderableIndex += 1;

		std::cout << snakeBody.m_uniforms.index << std::endl;
	}
}

void Snake::update(float deltaTime, std::vector<Renderable>& renderersRenderables)
{
	// ------------------ Delta Translation from Key Input ------------------
	glm::mat4 firstSphereTranslation = glm::mat4(1.0f);
	firstSphereTranslation = glm::translate(firstSphereTranslation, glm::vec3(speed * velocity.x * deltaTime, speed * velocity.y * deltaTime, 0.0f));
	positions[1] = firstSphereTranslation * positions[1]; // matrix multiplication order is maintained in glm;
	renderersRenderables[2].model *= firstSphereTranslation;

	// ------------------ Follow Logic ------------------
	for (int i = 3; i < renderersRenderables.size(); i++)
	{
		// get relative position vector between two array contiguous circles
		glm::vec3 relPosVec3 = glm::vec3(positions[i - 2].x - positions[i - 1].x, positions[i - 2].y - positions[i - 1].y, positions[i - 2].z - positions[i - 1].z);
		float len = glm::length(relPosVec3) - (2.0f * radius);
		relPosVec3 = len * glm::normalize(relPosVec3);
		glm::mat4 secondCircleTranslation = glm::mat4(1.0f);
		secondCircleTranslation = glm::translate(secondCircleTranslation, relPosVec3);
		positions[i - 1] = secondCircleTranslation * positions[i - 1];
		renderersRenderables[i].model *= secondCircleTranslation;
	}

	// ------------------ Check for Eating ------------------
	glm::vec3 distToFood = positions[0] - positions[1];
	float distSqaured = dot(distToFood, distToFood);
	if (distSqaured < 4.0 * radius * radius)
	{
		//std::cout << "got a hit bruv" << std::endl;
		float randomPosX = 2.0f * (float)(std::rand() % 10) - 10.0f; // magic number needs to be changed -- game width/ dimensions w/e
		float randomPosY = 2.0f * (float)(std::rand() % 10) - 10.0f; // magic number needs to be changed -- game height

		//positions[0] = glm::vec4(randomPosX, randomPosY, 0.0f, 1.0);;
		glm::mat4 foodTransform = glm::mat4(1.0f);
		glm::vec3 newRandPos = glm::vec3(0.0f);
		// exception
		if (positions[0].x + randomPosX < 25.0f && positions[0].x + randomPosX> -25.0f)
		{
			newRandPos.x = randomPosX;
		}
		else
		{
			randomPosX = 2.0f * (float)(std::rand() % 10) - 10.0f;
		}
		if (positions[0].y + randomPosY < 20.0f && positions[0].y + randomPosY > -20.0f)
		{
			newRandPos.y = randomPosY;
		}
		else
		{
			float randomPosY = 2.0f * (float)(std::rand() % 10) - 10.0f;
		}

		// Move the food to another spot
		foodTransform = glm::translate(foodTransform, newRandPos);
		positions[0] = foodTransform * positions[0];

		//std::cout << positions[0].x << ",  " << positions[0].y << std::endl;
		renderersRenderables[1].model *= foodTransform;
		renderersRenderables[1].m_uniforms.pos = glm::vec3(positions[0].x, positions[0].y, 0.0f);

		// ------------------ Make New Body Link ------------------ 
		makeNewBodyLink(renderersRenderables);
	}
}
void Snake::reset()
{
	baseLength = 5;

	// clear renderables except background and food

	velocity.x = 1.0f;
	velocity.y = 0.0f;
	velocity.z = 0.0f;
}

void Snake::makeNewBodyLink(std::vector<Renderable>& renderersRenderables)
{
	// 1) make new body link and set 2 radii away in the direction of the rel pos vec of the last link and second to last link
	// 2) make a renderable & push into renderables with correct transform

	// relative position vector between second to last link and last link
	glm::vec3 relPosVec = glm::vec3(positions[lastRenderableIndex - 2].x - positions[lastRenderableIndex - 1].x,
									positions[lastRenderableIndex - 2].y - positions[lastRenderableIndex - 1].y,
									positions[lastRenderableIndex - 2].z - positions[lastRenderableIndex - 1].z);

	// make a renderable & push into renderables
	Shader snakeBodyShader = ResourceManager::getShader("snakeBody"); // made in renderer init
	Renderable snakeBody(renderersRenderables[lastRenderableIndex].model, circle, GL_TRIANGLES, snakeBodyShader, screenDimensions);
	snakeBody.m_uniforms.index = lastRenderableIndex;
	// mirror in position
	glm::vec4 secondCirclePos = positions[lastRenderableIndex - 1];
	glm::mat4 offset = glm::mat4(1.0f);
	offset = glm::translate(offset, -relPosVec);
	snakeBody.model *= offset;
	secondCirclePos = offset * secondCirclePos;

	renderersRenderables.push_back(std::move(snakeBody));
	positions.push_back(secondCirclePos);

	lastRenderableIndex += 1;
}

void Snake::moveRight()
{
	velocity.x = 1.0f;
	velocity.y = 0.0f;
}

void Snake::moveLeft()
{
	velocity.x = -1.0f;
	velocity.y = 0.0f;
}

void Snake::moveUp()
{
	velocity.x = 0.0f;
	velocity.y = 1.0f;
}

void Snake::moveDown()
{
	velocity.x = 0.0f;
	velocity.y = -1.0f;
}

