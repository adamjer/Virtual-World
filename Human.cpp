#include "Human.h"


namespace organisms
{
	Human::Human(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 4;
		this->strength = 5;
		this->location = location;
		this->world = world;
		this->name = "Human";
		this->isAfterAction = false;
		this->isSuperPowerActive = false;
		this->superPowerCounter = 0;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Cartman.png");
		this->superPower.loadFromFile(this->world->getRenderer(), "data/Images/CartmanCop.png");
	}


	Human::Human(Human& a)
	{
		this->name = a.name;
		this->strength = a.strength;
		this->location = a.location;
		this->oldLocation = a.oldLocation;
		this->initiative = a.initiative;
		this->world = a.world;
		this->isAfterAction = a.isAfterAction;
		this->isSuperPowerActive = a.isSuperPowerActive;
		this->superPowerCounter = a.superPowerCounter;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Cartman.png");
		this->superPower.loadFromFile(this->world->getRenderer(), "data/Images/CartmanCop.png");
	}


	Human::~Human()
	{
	}


	void Human::action()
	{
		this->drawYourTurn();
		this->oldLocation = this->location;
		int direction = this->setDirection();
		switch (direction)
		{
		case Directions::Up:
			this->location.y--;
			if (this->location.y < 0)
				this->location.y++;
			break;
		case Directions::Down:
			this->location.y++;
			if (this->location.y >= WORLD_SIZE)
				this->location.y--;
			break;
		case Directions::Left:
			this->location.x--;
			if (this->location.x < 0)
				this->location.x++;
			break;
		case Directions::Right:
			this->location.x++;
			if (this->location.x >= WORLD_SIZE)
				this->location.x--;
			break;
		case Directions::Activation:
			this->setSuperPower();
			break;
		}
		this->superPowerCounter--;
		if (this->superPowerCounter <= 5)
			this->isSuperPowerActive = false;
		if (isSuperPowerActive)
			this->destroy();
		this->collision();
		this->world->draw();
		SDL_Delay(ANIMAL_SPEED);
	}


	void Human::setSuperPower()
	{
		if (!this->isSuperPowerActive && this->superPowerCounter <= 0)
		{
			this->isSuperPowerActive = true;
			this->superPowerCounter = 11;
		}
	}


	void Human::drawYourTurn()
	{
		TTF_Font* tempFont;
		SDL_Color color = { WHITE_COLOR };
		const std::string text[2] = { "Your Round", "Use Arrows" };
		Texture textures[2];

		tempFont = TTF_OpenFont("data/Fonts/DosLike.ttf", FONT_MENU_SIZE / 2);
		for (int i = 0; i < 2; i++)
		{
			textures[i].loadFromRederedText(this->world->getRenderer(), tempFont, color, text[i]);
			SDL_Point renderPoint;
			renderPoint.x = GAME_STATE_X + ((RESOLUTION_X - GAME_STATE_X) / 2) - textures[i].getWidth() / 2;
			renderPoint.y = GAME_STATE_Y + (i * 25);
			textures[i].render(this->world->getRenderer(), renderPoint);
		}
		SDL_RenderPresent(this->world->getRenderer());
		TTF_CloseFont(tempFont);
	}


	void Human::destroy()
	{
		std::vector<SDL_Point> squares;
		this->addAllSquares(squares);
		for (int i = 0; i < squares.size(); i++)
		{
			for (int j = 0; j < (int)this->world->getAllOrganisms().size(); j++)
			{
				if (squares[i].x == this->world->getAllOrganisms()[j]->getLocation().x && 
					squares[i].y == this->world->getAllOrganisms()[j]->getLocation().y)
				{
					this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + j);
					j--;
					break;
				}
			}
		}
	}


	void Human::collision()
	{
		bool alreadyTaken = false;
		int defender = -1;
		int attacker = -1;
		for (int i = 0; i < (int)this->world->getAllOrganisms().size(); i++)
		{
			if (this == this->world->getAllOrganisms()[i])
			{
				attacker = i;
			}
			else if (this->location.x == this->world->getAllOrganisms()[i]->getLocation().x && 
				this->location.y == this->world->getAllOrganisms()[i]->getLocation().y)
			{
				defender = i;
				alreadyTaken = true;
			}
		}
		if (alreadyTaken)
		{
			if (this->strength >= this->world->getAllOrganisms()[defender]->getStrength())
			{
				std::cout << this->name << " ate " << this->world->getAllOrganisms()[defender]->getName() << std::endl;
				if (this->world->getAllOrganisms()[defender]->getName() == "Guarane")
					this->setStrength(this->getStrength() + 3);
				this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + defender);
			}
			else if (this->strength < this->world->getAllOrganisms()[defender]->getStrength())
			{
				std::cout << this->name << " was eaten by " << this->world->getAllOrganisms()[defender]->getName() << std::endl;
				if (this->world->getAllOrganisms()[defender]->getName() == "WolfBerries")
					this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + defender);
				this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + attacker);
			}
		}
	}


	void Human::draw()
	{
		SDL_Point temp = { this->location.x * SQUARE_SIZE, this->location.y * SQUARE_SIZE };
		if (this->isSuperPowerActive)
			this->superPower.render(this->world->getRenderer(), temp);
		else
			this->texture.render(this->world->getRenderer(), temp);
	}


	int Human::setDirection()
	{
		bool quit = false;
		SDL_Event e;
		int direction = -1;
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						direction = Directions::Up;
						quit = true;
						break;
					case SDLK_DOWN:
						direction = Directions::Down;
						quit = true;
						break;
					case SDLK_RIGHT:
						direction = Directions::Right;
						quit = true;
						break;
					case SDLK_LEFT:
						direction = Directions::Left;
						quit = true;
						break;
					case SDLK_c:
						direction = Directions::Activation;
						quit = true;
						break;
					}
				}
			}
		}
		return direction;
	}
}