#pragma once
#include"Headers.h"

namespace menu
{
	class GameMenu;
}

namespace organisms
{
	class Organism;
}

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
}


namespace organisms
{
	class Organism
	{
	public:
		virtual ~Organism();
		virtual void action() = 0;
		virtual void collision() = 0;
		virtual void draw();
		virtual SDL_Point& getLocation();
		virtual SDL_Point& getOldLocation();
		virtual int getInitiative();
		virtual std::string getName();
		virtual int getStrength();
		virtual void setAfterAction();
		virtual void setStrength(int);
		virtual void setLocation(SDL_Point);
		void addAllSquares(std::vector<SDL_Point>&);
		friend std::ostream& operator<<(std::ostream&, Organism*);
		void display(std::ostream&);
		Texture& getTexture();

	protected:
		int strength;
		int initiative;
		bool isAfterAction;
		SDL_Point location;
		SDL_Point oldLocation;
		worlds::VirtualWorld* world;
		Texture texture;
		std::string name;

		void addBottom(std::vector<SDL_Point>&);
		void addTop(std::vector<SDL_Point>&);
		void addRight(std::vector<SDL_Point>&);
		void addLeft(std::vector<SDL_Point>&);
		void addBottomLeft(std::vector<SDL_Point>&);
		void addBottomRight(std::vector<SDL_Point>&);
		void addTopLeft(std::vector<SDL_Point>&);
		void addTopRight(std::vector<SDL_Point>&);
	};
}
