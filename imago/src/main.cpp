#pragma once

#include "GameLoop.h"

int main(int argc, char* argv[]) {
	GameLoop* gameLoop = new GameLoop();
	gameLoop->init();

	while (gameLoop->handleInput()) {
		gameLoop->update();
		gameLoop->draw();
	}

	gameLoop->clean();
	delete gameLoop;
	return 0;
}