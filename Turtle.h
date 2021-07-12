#pragma once
#include"Animal.h"


namespace organisms
{
	class Turtle : public Animal
	{
	public:
		Turtle(worlds::VirtualWorld*, SDL_Point&);
		Turtle(Turtle&);
		~Turtle();

		void action();
		void collision();

	private:
		int actionCounter;

		void multipflication();
	};
}

