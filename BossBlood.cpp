#include <iostream>
#include "BossBlood.h"

BossBlood::BossBlood()
{
	number_ = 0;
}
BossBlood::~BossBlood()
{

}

void BossBlood::AddPos(const int& xp)
{
	pos_list_.push_back(xp);
}

void BossBlood::Init(SDL_Renderer* screen)
{
	Loadimage("img//boss_blood.png", screen);
	number_ = 3;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	AddPos(1000);
	AddPos(1075);
	AddPos(1150);

}

void BossBlood::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list_.size(); i++)
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void BossBlood::InitDecrease()
{
	number_--;
	pos_list_.pop_back();
}

void BossBlood::InitCrease()
{
	number_++;
	int last_pos = pos_list_.back();
	last_pos += 50;
	pos_list_.push_back(last_pos);
	// xu ly am thanh duoi day
}

BossBack::BossBack()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
BossBack::~BossBack()
{

}

void BossBack::Init(SDL_Renderer* screen)
{
	bool ret = Loadimage("img//back.png", screen);
}

void BossBack::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}