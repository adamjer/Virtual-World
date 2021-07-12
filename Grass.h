#pragma once
#include"Plant.h"


namespace organisms
{
	class Grass : public Plant
	{
	public:
		Grass(worlds::VirtualWorld*, SDL_Point&);
		Grass(Grass&);
		~Grass();

		void action();
		void collision();
	};
}

