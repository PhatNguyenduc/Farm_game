#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "commonFunction.h"
#include "BaseObject.h"
#define SPEED 5
class Player : public BaseObject {
public:
	Player();
	~Player();
	
	bool LoadImg(string path, SDL_Renderer* grenderer);
	void show(SDL_Renderer* grenderer);
	void HandleInput(SDL_Event event, SDL_Renderer* grenderer);
	void set_clip();
	void Moving(MAP& map_data);
	//SDL_Rect Get_Rect();
	void SetMapXY(const int MAP_X, const int MAP_Y) { map_x = MAP_X,map_y = MAP_Y; };
	void Stop();
	void CenterMap_on_player(MAP& map_data);
private:
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int frame_w;
	int frame_h;

	int map_x;
	int map_y;

	SDL_Rect frame_clip[4];
	int frame;
	Input move;


};
#endif // !PLAYER_H
