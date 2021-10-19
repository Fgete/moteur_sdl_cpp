#include "objectRenderer.h"

ObjectRenderer::ObjectRenderer()
{
	this->name = "";
	this->pSurface = NULL;
	this->pTexture = NULL;
}

ObjectRenderer::ObjectRenderer(SDL_Surface* s, SDL_Texture* t)
{
	this->name = "";
	this->pSurface = s;
	this->pTexture = t;
}

ObjectRenderer::ObjectRenderer(const ObjectRenderer& o)
{
	this->name = o.GetName();
	this->pSurface = o.GetSurface();
	this->pTexture = o.GetTexture();
}

ObjectRenderer::~ObjectRenderer()
{
}

SDL_Surface* ObjectRenderer::GetSurface() const
{
	return this->pSurface;
}

SDL_Texture* ObjectRenderer::GetTexture() const
{
	return this->pTexture;
}

string ObjectRenderer::GetName() const
{
	return this->name;
}

void ObjectRenderer::SetSurface(SDL_Surface* s)
{
	this->pSurface = s;
}

void ObjectRenderer::SetTexture(SDL_Texture* t)
{
	this->pTexture = t;
}

void ObjectRenderer::SetName(string s)
{
	this->name = s;
}

ObjectRenderer ObjectRenderer::operator=(const ObjectRenderer& o)
{
	this->name = o.name;
	this->pSurface = o.GetSurface();
	this->pTexture = o.GetTexture();
	return *this;
}

Sprite::Sprite()
{
	SDL_Color defaultColor = { 255, 255, 255, 255 };
	this->color = defaultColor;

	this->transform.position.x = 0;
	this->transform.position.y = 0;

	this->transform.scale.x = 100;
	this->transform.scale.y = 100;

	this->format.x = 100;
	this->format.y = 100;
	
	this->tileCount.x = 1;
	this->tileCount.y = 1;

	this->currentFrame = 1;
	this->tileNumber = 1;
}

Sprite::Sprite(SDL_Color c)
{
	this->color = c;

	this->transform.position.x = 0;
	this->transform.position.y = 0;

	this->transform.scale.x = 100;
	this->transform.scale.y = 100;

	this->format.x = 100;
	this->format.y = 100;

	this->tileCount.x = 1;
	this->tileCount.y = 1;

	this->currentFrame = 1;
	this->tileNumber = 1;
}

Sprite::Sprite(SDL_Surface* s)
{
	SDL_Color defaultColor = { 255, 255, 255, 255 };
	this->color = defaultColor;
	this->pSurface = s;

	this->transform.position.x = 0;
	this->transform.position.y = 0;

	this->transform.scale.x = 100;
	this->transform.scale.y = 100;

	this->format.x = 100;
	this->format.y = 100;

	this->tileCount.x = 1;
	this->tileCount.y = 1;

	this->currentFrame = 1;
	this->tileNumber = 1;
}

Sprite::Sprite(SDL_Color c, const float x, const float y, const float z, const float h, const float w)
{
	this->color = c;

	this->transform.position.x = x;
	this->transform.position.y = y;
	this->transform.position.z = z;

	this->transform.scale.x = w;
	this->transform.scale.y = h;

	this->format.x = 100;
	this->format.y = 100;

	this->tileCount.x = 1;
	this->tileCount.y = 1;

	this->currentFrame = 1;
	this->tileNumber = 1;
}

Sprite::Sprite(SDL_Surface* s, const float x, const float y, const float z, const float h, const float w)
{
	SDL_Color defaultColor = { 255, 255, 255, 255 };
	this->color = defaultColor;
	this->pSurface = s;

	this->transform.position.x = x;
	this->transform.position.y = y;
	this->transform.position.z = z;

	this->transform.scale.x = w;
	this->transform.scale.y = h;

	this->format.x = 100;
	this->format.y = 100;

	this->tileCount.x = 1;
	this->tileCount.y = 1;

	this->currentFrame = 1;
	this->tileNumber = 1;
}

Sprite::Sprite(const Sprite& s)
{
	this->name = s.name;

	this->pSurface = s.pSurface;
	this->pTexture = s.pTexture;

	this->transform = s.transform;

	this->format = s.format;

	this->tileCount = s.tileCount;

	this->currentFrame = s.currentFrame;
	this->tileNumber = s.tileNumber;
}

Sprite::~Sprite()
{
}

Transform Sprite::GetTransform() const
{
	return this->transform;
}

Vector2 Sprite::GetFormat() const
{
	return this->format;
}

Vector2 Sprite::GetTileCount() const
{
	return this->tileCount;
}

int Sprite::GetCurrentFrame() const
{
	return this->currentFrame;
}

int Sprite::GetTileNumber() const
{
	return this->tileNumber;
}

void Sprite::SetTransform(const Transform t)
{
	this->transform = t;
}

void Sprite::SetPosition(const Vector3 p)
{
	this->transform.position = p;
}

void Sprite::SetPosition(const float x, const float y, const float z)
{
	this->transform.position.x = x;
	this->transform.position.y = y;
	this->transform.position.z = z;
}

void Sprite::SetFormat(const Vector2 f)
{
	this->format = f;
}

void Sprite::SetFormat(const int x, const int y)
{
	this->format.x = x;
	this->format.y = y;
}

void Sprite::SetTileCount(const Vector2 tc)
{
	this->tileCount = tc;
}

void Sprite::SetCurrentFrame(const int cf)
{
	this->currentFrame = cf;
}

void Sprite::SetTileNumber(const int tn)
{
	this->tileNumber = tn;
}

void Sprite::SetColor(const SDL_Color c)
{
	this->color = c;
}

Sprite Sprite::operator=(const Sprite& s)
{
	this->pSurface = s.pSurface;
	this->pTexture = s.pTexture;

	this->transform = s.transform;

	this->format = s.format;

	this->tileCount = s.tileCount;

	this->currentFrame = s.currentFrame;
	this->tileNumber = s.tileNumber;

	return *this;
}

void Sprite::Draw(Renderer r)
{
	// Set frame numbers
	int frameX = 1;
	int frameY = 1;
	if (this->tileCount.x > 0)
		frameX = this->currentFrame % (int)this->tileCount.x;
	if (this->tileCount.y > 0)
		frameY = this->currentFrame % (int)this->tileCount.y;

	// Sprite rects
	SDL_Rect imageRect;
	imageRect.x = (this->transform.position.x - this->transform.scale.x / 2) * r.windowRatio + r.MaxXScreen() * .5;
	imageRect.y = (this->transform.position.y - this->transform.scale.y / 2) * r.windowRatio + r.MaxYScreen() * .5;
	imageRect.w = this->transform.scale.x * r.windowRatio;
	imageRect.h = this->transform.scale.y * r.windowRatio;
	SDL_Rect tileRect;
	tileRect.x = (this->format.x / this->tileCount.x) * frameX;
	tileRect.y = (this->format.y / this->tileCount.y) * frameY;
	tileRect.w = (this->format.x / this->tileCount.x);
	tileRect.h = (this->format.y / this->tileCount.y);

	// Render
	if (&this->pSurface)
		this->SetTexture(SDL_CreateTextureFromSurface(r.pRenderer, this->pSurface));

	if (this->tileCount.x > 1 || this->tileCount.y > 1) { // If there is several tiles
		if (&this->pTexture) SDL_RenderCopy(r.pRenderer, this->pTexture, &tileRect, &imageRect);
		else {
			SDL_SetRenderDrawColor(r.pRenderer, this->color.r, this->color.g, this->color.b, this->color.a);
			SDL_RenderDrawRect(r.pRenderer, &imageRect);
		}
		if (this->currentFrame < this->tileNumber)
			this->currentFrame++; // Next tile
		else
			this->currentFrame = 1;
	}
	else {
		if (&this->pTexture) SDL_RenderCopy(r.pRenderer, this->pTexture, &tileRect, &imageRect);
		else {
			SDL_SetRenderDrawColor(r.pRenderer, this->color.r, this->color.g, this->color.b, this->color.a);
			SDL_RenderDrawRect(r.pRenderer, &imageRect);
		}
	}
	SDL_DestroyTexture(this->GetTexture());
}

Text::Text()
{
	this->transform.position.x = 0;
	this->transform.position.y = 0;
	this->transform.position.z = 0;
	
	this->transform.scale.x = 0;
	this->transform.scale.y = 0;

	this->caption = "";
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	this->color = color;
}

Text::Text(string caption, SDL_Color color)
{
	this->transform.position.x = 0;
	this->transform.position.y = 0;
	this->transform.position.z = 0;

	this->transform.scale.x = 0;
	this->transform.scale.y = 0;

	this->caption = caption;
	this->color = color;
}

Text::Text(const Text& t)
{
	this->name = t.name;

	this->pSurface = t.pSurface;
	this->pTexture = t.pTexture;

	this->transform = t.transform;
	this->caption = t.caption;
	this->color = t.color;
}

Text::~Text()
{
}

Transform Text::GetTransform() const
{
	return this->transform;
}

string Text::GetCaption() const
{
	return this->caption;
}

SDL_Color Text::GetColor() const
{
	return this->color;
}

void Text::SetTransform(const Transform& t)
{
	this->transform = t;
}

void Text::SetTransform(const float posX, const float posY, const float posZ, const float h, const float w)
{
	this->transform.position.x = posX;
	this->transform.position.y = posY;
	this->transform.position.z = posZ;

	this->transform.scale.x = w;
	this->transform.scale.y = h;
}

void Text::SetCaption(const string caption)
{
	this->caption = caption;
}

void Text::SetColor(const SDL_Color color)
{
	this->color = color;
}

Text Text::operator=(const Text& t)
{
	this->pSurface = t.pSurface;
	this->pTexture = t.pTexture;

	this->transform = t.transform;

	this->caption = t.caption;
	this->color = t.color;

	return *this;
}

void Text::Draw(Renderer r, TTF_Font* f)
{	// String
	int n = this->caption.length();
	float fontSize = .01;
	// char charArray[n + 1];
	char charArray[64];
	strcpy_s(charArray, this->caption.c_str());
	// Sprite
	SDL_Rect titleRect;
	titleRect.w = r.MaxXScreen() * .5 * this->transform.scale.x * fontSize * strlen(charArray) * .1;
	titleRect.h = r.MaxYScreen() * .1 * this->transform.scale.y * fontSize;
	titleRect.x = r.MaxXScreen() * .5 - titleRect.w * .5 + r.windowRatio * this->transform.position.x;
	titleRect.y = r.MaxYScreen() * .5 - titleRect.h * .5 + r.windowRatio * this->transform.position.y;
	// Render
	this->SetSurface(TTF_RenderText_Solid(f, charArray, this->color));
	this->SetTexture(SDL_CreateTextureFromSurface(r.pRenderer, this->pSurface));
	SDL_RenderCopy(r. pRenderer, this->pTexture, NULL, &titleRect);
	SDL_FreeSurface(this->GetSurface());
	SDL_DestroyTexture(this->GetTexture());
}

bool Text::IsInFront(const Sprite& a, const Sprite& b)
{
	return a.transform.position.z < b.transform.position.z;
}
