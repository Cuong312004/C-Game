#include <iostream>
#include "Theats.h"

TheatsObject::TheatsObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground = false;
	comebacktime = 0;
	frame_ = 0;
	
	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 0;
	input_type_.kunai_ = 0;
	type_move_ = STATIC_THEAT;

	distance = 0;
}
TheatsObject::~TheatsObject()
{

}

SDL_Rect TheatsObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

bool TheatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = baseobject::Loadimage(path, screen);
	if (ret)
	{
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;
	}
	return ret;
}

void TheatsObject::set_clip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame_;
		frame_clip[0].h = height_frame_;

		frame_clip[1].x = width_frame_;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame_;
		frame_clip[1].h = height_frame_;

		frame_clip[2].x = 2 * width_frame_;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame_;
		frame_clip[2].h = height_frame_;

		frame_clip[3].x = 3 * width_frame_;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame_;
		frame_clip[3].h = height_frame_;

		frame_clip[4].x = 4 * width_frame_;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame_;
		frame_clip[4].h = height_frame_;

		frame_clip[5].x = 5 * width_frame_;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame_;
		frame_clip[5].h = height_frame_;

		frame_clip[6].x = 6 * width_frame_;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame_;
		frame_clip[6].h = height_frame_;

		frame_clip[7].x = 7 * width_frame_;
		frame_clip[7].y = 0;
		frame_clip[7].w = width_frame_;
		frame_clip[7].h = height_frame_;
	}
}

void TheatsObject::show(SDL_Renderer* des)
{
	if (comebacktime == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if(frame_ >=8)
		{
			frame_ = 0;
		}
		SDL_Rect* current_clip = &frame_clip[frame_];

		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };

		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
	}
}
void TheatsObject::DoPlayer(Map& gMap)
{
	if (comebacktime == 0)
	{
		x_val_ = 0;
		y_val_ += THEATS_GRAVITY_SPEED;
		if (y_val_ >= THEATS_MAX_FALL_SPEED)
		{
			y_val_ = THEATS_MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1 && distance == 0)
		{
			x_val_ -= THEATS_SPEED;
		}
		else if (input_type_.right_ == 1 && distance == 0)
		{
			x_val_ += THEATS_SPEED;
		}
		CheckToMap(gMap);
	}
	else if (comebacktime > 0)
	{
		comebacktime--;
		if (comebacktime == 0)
		{
			InitTheats();
		}
	}
	
}

void TheatsObject::InitTheats()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256)
	{
		x_pos_ -= 256;
		animation_a_ -= 256;
		animation_b_ -= 256;
	}
	else
	{
		x_pos_ = 0;
	}
	y_pos_ = 0;
	comebacktime = 0;
	input_type_.left_ = 1;
}

void TheatsObject::CheckToMap(Map& map_data)
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
			if ((val1 != BLANK_TILE && val1 != SUPPORT) || (val2 != BLANK_TILE && val2 != SUPPORT))
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
				animation_b_ = x_pos_;
			}
		
		}
		else if (x_val_ < 0) // di chuyen qua trai
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if ((val1 != BLANK_TILE && val1 != SUPPORT) || (val2 != BLANK_TILE && val2 != SUPPORT))
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
				animation_a_ = x_pos_;
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
			if ((val1 != BLANK_TILE && val1 != SUPPORT) || (val2 != BLANK_TILE && val2 != SUPPORT))
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground = true;
			}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if ((val1 != BLANK_TILE && val1!= SUPPORT) || (val2 != BLANK_TILE && val2 != SUPPORT))
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
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

void TheatsObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_THEAT)
	{
		if (input_type_.kunai_ == 1)
		{
			LoadImg("img//theat_shot.png", screen);
			//input_type_.kunai_ = 0;
		}
		else
		{
			LoadImg("img//theat.png", screen);
		}
	}
	else
	{
		if (on_ground == true)
		{
			if (x_pos_ >= animation_b_)
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("img//theat_left.png", screen);
			}
			else if (x_pos_ <= animation_a_)
			{
				input_type_.left_ = 0;
				input_type_.right_ = 1;
				LoadImg("img//theat_right.png", screen);
			}
			if (distance == 1)
			{
				if (input_type_.left_ == 1)
				{
					LoadImg("img//attack_left.png", screen);
				}
				else
				{
					LoadImg("img//attack_right.png", screen);
				}
			}
		}
		else
		{
			if (input_type_.left_ == 1)
			{
				LoadImg("img//theat_left.png", screen);
			}
		}
	}
}

void TheatsObject::InitSamurai(Kunai* p_Samurai, SDL_Renderer* screen)
{
	if (p_Samurai != NULL)
	{
		p_Samurai->set_kunai_type(Kunai::CungTen);
		bool ret = p_Samurai->LoadImgKunai(screen,2);
		if (ret)
		{
				p_Samurai->Set_is_move(true);
				p_Samurai->set_kunai_dir(Kunai::DIR_LEFT);
				p_Samurai->setrect(rect_.x + 5, y_pos_ + 55);
				p_Samurai->Set_x_val(15);
				samurai_list_.push_back(p_Samurai);
		}
		
	}
}

void TheatsObject::MakeSamurai(SDL_Renderer* screen, const int& x_limit_, const int& y_limit_)
{
	for (int i = 0; i < samurai_list_.size(); i++)
	{
		Kunai* p_Samurai = samurai_list_.at(i);
		if (p_Samurai != NULL)
		{
			if (p_Samurai->get_is_move())
			{
				int Samurai_distance = rect_.x + width_frame_ - p_Samurai->getrect().x;
				if (Samurai_distance < 500 && Samurai_distance > 0)
				{
					p_Samurai->HandleMove(x_limit_, y_limit_);
					p_Samurai->Render(screen);
				}
				else
				{
					p_Samurai->Set_is_move(false);

				}
				if (Samurai_distance > 150)
				{
					input_type_.kunai_ = 0;
				}
			}
			else
			{
				input_type_.kunai_ = 1;
				p_Samurai->Set_is_move(true);
				p_Samurai->setrect(rect_.x + 5, y_pos_ + 55);
			}
		}
	}
}
void TheatsObject::RemoveKunai(const int& idx)
{
	int size = samurai_list_.size();
	if (size > 0 && idx < size)
	{
		Kunai* p_kunai = samurai_list_.at(idx);
		samurai_list_.erase(samurai_list_.begin() + idx);
		if (p_kunai)
		{
			delete p_kunai;
			p_kunai = NULL;
		}
	}
}

void TheatsObject::setBOOLdistance()
{
	distance = 1;
}

void TheatsObject::resetBOOLdistance()
{
	distance = 0;
}