#include <iostream>
#include "PlayerBlood.h"

PlayerBlood::PlayerBlood()
{
	number_ = 0;
}
PlayerBlood::~PlayerBlood()
{

}

void PlayerBlood::AddPos(const int& xp)
{
	pos_list_.push_back(xp);
}

void PlayerBlood::Init(SDL_Renderer* screen)
{
	Loadimage("img//player_blood.png", screen);
	number_ = 3;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	AddPos(103);
	AddPos(178);
	AddPos(253);

}

void PlayerBlood::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list_.size(); i++)
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void PlayerBlood::InitDecrease()
{
	number_--;
	pos_list_.pop_back();
}

void PlayerBlood::InitCrease()
{
	number_++;
	int last_pos = pos_list_.back();
	last_pos += 50;
	pos_list_.push_back(last_pos);
	// xu ly am thanh duoi day
}

Avatar::Avatar()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
Avatar::~Avatar()
{

}

void Avatar::Init(SDL_Renderer* screen)
{
	bool ret = Loadimage("img//avatar.png", screen);
}

void Avatar::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}

Back::Back()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
Back::~Back()
{

}

void Back::Init(SDL_Renderer* screen)
{
	bool ret = Loadimage("img//back.png", screen);
}

void Back::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}