#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include<vector>

#include"Texture.h"

#define RESOLUTION_X	640
#define RESOLUTION_Y	480
#define SQUARE_SIZE	24
#define WORLD_SIZE	20
#define FONT_MENU_SIZE	30
#define MENU_SIZE	5
#define SEEDING_PROBABILITY 4
#define GAME_STATE_X	(WORLD_SIZE * SQUARE_SIZE)
#define GAME_STATE_Y	400
#define ANIMAL_SPEED 200
#define PLANT_SPEED 100

#define BLACK_COLOR	0, 0, 0
#define RED_COLOR	255, 0, 0
#define GREY_COLOR	216, 216, 216
#define WHITE_COLOR	255, 255, 255
#define BACKGROUND_COLOR	0, 0, 200, 0


enum Menu
{
	NewGame,
	Continue,
	LoadGame,
	SaveGame,
	Exit
};


enum Directions
{
	Up,
	Down,
	Right,
	Left,
	Activation
};


enum Zoo
{
	Human,
	Wolf,
	Sheep,
	Fox,
	Turtle,
	Antelope,
	Grass,
	SowThistle,
	Guarane,
	WolfBerries
};