#pragma once
#include"Plant.h"


namespace organisms
{
	class SowThistle : public Plant
	{
	public:
		SowThistle(worlds::VirtualWorld*, SDL_Point&);
		SowThistle(SowThistle&);
		~SowThistle();

		void action();
		void collision();
	};
}

