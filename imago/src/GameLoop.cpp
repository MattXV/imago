#include "GameLoop.h"

GameLoop::GameLoop() :
	glContext(),
	window(nullptr),
	modelRenderer(nullptr),
	model(nullptr)
{
}

GameLoop::~GameLoop() {
	delete camera;
	delete modelRenderer;
	delete model;
}

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

	// Initialise resources
	camera = new FPSCamera(window);
	modelRenderer = new ModelRenderer(camera);
	modelRenderer->init();
	
	
	texture = new Texture("models/DMTConference_Mesh_BWall.png");
	model = new Model("models/DMTConference_Mesh_BWall.fbx");
	model->setTexture(texture);


	Utils::glCheckError();
	printf("Resources initialised Correctly! \n");
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
	glClearColor(0.0f, 0.384f, 0.929f, 0.32f);

	glClear(GL_COLOR_BUFFER_BIT);
	GLCALL(glEnable(GL_CULL_FACE));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (model) {
		x += increment;
		x = std::int8_t(x) % 360 ? 0.0f : x;

		model->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
		model->setRotation(glm::vec3(0.0f, x, 0.0f));
		modelRenderer->drawModel(model);
	}
	// Show window
	SDL_GL_SwapWindow(window);
}

void GameLoop::clean() {
	modelRenderer->clean();
}
