#include "GameLoop.h"

GameLoop::GameLoop() :
	glContext(),
	window(nullptr),
	camera(new Camera())
{
	triangleRenderer = new TriangleRenderer(camera);
};

GameLoop::~GameLoop() {
	delete triangleRenderer;
	delete camera;
};

void GameLoop::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("sdl could not init!");
		return;
	}
	// Set opengl version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create a window
	window = SDL_CreateWindow("Main Window", 50, 50, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!window) {
		printf("could not create window!");
		return;
	}

	glContext = SDL_GL_CreateContext(window);

	if (!glContext) {
		printf("Could not create GL Context! \n %s \n", SDL_GetError());
		return;
	}

	// Init glew
	glewExperimental = true;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("Could not instantiate OpenGl \n %s \n", glewGetErrorString(glewError));
		return;
	}

	// Set Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
		printf("Unable to set Vsync! \n %s \n", SDL_GetError());

	triangleRenderer->init();
	printf("SDL correctly initialised :D stonks \n");
}

bool GameLoop::handleInput() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void GameLoop::update() {

}

void GameLoop::draw() {
	glClearColor(0.392f, 0.384f, 0.929f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	triangleRenderer->draw();

	// Show window
	SDL_GL_SwapWindow(window);
}

void GameLoop::clean() {
	triangleRenderer->clean();
}
