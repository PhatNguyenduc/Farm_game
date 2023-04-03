#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H
#include"BaseObject.h"
#include "commonFunction.h"

class Animal :public BaseObject
{
public:
	Animal();
	~Animal();
	void set_x_val(const float& xval) { x_val = xval; }
	void set_y_val(const float& yval) { y_val = yval; }
	void set_x_pos(const float& xpos) { x_pos = xpos; }
	void set_y_pos(const float& ypos) { y_pos = ypos; }
	void set_MapXY(const int& mapx, const int& mapy) { map_x = mapx; map_y = mapy; }

	void set_clip();
	bool LoadImg(string path,SDL_Renderer* grenderer);
	void Show(SDL_Renderer* grenderer);
	int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }
	void doPlayer(MAP& map_data);
	void ChecktoMap(MAP& map_data);

private:
	float x_pos;
	float y_pos;
	float x_val;
	float y_val;
	int map_x;
	int map_y;
	SDL_Rect frame_clip[8];
	int width_frame;
	int height_frame;
	int frame;

};
#endif // !ANIMAL_H
