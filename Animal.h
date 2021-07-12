#pragma once
#include"Organism.h"


namespace organisms
{
	class Animal : public Organism
	{
	public:
		virtual void action() = 0;
		virtual void collision() = 0;
	};
}

