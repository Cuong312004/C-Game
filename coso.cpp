#include "coso.h"

baseobject::baseobject()
{
	p_object = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}
baseobject::~baseobject()
{
	Free();
}

bool baseobject::CheckFocuswithRect(const int& x, const int& y, int& rectx, int& recty, Text textmenu)
{
	if (x >= rectx && x <= rectx + textmenu.GetWidth() && y > recty && y <= recty + textmenu.GetHeight())
	{
		return true;
	}
	return false;
}

bool baseobject::Loadimage(std::string path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* new_texture = NULL;//bien cuoi cung
	//doc anh
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));//set nen nhan vat giong mau nen backgound de xoa
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		//gan new_texture thanh cong
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);//xoa load_surface
	}
	p_object = new_texture;

	return p_object != NULL;
}

void baseobject::Render(SDL_Renderer* des, const SDL_Rect* clip )
{
	SDL_Rect renderquad = { rect_.x,rect_.y,rect_.w,rect_.h };

	SDL_RenderCopy(des, p_object, clip, &renderquad);//day thong so p_object len des
}
// huy p_object do ton bo nho
void baseobject::Free()
{
	if (p_object != NULL)
	{
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}

int baseobject::ShowMenu(SDL_Renderer* des, TTF_Font* font)
{
	bool ret = Loadimage("start.jpg", des);
	if (ret == NULL)
	{
		return 1;
	}

	const int MenuItemNum = 2;
	SDL_Rect pos_arr[MenuItemNum];
	pos_arr[0].x = 550;
	pos_arr[0].y = 500;

	pos_arr[1].x = 550;
	pos_arr[1].y = 350;
	
	std::pair<int,int> position_arr[2];
	position_arr[0].first = 550;
	position_arr[0].second = 500;

	position_arr[1].first = 550;
	position_arr[1].second = 350;

	Text textMenu[MenuItemNum];
	textMenu[0].SetText("START");
	textMenu[0].SetColor(Text::BLACK);
	textMenu[0].RenderText(des, pos_arr[0].x, pos_arr[0].y);

	textMenu[1].SetText("QUIT");
	textMenu[1].SetColor(Text::BLACK);
	textMenu[1].RenderText(des, pos_arr[1].x, pos_arr[1].y);

	bool selected[MenuItemNum] = { 0,0 };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true)
	{
		Render(des);
		for (int i = 0; i < MenuItemNum; i++)
		{
			textMenu[i].LoadFromRenderText(font, des);
			textMenu[i].RenderText(des, pos_arr[i].x, pos_arr[i].y);
		}
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				for (int i = 0; i < MenuItemNum; i++)
				{
					if (CheckFocuswithRect(xm, ym, position_arr[i].first, position_arr[i].second, textMenu[i]))
					{
						if (selected[i] == 0)
						{
							selected[i] = 1;
							textMenu[i].SetColor(Text::RED);
						}
					}
					else
					{
						if (selected[i] == 1)
						{
							selected[i] = 0;
							textMenu[i].SetColor(Text::BLACK);
						}
					}
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;
				for (int i = 0; i < MenuItemNum; i++)
				{
					if (CheckFocuswithRect(xm, ym, position_arr[i].first, position_arr[i].second, textMenu[i]))
					{
						return i;
					}
				}
			}
			break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym = SDLK_ESCAPE)
				{
					return 1;
				}
			}
		}
		SDL_RenderPresent(des);
	}
	return 1;
}