#pragma once
#include"Headers.h"
#include"World.h"

int main(int argc, char **argv)
{
	srand((unsigned)time(0));
	worlds::VirtualWorld world;
	world.menuOption(world.getMenu()->mainLoop());

	/*worlds::VirtualWorld world2;
	world2.addOrganism(world.getOrganism(0));
	world2.menuOption(world2.getMenu()->mainLoop());*/
	return 0;
}