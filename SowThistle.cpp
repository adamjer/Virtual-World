#include "SowThistle.h"


namespace organisms
{
	SowThistle::SowThistle(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 0;
		this->strength = 0;
		this->location = location;
		this->world = world;
		this->name = "SowThistle";		
		this->isAfterAction = false;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/SowThistle.png");
	}


	SowThistle::SowThistle(SowThistle& a)
	{
		this->initiative = a.initiative;
		this->strength = a.strength;
		this->location = a.location;
		this->world = a.world;
		this->name = a.name;
		this->isAfterAction = a.isAfterAction;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/SowThistle.png");
	}


	SowThistle::~SowThistle()
	{
	}


	void SowThistle::action()
	{
		if (!this->isAfterAction)
		{
			for (int k = 0; k < 3; k++)
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
					if ((int)freeSquares.size() > 0)
					{
						place = rand() % (int)freeSquares.size();
      					this->world->getAllOrganisms().push_back(new SowThistle(this->world, freeSquares[place]));
						this->world->getAllOrganisms()[this->world->getAllOrganisms().size() - 1]->setAfterAction();
						this->isAfterAction = false;
						this->collision();
						this->world->draw();
						SDL_Delay(PLANT_SPEED);
					}
				}
			}
		}
	}


	void SowThistle::collision()
	{
		Plant::collision();
	}
}
