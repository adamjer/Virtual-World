#include "Antelope.h"


namespace organisms
{
	Antelope::Antelope(worlds::VirtualWorld* world, SDL_Point& location)
	{
		this->initiative = 4;
		this->strength = 4;
		this->location = location;
		this->world = world;
		this->name = "Antelope";
		this->isAfterAction = false;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Antelope.png");
	}


	Antelope::Antelope(Antelope& a)
	{
		this->name = a.name;
		this->strength = a.strength;
		this->location = a.location;
		this->oldLocation = a.oldLocation;
		this->initiative = a.initiative;
		this->world = a.world;
		this->isAfterAction = a.isAfterAction;
		this->texture.loadFromFile(this->world->getRenderer(), "data/Images/Antelope.png");
	}


	Antelope::~Antelope()
	{
	}


	void Antelope::action()
	{
		if (!this->isAfterAction)
		{
			std::vector<SDL_Point> availableSquares;
			this->addMoreSquares(availableSquares);
			int place = rand() % availableSquares.size();
			this->oldLocation = this->location;
			this->location = availableSquares[place];
		}
		this->isAfterAction = false;
		this->collision();
		this->world->draw();
		SDL_Delay(ANIMAL_SPEED);
	}


	void Antelope::collision()
	{
		this->multipflication();
		Animal::collision();
	}


	void Antelope::multipflication()
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
				std::cout << "Antelopes multipflied!\n";
				int place = rand() % (int)freeSquares.size();
				this->world->getAllOrganisms().push_back(new Antelope(this->world, freeSquares[place]));
				this->world->getAllOrganisms()[this->world->getAllOrganisms().size() - 1]->setAfterAction();
				this->world->getAllOrganisms()[female]->setAfterAction();
			}
		}
	}


	void Antelope::addMoreSquares(std::vector<SDL_Point>& availableSquares)
	{
		int startX = this->location.x - 2;
		int startY = this->location.y - 2;
		int endX = this->location.x + 2;
		int endY = this->location.y + 2;
		if (startX < 0)
			startX = 0;
		else if (endX >= WORLD_SIZE)
			endX = WORLD_SIZE - 1;
		if (startY < 0)
			startY = 0;
		else if (endY >= WORLD_SIZE)
			endY = WORLD_SIZE - 1;
		for (int i = startX; i <= endX; i++)
		{
			for (int j = startY; j <= endY; j++)
			{
				if (i == this->location.x && j == this->location.y)
					continue;
				SDL_Point temp = { i, j };
				availableSquares.push_back(temp);
			}
		}
	}
}
