#include"commonFunction.h"
#include"BaseObject.h"
#include"Player.h"
#include"OtherObject.h"
#include"Game_map.h"
#include"Animal.h"
#include <vector>
#include"ImpTimer.h"
#include "Text.h"
BaseObject End_game;
Player player;
TTF_Font* font_time = NULL;


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
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
			
			
		}
		
		
	}
	
	return success;
}


void close()
{
	TTF_CloseFont(font_time);
	font_time = NULL;
	
	
	SDL_DestroyRenderer(grenderer);
	SDL_DestroyWindow(gwindow);
	gwindow = NULL;
	grenderer = NULL;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();

}
//animal
vector<Animal*>animal()
{
	vector<Animal*>list_animal;

	Animal* dynamic_animal = new Animal[1];
	
		Animal* p_animal = dynamic_animal ;
		if (p_animal != NULL)
		{
			p_animal->LoadImg("Image_game/catto.png", grenderer);
			p_animal->set_x_pos(650);
			p_animal->set_y_pos(500);
			p_animal->set_clip();
			
			int left = p_animal->get_x_pos() - 128;
			int right = p_animal->get_x_pos() + 128;
			int up = p_animal->get_y_pos() - 128;
			int down = p_animal->get_y_pos() + 128;
			p_animal->Set_Area(left, right,up,down);
			list_animal.push_back(p_animal); 
		}
	

	return list_animal;
}
vector<Animal*>dog()
{
	vector<Animal*>list_animal;

	Animal* dynamic_animal = new Animal[1];

	Animal* p_animal = dynamic_animal;
	if (p_animal != NULL)
	{
		p_animal->LoadImg("Image_game/doggo1.png", grenderer);
		p_animal->set_x_pos(600);
		p_animal->set_y_pos(400);
		p_animal->set_clip();

		list_animal.push_back(p_animal);
	}


	return list_animal;
}
vector<Animal*>chicken()
{
	vector<Animal*>list_animal;

	Animal* dynamic_animal = new Animal[5];
	for (int i = 0; i < 5; i++)
	{


		Animal* p_animal = dynamic_animal+i;
		if (p_animal != NULL)
		{
			p_animal->LoadImg("Image_game/chicken8.png", grenderer);
			p_animal->set_x_pos(300*i+100);
			p_animal->set_y_pos(150*i*i+13*i+88);
			p_animal->set_clip();
			int left = p_animal->get_x_pos() - 60;
			int right = p_animal->get_x_pos() + 60;
			int up = p_animal->get_y_pos() - 60;
			int down = p_animal->get_y_pos() + 60;
			p_animal->Set_Area(left, right, up, down);
			list_animal.push_back(p_animal);
		}

	}
	return list_animal;
}

int main(int argc, char* argv[])
{	
	//time
	ImpTimer fps_timer;
	if (init() == false)
	{
		return -1;
	}
	font_time = TTF_OpenFont("font/lazy.ttf", 25);
	
	//text
	text time_game;
	time_game.SetColor(text::WHITE);
	
	text paddy_cnt;
	paddy_cnt.SetColor(text::RED);
	
	text tomato_cnt;
	tomato_cnt.SetColor(text::RED);
	
	text carrot_cnt;
	carrot_cnt.SetColor(text::RED);
	
	text pumpkin_cnt;
	pumpkin_cnt.SetColor(text::RED);
	
	text egg_cnt;
	egg_cnt.SetColor(text::RED);
	
	text apple_cnt;
	apple_cnt.SetColor(text::RED);
	
	text wood_cnt;
	wood_cnt.SetColor(text::RED);
	


	
	bool is_quit = false;
	//map
	GameMap layer1;
	char name_1[21] = "Map_/layer1.txt";
	layer1.LoadMap(name_1);
	layer1.LoadTiles(grenderer);

	GameMap layer2;
	char name_2[21] = "Map_/tile2.txt";
	layer2.LoadMap(name_2);
	layer2.LoadTiles(grenderer);

	
	//animal
	vector<Animal*>ANIMAL = animal();
	vector<Animal*>DOG = dog();
	vector<Animal*>CHICKEN = chicken();
	while (!is_quit) 
	{
		fps_timer.start();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT )
			{
				is_quit = true;
			}
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: is_quit = true; 
				break;
			}
			player.HandleInput(event, grenderer);
			
		}
		
		MAP map_data = layer1.getMap();
		MAP map_data_1 = layer2.getMap();
	
		player.Moving(map_data);
	    player.Moving(map_data_1);
		SDL_SetRenderDrawColor(grenderer, 255, 255, 255, 255);
		SDL_RenderClear(grenderer);
		
		
		
		
		player.SetMapXY(map_data.start_x, map_data.start_y);
		player.SetMapXY(map_data_1.start_x, map_data_1.start_y);

		layer1.Draw_Map(grenderer);
		layer2.Draw_Map(grenderer);
		layer2.setMap(map_data_1);
		layer1.setMap(map_data);
		
		

	
		player.show(grenderer);
		player.set_clip();
		player.cycle_player();
		
	
		player.Free();

		for (int i = 0; i < ANIMAL.size(); i++)
		{
			Animal* p_animal = ANIMAL.at(i);
			if (p_animal != NULL)
			{
				p_animal->set_MapXY(map_data.start_x, map_data.start_y);
				
				p_animal->move_ani(map_data);
				
				p_animal->Show(grenderer);
				
			}
		}
		for (int i = 0; i < DOG.size(); i++)
		{
			Animal* p_animal = DOG.at(i);
			if (p_animal != NULL)
			{
				p_animal->set_MapXY(map_data.start_x, map_data.start_y);
				

				p_animal->follow(player.get_x_pos(), player.get_y_pos(), map_data);

				p_animal->Show(grenderer);

			}
		}
		for (int i = 0; i < CHICKEN.size(); i++)
		{
			Animal* p_animal = CHICKEN.at(i);
			if (p_animal != NULL)
			{
				p_animal->set_MapXY(map_data.start_x, map_data.start_y);

				p_animal->move_ani(map_data);

				p_animal->Show(grenderer);

			}
		}
		
		
		
		//  show game_time
		 string str_time = "TIME : ";
		 Uint32 time_val = SDL_GetTicks() / 1000;
		 string val = to_string(time_val);
		 str_time += val;
		 time_game.SetText(str_time);
		 time_game.Load_from_file("font/lazy.ttf");
		 time_game.LoadFromRenderText(font_time, grenderer);
		 time_game.RenderText(grenderer,WIDTH - 300, 20);
		  //show agricultural
		 
		 string str_paddy = "paddy : " + to_string(player.paddy);
		 
		 paddy_cnt.SetText(str_paddy);
		 paddy_cnt.Load_from_file("font/lazy.ttf");
		 paddy_cnt.LoadFromRenderText(font_time, grenderer);
		 paddy_cnt.RenderText(grenderer, 0, 0);

		 string str_tomato = "tomato : " + to_string(player.tomato);

		 tomato_cnt.SetText(str_tomato);
		 tomato_cnt.Load_from_file("font/lazy.ttf");
		 tomato_cnt.LoadFromRenderText(font_time, grenderer);
		 tomato_cnt.RenderText(grenderer, 0, 64);

		 string str_carrot = "carrot : " + to_string(player.carrot);

		 carrot_cnt.SetText(str_carrot);
		 carrot_cnt.Load_from_file("font/lazy.ttf");
		 carrot_cnt.LoadFromRenderText(font_time, grenderer);
		 carrot_cnt.RenderText(grenderer, 0, 128);
		 
		 string str_pumpkin = "pumpkin : " + to_string(player.pumpkin);

		 pumpkin_cnt.SetText(str_pumpkin);
		 pumpkin_cnt.Load_from_file("font/lazy.ttf");
		 pumpkin_cnt.LoadFromRenderText(font_time, grenderer);
		 pumpkin_cnt.RenderText(grenderer, 256, 0);

		 string str_apple = "apple : " + to_string(player.apple);

		 apple_cnt.SetText(str_apple);
		 apple_cnt.Load_from_file("font/lazy.ttf");
		 apple_cnt.LoadFromRenderText(font_time, grenderer);
		 apple_cnt.RenderText(grenderer, 256, 64);

		 string str_egg = "egg : " + to_string(player.egg);

		 egg_cnt.SetText(str_egg);
		 egg_cnt.Load_from_file("font/lazy.ttf");
		 egg_cnt.LoadFromRenderText(font_time, grenderer);
		 egg_cnt.RenderText(grenderer, 256, 128);

		 string str_wood = "wood : " + to_string(player.wood);

		 wood_cnt.SetText(str_wood);
		 wood_cnt.Load_from_file("font/lazy.ttf");
		 wood_cnt.LoadFromRenderText(font_time, grenderer);
		 wood_cnt.RenderText(grenderer, 512, 0);
		 
		 paddy_cnt.Free();
		 tomato_cnt.Free();
		 egg_cnt.Free();
		 carrot_cnt.Free();
		 pumpkin_cnt.Free();
		 wood_cnt.Free();
		 apple_cnt.Free();
		 time_game.Free();
		 

		 if (player.apple >= 3 && player.paddy >= 10 && player.wood >= 2 && player.egg >= 2 && player.tomato >= 4 && player.pumpkin >= 5) {

			 End_game.Load_Img("Image_game/END.png", grenderer);
			 End_game.Render(grenderer, NULL);
			 End_game.Free();
				
			 player.Stop();
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


