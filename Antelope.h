#pragma once
#include"Animal.h"


namespace organisms
{
	class Antelope : public Animal
	{
	public:
		Antelope(worlds::VirtualWorld* , SDL_Point&);
		Antelope(Antelope&);
		~Antelope();

		void action();
		void collision();

	private:
		void addMoreSquares(std::vector<SDL_Point>&);
		void multipflication();
	};
}

