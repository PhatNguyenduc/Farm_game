#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "commonFunction.h"
#include "BaseObject.h"
#define SPEED 2
class Player : public BaseObject {
public:
	Player();
	~Player();
	
	bool LoadImg(string path, SDL_Renderer* grenderer);
	void show(SDL_Renderer* grenderer);
	void HandleInput(SDL_Event event, SDL_Renderer* grenderer);
	void set_clip();
	void Moving();
	SDL_Rect Get_Rect();
	void Stop();
private:
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int frame_w;
	int frame_h;
	
	SDL_Rect frame_clip[4];
	int frame;
	Input move;


};
#endif // !PLAYER_H
