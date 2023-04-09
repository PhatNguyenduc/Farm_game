#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "commonFunction.h"
#include "BaseObject.h"

const int SPEED = 3;
const int APPLE = 52;
const int PADDY = 53;
const int CARROT = 54;
const int TOMATO = 55;
const int PUMPKIN = 56;
const int EGG = 68;
const int EMPTY_EGG = 69;
const int EMPTY_APPLE = 80;
const int WOOD = 47;



class Player : public BaseObject {
public:
	Player();
	~Player();
	enum
	{
		
		DOWN = 0,
		UP = 1,
		RIGHT = 2,
		LEFT = 3,
	};
	bool LoadImg(string path, SDL_Renderer* grenderer);
	void show(SDL_Renderer* grenderer);
	void HandleInput(SDL_Event event, SDL_Renderer* grenderer);
	void set_clip();
	void Moving(MAP& map_data);
	void cycle_player();
	float get_x_pos() { return x_pos; };
	float get_y_pos() { return y_pos; };

	
	void SetMapXY(const int MAP_X, const int MAP_Y) { map_x = MAP_X,map_y = MAP_Y; };
	void Stop();
	void CenterMap_on_player(MAP& map_data);
	void collision(MAP& map_data);

	void increase_apple() { apple++; };
	void increase_paddy() { paddy++; };
	void increase_carrot() { carrot++; };
	void increase_pumpkin() { pumpkin++; };
	void increase_egg() { egg++; };
	void increase_wood() { wood++; };
	void increase_tomato() { tomato++; };
	
	int paddy = 0;
	int tomato = 0;
	int carrot = 0;
	int pumpkin = 0;
	int egg = 0;
	int apple = 0;
	int wood = 0;
	
	
private:
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int frame_w;
	int frame_h;

	int map_x;
	int map_y;

	SDL_Rect frame_clip[8];
	int frame;
	Input move;
	int status;
	


};
#endif // !PLAYER_H
