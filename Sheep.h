#pragma once
#include"Animal.h"

namespace organisms
{
	class Sheep : public Animal
	{
	public:
		Sheep(worlds::VirtualWorld*, SDL_Point&);
		Sheep(Sheep&);
		~Sheep();

		void action();
		void collision();

	private:
		void multipflication();
	};
}

