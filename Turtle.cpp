#include "Turtle.h"


namespace organisms
{
	Turtle::Turtle(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 1;
		this->strength = 2;
		this->actionCounter = 0;
		this->location = location;
		this->world = world;
		this->name = "Turtle";
		this->isAfterAction = false;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Turtle.png");
	}


	Turtle::Turtle(Turtle& a)
	{
		this->initiative = a.initiative;
		this->strength = a.strength;
		this->location = a.location;
		this->world = a.world;
		this->name = a.name;
		this->isAfterAction = a.isAfterAction;
		this->actionCounter = a.actionCounter;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Turtle.png");
	}


	Turtle::~Turtle()
	{
	}


	void Turtle::action()
	{
		this->actionCounter++;
		if (this->actionCounter == 3)
		{
			Animal::action();
			this->actionCounter = 0;
		}
		this->collision();
		this->world->draw();
		SDL_Delay(ANIMAL_SPEED);
	}


	void Turtle::collision()
	{
		this->multipflication();
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
				if (this->world->getAllOrganisms()[defender]->getName() == "Antelope")
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
				if (this->world->getAllOrganisms()[defender]->getStrength() < 5)
				{
					std::cout << "Turtle defended himself!\n";
					this->world->getAllOrganisms()[defender]->setLocation(this->world->getAllOrganisms()[defender]->getOldLocation());
					return;
				}
				std::cout << this->name << " was eaten by " << this->world->getAllOrganisms()[defender]->getName() << std::endl;
				if (this->world->getAllOrganisms()[defender]->getName() == "WolfBerries")
					this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + defender);
				this->world->getAllOrganisms().erase(this->world->getAllOrganisms().begin() + attacker);
			}
		}
	}


	void Turtle::multipflication()
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
				std::cout << "Turtles multiplied!\n";
				int place = rand() % (int)freeSquares.size();
				this->world->getAllOrganisms().push_back(new Turtle(this->world, freeSquares[place]));
				this->world->getAllOrganisms()[this->world->getAllOrganisms().size() - 1]->setAfterAction();
				this->world->getAllOrganisms()[female]->setAfterAction();
			}
		}
	}
}
