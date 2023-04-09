#pragma once
#ifndef TEXT_H
#define TEXT_H
#include"commonFunction.h"

class text {
public:
	text();
	~text();
	enum {
		RED = 0,
		WHITE = 1,
		BLACK = 2,
	};
	bool Load_from_file(string path);
	bool LoadFromRenderText(TTF_Font* gfont, SDL_Renderer* grenderer);
	void Free();
	void Set_Color(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* grenderer, 
		int xp, int yp, SDL_Rect* clip = NULL, 
		double angle = 0.0, SDL_Point* center = NULL, 
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth()const { return width; }
	int GetHeight()const { return height; }
	void SetText(string& text){str_val=text;}
	string GetText()const { return str_val; }
private:
	string str_val;
	SDL_Color text_color;
	SDL_Texture* text_ture;
	int width;
	int height;

};
#endif // !TEXT_H
