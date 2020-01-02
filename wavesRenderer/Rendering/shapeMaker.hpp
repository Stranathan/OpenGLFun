#pragma once
#include <iostream>
#include "shape.hpp"
#include "glm/glm.hpp"

namespace Rendering
{
	class ShapeMaker
	{
	private:

	public:
		static Rendering::Shape makeRectangle(glm::vec2 size, glm::vec4 color);
		static Rendering::Shape makeSolidCircle(glm::vec4 color);
		static Rendering::Shape makeVerticalLine(glm::vec4 color);
		//static Rendering::Shape makeOutlineCircle(glm::vec4 color);
	};
}