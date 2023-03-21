#pragma once
#ifndef MAP_H
#define MAP_H

#include "commonFunction.h"
#include "BaseObject.h"
#define MAX_TILES 50
class Tile : public BaseObject
{
public:
	Tile() { ; }
	~Tile() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(char* name);
	void LoadTile(SDL_Renderer* grenderer);
	void DrawMap(SDL_Renderer* grenderer);
private:
	Map game_map_;
	Tile tile_map[MAX_TILES];


};

#endif // !MAP_H
