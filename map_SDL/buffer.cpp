#include "buffer.h"

GraphicBuffer::GraphicBuffer() {
}

GraphicBuffer::GraphicBuffer(const GraphicBuffer& gb) {
	this->defaultFont = gb.defaultFont;
	this->spriteBuffer = gb.spriteBuffer;
	this->textBuffer = gb.textBuffer;
}

GraphicBuffer::~GraphicBuffer() {
}

Sprite* GraphicBuffer::GetSpriteAt(const int n) const {
	auto el = this->spriteBuffer.begin();
	advance(el, n);
	Sprite s = *el;
	return &s;
}

Sprite* GraphicBuffer::GetSpriteByName(const string name) {
	list<Sprite>::iterator it = this->spriteBuffer.begin();
	if (it->GetName() == name)
		return &(*it);
	else
		for (int i = 1; i < this->spriteBuffer.size(); i++) {
			advance(it, 1);
			if (it->GetName() == name)
				return &(*it);
		}
	Sprite* defaultSprite = new Sprite();
	return defaultSprite;
}

Text* GraphicBuffer::GetTextAt(const int n) const {
	auto el = this->textBuffer.begin();
	advance(el, n);
	Text s = *el;
	return &s;
}

Text* GraphicBuffer::GetTextByName(const string name) {
	list<Text>::iterator it = this->textBuffer.begin();
	if (it->GetName() == name)
		return &(*it);
	else
		for (int i = 1; i < this->textBuffer.size(); i++) {
			advance(it, 1);
			if (it->GetName() == name)
				return &(*it);
		}
	Text* defaultText = new Text();
	return defaultText;
}

TTF_Font* GraphicBuffer::GetFont() const {
	return this->defaultFont;
}

void GraphicBuffer::AddSprite(const Sprite& s) {
	this->spriteBuffer.push_back(s);
}

void GraphicBuffer::AddText(const Text& t) {
	this->textBuffer.push_back(t);
}

void GraphicBuffer::SetFont(TTF_Font* f) {
	this->defaultFont = f;
}

GraphicBuffer GraphicBuffer::operator=(const GraphicBuffer& gb) {
	this->spriteBuffer = gb.spriteBuffer;
	this->textBuffer = gb.textBuffer;
	return *this;
}

void GraphicBuffer::Draw(Renderer r) const {
	SDL_RenderClear(r.pRenderer);

	for (auto it = this->spriteBuffer.begin(); it != this->spriteBuffer.end(); ++it) {
		Sprite currentSprite = *it;
		currentSprite.Draw(r);
	}

	for (auto it = this->textBuffer.begin(); it != this->textBuffer.end(); ++it) {
		Text currentText = *it;
		currentText.Draw(r, this->defaultFont);
	}

	SDL_RenderPresent(r.pRenderer);
}