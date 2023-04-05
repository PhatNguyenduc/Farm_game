#include"commonFunction.h"
#include"BaseObject.h"
#include"Player.h"
#include"OtherObject.h"
#include"Game_map.h"
#include"Animal.h"
#include <vector>
#include"ImpTimer.h"
BaseObject background;
Player player;



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

	Animal* dynamic_animal = new Animal[5];
	for (int i = 0; i < 5; i++) {
		Animal* p_animal = (dynamic_animal + i);
		if (p_animal != NULL)
		{
			p_animal->LoadImg("Image_game/threat_left.png", grenderer);
			p_animal->set_x_pos(i * 300 + 300);
			p_animal->set_y_pos(400);
			p_animal->set_clip();
			p_animal->set_type_move(Animal::MOVE_);
			int left = p_animal->get_x_pos() - 128;
			int right = p_animal->get_x_pos() + 128;
			p_animal->Set_Area(left, right);
			list_animal.push_back(p_animal); 
		}
	}



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
			p_animal->set_type_move(Animal::STAND_);
			p_animal->set_input_left(0);
			list_animal.push_back(p_animal);

		}
	}
	return list_animal;
}
int main(int argc, char* argv[])
{	

	ImpTimer fps_timer;
	if (init() == false)
	{
		return -1;
	}
	
	
	bool is_quit = false;

	GameMap gamemap;
	char name[14] = "map/map.txt";
	gamemap.LoadMap(name);
	gamemap.LoadTiles(grenderer);
	
	vector<Animal*>ANIMAL = animal();
	while (!is_quit) 
	{
		fps_timer.start();
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
		
		player.Free();

		for (int i = 0; i < ANIMAL.size(); i++)
		{
			Animal* p_animal = ANIMAL.at(i);
			if (p_animal != NULL)
			{
				p_animal->set_MapXY(map_data.start_x, map_data.start_y);
				p_animal->ImpMoveType(grenderer);
				p_animal->doPlayer(map_data);
				p_animal->Show(grenderer);
				//p_animal->Free();
			}
		}
		
		
		
		SDL_RenderPresent(grenderer);
		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FPS;

		if (real_imp_time < time_one_frame)
		{
			SDL_Delay(time_one_frame - real_imp_time);
		}

		
	}
	close();
	return 0;
}