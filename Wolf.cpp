#include "Wolf.h"


namespace organisms
{
	Wolf::Wolf(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 5;
		this->strength = 9;
		this->location = location;
		this->world = world;
		this->name = "Wolf";
		this->isAfterAction = false;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Wolf.png");
	}


	Wolf::Wolf(Wolf& a)
	{
		this->initiative = a.initiative;
		this->strength = a.strength;
		this->location = a.location;
		this->world = a.world;
		this->name = a.name;
		this->isAfterAction = a.isAfterAction;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Wolf.png");
	}


	Wolf::~Wolf()
	{
	}


	void Wolf::action()
	{
		Animal::action();
		this->collision();
		this->world->draw();
		SDL_Delay(ANIMAL_SPEED);
	}


	void Wolf::collision()
	{
		this->multipflication();
		Animal::collision();
	}


	void Wolf::multipflication()
	{
		bool alreadyTaken = false;
		int male = -1;
		int female = -1;
		for (int i = 0; i < (int)this->world->getAllOrganisms().size(); i++)
		{
			if (this == this->world->getAllOrganisms()[i])
			{
				male = i;
			}
			else if (this->location.x == this->world->getAllOrganisms()[i]->getLocation().x &&
				this->location.y == this->world->getAllOrganisms()[i]->getLocation().y)
			{
				female = i;
				alreadyTaken = true;
			}
		}
		if (alreadyTaken && this->name == this->world->getAllOrganisms()[female]->getName())
		{
			this->location = this->oldLocation;
			std::vector<SDL_Point> availableSquares;
			this->addAllSquares(availableSquares);
			this->world->getAllOrganisms()[female]->addAllSquares(availableSquares);
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
				std::cout << "Wolfes multiplied!\n";
				int place = rand() % (int)freeSquares.size();
				this->world->getAllOrganisms().push_back(new Wolf(this->world, freeSquares[place]));
				this->world->getAllOrganisms()[this->world->getAllOrganisms().size() - 1]->setAfterAction();
				this->world->getAllOrganisms()[female]->setAfterAction();
			}
		}
	}
}
