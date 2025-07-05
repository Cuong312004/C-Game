#include "Boss.h"

Boss::Boss()
{
	frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0;
	y_pos_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	comebacktime = 0;
	map_x_ = 0;
	map_y_ = 0;
}

Boss::~Boss()
{

}

bool Boss::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = baseobject::Loadimage(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / FRAME_NUM_32;
		height_frame_ = rect_.h;
	}
	return ret;
}

void Boss::set_clip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < FRAME_NUM_32; i++)
		{
			frame_clip[i].x = width_frame_ * i;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame_;
			frame_clip[i].h = height_frame_;
		}
	}
}

void Boss::Show(SDL_Renderer* des)
{
	if (comebacktime == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= 32)
		{
			frame_ = 0;
		}

		SDL_Rect* currentClip = &frame_clip[frame_];
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		if (currentClip != NULL)
		{
			renderQuad.w = currentClip->w;
			renderQuad.h = currentClip->h;
		}
		SDL_RenderCopy(des, p_object, currentClip, &renderQuad);
	}
}

void Boss::Doplayer(Map& g_map)
{
	if (comebacktime == 0)
	{
		x_val_ = 0;
		y_val_ += GRAVITY_SPEED;
		if (y_val_ >= MAX_FALL_SPEED)
		{
			y_val_ = MAX_FALL_SPEED;
		}
		if (input_type_.left_ == 1)
		{
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += PLAYER_SPEED;
		}

		if (input_type_.jump_ == 1)
		{
			if (on_ground_ == 1)
			{
				y_val_ = -PLAYER_HIGHT_VAL;
			}
			input_type_.jump_ = 0;
		}
		CheckToMap(g_map);
	}
	if (comebacktime > 0)
	{
		comebacktime--;
		if (comebacktime == 0)
		{
			InitPlayer();
		}
	}
}

void Boss::InitPlayer()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256)
	{
		x_pos_ -= 256;
	}
	else
		x_pos_ = 0;
	y_pos_ = 0;
	comebacktime = 0;
	input_type_.left_ = 1;
}

void Boss::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// check chieu ngang
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // nhan vat di chuyen qua phai
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == SUPPORT || val2 == SUPPORT)
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else
			{
				if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
				{
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;
				}
			}
		}
		else if (x_val_ < 0) // di chuyen qua trai
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == SUPPORT || val2 == SUPPORT)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
			}
			else
			{
				if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
				{
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
			}
		}
	}

	// check chieu doc 
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == SUPPORT || val2 == SUPPORT)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else
			{
				if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
				{
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground_ = 1;
				}
			}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 == SUPPORT || val2 == SUPPORT)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else
			{
				if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
				{
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}
		}
	}


	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_)
	{
		comebacktime = 30;
	}
}
void Boss::InitKunai(SDL_Renderer* screen)
{
	Kunai* p_kunai = new Kunai();
	bool ret = p_kunai->Loadimage("img//boss_bullet.png", screen);
	if (ret)
	{
		p_kunai->set_kunai_dir(Kunai::DIR_LEFT);
		p_kunai->Set_is_move(true);
		p_kunai->setrect(rect_.x - 50, rect_.y + height_frame_ - 30);
		p_kunai->Set_x_val(15);
		kunai_list.push_back(p_kunai);
	}
}

void Boss::MakeKunai(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
	if (frame_ == 18)
	{
		InitKunai(des);
	}
	for (int i = 0; i < kunai_list.size(); i++)
	{
		Kunai* p_kunai = kunai_list.at(i);
		if (p_kunai != NULL)
		{
			if (p_kunai->get_is_move())
			{
				p_kunai->HandleMove(x_limit, y_limit);
				p_kunai->Render(des);
			}
			else
			{
				p_kunai->Free();
				kunai_list.erase(kunai_list.begin() + i);
			}
		}
	}
}

SDL_Rect Boss::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}