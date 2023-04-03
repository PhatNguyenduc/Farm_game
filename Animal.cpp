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

}
Animal::~Animal()
{

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
	if (frame > 8)frame = 0;
	SDL_Rect* current_clip = &frame_clip[frame/3];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(grenderer, p_object, current_clip, &renderQuad);
}

void Animal::doPlayer(MAP& map_data)
{
	x_val = 0;
	y_val = 0;
	ChecktoMap(map_data);
}

void Animal::ChecktoMap(MAP& map_data)
{
	int x1;
	int x2;
	int y1;
	int y2;


	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)
		{
			if (
				map_data.tile[y1][x2] == 1
				|| map_data.tile[y1][x2] == 24
				|| map_data.tile[y1][x2] == 25
				|| map_data.tile[y1][x2] == 3

				|| map_data.tile[y2][x2] == 1
				|| map_data.tile[y2][x2] == 24
				|| map_data.tile[y2][x2] == 25
				|| map_data.tile[y2][x2] == 3
				)
			{
				x_pos -= x_val;
			}
		}
		else if (x_val < 0)
		{
			if (map_data.tile[y1][x1] == 1
				|| map_data.tile[y1][x1] == 24
				|| map_data.tile[y1][x1] == 25
				|| map_data.tile[y1][x1] == 3

				|| map_data.tile[y2][x1] == 1
				|| map_data.tile[y2][x1] == 24
				|| map_data.tile[y2][x1] == 25
				|| map_data.tile[y2][x1] == 3
				)
			{
				x_pos -= x_val;
			}
		}
	}
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			if (
				map_data.tile[y2][x1] == 1
				|| map_data.tile[y2][x1] == 24
				|| map_data.tile[y2][x1] == 25
				|| map_data.tile[y2][x1] == 3

				|| map_data.tile[y2][x2] == 1
				|| map_data.tile[y2][x2] == 24
				|| map_data.tile[y2][x2] == 25
				|| map_data.tile[y2][x2] == 3
				)
			{
				y_pos -= y_val;
			}
		}
		else if (y_val < 0)
		{
			if (map_data.tile[y1][x1] == 1
				|| map_data.tile[y1][x1] == 24
				|| map_data.tile[y1][x1] == 25
				|| map_data.tile[y1][x1] == 3

				|| map_data.tile[y1][x2] == 1
				|| map_data.tile[y1][x2] == 24
				|| map_data.tile[y1][x2] == 25
				|| map_data.tile[y1][x2] == 3
				)
			{
				y_pos -= y_val;
			}
		}
	}
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

