#include "Grass.h"


namespace organisms
{
	Grass::Grass(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 0;
		this->strength = 0;
		this->location = location;
		this->world = world;
		this->name = "Grass";
		this->isAfterAction = false;	
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Grass.png");
	}


	Grass::Grass(Grass& a)
	{
		this->name = a.name;
		this->strength = a.strength;
		this->location = a.location;
		this->oldLocation = a.oldLocation;
		this->initiative = a.initiative;
		this->world = a.world;
		this->isAfterAction = a.isAfterAction;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Grass.png");
	}


	Grass::~Grass()
	{
	}


	void Grass::action()
	{
		if (!this->isAfterAction)
		{
			std::vector<SDL_Point> availableSquares;
			int place;
			this->addAllSquares(availableSquares);
			int seeding = rand() % 100;
			if (seeding < SEEDING_PROBABILITY)
			{
				std::vector<SDL_Point> freeSquares;
				for (int i = 0; i < (int)availableSquares.size(); i++)
				{
					bool isFree = true;
					for (int j = 0; j < (int)this->world->getAllOrganisms().size(); j++)
					{
						if (availableSquares[i].x == this->world->getAllOrganisms()[j]->getLocation().x &&
							availableSquares[i].y == this->world->getAllOrganisms()[j]->getLocation().y)
						{
							isFree = false;
							break;
						}
					}
					if (isFree)
						freeSquares.push_back(availableSquares[i]);
				}
				if (freeSquares.size() > 0)
				{
					place = rand() % (int)freeSquares.size();
					this->world->getAllOrganisms().push_back(new Grass(this->world, freeSquares[place]));
					this->world->getAllOrganisms()[this->world->getAllOrganisms().size() - 1]->setAfterAction();
					this->isAfterAction = false;
					this->collision();
					this->world->draw();
					SDL_Delay(PLANT_SPEED);
				}
			}
		}
	}


	void Grass::collision()
	{
		Plant::collision();
	}
}