#pragma once
#include"Plant.h"


namespace organisms
{
	class Guarane : public Plant
	{
	public:
		Guarane(worlds::VirtualWorld*, SDL_Point&);
		Guarane(Guarane&);
		~Guarane();

		void action();
		void collision();
	};
}

