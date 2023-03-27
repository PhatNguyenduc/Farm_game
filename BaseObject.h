#pragma once

#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H


#include"commonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void Set_Rect(const int& X, const int& Y) {
		rect.x = X;
		rect.y = Y;

	}
	SDL_Rect GetRect() const {
		return rect;
	}
	SDL_Texture* GetObject() const {
		return p_object;
	}

	virtual bool Load_Img(std::string path, SDL_Renderer* grenderer);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Texture* p_object;
	SDL_Rect rect;

};

#endif // !BASE_OBJECT_H
