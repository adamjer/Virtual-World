#pragma once
#include"Plant.h"


namespace organisms
{
	class WolfBerries : public Plant
	{
	public:
		WolfBerries(worlds::VirtualWorld*, SDL_Point&);
		WolfBerries(WolfBerries&);
		~WolfBerries();

		void action();
		void collision();
	};
}

