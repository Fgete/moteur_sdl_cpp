#pragma once

#include <iterator>
#include <list>

#include "objectRenderer.h"

typedef struct GE {
	ObjectRenderer* elem;
	GE* next;
};

typedef struct GE_List {
	GE* elem_head;
	int length;
};

class GraphicBuffer {
protected:
	list<Sprite>         spriteBuffer;
	list<Text>           textBuffer;

	TTF_Font* defaultFont;
public:
	// Builders
	GraphicBuffer();
	
	// Copier
	GraphicBuffer(const GraphicBuffer& gb);

	// Destroyer
	~GraphicBuffer();

	// Accessors
	Sprite*   GetSpriteAt(const int index) const;
	Sprite*   GetSpriteByName(const string name);
	Text*     GetTextAt(const int index) const;
	Text*     GetTextByName(const string name);
	TTF_Font* GetFont() const;

	// Mutators
	void AddSprite(const Sprite& s);
	void AddText  (const Text&   t);
	void SetFont  (TTF_Font*     f);

	// Operators
	GraphicBuffer operator=(const GraphicBuffer& gb);

	// Render
	void Draw(Renderer renderer) const;
};