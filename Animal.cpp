#include "Animal.h"

namespace organisms
{
	void Animal::action()
	{
		if (!this->isAfterAction)
		{
			std::vector<SDL_Point> availableSquares;
			this->addAllSquares(availableSquares);
			int place = rand() % availableSquares.size();
			this->oldLocation = this->location;
			this->location = availableSquares[place];
		}
		this->isAfterAction = false;
		this->world->draw();
		SDL_Delay(ANIMAL_SPEED);
	}


	void Animal::collision()
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
				if (this->world->getAllOrganisms()[defender]->getName() == "Turtle" && this->strength < 5)
				{
					std::cout << "Turtle defended himself!\n";
					this->location = this->oldLocation;
				}
				else if (this->world->getAllOrganisms()[defender]->getName() == "Antelope")
				{
					std::vector<SDL_Point> availableSquares;
					this->addAllSquares(availableSquares);
					int escape = rand() % 100;
					if (escape < 50)
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
							std::cout << "Antelope fled from battle!\n";
							int place = rand() % (int)freeSquares.size();
							this->world->getAllOrganisms()[defender]->setLocation(freeSquares[place]);
						}
					}
				}
				else
				{
					std::cout << this->name << " ate " << this->world->getAllOrganisms()[defender]->getName() << std::endl;
					if (this->world->getAllOrganisms()[defender]->getName() == "Guarane")
					{
						this->setStrength(this->getStrength() + 3);
					}
					this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + defender);
				}
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
}
