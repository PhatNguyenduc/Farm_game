#include"commonFunction.h"
#include"BaseObject.h"
#include"Player.h"
#include"OtherObject.h"
#include"Game_map.h"
#include"Animal.h"
#include <vector>
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


//bool Load_BackGround()
//{	
//	bool res = background.Load_Img("Image_game//background2.png", grenderer);
//	if (res == false) 
//	{
//		return false;
//	}
//	return true;
//}


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

vector<Animal*>animal()
{
	vector<Animal*>list_animal;
	Animal* animal = new Animal[5];
	for (int i = 0; i < 5; i++)
	{
		Animal* p_animal = (animal + i);
		if (p_animal != NULL)
		{
			p_animal->LoadImg("Image_game/catto.png", grenderer);
			p_animal->set_clip();
			p_animal->set_x_pos(i*200+400);
			p_animal->set_y_pos(300);

			list_animal.push_back(p_animal);

		}
	}
	return list_animal;
}
int main(int argc, char* argv[])
{	
	if (init() == false)
	{
		return -1;
	}
	/*if (Load_BackGround() == false)
	{
		return -1;
	}*/
	
	//player.LoadImg("Image_game//DOWN.png", grenderer);
	
	
	Uint32 frame_start ;
	int frame_time ;
	bool is_quit = false;

	GameMap gamemap;
	char name[14] = "map/map.txt";
	gamemap.LoadMap(name);
	gamemap.LoadTiles(grenderer);
	
	vector<Animal*>ANIMAL = animal();
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
		
		MAP map_data = gamemap.getMap();
	
		player.Moving(map_data);
		SDL_SetRenderDrawColor(grenderer, 255, 255, 255, 255);
		SDL_RenderClear(grenderer);
		
		//background.Render(grenderer, NULL);
		
		
		player.SetMapXY(map_data.start_x, map_data.start_y);


		gamemap.Draw_Map(grenderer);
		gamemap.setMap(map_data);

		
		gamemap.Draw_Map(grenderer);
		gamemap.setMap(map_data);
	
		player.show(grenderer);
		player.set_clip();
		player.cycle_player();
		
		player.set_clip();
		player.cycle_player();
		
		/*fountain.obj_show("Image_game//fountain2.png", grenderer);
		fountain.cycle_obj();
		water.obj_show("Image_game//waterfall.png",grenderer);
		water.cycle_obj();
		tree.Load_Img("Image_game//Tree.png", grenderer);*/
		Chicken.obj_show("Image_game/chicken.png", grenderer);	
		/*tree.Render(grenderer,NULL);*/
		Chicken.cycle_obj();
		/*
		fountain.setPos(WIDTH/4*3,HEIGHT/4*3);
		water.setPos(WIDTH/2,0);
		tree.setPos(400,400);*/
		Chicken.setPos(0,0);

		//if (checkcollision(player.GetRect(), fountain.GetRect()))
		//{
		//	player.Stop();
		//}
		//if (checkcollision(player.GetRect(), water.GetRect()))
		//{
		//	player.Stop();
		//}
		
		
		///water.Free();
		player.Free();
		//fountain.Free();
		//tree.Free();
		Chicken.Free();
		
		for (int i = 0; i < ANIMAL.size(); i++)
		{
			Animal* p_animal = ANIMAL.at(i);
			if (p_animal != NULL)
			{
				p_animal->set_MapXY(map_data.start_x, map_data.start_y);
				p_animal->doPlayer(map_data);
				p_animal->Show(grenderer);
			}
		}
		
		
		
		SDL_RenderPresent(grenderer);

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_Delay > frame_time) { SDL_Delay(frame_Delay - frame_time); }
		
	}
	close();
	return 0;
}