#pragma once

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include <string>
#include<Windows.h>
using namespace std;


static SDL_Window* gwindow = NULL;
static SDL_Renderer* grenderer = NULL;
static SDL_Event event;

//screen

const int WIDTH = 1408;
const int HEIGHT = 704;
const int BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

typedef struct Input
{
	int left;
	int right;
	int up;
	int down;
};

namespace SDLCommonFunction
{
	bool Checkcollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif
