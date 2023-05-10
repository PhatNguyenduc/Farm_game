#include"Animal.h"

Animal::Animal()
{
	width_frame = 0;
	height_frame = 0;
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	frame = 0;
	Lim_Left = 0;
	Lim_Right = 0;
	input_type.left = 0;
	input_type.right = 1;
	flip = SDL_FLIP_NONE;
	
}
Animal::~Animal()
{
	Free();
}

bool Animal::LoadImg(string path, SDL_Renderer * grenderer)
{
	bool res = BaseObject::Load_Img(path, grenderer);
	if (res)
	{
		width_frame = rect.w / 8;
		height_frame = rect.h;

	}
	return res;
}
void Animal::Show(SDL_Renderer* grenderer)
{
	rect.x = x_pos - map_x;
	rect.y = y_pos - map_y;
	frame++;
	if (frame >=40 )frame = 0;
	SDL_Rect* current_clip = &frame_clip[frame/5];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopyEx(grenderer, p_object, current_clip, &renderQuad,0,NULL,flip);
}

void Animal::move_ani(MAP& map_data)
{
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1)
	{
		x_val -= 2;
		
	}
	else if (input_type.right == 1) {
		x_val += 2;
		
	}
	if (input_type.up == 1) {
		y_val -= 2;
	}
	else if (input_type.down == 1) {
		y_val += 2;
	}
	ChecktoMap(map_data);
	
}

void Animal::ChecktoMap(MAP& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	
	if ((x_pos < 0) || (x_pos + width_frame > 3200))
	{
		//Move back
		x_pos -= x_val;
	}


	y_pos += y_val;


	if ((y_pos < 0) || (y_pos + height_frame > 1600))
	{
		//Move back
		y_pos -= y_val;
	}

	//check x
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if (val1 == APPLE || val2 == APPLE) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == EGG || val2 == EGG) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == CARROT || val2 == CARROT) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PADDY || val2 == PADDY) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == TOMATO || val2 == TOMATO) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PUMPKIN || val2 == PUMPKIN) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == WOOD || val2 == WOOD) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			if (val1 == 2 || val1 == 5 || val1 == 6 || val1 == 9 || val1 == 10 || val1 == 13 || val1 == 14 || val1 == 17 || val1 == 18 || val1 == 34 || val1 == 36 || val1 == 37 || val1 == 40 || val1 == 41 || val1 == 42 || val1 == 43 || val1 == 44 || val1 == 45
				|| val1 == 46 || val1 == 47 || val1 == 48 || val1 == 49 || val1 == 50 || val1 == 51 || val1 == 67

				|| val2 == 2 || val2 == 5 || val2 == 6 || val2 == 9 || val2 == 10 || val2 == 13 || val2 == 14 || val2 == 17 || val2 == 18 || val2 == 34 || val2 == 36 || val2 == 37 || val2 == 40 || val2 == 41 || val2 == 42 || val2 == 43 || val2 == 44 || val2 == 45
				|| val2 == 46 || val2 == 47 || val2 == 48 || val2 == 49 || val2 == 50 || val2 == 51 || val2 == 67)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame;
				x_val = 0;
			}
		}
		else if (x_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == APPLE || val2 == APPLE) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == EGG || val2 == EGG) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == CARROT || val2 == CARROT) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PADDY || val2 == PADDY) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == TOMATO || val2 == TOMATO) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PUMPKIN || val2 == PUMPKIN) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == WOOD || val2 == WOOD) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			if (val1 == 2 || val1 == 5 || val1 == 6 || val1 == 9 || val1 == 10 || val1 == 13 || val1 == 14 || val1 == 17 || val1 == 18 || val1 == 34 || val1 == 36 || val1 == 37 || val1 == 40 || val1 == 41 || val1 == 42 || val1 == 43 || val1 == 44 || val1 == 45
				|| val1 == 46 || val1 == 47 || val1 == 48 || val1 == 49 || val1 == 50 || val1 == 51 || val1 == 67

				|| val2 == 2 || val2 == 5 || val2 == 6 || val2 == 9 || val2 == 10 || val2 == 13 || val2 == 14 || val2 == 17 || val2 == 18 || val2 == 34 || val2 == 36 || val2 == 37 || val2 == 40 || val2 == 41 || val2 == 42 || val2 == 43 || val2 == 44 || val2 == 45
				|| val2 == 46 || val2 == 47 || val2 == 48 || val2 == 49 || val2 == 50 || val2 == 51 || val2 == 67)

			{
				x_pos = x1 * TILE_SIZE - x_val;
				x_val = 0;
			}
		}
	}
	//check y
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == APPLE || val2 == APPLE) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == EGG || val2 == EGG) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == CARROT || val2 == CARROT) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PADDY || val2 == PADDY) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == TOMATO || val2 == TOMATO) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PUMPKIN || val2 == PUMPKIN) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == WOOD || val2 == WOOD) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			if (val1 == 2 || val1 == 5 || val1 == 6 || val1 == 9 || val1 == 10 || val1 == 13 || val1 == 14 || val1 == 17 || val1 == 18 || val1 == 34 || val1 == 36 || val1 == 37 || val1 == 40 || val1 == 41 || val1 == 42 || val1 == 43 || val1 == 44 || val1 == 45
				|| val1 == 46 || val1 == 47 || val1 == 48 || val1 == 49 || val1 == 50 || val1 == 51 || val1 == 67

				|| val2 == 2 || val2 == 5 || val2 == 6 || val2 == 9 || val2 == 10 || val2 == 13 || val2 == 14 || val2 == 17 || val2 == 18 || val2 == 34 || val2 == 36 || val2 == 37 || val2 == 40 || val2 == 41 || val2 == 42 || val2 == 43 || val2 == 44 || val2 == 45
				|| val2 == 46 || val2 == 47 || val2 == 48 || val2 == 49 || val2 == 50 || val2 == 51 || val2 == 67)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= height_frame;
				y_val = 0;
			}
		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == APPLE || val2 == APPLE) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == EGG || val2 == EGG) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == CARROT || val2 == CARROT) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PADDY || val2 == PADDY) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == TOMATO || val2 == TOMATO) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == PUMPKIN || val2 == PUMPKIN) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			else if (val1 == WOOD || val2 == WOOD) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;

			}
			if (val1 == 2 || val1 == 5 || val1 == 6 || val1 == 9 || val1 == 10 || val1 == 13 || val1 == 14 || val1 == 17 || val1 == 18 || val1 == 34 || val1 == 36 || val1 == 37 || val1 == 40 || val1 == 41 || val1 == 42 || val1 == 43 || val1 == 44 || val1 == 45
				|| val1 == 46 || val1 == 47 || val1 == 48 || val1 == 49 || val1 == 50 || val1 == 51 || val1 == 67

				|| val2 == 2 || val2 == 5 || val2 == 6 || val2 == 9 || val2 == 10 || val2 == 13 || val2 == 14 || val2 == 17 || val2 == 18 || val2 == 34 || val2 == 36 || val2 == 37 || val2 == 40 || val2 == 41 || val2 == 42 || val2 == 43 || val2 == 44 || val2 == 45
				|| val2 == 46 || val2 == 47 || val2 == 48 || val2 == 49 || val2 == 50 || val2 == 51 || val2 == 67)
			{
				y_pos = y1 * TILE_SIZE;
				y_val = 0;
			}
		}
	}
	if (x_val < 0 && x_pos < Lim_Left + 10)
	{
		x_val = 0;
		flip = SDL_FLIP_NONE;
		input_type.right = 1;
		input_type.left = 0;


	}
	else if (x_val > 0 && x_pos > Lim_Right - 10)
	{
		x_val = 0;
		flip = SDL_FLIP_HORIZONTAL;
		input_type.left = 1;
		input_type.right = 0;

	}
	if (y_val < 0 && y_pos < Lim_Up - 10)
	{
		y_val = 0;
		input_type.down = 1;
		input_type.up = 0;


	}
	else if (y_val > 0 && y_pos > Lim_Down + 10)
	{
		y_val = 0;
		input_type.down = 0;
		input_type.up = 1;

	}
	x_pos += x_val;
	y_pos += y_val;


}



void Animal::set_clip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void Animal::follow(const int& x, const int& y, MAP& map_data)
{

	if (x_pos > x + TILE_SIZE / 2)
	{
		input_type.left = 1;
		input_type.right = 0;

		flip = SDL_FLIP_HORIZONTAL;
		move_pet(map_data);
	}
	else if (x_pos < x - TILE_SIZE / 2)
	{
		input_type.left = 0;
		input_type.right = 1;

		flip = SDL_FLIP_NONE;
		move_pet(map_data);
	}
	else
	{
		input_type.left = 0;
		input_type.right = 0;
	}

	if (y_pos < y - TILE_SIZE / 2)
	{
		input_type.up = 0;
		input_type.down = 1;

		move_pet(map_data);
	}
	else if (y_pos > y + TILE_SIZE / 2)
	{
		input_type.up = 1;
		input_type.down = 0;

		move_pet(map_data);
	}
	else
	{
		input_type.up = 0;
		input_type.down = 0;
	}

}
void Animal::move_pet(MAP& map_data)
{
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1)
	{
		x_val -= 4;

	}
	else if (input_type.right == 1) {
		x_val += 4;

	}
	if (input_type.up == 1) {
		y_val -= 4;
	}
	else if (input_type.down == 1) {
		y_val += 4;
	}
	x_pos += x_val;
	y_pos += y_val;

}








void Animal::random_move(MAP& map_data)
{
	srand(time(NULL));

	x_val = 0;
	y_val = 0;

	x_val += rand() % 6;
	y_val += rand() % 4;
	if (rand() % 2 == 0) {
		x_pos += x_val;
		y_pos += y_val;
	}
	else
	{
		x_pos -= x_val;
		y_pos -= y_val;
	}
	ChecktoMap(map_data);
}

void Animal::Catch(const int& x, const int& y, MAP & map_data)
{

	if (x_pos >= x  - 32  )
	{
		input_type.left = 1;
		input_type.right = 0;

		flip = SDL_FLIP_NONE;
		move_monster(map_data);

	}
	else if (x_pos <= x - 32 )
	{
		input_type.left = 0;
		input_type.right = 1;

		flip = SDL_FLIP_HORIZONTAL;
		move_monster(map_data);
	}
	else
	{
		input_type.left = 0;
		input_type.right = 0;
	}

	if (y_pos <= y - 32 )
	{
		input_type.up = 0;
		input_type.down = 1;

		move_monster(map_data);
	}
	else if (y_pos >= y - 32 )
	{
		input_type.up = 1;
		input_type.down = 0;

		move_monster(map_data);
	}
	else
	{
		input_type.up = 0;
		input_type.down = 0;
	}

}

void Animal::move_monster(MAP& map_data)
{
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1)
	{
		x_val -= 1;

	}
	else if (input_type.right == 1) {
		x_val += 1;

	}
	if (input_type.up == 1) {
		y_val -= 1;
	}
	else if (input_type.down == 1) {
		y_val += 1;
	}
	x_pos += x_val;
	y_pos += y_val;

}
void Animal::stop_animal()
{
	x_pos -= x_val;
	y_pos -= y_val;
}