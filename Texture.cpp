#include "Texture.h"


Texture::Texture()
{
	this->itsTexture = 0;
	this->itsWidth = 0;
	this->itsHeight = 0;
}


Texture::~Texture()
{
	this->free();
}


bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string path)
{
	this->free();
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != 0)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		this->itsTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (this->itsTexture != 0)
		{
			this->itsWidth = loadedSurface->w;
			this->itsHeight = loadedSurface->h;
		}
		else
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;

		SDL_FreeSurface(loadedSurface);
	}
	else
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;

	return itsTexture != 0;
}


bool Texture::loadFromRederedText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const std::string text)
{
	this->free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (textSurface != 0)
	{
		this->itsTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (this->itsTexture != 0)
		{
			this->itsHeight = textSurface->h;
			this->itsWidth = textSurface->w;
		}
		else
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;

		SDL_FreeSurface(textSurface);
	}
	else
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;

	return this->itsTexture != 0;
}


void Texture::free()
{
	if (this->itsTexture != 0)
	{
		SDL_DestroyTexture(this->itsTexture);
		this->itsTexture = 0;
		this->itsHeight = 0;
		this->itsWidth = 0;
	}
}


void Texture::render(SDL_Renderer* renderer, SDL_Point renderPoint, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { renderPoint.x, renderPoint.y, this->itsWidth, this->itsHeight };

	if (clip != 0)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, this->itsTexture, clip, &renderQuad, angle, center, flip);
}


void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	if (SDL_SetTextureColorMod(this->itsTexture, red, green, blue) == -1)
		std::cout << "Couldn't change color! SDL_Error: " << SDL_GetError() << std::endl;
}


int Texture::getHeight()
{
	return this->itsHeight;
}


int Texture::getWidth()
{
	return this->itsWidth;
}


SDL_Texture* Texture::getTexture()
{
	return this->itsTexture;
}