#include "GameLoop.h"

GameLoop::GameLoop() :
	glContext(),
	window(nullptr),
	modelRenderer(nullptr),
	model(nullptr),
	terrain(nullptr)
{
}

GameLoop::~GameLoop() {
	delete camera;
	delete modelRenderer;
	delete model;
	delete terrain;
	delete skydome;
	delete triangleRenderer;
}

void GameLoop::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialise SDL!" << std::endl;
		return;
	}
	// OpenGL context initialisation.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	window = SDL_CreateWindow("Main Window", 50, 50, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Could not initialise window..." << std::endl;
		return;
	}
	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		std::cout << "Could not create GL context! ERROR: " << SDL_GetError() << std::endl;
		return;
	}
	glewExperimental = true;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "Could not instantiate Glew! Error: " << glewGetErrorString(glewError) << std::endl;
		return;
	}
	// Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
		std::cout << "Vsync is not supported!" << std::endl;

	// Initialise scene objects
	camera = new FPSCamera(window);
	triangleRenderer = new TriangleRenderer(camera);
	modelRenderer = new ModelRenderer(camera);
	triangleRenderer->init();
	modelRenderer->init();

	texture = new Texture("resources/models/monkey.png");
	model = new Model("resources/models/monkey.obj");
	model->setTexture(texture);

	terrainTexure = new Texture("resources/models/terrain/moon_texture.png");
	terrain = new Terrain("resources/models/terrain/blurred.png", terrainTexure);

	skydomeTexture = new Texture("resources/models/terrain/sky.png");
	
	skydome = new SkyDome(skydomeTexture, 15.0f, 16U);

	Utils::glCheckError();
}

bool GameLoop::handleInput() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return false;
		}
		camera->handleInput(e);
	}
	return true;
}

void GameLoop::update() {
	camera->update();
}

void GameLoop::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_CULL_FACE);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	x += increment;
	x = std::int8_t(x) % 360 ? 0.0f : x;

	model->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	model->setRotation(glm::vec3(0.0f, x, 0.0f));
	//triangleRenderer->draw();
	modelRenderer->drawModel(model);
	modelRenderer->renderTerrain(terrain);
	modelRenderer->renderSkyDome(skydome, x);

	SDL_GL_SwapWindow(window);
}

void GameLoop::clean() {
	modelRenderer->clean();
	triangleRenderer->clean();
}
