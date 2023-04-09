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
#include<cmath>
#include<math.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>

const int APPLE = 52;
const int PADDY = 53;
const int CARROT = 54;
const int TOMATO = 55;
const int PUMPKIN = 56;
const int EGG = 68;
const int EMPTY_EGG = 69;
const int EMPTY_APPLE = 80;
const int WOOD = 47;

using namespace std;


static SDL_Window* gwindow = NULL;
static SDL_Renderer* grenderer = NULL;
static SDL_Event event;

//screen

const float WIDTH = 1280;
const float HEIGHT = 640;
const int FPS = 60;



const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int TILE_SIZE = 64;
const int  MAX_MAP_X = 50;
const int MAX_MAP_Y = 35;
typedef struct Input
{
	int left;
	int right;
	int up;
	int down;
};
typedef struct MAP {
	int start_x	 ;
	int start_y	 ;

	int max_x  ;
	int max_y  ;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;

};

#endif
