#include "Sprite.h"
#include <SDL_image.h>

FG::Sprite::Sprite(SDL_Texture* texture, int x, int y, int w, int h)
{
	myTexture = texture;
	SetSource(x, y, h, w);
}

FG::Sprite::~Sprite()
{
}

SDL_Rect FG::Sprite::GetSource()
{
	return Source;
}

SDL_Texture* FG::Sprite::GetTexture()
{
	return myTexture;
}

void FG::Sprite::SetSource(int x, int y, int h, int w)
{
	Source.x = x;
	Source.y = y;
	Source.h = h;
	Source.w = w;
}

FG::Sprite::Sprite()
	: myTexture(nullptr), Source({ 0,0,0,0 })
{}
