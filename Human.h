#pragma once
#include"Animal.h"


namespace organisms
{
	class Human : public Animal
	{
	public:
		Human(worlds::VirtualWorld*, SDL_Point&);
		Human(Human&);
		~Human();
		
		void action();
		void collision();
		void setSuperPower();
		void draw();

	private:
		bool isSuperPowerActive;
		int superPowerCounter;
		Texture superPower;

		void destroy();
		int setDirection();
		void drawYourTurn();
	};
}

