#pragma once
#ifndef MENU_H
#define MENU_H

#include"commonFunction.h"
#include"Text.h"
#pragma once
#include"BaseObject.h"
#include"Text.h"
#include"commonFunction.h"
#include"ImpTimer.h"

class Menu :public BaseObject{
public:
	int show_menu(SDL_Renderer* des, TTF_Font* font, ImpTimer& time_game);
	bool checkFocuswithRect(int& x, int& y, int& w, int& h, const SDL_Rect& rect);

};

#endif // !MENU_H
