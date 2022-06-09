#include "Cube.h"

#include <memory>
#include <Components/Mesh.h>
#include <Components/ShaderProgram.h>
#include <Meshes/Cube.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace ExampleGame
{

	Cube::Cube()
	{
		std::shared_ptr<GameEngine::Cube> mesh = Component::createComponent<GameEngine::Cube>();
		this->addComponent(mesh);
		std::shared_ptr<ShaderProgram> shader = Component::createComponent<ShaderProgram>();
		this->addComponent(shader);
	};

	void Cube::onTick()
	{
		clock_t now = clock();

		float timeSinceLastTickSeconds = float(now - this->lastTick) / CLOCKS_PER_SEC;

		const float DEGREES_PER_SECOND = 90 * (2 * 3.14159265359 / 360);

		// Rotate the cube
		Vector3 newCubeRotation = this->relativeRotation();
		newCubeRotation.y += std::fmodf(DEGREES_PER_SECOND * timeSinceLastTickSeconds, 2 * M_PI);
		this->relativeRotation(newCubeRotation);

		this->lastTick = now;
	}

}