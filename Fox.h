#pragma once
#include"Animal.h"


namespace organisms
{
	class Fox : public Animal
	{
	public:
		Fox(worlds::VirtualWorld*, SDL_Point&);
		Fox(Fox&);
		~Fox();

		void action();
		void collision();

	private:
		void multipflication();
	};
}

