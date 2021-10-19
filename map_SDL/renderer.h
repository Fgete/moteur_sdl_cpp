#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <windows.h>

#include "geometry.h"

using namespace std;


class Renderer {
public:
	// SDL Renderer
	SDL_Surface*  pSurface;
	SDL_Window*   pWindow;
	SDL_Renderer* pRenderer;

	// Graphics
	float windowRatio = .5;

public:
	// Builders
	Renderer();

	// Copier
	Renderer(const Renderer& r);

	// Destroyer
	~Renderer();

	// Accessors
	SDL_Surface*  GetSurface();
	SDL_Window*   GetWindow();
	SDL_Renderer* GetRenderer();
	Vector2       ScreenCenter() const;

	int           MinXScreen() const;
	int           MaxXScreen() const;
	int           MinYScreen() const;
	int           MaxYScreen() const;

	// Mutators
	void SetSurface(SDL_Surface* s);
	void SetWindow(SDL_Window* w);
	void SetRenderer(SDL_Renderer* r);

	// Operators
	Renderer operator=(const Renderer& r);

	// Render
	void RenderWindow();
};