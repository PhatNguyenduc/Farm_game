#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include"commonFunction.h"
#include"BaseObject.h"

#define MAX_TILE 100
class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }

};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* grenderer);
	void Draw_Map(SDL_Renderer* grenderer);
	MAP getMap()const { return game_map; };
	void setMap(MAP& map_data) {
		game_map = map_data;
	};

private:
	MAP game_map;
	TileMap tile_map[MAX_TILE];

};

#endif // !GAME_MAP_H

