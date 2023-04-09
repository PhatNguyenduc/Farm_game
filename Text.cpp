#include "Text.h"


text::text()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	text_ture = NULL;
}
text::~text() {
	Free();

}
bool text::Load_from_file(string path)
{
	//Get rid of preexisting texture
	//Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		;
	}
	else
	{
		////Color key image
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(grenderer, loadedSurface);
		if (newTexture == NULL)
		{
			;
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	text_ture = newTexture;
	return text_ture != NULL;
}
bool text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* grenderer) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (text_surface != NULL) {
		text_ture = SDL_CreateTextureFromSurface(grenderer, text_surface);
		width = text_surface->w;
		height = text_surface->h;
		SDL_FreeSurface(text_surface);
	}
	return text_ture != NULL;
}
void text::Free() {
	if (text_ture != NULL)
	{
		SDL_DestroyTexture(text_ture);
		text_ture = NULL;
	}

}
void text::Set_Color(Uint8 red, Uint8 green, Uint8 blue) {
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;

}
void text::SetColor(int type) {
	if (type == RED)
	{
		SDL_Color color = { 255,0,0 };
		text_color = color;

	}
	else if (type == WHITE)
	{

		SDL_Color color = { 255,255,255 };
		text_color = color;
	}
	else if (type == BLACK)
	{

		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}
void text::RenderText(SDL_Renderer* grenderer, int xp, int yp, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { xp,yp,width,height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

	}
	SDL_RenderCopyEx(grenderer, text_ture, clip, &renderQuad, angle, center,flip);
}


