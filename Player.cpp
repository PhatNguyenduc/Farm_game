#include "Player.h"

Player::Player()
{
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	frame_w = 0;
	frame_h = 0;
	move.down = 0;
	move.up = 0;
	move.left = 0;
	move.down = 0;
}
Player::~Player()
{

}

bool Player::LoadImg(string path, SDL_Renderer* grenderer)
{
	bool res = BaseObject::Load_Img(path, grenderer);
	if (res) {
		frame_w = rect.w / 4;
		frame_h = rect.h;
	}
	return res;
}
void Player::set_clip()
{
	if (frame_w > 0 && frame_h > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			frame_clip[i].x = i * frame_w;
			frame_clip[i].y = 0;
			frame_clip[i].w = frame_w;
			frame_clip[i].h = frame_h;
		}
	}

}

void Player::show(SDL_Renderer* grenderer) {
	LoadImg("Image_game//player.png", grenderer);
	/*if (move.left == 1 || move.right == 1 || move.down == 1 || move.up == 1) {
		frame++;
	}
	else {frame = 0;}
	if (frame >= 4) { frame = 0; }*/
	if (move.down == 1) {
		frame = 0;
	}
	else if (move.left == 1) {
		frame = 1;
	}
	else if (move.right == 1) {
		frame = 2;
	}
	else if (move.up == 1) {
		frame = 3;
	}
	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* currentclip = &frame_clip[frame];
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
			move.left = 1;
			move.right = 0;
			move.up = 0;
			move.down = 0;
			x_val -= SPEED;
			break;
		}
		case SDLK_d:
		{
			move.left = 0;
			move.right = 1;
			move.up = 0;
			move.down = 0;
			x_val += SPEED;
			break;
		}
		case SDLK_w:
		{
			move.up = 1;
			move.down = 0;
			move.left = 0;
			move.right = 0;
			y_val -= SPEED;
			break;
		}
		case SDLK_s:
		{
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
void Player::Moving() {
	//Move the dot left or right
	x_pos += x_val;

	//If the dot went too far to the left or right
	if ((x_pos < 0) || (x_pos +frame_w > WIDTH))
	{
		//Move back
		x_pos -= x_val;
	}

	//Move the dot up or down
	y_pos+= y_val;

	//If the dot went too far up or down
	if ((y_pos < 0) || (y_pos + frame_h > HEIGHT))
	{
		//Move back
		y_pos -= y_val;
	}
}

SDL_Rect Player::Get_Rect()
{
	SDL_Rect temp;
	temp.x = rect.x;
	temp.y = rect.y;
	temp.h = frame_h;
	temp.w = frame_w;
	return temp;
}
void Player::Stop()
{
	    //Move back
		x_pos -= x_val;
		y_pos -= y_val;
}