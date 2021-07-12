#pragma once
#include"Headers.h"
#include"GameMenu.h"
#include"Wolf.h"
#include"Sheep.h"
#include"Fox.h"
#include"Antelope.h"
#include"Turtle.h"
#include"Human.h"
#include"Grass.h"
#include"SowThistle.h"
#include"Guarane.h"
#include"WolfBerries.h"
#include"myExceptions.h"

/*
namespace worlds
{
	class VirtualWorld
	{
	public:
		VirtualWorld();
		~VirtualWorld();

		void menuOption(const int);
		menu::GameMenu* getMenu();
		SDL_Renderer* getRenderer();
		std::vector<organisms::Organism*>& getAllOrganisms();
		void draw();
		void addOrganism(organisms::Organism&);
		organisms::Organism& getOrganism(int);

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event e;
		menu::GameMenu* gameMenu;
		Texture mapPiece;
		bool quit;
		std::vector<organisms::Organism*> allOrganisms;

		void handleKeyboardInput();
		void gameLoop();
		void makeTurn();
		void newGame();
		void addHuman();
		void addPlants();
		void addAnimals();
		void addWolfs();
		void addSheeps();
		void addFoxes();
		void addTurtles();
		void addAntelopes();
		void addGrass();
		void addSowThistles();
		void addGuaranes();
		void addWolfBerries();
		void state();
		std::string inputText();
		void saveGame();
		void loadGame();
		void drawActiveTurn();
		static SDL_Point randPoint();
	};
}*/


template<typename T>
void saveToFile(T& t, std::ostream& out)
{
	out << "----------\n";
	out << t;
}