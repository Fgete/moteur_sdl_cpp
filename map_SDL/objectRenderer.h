#pragma once

#include <string>
#include <string.h>
#include "renderer.h"

using namespace std;


class ObjectRenderer {
protected:
	string name;
	SDL_Surface* pSurface;
	SDL_Texture* pTexture;

public:
	// Builders
	ObjectRenderer();
	ObjectRenderer(SDL_Surface* s, SDL_Texture* t);

	// Copier
	ObjectRenderer(const ObjectRenderer& o);

	// Destroyer
	~ObjectRenderer();

	// Accessors
	SDL_Surface* GetSurface() const;
	SDL_Texture* GetTexture() const;
	string       GetName   () const;

	// Mutators
	void SetSurface(SDL_Surface* s);
	void SetTexture(SDL_Texture* t);
	void SetName   (string       s);

	// Operators
	ObjectRenderer operator=(const ObjectRenderer& o);
};

class Sprite : public ObjectRenderer {
protected:
	Vector2 format; // pixel format
	Vector2 tileCount; // number of row and column
	int currentFrame; // Current frame of animation
	int tileNumber; // Number of animation frame
	SDL_Color color;
public:
	Transform transform; // Position and scale

	// Builders
	Sprite();
	Sprite(SDL_Color c);
	Sprite(SDL_Surface* s);
	Sprite(SDL_Color c, const float posX, const float posY, const float posZ, const float height, const float width);
	Sprite(SDL_Surface* s, const float posX, const float posY, const float posZ, const float height, const float width);

	// Copier
	Sprite(const Sprite& s);

	// Destroyer
	~Sprite();

	// Accessors
	Transform GetTransform() const;
	Vector2 GetFormat() const;
	Vector2 GetTileCount() const;
	int GetCurrentFrame() const;
	int GetTileNumber() const;

	// Mutators
	void SetTransform(const Transform t);
	void SetPosition(const Vector3 p);
	void SetPosition(const float x, const float y, const float z);
	void SetFormat(const Vector2 f);
	void SetFormat(const int x, const int y);
	void SetTileCount(const Vector2 tc);
	void SetCurrentFrame(const int cf);
	void SetTileNumber(const int tn);
	void SetColor(const SDL_Color c);

	// Operators
	Sprite operator=(const Sprite& s);

	// Drawer
	void Draw(Renderer r);
};

class Text : public ObjectRenderer {
protected:
	string caption;
	SDL_Color color;
public:
	Transform transform;

	// Builders
	Text();
	Text(string caption, SDL_Color color);

	// Copier
	Text(const Text& t);

	// Destroyer
	~Text();

	// Accessors
	Transform GetTransform()const;
	string GetCaption()const;
	SDL_Color GetColor()const;

	// Mutators
	void SetTransform(const Transform& t);
	void SetTransform(const float posX, const float posY, const float posZ, const float h, const float w);
	void SetCaption(const string caption);
	void SetColor(const SDL_Color color);

	// Operators
	Text operator=(const Text& t);

	// Drawer
	void Draw(Renderer renderer, TTF_Font* font);
	bool IsInFront(const Sprite& a, const Sprite& b);
};