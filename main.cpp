#include"commonFunction.h"
#include"BaseObject.h"
#include"Player.h"
#include"OtherObject.h"
#include"Game_map.h"
#include"Animal.h"
#include <vector>
#include"ImpTimer.h"
#include "Text.h"
#include"Menu.h"
BaseObject End_game;
Player player;
TTF_Font* font_time = NULL;
BaseObject Pad;
BaseObject Tom;
BaseObject Car;
BaseObject Pum;
BaseObject App;
BaseObject Egg;
BaseObject Woo;
BaseObject lost;
BaseObject Instruct;
Menu menu;
ImpTimer time_game_; 

//Audio 
Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* music_chunk = NULL;



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
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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

	Mix_FreeChunk(music_chunk);
	music_chunk = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	Mix_Quit();


}
bool check = true;
bool Check_Collision(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	int centerX1 = rect1.x + rect1.w / 16;
	int centerY1 = rect1.y + rect1.h / 2;
	int centerX2 = rect2.x + rect2.w / 16;
	int centerY2 = rect2.y + rect2.h / 2;

	// Tính khoảng cách giữa hai tâm
	int distance = sqrt(pow(centerX1 - centerX2, 2) + pow(centerY1 - centerY2, 2));

	// Tính tổng của nửa chiều dài của hai hình vuông
	int sumHalfWidth = rect1.w / 16 + rect2.w / 16;
	int sumHalfHeight = rect1.h / 2 + rect2.h / 2;
	if (distance <= sumHalfWidth && distance <= sumHalfHeight) {
		return true;
	}

	return false;
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


vector<Animal*>Orc()
{
	vector<Animal*>list_animal;

	Animal* dynamic_animal = new Animal[1];
	
	Animal* p_animal = dynamic_animal;
	if (p_animal != NULL)
	{
		p_animal->LoadImg("Image_game/wolf2big.png",grenderer);
		p_animal->set_x_pos(3200);
		p_animal->set_y_pos(768);
		p_animal->set_clip();

		list_animal.push_back(p_animal);
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
	
	font_time = TTF_OpenFont("font/RobotoCondensed-Italic.ttf", 20);
	gMusic = Mix_LoadMUS("Music/chillin39-20915.mp3");
	//text
	text time_game;
	time_game.SetColor(text::WHITE);
	
	text paddy_cnt;
	paddy_cnt.SetColor(text::BLACK);
	
	text tomato_cnt;
	tomato_cnt.SetColor(text::BLACK);
	
	text carrot_cnt;
	carrot_cnt.SetColor(text::BLACK);
	
	text pumpkin_cnt;
	pumpkin_cnt.SetColor(text::BLACK);
	
	text egg_cnt;
	egg_cnt.SetColor(text::BLACK);

	text apple_cnt;
	apple_cnt.SetColor(text::BLACK);
	
	text wood_cnt;
	wood_cnt.SetColor(text::BLACK);
	


	
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

	vector<Animal*>ORC = Orc();


	int menu_ = menu.show_menu(grenderer,font_time,time_game_ );
	bool q = false;
	while (!q) {


		if (menu_ == 1) {
			q = true;
			time_game_.count = true;
		}
		else if (menu_ == 2) {
			q = true;
			is_quit = true;
		}
		
	}
	
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
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(gMusic, -1);
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
		
	
		
		

		for (int i = 0; i < ORC.size(); i++)
		{
			Animal* p_animal = ORC.at(i);
			if (p_animal != NULL)
			{
				p_animal->set_MapXY(map_data.start_x, map_data.start_y);


				p_animal->Catch(player.get_x_pos(), player.get_y_pos(), map_data);

				p_animal->Show(grenderer);
				if (Check_Collision(player.GetRect(),ORC.at(i)->GetRect())==true)
				{
					
					check = false;
				}
				if (!check)
				{

					lost.Load_Img("Image_game/lose.png", grenderer);
					lost.Set_Rect(WIDTH / 4, HEIGHT / 4);
					lost.Render(grenderer, NULL);
					lost.Free();
					ORC.at(i)->stop_animal();
					player.Stop();
				}

			}
			
		}
		
		//  show game_time
		if (time_game_.count == true) 
		{
			string str_time = "TIME : ";

			int time_val = 200 - time_game_.get_ticks() / 1000;

			string val = to_string(time_val);
			if (time_val < 0) {
				lost.Load_Img("Image_game/lose.png", grenderer);
				lost.Set_Rect(WIDTH / 4, HEIGHT / 4);
				lost.Render(grenderer, NULL);
				lost.Free();
				player.Stop();
			}
			else {
				str_time += val;
				time_game.SetText(str_time);
				time_game.Load_from_file("font/RobotoCondensed-Italic.ttf");
				time_game.LoadFromRenderText(font_time, grenderer);
				time_game.RenderText(grenderer, WIDTH - 300, 20);
			}
			


			
		}
		  //show agricultural
		 
		 string str_paddy = "paddy : " + to_string(player.paddy) +" / 10 ";
		 
		 paddy_cnt.SetText(str_paddy);
		 paddy_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
		 paddy_cnt.LoadFromRenderText(font_time, grenderer);
		 paddy_cnt.RenderText(grenderer, 0, 0);

		 string str_tomato = "tomato : " + to_string(player.tomato) + " / 4";

		 tomato_cnt.SetText(str_tomato);
		 tomato_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
		 tomato_cnt.LoadFromRenderText(font_time, grenderer);
		 tomato_cnt.RenderText(grenderer, 0, 64);

		 string str_carrot = "carrot : " + to_string(player.carrot)+" / 5";

		 carrot_cnt.SetText(str_carrot);
		 carrot_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
		 carrot_cnt.LoadFromRenderText(font_time, grenderer);
		 carrot_cnt.RenderText(grenderer, 0, 128);
		 
		 string str_pumpkin = "pumpkin : " + to_string(player.pumpkin) + "/ 5";

		 pumpkin_cnt.SetText(str_pumpkin);
		 pumpkin_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
		 pumpkin_cnt.LoadFromRenderText(font_time, grenderer);
		 pumpkin_cnt.RenderText(grenderer, 256, 0);

		 string str_apple = "apple : " + to_string(player.apple) + " / 3";

		 apple_cnt.SetText(str_apple);
		 apple_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
		 apple_cnt.LoadFromRenderText(font_time, grenderer);
		 apple_cnt.RenderText(grenderer, 256, 64);

		 string str_egg = "egg : " + to_string(player.egg) + " / 2";

		 egg_cnt.SetText(str_egg);
		 egg_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
		 egg_cnt.LoadFromRenderText(font_time, grenderer);
		 egg_cnt.RenderText(grenderer, 256, 128);

		 string str_wood = "wood : " + to_string(player.wood)+" / 2";

		 wood_cnt.SetText(str_wood);
		 wood_cnt.Load_from_file("font/RobotoCondensed-Italic.ttf");
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

		 Pad.Load_Img("Image_game/pad.png", grenderer);
		 Pad.Set_Rect(100,0);
		 Pad.Render(grenderer, NULL);
		 Pad.Free();

		 Tom.Load_Img("Image_game/tom.png", grenderer);
		 Tom.Set_Rect(100, 64);
		 Tom.Render(grenderer, NULL);
		 Tom.Free();

		 Car.Load_Img("Image_game/car.png", grenderer);
		 Car.Set_Rect(100,128);
		 Car.Render(grenderer, NULL);
		 Car.Free();

		 Pum.Load_Img("Image_game/pum.png", grenderer);
		 Pum.Set_Rect(256+100+20,0);
		 Pum.Render(grenderer, NULL);
		 Pum.Free();

		 App.Load_Img("Image_game/app.png", grenderer);
		 App.Set_Rect(256+100,64);
		 App.Render(grenderer, NULL);
		 App.Free();

		 Egg.Load_Img("Image_game/egg.png", grenderer);
		 Egg.Set_Rect(256+100,128);
		 Egg.Render(grenderer,NULL);
		 Egg.Free();
		 
		 Woo.Load_Img("Image_game/woo.png", grenderer);
		 Woo.Set_Rect(512 + 100, 0);
		 Woo.Render(grenderer, NULL);
		 Woo.Free();

		 if (player.apple >= 3 && player.paddy >= 10 && player.wood >= 2 && player.egg >= 2 && player.tomato >= 4 && player.pumpkin >= 5 && player.carrot>=5) {

			 End_game.Load_Img("Image_game/END.png", grenderer);
			 End_game.Set_Rect(WIDTH / 4, HEIGHT / 4);
			 End_game.Render(grenderer, NULL);
			 End_game.Free();
				
			 player.Stop();
		 }
		/*if (!check)
		 {

			 lost.Load_Img("Image_game/lose.png", grenderer);
			 lost.Set_Rect(WIDTH / 4, HEIGHT / 4);
			 lost.Render(grenderer, NULL);
			 lost.Free();
			 
			 player.Stop();
		 }*/
		 


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


