#include"Game_map.h"

void GameMap::LoadMap(char* name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) 
	{
		return;
	}
	game_map.max_x = 0;
	game_map.max_y = 0;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			fscanf_s(fp, "%d", &game_map.tile[i][j]);
			int val = game_map.tile[i][j];
			if (val > 0)
			{
				if (j > game_map.max_x)
				{
					game_map.max_x = j;
				}
				if (i > game_map.max_y)
				{
					game_map.max_y = i;
				}
			}
		}
	}

	game_map.max_x = (game_map.max_x + 1) * TILE_SIZE;
	game_map.max_y = (game_map.max_y + 1) * TILE_SIZE;
	
	game_map.start_x = 0;
	game_map.start_y = 0;
	game_map.file_name = name;
	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* grenderer)
{
	char file_img[100];
	FILE* fp = NULL;
	for (int i = 1; i <= 90; i++) {
		sprintf_s(file_img, "Map_/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}

		fclose(fp);

		tile_map[i].Load_Img(file_img, grenderer);
	}
}

void GameMap::Draw_Map(SDL_Renderer* grenderer)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map.start_x / TILE_SIZE;
	map_y = game_map.start_y / TILE_SIZE;
	x1 = (game_map.start_x % TILE_SIZE ) * -1;
	x2 = x1 + WIDTH + (x1 == 0 ? 0 : TILE_SIZE );

	y1 = (game_map.start_y % TILE_SIZE) * -1;
	y2 = x1 + HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) 
	{
		map_x = game_map.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) 
		{
			int val = game_map.tile[map_y][map_x]; 
			if (val > 0)
			{
				tile_map[val].Set_Rect(j, i);
				tile_map[val].Render(grenderer);
			}
			map_x++;
		}
		map_y++;
	}
};