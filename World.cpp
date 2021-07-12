#include "World.h"

namespace worlds
{
	VirtualWorld::VirtualWorld()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL couldn't be initialized!\n";
			this->quit = true;
		}
		else
		{
			this->window = SDL_CreateWindow("Virtual World by Adam Jereczek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RESOLUTION_X, RESOLUTION_Y,
				SDL_WINDOW_SHOWN);
			if (this->window == 0)
			{
				std::cout << "Window couldn't be created!\n";
				this->quit = true;
			}
			else
			{
				this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
				if (this->renderer == 0)
				{
					std::cout << "Renderer couldn't be created!\n";
					this->quit = true;
				}
				else
				{
					if (TTF_Init() != 0)
						std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;

					//SDL_RenderSetLogicalSize(renderer, RESOLUTION_X, RESOLUTION_Y);
					this->gameMenu = new menu::GameMenu(this->renderer);
					this->mapPiece.loadFromFile(this->renderer, "data/Images/MapPiece.png");
				}
			}
			//SDL_MaximizeWindow(window);
		}
	}


	VirtualWorld::~VirtualWorld()
	{
		SDL_DestroyWindow(this->window);
		this->window = 0;
		SDL_DestroyRenderer(this->renderer);
		this->renderer = 0;
		this->gameMenu->close();
		this->gameMenu = 0;
	}


	void VirtualWorld::gameLoop()
	{
		while (!(this->quit))
		{
			this->handleKeyboardInput();
			this->draw();
			this->drawActiveTurn();
		}
	}


	void VirtualWorld::handleKeyboardInput()
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				this->quit = true;
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->menuOption(this->gameMenu->mainLoop());
					break;
				case SDLK_SPACE:
					system("cls");
					this->makeTurn();
					break;
				default:
					break;
				}
			}
		}
	};


	void VirtualWorld::state()
	{
		TTF_Font* temp;
		temp = TTF_OpenFont("data/Fonts/DosLike.ttf", (int)(FONT_MENU_SIZE / 1.5));
		int zoo[10] = { 0 };
		Texture zooPics[10];
		zooPics[Zoo::Human].loadFromFile(this->renderer, "data/Images/Cartman.png");
		zooPics[Zoo::Wolf].loadFromFile(this->renderer, "data/Images/Wolf.png");
		zooPics[Zoo::Fox].loadFromFile(this->renderer, "data/Images/Fox.png");
		zooPics[Zoo::Sheep].loadFromFile(this->renderer, "data/Images/Sheep.png");
		zooPics[Zoo::Antelope].loadFromFile(this->renderer, "data/Images/Antelope.png");
		zooPics[Zoo::Turtle].loadFromFile(this->renderer, "data/Images/Turtle.png");
		zooPics[Zoo::Grass].loadFromFile(this->renderer, "data/Images/Grass.png");
		zooPics[Zoo::Guarane].loadFromFile(this->renderer, "data/Images/Guarane.png");
		zooPics[Zoo::WolfBerries].loadFromFile(this->renderer, "data/Images/WolfBerries.png");
		zooPics[Zoo::SowThistle].loadFromFile(this->renderer, "data/Images/SowThistle.png");
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			if (allOrganisms[i]->getName() == "Human")
				zoo[Zoo::Human]++;
			else if (allOrganisms[i]->getName() == "Wolf")
				zoo[Zoo::Wolf]++;
			else if (allOrganisms[i]->getName() == "Fox")
				zoo[Zoo::Fox]++;
			else if (allOrganisms[i]->getName() == "Sheep")
				zoo[Zoo::Sheep]++;
			else if (allOrganisms[i]->getName() == "Antelope")
				zoo[Zoo::Antelope]++;
			else if (allOrganisms[i]->getName() == "Turtle")
				zoo[Zoo::Turtle]++;
			else if (allOrganisms[i]->getName() == "SowThistle")
				zoo[Zoo::SowThistle]++;
			else if (allOrganisms[i]->getName() == "WolfBerries")
				zoo[Zoo::WolfBerries]++;
			else if (allOrganisms[i]->getName() == "Grass")
				zoo[Zoo::Grass]++;
			else if (allOrganisms[i]->getName() == "Guarane")
				zoo[Zoo::Guarane]++;
		}
		SDL_Color color = { WHITE_COLOR };
		for (int i = 0; i < 10; i++)
		{
			Texture number;
			SDL_Point location = { 500, 20 };
			location.y += (30 * i);
			std::ostringstream ss;
			ss << zoo[i];
			std::string text = "x ";
			text += ss.str();
			zooPics[i].render(this->renderer, location);
			number.loadFromRederedText(this->renderer, temp, color, text);
			location.x += 30;
			number.render(this->renderer, location);
		}
		TTF_CloseFont(temp);
	}


	organisms::Organism& VirtualWorld::getOrganism(int index)
	{
		organisms::Organism* temp = this->allOrganisms[index];
		this->allOrganisms.erase(this->allOrganisms.begin() + index);
		return *temp;
	}


	void VirtualWorld::addOrganism(organisms::Organism& o)
	{
		this->allOrganisms.push_back(&o);
	}


	menu::GameMenu* VirtualWorld::getMenu()
	{
		return this->gameMenu;
	}


	SDL_Renderer* VirtualWorld::getRenderer()
	{
		return this->renderer;
	}


	std::string VirtualWorld::inputText()
	{
		SDL_Color color = { WHITE_COLOR };
		TTF_Font* font = TTF_OpenFont("data/Fonts/DosLike.ttf", (int)(FONT_MENU_SIZE / 1.5));
		Texture texts[2];
		texts[0].loadFromRederedText(this->renderer, font, color, "Input file name");
		std::string text = "";
		bool tQuit = false;
		SDL_StartTextInput();
		while (!tQuit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_TEXTINPUT && text.size() < 20)
				{
					text += e.text.text;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_BACKSPACE && text.size() > 0)
					{
						text.pop_back();
					}
					else if (e.key.keysym.sym == SDLK_RETURN && text.size() > 0)
					{
						tQuit = true;
					}
				}
				SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
				SDL_RenderClear(this->renderer);
				SDL_Point temp = { RESOLUTION_X / 2 - texts[0].getWidth() / 2, 200 };
				texts[0].render(renderer, temp);
				if (text.size() > 0)
				{
					texts[1].loadFromRederedText(this->renderer, font, color, text);
					temp = { RESOLUTION_X / 2 - texts[1].getWidth() / 2, 250 };
					texts[1].render(this->renderer, temp);
				}
				SDL_RenderPresent(renderer);
			}
		}
		SDL_StopTextInput();
		TTF_CloseFont(font);
		return text;
	}


	void VirtualWorld::saveGame()
	{
		try
		{
			std::string fileName = this->inputText();
			std::fstream fout;
			fout.open(fileName, std::ios::out);
			if (!fout.good())
			{
				throw Exception("Can't create entered file!\n");
			}
			for (int i = 0; i < (int)this->allOrganisms.size(); i++)
			{
				saveToFile(this->allOrganisms[i], fout);
			}
			fout.close();
		}
		catch (Exception& ex)
		{
			std::cout << "Exception: " << ex.text;
		}
	}


	void VirtualWorld::loadGame()
	{
		try
		{
			std::string fileName = this->inputText();
			std::fstream fin;
			fin.open(fileName, std::ios::in);
			this->allOrganisms.clear();
			if (!fin.good())
				throw RepeatException("Can't open file!\n");
			if (this->allOrganisms.size() <= 0)
				this->allOrganisms.clear();
			while (!fin.eof())
			{
				std::string name;
				SDL_Point temp;
				int strength;
				fin >> name;
				fin >> name;
				fin >> temp.x;
				fin >> temp.y;
				fin >> strength;
				if (name == "Human")
				{
					this->allOrganisms.push_back(new organisms::Human(this, temp));
				}
				else if (name == "Wolf")
				{
					this->allOrganisms.push_back(new organisms::Wolf(this, temp));
				}
				else if (name == "Fox")
				{
					this->allOrganisms.push_back(new organisms::Fox(this, temp));
				}
				else if (name == "Sheep")
				{
					this->allOrganisms.push_back(new organisms::Sheep(this, temp));
				}
				else if (name == "Turtle")
				{
					this->allOrganisms.push_back(new organisms::Turtle(this, temp));
				}
				else if (name == "Antelope")
				{
					this->allOrganisms.push_back(new organisms::Antelope(this, temp));
				}
				else if (name == "Grass")
				{
					this->allOrganisms.push_back(new organisms::Grass(this, temp));
				}
				else if (name == "SowThistle")
				{
					this->allOrganisms.push_back(new organisms::SowThistle(this, temp));
				}
				else if (name == "Guarane")
				{
					this->allOrganisms.push_back(new organisms::Guarane(this, temp));
				}
				else if (name == "WolfBerries")
				{
					this->allOrganisms.push_back(new organisms::WolfBerries(this, temp));
				}
			}
			fin.close();
		}
		catch (RepeatException& ex)
		{
			std::cout << "Exception: " << ex.text;
			this->loadGame();
		}
	}


	void VirtualWorld::drawActiveTurn()
	{
		TTF_Font* tempFont;
		SDL_Color color = { WHITE_COLOR };
		const std::string text[2] = { "Next Round", "Press Space" };
		Texture textures[2];

		tempFont = TTF_OpenFont("data/Fonts/DosLike.ttf", (double)(FONT_MENU_SIZE / 2.5));
		for (int i = 0; i < 2; i++)
		{
			textures[i].loadFromRederedText(this->renderer, tempFont, color, text[i]);
			SDL_Point renderPoint;
			renderPoint.x = GAME_STATE_X + ((RESOLUTION_X - GAME_STATE_X) / 2) - textures[i].getWidth() / 2;
			renderPoint.y = GAME_STATE_Y + (i * 20);
			textures[i].render(this->renderer, renderPoint);
		}
		SDL_RenderPresent(this->renderer);
		TTF_CloseFont(tempFont);
	}


	std::vector<organisms::Organism*>& VirtualWorld::getAllOrganisms()
	{
		return this->allOrganisms;
	}


	void VirtualWorld::makeTurn()
	{
		std::cout << "*****PRESENT TURN*****\n";
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			if (this->allOrganisms[i]->getInitiative() == 7)
			{
				this->allOrganisms[i]->action();
			}
		}
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			if (this->allOrganisms[i]->getInitiative() == 5)
			{
				this->allOrganisms[i]->action();
			}
		}
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			if (this->allOrganisms[i]->getInitiative() == 4)
			{
				this->allOrganisms[i]->action();
			}
		}
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			if (this->allOrganisms[i]->getInitiative() == 1)
			{
				this->allOrganisms[i]->action();
			}
		}
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			if (this->allOrganisms[i]->getInitiative() == 0)
			{
				this->allOrganisms[i]->action();
			}
		}
	}


	void VirtualWorld::newGame()
	{
		this->allOrganisms.clear();
		this->addHuman();
		this->addPlants();
		this->addAnimals();
	}


	void VirtualWorld::addHuman()
	{
		SDL_Point tempLocation = this->randPoint();
		this->allOrganisms.push_back(new organisms::Human(this, tempLocation));
	}


	SDL_Point VirtualWorld::randPoint()
	{
		int placeX = rand() % WORLD_SIZE;
		int placeY = rand() % WORLD_SIZE;
		SDL_Point temp = { placeX, placeY };
		return temp;
	}


	void VirtualWorld::addAnimals()
	{
		this->addWolfs();
		this->addSheeps();
		this->addFoxes();
		this->addTurtles();
		this->addAntelopes();
	}


	void VirtualWorld::addPlants()
	{
		this->addWolfBerries();
		this->addGrass();
		this->addSowThistles();
		this->addGuaranes();

	}


	void VirtualWorld::menuOption(const int option)
	{
		switch (option)
		{
		case Menu::NewGame:
			this->newGame();
			this->gameLoop();
			break;
		case Menu::Continue:
			this->gameLoop();
			break;
		case Menu::LoadGame:
			this->loadGame();
			this->gameLoop();
			break;
		case Menu::SaveGame:
			this->saveGame();
			this->gameLoop();
			break;
		case Menu::Exit:
			this->quit = true;
			break;
		default:
			break;
		}
	}


	void VirtualWorld::draw()
	{
		SDL_SetRenderDrawColor(this->renderer, BACKGROUND_COLOR);
		SDL_RenderClear(this->renderer);
		for (int i = 0; i < WORLD_SIZE; i++)
		{
			for (int j = 0; j < WORLD_SIZE; j++)
			{
				SDL_Point temp = { i*SQUARE_SIZE, j*SQUARE_SIZE };
				this->mapPiece.render(this->renderer, temp);
			}
		}
		for (int i = 0; i < (int)this->allOrganisms.size(); i++)
		{
			this->allOrganisms[i]->draw();
		}
		this->state();
		SDL_RenderPresent(this->renderer);
	}


	void VirtualWorld::addTurtles()
	{
		int n = (rand() % 4) + 2;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Turtle(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addAntelopes()
	{
		int n = (rand() % 5) + 2;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Antelope(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addWolfs()
	{
		int n = (rand() % 3) + 2;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Wolf(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addSheeps()
	{
		int n = (rand() % 6) + 2;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Sheep(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addFoxes()
	{
		int n = (rand() % 4) + 2;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Fox(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addGrass()
	{
		int n = (rand() % 30) + 15;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Grass(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addGuaranes()
	{
		int n = (rand() % 5) + 5;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::Guarane(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addSowThistles()
	{
		int n = (rand() % 10) + 5;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::SowThistle(this, tempLocation));
					break;
				}
			}
		}
	}


	void VirtualWorld::addWolfBerries()
	{
		int n = (rand() % 4) + 1;
		for (int i = 0; i < n; i++)
		{
			while (true)
			{
				bool addable = true;
				SDL_Point tempLocation = this->randPoint();
				for (int j = 0; j < (int)this->allOrganisms.size(); j++)
				{
					if (tempLocation.x == this->allOrganisms[j]->getLocation().x && tempLocation.y == this->allOrganisms[j]->getLocation().y)
					{
						addable = false;
						break;
					}
				}
				if (addable)
				{
					this->allOrganisms.push_back(new organisms::WolfBerries(this, tempLocation));
					break;
				}
			}
		}
	}
}
