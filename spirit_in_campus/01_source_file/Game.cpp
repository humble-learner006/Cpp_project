/*
 * Game loop implementation
 * 1. Initialize the game
 * 2. Check whether the game is running (MENU PLAYING SCENE1)
 * 3. Handle player's events keyboard/mouse
 * 4. Update postions of moving objects
 * 5. Render objects occur on the screen
 * 6. Clean up
*/

//TODO
/*
1. resize of window
2. resorce management (maybe will have a list of all object(entity) in one scene)
3. Possession and distance (which to possess?)
4. Dialog and text block (beatify and have avatar)
5. Scene transition (how to change the scene)
6. Sound effect (how to play the sound effect) event driven
7. front and back? (how to decide which one is in front of the other)
8. location of object (need explanation)
*/

#include "Game.h"
#include "Button.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "SceneManager.h"

GameObject* player;
GameObject* tmp;
GameObject* instrument1;
GameObject* plant;
map* scene_music;
Label* label;



SDL_Renderer* Game::renderer = nullptr;

bool isPossess = false;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	// Choose whether have fullscreen or not
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	// Check Initialization of SDL and generate the window
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		//cout << "Subsystems Initialized!..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			//cout << "Window created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		isRunning = true;

		
	}
	else
	{
		isRunning = false;
	}

	// Specific object initialization
	startButton = new Button("Begin", 100, 100, 200, 50, renderer);
	settingsButton = new Button("Settings", 100, 200, 200, 50, renderer);
	quitButton = new Button("Exit", 100, 300, 200, 50, renderer);

	player = new GameObject("../00_Asset/spirit.png", 0, 300, 320, 320);
	player->animation(true, 7, 150);
	plant = new GameObject("../00_Asset/bunny_grass.png", "../00_Asset/bunny_outline.png",  1000, 500, 200, 200);
	instrument1 = new GameObject("../00_Asset/instrument1.png", "../00_Asset/instrument1_outline.png", 500, 500, 200, 200);
	tmp = new GameObject("", 0, 300, 320, 320);

	scene_music = new map("../00_Asset/scene1_music.png",0, 0, 1536, 1024);
	scene_music->setBond(0, 1200, 150, 700);

	label = new Label("Press space to skip the dialog and close the text block.", 1536, 1024, 300, renderer);


	}
}

// Handle player's events keyboard/mouse
void Game::handleEvent() {
	// Player moving
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (currentState == PLAYING){
		if (state[SDL_SCANCODE_A]) {
			player->Move(-10, 0, scene_music);
		}
		if (state[SDL_SCANCODE_D]) {
			player->Move(10, 0, scene_music); 
		}
		if (state[SDL_SCANCODE_W]) {
			player->Move(0, -10, scene_music);
		}
		if (state[SDL_SCANCODE_S]) {
			player->Move(0, 10, scene_music);
		}
		if (state[SDL_SCANCODE_TAB]) {
			plant->highlight();
		}
		else
		{
			plant->dehighlight();
		}
	}
	// Button, Label, Possesion
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		SceneManager::handleEvents();

		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		label->HandleEvent(event);
		if (currentState == MENU) {
			if (startButton->IsClicked(event)) {
				currentState = PLAYING;
			}
			else if (settingsButton->IsClicked(event)) {
				// TODO: setting screen (PAUSE MENUE)
			}
			else if (quitButton->IsClicked(event)) {
				isRunning = false;
			}
		}
		// Possesion checking
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
			if (!isPossess) {
				isPossess = true;
				//TODO: how to decide which one to possess?
				/*step1: find nearest interactive object
				  step2: decide whether the distance is smaller than 100
				  step3: tmp = player, player = nearest interactive object
				*/
				tmp = player;
				player = instrument1;
			}
			else
			{	
				isPossess = false;
				//*tmp -> GetX = *instrument1 -> GetX -=30; TODO: CALCULATE the position of the player AFTER POSSESION
				player = tmp;
			}
			
		}
		
	}
}

// Update postions of moving objects
void Game::update() {
	Uint32 currentTime = SDL_GetTicks();
	if (currentState == PLAYING) {
		player->Update();
		tmp->Update();
		plant->Update();
		instrument1 -> Update();
		label->Update(currentTime);

	}
	SceneManager::update();
}

// Render objects occur on the screen
void Game::render() {
	SDL_RenderClear(renderer);

	if (currentState == MENU) {
		startButton->Render();
		settingsButton->Render();
		quitButton->Render();
	}
	else if (currentState == PLAYING) {
		scene_music->DrawMap();
		player->Render();
		plant->Render();
		instrument1->Render();
		label->Render();
	}

	SceneManager::render();
	SDL_RenderPresent(renderer);
}

// Render objects occur on the screen
void Game::clean() {
	delete startButton;
	delete settingsButton;
	delete quitButton;
	delete player;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}