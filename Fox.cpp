#include "Fox.h"


namespace organisms
{
	Fox::Fox(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 7;
		this->strength = 3;
		this->location = location;
		this->world = world;
		this->name = "Fox";
		this->isAfterAction = false;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Fox.png");
	}


	Fox::Fox(Fox& a)
	{
		this->name = a.name;
		this->strength = a.strength;
		this->location = a.location;
		this->oldLocation = a.oldLocation;
		this->initiative = a.initiative;
		this->world = a.world;
		this->isAfterAction = a.isAfterAction;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Fox.png");
	}


	Fox::~Fox()
	{
	}


	void Fox::action()
	{
		if (!this->isAfterAction)
		{
			std::vector<SDL_Point> availableSquares;
			this->addAllSquares(availableSquares);
			for (int i = 0; i < (int)availableSquares.size(); i++)
			{
				for (int j = 0; j < (int)this->world->getAllOrganisms().size(); j++)
				{
					if (availableSquares[i].x == this->world->getAllOrganisms()[j]->getLocation().x && availableSquares[i].y == this->world->getAllOrganisms()[j]->getLocation().y)
					{
						if (this->strength < this->world->getAllOrganisms()[j]->getStrength() && this->name != this->world->getAllOrganisms()[j]->getName())
						{
							availableSquares.erase(availableSquares.begin() + i);
							break;
						}
					}
				}
			}
			if (availableSquares.size() > 0)
			{
				int place = rand() % availableSquares.size();
				this->oldLocation = this->location;
				this->location = availableSquares[place];
			}
		}
		this->isAfterAction = false;
		this->collision();
		this->world->draw();
		SDL_Delay(ANIMAL_SPEED);
	}


	void Fox::collision()
	{
		this->multipflication();
		Animal::collision();
	}


	void Fox::multipflication()
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
			else if (this->location.x == this->world->getAllOrganisms()[i]->getLocation().x && this->location.y == this->world->getAllOrganisms()[i]->getLocation().y)
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
					if (availableSquares[i].x == this->world->getAllOrganisms()[j]->getLocation().x && availableSquares[i].y == this->world->getAllOrganisms()[j]->getLocation().y)
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
				std::cout << "Foxes multiplied!\n";
				int place = rand() % (int)freeSquares.size();
				this->world->getAllOrganisms().push_back(new Fox(this->world, freeSquares[place]));
				this->world->getAllOrganisms()[this->world->getAllOrganisms().size() - 1]->setAfterAction();
				this->world->getAllOrganisms()[female]->setAfterAction();
			}
		}
	}
}
