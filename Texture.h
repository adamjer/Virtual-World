#pragma once
#include"Headers.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(SDL_Renderer* renderer, const std::string path);
	bool loadFromRederedText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const std::string text);
	void free();
	void render(SDL_Renderer* renderer, SDL_Point renderPoint, SDL_Rect* clip = 0, double angle = 0.0,
		SDL_Point* center = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	int getHeight();
	int getWidth();
	SDL_Texture* getTexture();

private:
	SDL_Texture* itsTexture;
	int itsWidth;
	int itsHeight;
};

