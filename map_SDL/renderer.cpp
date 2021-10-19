#include "renderer.h"

Renderer::Renderer()
{
	this->pSurface = NULL;
	this->pWindow = NULL;
	this->pRenderer = NULL;
}

Renderer::Renderer(const Renderer& r)
{
	this->pSurface = r.pSurface;
	this->pWindow = r.pWindow;
	this->pRenderer = r.pRenderer;
}

Renderer::~Renderer()
{
}

SDL_Surface* Renderer::GetSurface()
{
	return this->pSurface;
}

SDL_Window* Renderer::GetWindow()
{
	return this->pWindow;
}

SDL_Renderer* Renderer::GetRenderer()
{
	return this->pRenderer;
}

Vector2 Renderer::ScreenCenter() const
{
	Vector2 screenCenter;
	screenCenter.x = static_cast<int>(GetSystemMetrics(SM_CXSCREEN) * this->windowRatio);
	screenCenter.y = static_cast<int>(GetSystemMetrics(SM_CYSCREEN) * this->windowRatio);
	return screenCenter;
}

int Renderer::MinXScreen() const
{
	return -GetSystemMetrics(SM_CXSCREEN) * this->windowRatio;
}

int Renderer::MaxXScreen() const
{
	return GetSystemMetrics(SM_CXSCREEN) * this->windowRatio;
}

int Renderer::MinYScreen() const
{
	return -GetSystemMetrics(SM_CYSCREEN) * this->windowRatio;
}

int Renderer::MaxYScreen() const
{
	return GetSystemMetrics(SM_CYSCREEN) * this->windowRatio;
}

void Renderer::SetSurface(SDL_Surface* s)
{
	this->pSurface = s;
}

void Renderer::SetWindow(SDL_Window* w)
{
	this->pWindow = w;
}

void Renderer::SetRenderer(SDL_Renderer* r)
{
	this->pRenderer = r;
}

Renderer Renderer::operator=(const Renderer& r)
{
	this->pSurface = r.pSurface;
	this->pWindow = r.pWindow;
	this->pRenderer = r.pRenderer;
	return *this;
}

void Renderer::RenderWindow()
{
	if (this->pWindow)
		SDL_DestroyWindow(this->pWindow);
	this->pWindow = SDL_CreateWindow(
		"PONG",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(GetSystemMetrics(SM_CXSCREEN) * this->windowRatio),
		static_cast<int>(GetSystemMetrics(SM_CYSCREEN) * this->windowRatio),
		SDL_WINDOW_SHOWN);
	this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
}
