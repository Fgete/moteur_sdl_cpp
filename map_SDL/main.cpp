#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// #include <SDL_mixer.h>
#include <windows.h>

#include "buffer.h"

using namespace std;

int  InitAll     (Renderer* renderer);
void Introduction(GraphicBuffer gb, Renderer r, int* gs);
void Pong        (GraphicBuffer gb, Renderer r, int* gs);
GraphicBuffer InitIntroGraphics();
GraphicBuffer InitPongGraphics ();
void GameInputAction(Renderer r, GraphicBuffer* gb, bool* isPongging, int* gs);

int main(int argc, char** args) {

	Renderer renderer;

	if (!InitAll(&renderer))
		return 1;

	// ------ PROGRAM ------

	GraphicBuffer introGB(InitIntroGraphics());
	GraphicBuffer pongGB(InitPongGraphics());

	int gameState = 0;

	while (gameState != -1) {
		switch (gameState) {
			case 0: /* INTRODUCTION */
				Introduction(introGB, renderer, &gameState); break;
			case 1: /* PONG */
				Pong(pongGB, renderer, &gameState); break;
			default: gameState = -1; break;
		}
	}

	// --- TODO ---
	// GB -> renvoyer un pointer dans la fonction GetSpriteAt et GetTextAt
	// GB -> transformer en class abstraite de ObjectRenderer
	// Ajouter l'axe z dans la position du transform pour ranger le buffer
	// Sprite sans image -> rect par default (avec couleur)
	// Renderer -> retourner les limites de l'ecran

	SDL_DestroyWindow(renderer.pWindow);

	SDL_Quit();

	cout << "Program ends successfully" << endl;
	return 0;
}

int InitAll(Renderer* renderer) {

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 0;
	}

	// Create our window
	renderer->RenderWindow();

	// Make sure creating the window succeeded
	if (!renderer->pWindow) {
		cout << "Error creating window : " << SDL_GetError() << endl;
		system("pause");
		return 0;
	}

	// Get the surface from the window
	renderer->pSurface = SDL_GetWindowSurface(renderer->pWindow);

	// Make sure getting the surface succeeded
	if (!renderer->pSurface) {
		cout << "Error getting surface : " << SDL_GetError() << endl;
		system("pause");
		return 0;
	}

	// SDL2_image init
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		SDL_Log("IMG_Init : Failed to init required .png .jpg support !\n");
		SDL_Log("IMG_Init : %s\n", IMG_GetError());
		return 0;
	}

	// TTF init
	if (TTF_Init() != 0) {
		SDL_Log("SDL_TTF -> ERROR");
		return 0;
	}

	return 1;
}

void Introduction(GraphicBuffer gb, Renderer r, int* gs) {

	// --- INPUTS ---
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE: /* VALIDATE */
				*gs = 1;
				break;
			default:
				break;
			}
		}
		if (event.type == SDL_QUIT) {
			*gs = -1;
			break;
		}
		fflush(stdin);
	}

	// --- RENDER ---
	gb.Draw(r);
}

void Pong(GraphicBuffer gb, Renderer r, int* gs) {

	bool isPongging = true;

	// Ball behavior
	Sprite* ball = gb.GetSpriteByName("ball");
	Vector2 ballMovement = { 1, -1 };
	float initialBallSpeed = 3;
	float ballSpeed = initialBallSpeed;

	// Score
	int leftPlayer  = 0;
	int rightPlayer = 0;

	while (isPongging) {
		
		// BALL MOVEMENT
		ball->transform.position += Vector3(ballMovement.x * ballSpeed, ballMovement.y * ballSpeed, 0);

		// BORDERS COLLISION
		if (ball->transform.position.y > (r.MaxYScreen() - ball->transform.scale.y / 2) && ballMovement.y > 0)
			ballMovement.y = -ballMovement.y;
		if (ball->transform.position.y < (r.MinYScreen() + ball->transform.scale.y / 2) && ballMovement.y < 0)
			ballMovement.y = -ballMovement.y;

		// GOAL COLLISION
		if (ball->transform.position.x > (r.MaxXScreen() - ball->transform.scale.x / 2) && ballMovement.x > 0) {
			ballMovement.x = -ballMovement.x;
			leftPlayer++;
			ball->SetPosition(0, 0, ball->transform.position.z);
			ballSpeed = initialBallSpeed;
		}
		if (ball->transform.position.x < (r.MinXScreen() + ball->transform.scale.x / 2) && ballMovement.x < 0) {
			ballMovement.x = -ballMovement.x;
			rightPlayer++;
			ball->SetPosition(0, 0, ball->transform.position.z);
			ballSpeed = initialBallSpeed;
		}

		// BOARD COLLISION
		if (ball->transform.Collide(gb.GetSpriteByName("boardRight")->transform) && ballMovement.x > 0) {
			ballMovement.x = -1;
			ballSpeed *= 1.5;
		}
		if (ball->transform.Collide(gb.GetSpriteByName("boardLeft")->transform) && ballMovement.x < 0) {
			ballMovement.x = 1;
			ballSpeed *= 1.5;
		}

		// UPDATE SCORES
		gb.GetTextByName("leftScore")->SetCaption("- " + to_string(leftPlayer) + " -");
		gb.GetTextByName("rightScore")->SetCaption("- " + to_string(rightPlayer) + " -");

		GameInputAction(r, &gb, &isPongging, gs);

		// --- RENDER ---
		gb.Draw(r);
	}
}

GraphicBuffer InitIntroGraphics() {
	GraphicBuffer gb;
	TTF_Font* defaultFont = TTF_OpenFont("./assets/fonts/default.ttf", 64);
	gb.SetFont(defaultFont);

	Sprite myLogo(IMG_Load("./assets/images/logo.png"), 0, 0, 0, 500, 500);
	myLogo.SetFormat(1080, 1080);
	gb.AddSprite(myLogo);

	SDL_Color textIntroColor = { 255, 255, 255, 150 };
	Text textIntro("- Press SPACE to continue -", textIntroColor);
	textIntro.SetTransform(0, 350, -1, 50, 50);
	gb.AddText(textIntro);

	return gb;
}

GraphicBuffer InitPongGraphics() {
	GraphicBuffer gb;
	TTF_Font* defaultFont = TTF_OpenFont("./assets/fonts/default.ttf", 64);
	gb.SetFont(defaultFont);

	// BALL
	Sprite ball(IMG_Load("./assets/images/logo.png"), 0, 0, 0, 50, 50);
	ball.SetFormat(1080, 1080);
	ball.SetName("ball");
	gb.AddSprite(ball);

	// TITLE
	SDL_Color titleColor = { 255, 255, 255, 150 };
	Text titlePong("PONG", titleColor);
	titlePong.SetTransform(0, -400, -10, 50, 50);
	titlePong.SetName("title");
	gb.AddText(titlePong);

	// SCORE LEFT
	SDL_Color scoreLeftColor = { 200, 100, 0, 255 };
	Text scoreLeftText("- 0 -", scoreLeftColor);
	scoreLeftText.SetTransform(-200, -400, -10, 50, 50);
	scoreLeftText.SetName("leftScore");
	gb.AddText(scoreLeftText);

	// SCORE RIGHT
	SDL_Color scoreRightColor = { 100, 200, 0, 255 };
	Text scoreRightText("- 0 -", scoreRightColor);
	scoreRightText.SetTransform(200, -400, -10, 50, 50);
	scoreRightText.SetName("rightScore");
	gb.AddText(scoreRightText);

	// BOARD LEFT
	Sprite boardLeft(IMG_Load("./assets/images/boardLeft.png"), -600, 0, -1, 200, 40);
	boardLeft.SetFormat(40, 200);
	boardLeft.SetName("boardLeft");
	gb.AddSprite(boardLeft);

	// BOARD RIGHT
	Sprite boardRight(IMG_Load("./assets/images/boardRight.png"), 600, 0, 1, 200, 40);
	boardRight.SetFormat(40, 200);
	boardRight.SetName("boardRight");
	gb.AddSprite(boardRight);

	return gb;
}

void GameInputAction(Renderer r, GraphicBuffer* gb, bool* isPongging, int* gs) {
	SDL_Event event;
	Sprite* boardLeft = gb->GetSpriteByName("boardLeft");
	Sprite* boardRight = gb->GetSpriteByName("boardRight");
	float boardSpeed = 5;

	if (GetAsyncKeyState('Z') & 0x8000)
		if (boardLeft->transform.position.y - boardLeft->transform.scale.y / 2 > r.MinYScreen())
			boardLeft->transform.position += Vector3(0, -boardSpeed, 0);

	if (GetAsyncKeyState('S') & 0x8000)
		if (boardLeft->transform.position.y + boardLeft->transform.scale.y / 2 < r.MaxYScreen())
			boardLeft->transform.position += Vector3(0, +boardSpeed, 0);

	if (GetAsyncKeyState('O') & 0x8000)
		if (boardRight->transform.position.y - boardRight->transform.scale.y / 2 > r.MinYScreen())
			boardRight->transform.position += Vector3(0, -boardSpeed, 0);

	if (GetAsyncKeyState('L') & 0x8000)
		if (boardRight->transform.position.y + boardRight->transform.scale.y / 2 < r.MaxYScreen())
			boardRight->transform.position += Vector3(0, +boardSpeed, 0);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE: // VALIDATE
				*isPongging = false;
				*gs = -1;
				break;
			default:
				break;
			}
		}
		if (event.type == SDL_QUIT) {
			*isPongging = false;
			*gs = -1;
			break;
		}
		fflush(stdin);
	}
}