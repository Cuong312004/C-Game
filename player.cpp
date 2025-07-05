#include "player.h" 

// Xu ly hinh anh nhan vat , di chuyen

Player::Player()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	input_type_.kunai_ = 0;
	input_type_.kunai_type_ = 0;
	on_ground_ = 0;
	map_x_ = 0;
	map_y_ = 0; 
	comebacktime = 0;
	dem = 0;
	count_support = 0;
}

 
bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = baseobject::Loadimage(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / 11;
		height_frame_ = rect_.h ;
	}
	return ret;
}

SDL_Rect Player::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}

void Player::set_clips()
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

		frame_clip[2].x = 2*width_frame_;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame_;
		frame_clip[2].h = height_frame_;

		frame_clip[3].x = 3*width_frame_;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame_;
		frame_clip[3].h = height_frame_;

		frame_clip[4].x = 4*width_frame_;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame_;
		frame_clip[4].h = height_frame_;

		frame_clip[5].x = 5*width_frame_;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame_;
		frame_clip[5].h = height_frame_;

		frame_clip[6].x = 6*width_frame_;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame_;
		frame_clip[6].h = height_frame_;

		frame_clip[7].x = 7*width_frame_;
		frame_clip[7].y = 0;
		frame_clip[7].w = width_frame_;
		frame_clip[7].h = height_frame_;

		frame_clip[8].x = 8*width_frame_;
		frame_clip[8].y = 0;
		frame_clip[8].w = width_frame_;
		frame_clip[8].h = height_frame_;

		frame_clip[9].x = 9 * width_frame_;
		frame_clip[9].y = 0;
		frame_clip[9].w = width_frame_;
		frame_clip[9].h = height_frame_;

		frame_clip[10].x = 10 * width_frame_;
		frame_clip[10].y = 0;
		frame_clip[10].w = width_frame_;
		frame_clip[10].h = height_frame_;
		
	}
}

void Player::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des);

	if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.kunai_ == 1)
	{
		frame_++;
		if (dem == 7)
		{
			input_type_.kunai_ = 0;
			dem = 0;
		}
		if(input_type_.kunai_ == 1)
			dem++;
	}
	else
	{
		frame_ = 0;
		LoadImg("img//player_right.png", des);
	}

	if (frame_ >= 11)
	{
		frame_ = 1;
	}

	if (comebacktime == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;

		SDL_Rect* current_clip = &frame_clip[frame_];

		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };

		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
	}
}

void Player::HandelInputAction(SDL_Event events,SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_RIGHT:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				UpdateImagePlayer(screen);
			}
			break;
			case SDLK_LEFT:
			{
				status_ = WALK_LEFT;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				UpdateImagePlayer(screen);
			}
			break;

		}

	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_RIGHT:
			{
				input_type_.right_ = 0;
			}
			break;
			case SDLK_LEFT:
			{
				input_type_.left_ = 0;
			}
			break;
			case SDLK_UP:
			{
				input_type_.up_ = 0;
			}
			break;

		}
	}

	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_UP:
			{
				input_type_.jump_ = 1;
			}
			case SDLK_DOWN:
			{
				input_type_.kunai_type_ = 1;
			}
			break;
		}
		
	}

	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_RIGHT)
		{
			input_type_.jump_ = 1;
		}
		else if (events.button.button == SDL_BUTTON_LEFT)
		{
			input_type_.kunai_ = 1; // dung de load frame
			Kunai* p_kunai = new Kunai();
			if (input_type_.kunai_type_ == 1) // doi vu khi
			{
				p_kunai->ChangeKunai();
				input_type_.kunai_type_ = 0;
			}

			if (status_ == WALK_LEFT)
			{
				UpdateImagePlayer(screen);
				p_kunai->LoadImgKunai(screen,WALK_LEFT);
				p_kunai->set_kunai_dir(Kunai::DIR_LEFT);
				p_kunai->setrect(this->rect_.x, rect_.y + height_frame_ * 0.3);
			}
			else if (status_ == WALK_RIGHT)
			{
				UpdateImagePlayer(screen);
				p_kunai->LoadImgKunai(screen, WALK_RIGHT);
				p_kunai->set_kunai_dir(Kunai::DIR_RIGHT);
				p_kunai->setrect(this->rect_.x + width_frame_ - 15, rect_.y + height_frame_ * 0.4);
			}
			p_kunai->Set_x_val(20);
			p_kunai->Set_is_move(true);

			p_kunai_list.push_back(p_kunai);
		}
	}
}

void Player::HandleKunai(SDL_Renderer* des)
{
	for (int i = 0; i < p_kunai_list.size(); i++)
	{
		Kunai* p_kunai = p_kunai_list.at(i);
		if (p_kunai != NULL)
		{
			if (p_kunai->get_is_move() == true)
			{
				p_kunai->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_kunai->Render(des);
			}
			else
			{
				p_kunai_list.erase(p_kunai_list.begin() + i);
				if (p_kunai != NULL)
				{
					delete p_kunai;
					p_kunai = NULL;
				}
			}
		}
	}
}

void Player::Doplayer(Map& map_data,int centerentityonmap)
{
	if (comebacktime == 0)
	{
		x_val_ = 0;
		y_val_ += 0.8;

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

		if (input_type_.up_ == 1)
		{
			if (on_ground_ == 1)
			{
				y_val_ = -PLAYER_JUMP;
				on_ground_ = 0;
			}
			input_type_.jump_ = 0;
		}

		if (input_type_.jump_ == 1)
		{
			if (on_ground_ == 1)
			{
				y_val_ = -PLAYER_JUMP;
			}
			on_ground_ = 0;
			input_type_.jump_ = 0;
		}
		CheckToMap(map_data);
		if(centerentityonmap == 1)
			CenterEntityOnMap(map_data);
	}

	if (comebacktime > 0)
	{
		comebacktime--;
		if (comebacktime == 0)
		{
			on_ground_ = 0;
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256;
				map_x_ -= 256;
			}
			else
				x_pos_ = 0;
		}
	}
}

void Player::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + SCREEN_WIDTH > MAX_MAP_X * TILE_SIZE)
	{
		map_data.start_x = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH;
	}
	else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x = map_data.max_x_ - SCREEN_WIDTH;
	}
	

	map_data.start_y = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y < 0)
	{
		map_data.start_y = 0;
	}
	else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void Player::CheckToMap(Map& map_data)
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
				countSupport();
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
				countSupport();
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
				countSupport();
			}
			else
			{
				if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
				{
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground_ = 1;
					if (status_ == WALK_NONE)
					{
						status_ = WALK_RIGHT;
					}
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
				countSupport();
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

void Player::countSupport()
{
	count_support++;
}

void Player::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground_ == 1)
	{

		if (status_ == WALK_LEFT)
		{
			LoadImg("img//player_left.png", des);
		}
		else
		{
			LoadImg("img//player_right.png", des);
		}

	}
	else
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("img//jum_left.png", des);
		}
		else 
		{
			LoadImg("img//jum_right.png", des);
		}
		
	}

	if (input_type_.kunai_ == 1)
	{
		if (on_ground_ == 0)
		{
			if (status_ == WALK_LEFT)
			{
				LoadImg("img//Jump_Throw_left.png", des);
			}
			else if (status_ == WALK_RIGHT)
			{
				LoadImg("img//Jump_Throw_right.png", des);
			}
		}
		else
		{
			if (status_ == WALK_LEFT)
			{
				LoadImg("img//Throw_left.png", des);
			}
			else if (status_ == WALK_RIGHT)
			{
				LoadImg("img//Throw_right.png", des);
			}
		}
	}

}

void Player::RemoveKunai(const int& idx)
{
	int size = p_kunai_list.size();
	if (size > 0 && idx < size)
	{
		Kunai* p_kunai = p_kunai_list.at(idx);
		p_kunai_list.erase(p_kunai_list.begin() + idx);
		if (p_kunai)
		{
			delete p_kunai;
			p_kunai = NULL;
		}
	}
}