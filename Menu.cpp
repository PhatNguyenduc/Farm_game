#include "Menu.h"

int Menu::show_menu(SDL_Renderer* des, TTF_Font* font,ImpTimer& time_game_)
{
	Load_Img("Image_game/Menu_image.jpg",des);
	TTF_Font *Menu_font = TTF_OpenFont("font/RobotoCondensed-Italic.ttf", 20);
	const int kMenuItem = 3;


	text text_menu[kMenuItem];
	string a = "PLAY";
	text_menu[0].SetText(a);
	text_menu[0].SetColor(text::BLACK);
	text_menu[0].Set_Rect(500, 400);

	string b = "Instruction";
	text_menu[1].SetText(b);
	text_menu[1].SetColor(text::BLACK);
	text_menu[1].Set_Rect(500, 500);

	string c = "EXIT";
	text_menu[2].SetText(c);
	text_menu[2].SetColor(text::BLACK);
	text_menu[2].Set_Rect(500, 600);

	bool selected[kMenuItem] = { 0,0,0 };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true) {
		Render(des);
		text_menu[0].Load_from_file("font/RobotoCondensed-Italic.ttf");
		text_menu[1].Load_from_file("font/RobotoCondensed-Italic.ttf");
		text_menu[2].Load_from_file("font/RobotoCondensed-Italic.ttf");

		text_menu[0].LoadFromRenderText(Menu_font,des);
		text_menu[1].LoadFromRenderText(Menu_font, des);
		text_menu[2].LoadFromRenderText(Menu_font, des);



		text_menu[0].RenderText(des,500,400);
		text_menu[1].RenderText(des,500,500);
		text_menu[2].RenderText(des,500,600);
		

		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return 2;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				for (int i = 0; i < kMenuItem; i++) {
					int w = text_menu[i].GetWidth();
					int h = text_menu[i].GetHeight();
					if (checkFocuswithRect(xm, ym ,w ,h , text_menu[i].GetRect()))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(text::RED);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(text::BLACK);
						}

					}
				}
				
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;
				
					int w = text_menu[0].GetWidth();
					int h = text_menu[0].GetHeight();
					if (checkFocuswithRect(xm, ym,w, h, text_menu[0].GetRect()))
					{
						time_game_.start();
						return 1;
					}
					else if(checkFocuswithRect(xm,ym,w,h,text_menu[1].GetRect()))
					{
						Load_Img("Image_game/Instruct.png", des);
						Render(des);
					
						

				    }
					else if (checkFocuswithRect(xm, ym, w, h, text_menu[2].GetRect()))
					{
						return 2;
					}
			}
			break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1;
				}
			break;
			default:
				break;
			}
		}
		for (int i = 0; i < kMenuItem; i++) {
			text_menu[i].Free();
		}
		SDL_RenderPresent(des);
	}

	return -1;
}

bool Menu::checkFocuswithRect(int& x, int& y,int&w,int&h, const SDL_Rect& rect)
{
	

	if (x >= rect.x && x < rect.x + w &&
		y >= rect.y && y < rect.y + h)
	{
		return true;
	}
	return false;
}
	
