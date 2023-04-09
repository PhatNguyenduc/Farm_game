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
	float get_x_pos()const { return x_pos; }
	float get_y_pos()const { return y_pos; }
	void set_clip();
	void follow(const int& x, const int& y, MAP& map_data);
	void move_pet(MAP& map_data);
	
	bool LoadImg(string path,SDL_Renderer* grenderer);
	void Show(SDL_Renderer* grenderer);
	int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }
	void move_ani(MAP& map_data);
	void ChecktoMap(MAP& map_data);
	
	void Set_Area(const int & pos_a,const int & pos_b,const int& pos_c,const int &pos_d)
	{
			Lim_Left = pos_a, Lim_Right = pos_b,
			Lim_Up = pos_c, Lim_Down = pos_d;
	}
	void set_input_left(const int& ipLeft) { input_type.left = ipLeft; }
	
private:
	float x_pos;
	float y_pos;
	float x_val;
	float y_val;
	int Lim_Left;
	int Lim_Right;
	int Lim_Up;
	int Lim_Down;
	int map_x;
	int map_y;
	SDL_Rect frame_clip[8];
	int width_frame;
	int height_frame;
	int frame;
	SDL_RendererFlip flip;
	
	Input input_type;
	
};
#endif // !ANIMAL_H
