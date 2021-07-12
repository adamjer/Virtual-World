#include "GameMenu.h"

namespace menu
{
	GameMenu::GameMenu(SDL_Renderer *renderer)
	{
		this->started = false;
		this->quit = false;
		this->actualPosition = 0;
		this->renderer = renderer;

		this->menuFont = 0;
		this->menuFont = TTF_OpenFont("data/Fonts/DosLike.ttf", FONT_MENU_SIZE);
		this->initialsFont = TTF_OpenFont("data/Fonts/DosLike.ttf", (int)(FONT_MENU_SIZE / 1.5));
		if (this->menuFont != 0)
			this->loadImages();
		else
			std::cout << "Unable to load font! TTF_Error: " << TTF_GetError() << std::endl;
	}


	GameMenu::~GameMenu()
	{
		this->close();
	}


	int GameMenu::mainLoop()
	{
		int result = -1;
		while (!this->quit)
		{
			this->draw();
			this->handleEvent();
			result = actualPosition;
		}
		this->quit = false;
		this->actualPosition = 0;
		return result;
	}


	void GameMenu::loadImages()
	{
		SDL_Color menuColor = { WHITE_COLOR };
		SDL_Color initialsColor = { BLACK_COLOR };
		this->menuLogo.loadFromFile(this->renderer, "data/Images/MenuLogo.png");
		this->initials.loadFromRederedText(this->renderer, this->initialsFont, initialsColor, "Adam Jereczek[149448]");
		const std::string menuText[] = {
			"New Game",
			"Continue",
			"Load Game",
			"Save Game",
			"Exit",
		};
		for (int i = 0; i < MENU_SIZE; i++)
			this->menuTextures[i].loadFromRederedText(this->renderer, this->menuFont, menuColor, menuText[i]);
	}


	void GameMenu::draw()
	{
		SDL_Point renderPoint;
		SDL_Rect renderRect = { 0, 0, this->menuLogo.getWidth() * 2, this->menuLogo.getHeight() * 2 };

		SDL_SetRenderDrawColor(this->renderer, BACKGROUND_COLOR);
		renderPoint = { RESOLUTION_X / 2 - menuLogo.getWidth(), 0 };
		SDL_RenderClear(this->renderer);
		this->menuLogo.render(this->renderer, renderPoint, &renderRect);
		renderPoint.y = 100;
		for (int i = 0; i < MENU_SIZE; i++)
		{
			renderPoint.x = RESOLUTION_X / 2 - menuTextures[i].getWidth() / 2;
			renderPoint.y += int(menuTextures[i].getHeight() * 1.5);
			if ((i == Menu::SaveGame || i == Menu::Continue) && !this->started)
			{
				this->menuTextures[i].setColor(GREY_COLOR);
				this->menuTextures[i].render(this->renderer, renderPoint);
				this->menuTextures[i].setColor(WHITE_COLOR);
			}
			else if (i == this->actualPosition)
			{
				this->menuTextures[i].setColor(RED_COLOR);
				this->menuTextures[i].render(this->renderer, renderPoint);
				this->menuTextures[i].setColor(WHITE_COLOR);
			}
			else
				this->menuTextures[i].render(this->renderer, renderPoint);
		}
		renderPoint = { RESOLUTION_X / 2 - initials.getWidth() / 2, 450 };
		this->initials.render(this->renderer, renderPoint);
		SDL_RenderPresent(this->renderer);
	}


	void GameMenu::handleEvent()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					if (!this->started && (this->actualPosition == Menu::SaveGame + 1 || this->actualPosition == Menu::Continue + 1))
						this->actualPosition--;
					this->actualPosition--;
					if (this->actualPosition < 0)
						this->actualPosition++;
					break;
				case SDLK_DOWN:
					if (!this->started && (this->actualPosition == Menu::SaveGame - 1 || this->actualPosition == Menu::Continue - 1))
						this->actualPosition++;
					this->actualPosition++;
					if (this->actualPosition > (MENU_SIZE - 1))
						this->actualPosition--;
					break;
				case SDLK_ESCAPE:
					break;
				case SDLK_RETURN:	//press ENTER
					this->started = true;
					this->quit = true;
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_QUIT)
			{
				this->actualPosition = Menu::Exit;
				this->quit = true;
			}
		}
	}


	void GameMenu::close()
	{
		for (int i = 0; i < MENU_SIZE; i++)
			this->menuTextures[i].free();

		this->menuLogo.free();
		TTF_CloseFont(this->menuFont);
		this->menuFont = 0;
		TTF_CloseFont(this->initialsFont);
		this->initialsFont = 0;
	}
}