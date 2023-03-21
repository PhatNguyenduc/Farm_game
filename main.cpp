#include"commonFunction.h"
#include"BaseObject.h"
#include"Player.h"
#include"OtherObject.h"
BaseObject background;
Player player;
Object fountain;
Object water;
Object tree;
Object Chicken;
const int FPS = 60;
const int frame_Delay = 1000 / FPS;

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "khoi tao SDL2 that bai! ERROR log: " << SDL_GetError() << std::endl;
		success = false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gwindow = SDL_CreateWindow(" FARM ",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN);

	if (gwindow == NULL)
	{
		success = false;
	}
	else
	{
		grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (grenderer == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(grenderer, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))

			{
				success = false;
			}

		}
	}
	return success;
}


bool Load_BackGround()
{	
	bool res = background.Load_Img("Image_game//background2.png", grenderer);
	if (res == false) {
		return false;
	}
	return true;
}


void close()
{
	
	background.Free();
	
	SDL_DestroyRenderer(grenderer);
	SDL_DestroyWindow(gwindow);
	gwindow = NULL;
	grenderer = NULL;
	IMG_Quit();
	SDL_Quit();

}
bool checkcollision(const SDL_Rect& a, const SDL_Rect& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w / 7;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w / 7;
	topB = b.y;
	bottomB = b.y + b.h;
	//Here is where the collision detection happens.This code calculates the top / bottom and left / right of each of the collison boxes.
		//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
int main(int argc, char* argv[])
{	
	if (init() == false)
	{
		return -1;
	}
	if (Load_BackGround() == false)
	{
		return -1;
	}
	
	player.LoadImg("Image_game//player.png", grenderer);
	player.set_clip();
	
	Uint32 frame_start ;
	int frame_time ;
	bool is_quit = false;
	while (!is_quit) 
	{
		frame_start = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			player.HandleInput(event, grenderer);
			

		}
		player.Moving();

		SDL_SetRenderDrawColor(grenderer, 255, 255, 255, 255);
		SDL_RenderClear(grenderer);

		background.Render(grenderer, NULL);
		player.show(grenderer);
		fountain.obj_show("Image_game//fountain2.png", grenderer);
		fountain.cycle_obj();
		water.obj_show("Image_game//waterfall.png",grenderer);
		water.cycle_obj();
		tree.Load_Img("Image_game//Tree.png", grenderer);
		Chicken.obj_show("Image_game//chicken.png", grenderer);	
		tree.Render(grenderer,NULL);
		Chicken.cycle_obj();
		
		fountain.setPos(WIDTH/4*3,HEIGHT/4*3);
		water.setPos(WIDTH/2,0);
		tree.setPos(400,400);
		Chicken.setPos(WIDTH / 3, HEIGHT / 2);

		if (checkcollision(player.GetRect(), fountain.GetRect()))
		{
			player.Stop();
		}
		if (checkcollision(player.GetRect(), water.GetRect()))
		{
			player.Stop();
		}
		if (checkcollision(player.GetRect(), tree.Get_Rect()))
		{
			player.Stop();
		}
		water.Free();
		player.Free();
		fountain.Free();
		tree.Free();
		Chicken.Free();


		SDL_RenderPresent(grenderer);

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_Delay > frame_time) { SDL_Delay(frame_Delay - frame_time); }
		
	}
	close();
	return 0;
}