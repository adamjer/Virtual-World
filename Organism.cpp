#include "Organism.h"

namespace organisms
{
	Organism::~Organism()
	{
		this->world = NULL;
	}


	void Organism::draw()
	{
		SDL_Point temp = { this->location.x * SQUARE_SIZE, this->location.y * SQUARE_SIZE };
		this->texture.render(this->world->getRenderer(), temp);
	}


	std::ostream& operator<<(std::ostream& left, Organism* right)
	{
		right->display(left);
		return left;
	}


	Texture& Organism::getTexture()
	{
		return this->texture;
	}


	void Organism::display(std::ostream& out = std::cout)
	{
		out << this->name << '\n';
		out << this->location.x << '\n';
		out << this->location.y << '\n';
		out << this->strength << '\n';
	}


	int Organism::getInitiative()
	{
		return this->initiative;
	}


	std::string Organism::getName()
	{
		return this->name;
	}


	int Organism::getStrength()
	{
		return this->strength;
	}


	SDL_Point& Organism::getLocation()
	{
		return this->location;
	}


	SDL_Point& Organism::getOldLocation()
	{
		return this->oldLocation;
	}


	void Organism::setAfterAction()
	{
		this->isAfterAction = true;
	}


	void Organism::setStrength(int v)
	{
		this->strength = v;
	}


	void Organism::setLocation(SDL_Point l)
	{
		this->location = l;
	}


	void Organism::addAllSquares(std::vector<SDL_Point>& squareVector)
	{
		this->addBottom(squareVector);
		this->addTop(squareVector);
		this->addRight(squareVector);
		this->addLeft(squareVector);
		this->addBottomLeft(squareVector);
		this->addBottomRight(squareVector);
		this->addTopLeft(squareVector);
		this->addTopRight(squareVector);
	}


	void Organism::addBottom(std::vector<SDL_Point>& squareVector)
	{
		int placeY = this->location.y + 1;
		if (placeY < WORLD_SIZE)
		{
			SDL_Point temp = { this->location.x, placeY };
			squareVector.push_back(temp);
		}
	}


	void Organism::addTop(std::vector<SDL_Point>& squareVector)
	{
		int placeY = this->location.y - 1;
		if (placeY >= 0)
		{
			SDL_Point temp = { this->location.x, placeY };
			squareVector.push_back(temp);
		}
	}


	void Organism::addRight(std::vector<SDL_Point>& squareVector)
	{
		int placeX = this->location.x + 1;
		if (placeX < WORLD_SIZE)
		{
			SDL_Point temp = { placeX, this->location.y };
			squareVector.push_back(temp);
		}
	}


	void Organism::addLeft(std::vector<SDL_Point>& squareVector)
	{
		int placeX = this->location.x - 1;
		if (placeX >= 0)
		{
			SDL_Point temp = { placeX, this->location.y };
			squareVector.push_back(temp);
		}
	}


	void Organism::addBottomLeft(std::vector<SDL_Point>& squareVector)
	{
		int placeX = this->location.x - 1;
		int placeY = this->location.y + 1;
		if (placeX >= 0 && placeY < WORLD_SIZE)
		{
			SDL_Point temp = { placeX, placeY };
			squareVector.push_back(temp);
		}
	}


	void Organism::addBottomRight(std::vector<SDL_Point>& squareVector)
	{
		int placeX = this->location.x + 1;
		int placeY = this->location.y + 1;
		if (placeX < WORLD_SIZE && placeY < WORLD_SIZE)
		{
			SDL_Point temp = { placeX, placeY };
			squareVector.push_back(temp);
		}
	}


	void Organism::addTopLeft(std::vector<SDL_Point>& squareVector)
	{
		int placeX = this->location.x - 1;
		int placeY = this->location.y - 1;
		if (placeX >= 0 && placeY >= 0)
		{
			SDL_Point temp = { placeX, placeY };
			squareVector.push_back(temp);
		}
	}


	void Organism::addTopRight(std::vector<SDL_Point>& squareVector)
	{
		int placeX = this->location.x + 1;
		int placeY = this->location.y - 1;
		if (placeX < WORLD_SIZE && placeY >= 0)
		{
			SDL_Point temp = { placeX, placeY };
			squareVector.push_back(temp);
		}
	}
}
