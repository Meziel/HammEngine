#pragma once

#include <ctime>
#include <GameObject.h>

#include "common.h"

using namespace GameEngine;

namespace ExampleGame
{
	class Cube : public GameObject
	{
	public:
		Cube();
		virtual void onTick();

	private:
		clock_t lastTick;
	};
}