#pragma once
#include"Headers.h"

namespace menu
{
	class GameMenu
	{
	public:
		GameMenu(SDL_Renderer* renderer);
		~GameMenu();

		int mainLoop();
		void close();

	private:
		Texture menuTextures[MENU_SIZE];
		Texture menuLogo;
		Texture initials;
		TTF_Font* menuFont; 
		TTF_Font* initialsFont;
		SDL_Renderer* renderer;
		bool started, quit;
		int actualPosition;

		void loadImages();
		void draw();
		void handleEvent();
	};
}
