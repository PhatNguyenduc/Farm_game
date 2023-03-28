#include "Player.h"

Player::Player()
{
	frame = 0;
	x_pos = 448;
	y_pos = 576;
	x_val = 0;
	y_val = 0;
	frame_w = 0;
	frame_h = 0;
	move.down = 0;
	move.up = 0;
	move.left = 0;
	move.down = 0;
	map_x = 0;
	map_y = 0;
	status=0;
}
Player::~Player()
{

}

bool Player::LoadImg(string path, SDL_Renderer* grenderer)
{
	bool res = BaseObject::Load_Img(path, grenderer);
	if (res) {
		frame_w = rect.w / 8;
		frame_h = rect.h;
	}
	return res;
}
void Player::set_clip()
{
	if (frame_w > 0 && frame_h > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip[i].x = i * frame_w;
			frame_clip[i].y = 0;
			frame_clip[i].w = frame_w;
			frame_clip[i].h = frame_h;
		}
	}

}

void Player::show(SDL_Renderer* grenderer) {
	if (status == DOWN)
	{
		LoadImg("Image_game/DOWN.png", grenderer);
		
	}
	else if (status == UP)
	{
		LoadImg("Image_game/UP.png", grenderer);
	}
	else if (status == RIGHT)
	{
		LoadImg("Image_game/RIGHT.png", grenderer);
	}
	else if (status == LEFT)
	{
		LoadImg("Image_game/LEFT.png", grenderer);
	}
	
	
	/*if (move.down == 1) {
		frame++;

	}
	else frame = 0;
	if (move.left == 1) {
		
		
	}
	else frame = 0;
	 if (move.right == 1) {
		
		
	}
	else frame = 0;
	if (move.up == 1) {
		
		
	}
	else frame = 0;*/
	rect.x = x_pos - map_x;
	rect.y = y_pos - map_y;

	SDL_Rect* currentclip = &frame_clip[frame/10];
	SDL_Rect renderQuad = { rect.x,rect.y,frame_w,frame_h };
	SDL_RenderCopy(grenderer, p_object, currentclip, &renderQuad);
}
void Player::HandleInput(SDL_Event event, SDL_Renderer* grenderer)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
		{
			status = LEFT;
			move.left = 1;
			move.right = 0;
			move.up = 0;
			move.down = 0;
			x_val -= SPEED;
			break;
		}
		case SDLK_d:
		{
			status = RIGHT;
			move.left = 0;
			move.right = 1;
			move.up = 0;
			move.down = 0;
			x_val += SPEED;
			break;
		}
		case SDLK_w:
		{
			status = UP;
			move.up = 1;
			move.down = 0;
			move.left = 0;
			move.right = 0;
			y_val -= SPEED;
			break;
		}
		case SDLK_s:
		{
			status = DOWN;
			move.down = 1;
			move.up = 0;
			move.left = 0;
			move.right = 0;
			y_val += SPEED;
			break;
		}
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			move.left = 0;
			x_val += SPEED;
			break;
		case SDLK_d:
			move.right = 0;
			x_val -= SPEED;
			break;
		case SDLK_w:
			move.down = 0;
			y_val += SPEED;
			break;
		case SDLK_s:
			move.up = 0;
			y_val -= SPEED;
			break;
		}
	}
}
void Player::Moving(MAP& map_data) {
	
	x_pos += x_val;

	
	if ((x_pos < 0) || (x_pos + frame_w > 3200))
	{
		//Move back
	x_pos -= x_val;
	}

	
	y_pos+= y_val;

	
	if ((y_pos < 0)  || (y_pos + frame_h > 1600))
	{
		//Move back
		y_pos -= y_val;
	}
	CenterMap_on_player(map_data);
	collision(map_data);
}


void Player::Stop()
{
	    //Move back
		x_pos -= x_val;
		y_pos -= y_val;
}
void Player::CenterMap_on_player(MAP& map_data) {
	map_data.start_x = x_pos - (WIDTH / 2);
	if (map_data.start_x < 0)map_data.start_x = 0;
	else if (map_data.start_x + WIDTH >= map_data.max_x) 
	{
		map_data.start_x = map_data.max_x - WIDTH;
	}
	map_data.start_y = y_pos - (HEIGHT / 2);
	if (map_data.start_y < 0)map_data.start_y = 0;
	else if (map_data.start_y + HEIGHT >= map_data.max_y)
	{
		map_data.start_y = map_data.max_y - HEIGHT;
	}
	
}
void Player::collision(MAP& map_data)
{
	int x1;
	int x2;
	int y1;
	int y2;
	
	
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + frame_w - 1) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + frame_h - 1) / TILE_SIZE;
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
			if (   map_data.tile[y1][x1] == 1
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
			if (   map_data.tile[y1][x1] == 1
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
void Player::cycle_player() {
	++frame;
	if (frame / 8 > 8)frame = 0;
	
}

