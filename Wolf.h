#pragma once
#include"Animal.h"

namespace organisms
{
	class Wolf : public Animal
	{
	public:
		Wolf(worlds::VirtualWorld*, SDL_Point&);
		Wolf(Wolf&);
		~Wolf();

		void action();
		void collision();

	private:
		void multipflication();
	};
}

