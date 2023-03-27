#pragma once
#ifndef ORTHER_H
#define ORTHER_H

#include "commonFunction.h"
#include "BaseObject.h"
#include "Player.h"

class Object : public BaseObject {
public:
	Object();
	~Object();
	bool Load_object(string path, SDL_Renderer* grenderer);
	void obj_show(string path,SDL_Renderer*grenderer);
	void cycle_obj();
	void setPos(const int& x, const int& y) { rect.x = x;  rect.y = y; };

private:
	float obj_xpos;
	float obj_ypos;

	int obj_frame_w;
	int obj_frame_h;

	SDL_Rect obj_frame_clip[7];
	int obj_frame;

	
};

#endif // !ORTHER_H
