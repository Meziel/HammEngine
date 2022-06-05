#include <memory>

#include <Window.h>
#include <Scene.h>
#include <GameObject.h>
#include <Component.h>
#include <Vector3.h>

#include "Player.h"
#include "Cube.h"

using namespace GameEngine;
using namespace ExampleGame;

int main(int argc, char** argv) {

	int GAME_WINDOW_WIDTH = 800;
	int GAME_WINDOW_HEIGHT = 600;

	// Initialize a window for the game
	Window window("Example Game", GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
	window.backgroundColor = { 0.0f, 0.0f, 1.0f };
	
	// Make a scene and add objects to it
	std::shared_ptr<Scene> scene = Scene::createScene();
	window.setScene(scene);

	// Create a player
	std::shared_ptr<Player> player = GameObject::createGameObject<Player>();
	player->relativePosition(Vector3{ 0.0f, 0.0f, 0.0f });
	// Attach a mouse listener to the player object
	window.registerKeyboardListener(player.get());
	window.registerMouseListener(player.get());

	// Create a camera
	std::shared_ptr<Camera> camera = GameObject::createGameObject<Camera>();
	camera->relativePosition(Vector3{ 0.0f, 0.0f, 0.0f });
	camera->fov = 45.0f;
	camera->aspect = float(GAME_WINDOW_WIDTH) / float(GAME_WINDOW_HEIGHT);
	// Attach the camera to the player object so that it follows the player
	player->addGameObject(camera);
	player->followCamera = camera.get();

	// Create a cube
	std::shared_ptr<GameObject> cube1 = GameObject::createGameObject<ExampleGame::Cube>();
	cube1->relativePosition(Vector3{ 0.0f, 0.0f, -3.6576 });
	cube1->scale(Vector3{ 0.3048f, 0.3048f, 0.3048f }),

	// Adding the objects to the scene
	scene->addGameObject(player);
	scene->addGameObject(cube1);
	scene->activeCamera = camera;

	// Start the game
	window.lockCursor(true);
	window.init();

	return 0;
}
