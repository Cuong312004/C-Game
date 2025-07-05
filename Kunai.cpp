#include <iostream>
#include "Kunai.h"
#include "player.h"

Kunai::Kunai()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	if (demsolan == 0)
	{
		kunai_type_ = KUNAI;
		demsolan++;
	}
	else if (nho == KUNAI)
	{
		kunai_type_ = KUNAI;
	}
	else if (nho == SHURIKEN)
	{
		kunai_type_ = SHURIKEN;
	}
}

Kunai::~Kunai()
{

}

void Kunai::ChangeKunai()
{
	if (kunai_type_ == KUNAI)
	{
		kunai_type_ = SHURIKEN;
		nho = SHURIKEN;
	}
	else if (kunai_type_ == SHURIKEN)
	{
		kunai_type_ = KUNAI;
		nho = KUNAI;
	}
}
 
bool Kunai::LoadImgKunai(SDL_Renderer* des , int status)
{
	bool ret = false;
	if (kunai_type_ == KUNAI)
	{
		if (status == 2)
		{
			ret = Loadimage("img//Kunai_left.png", des);
		}
		else if (status == 1)
		{
			ret = Loadimage("img//Kunai_right.png", des);
		}
	}
	else if (kunai_type_ == SHURIKEN)
	{
		ret = Loadimage("img//Shuriken.png", des);
	}
	else if (kunai_type_ == CungTen)
	{
		ret = Loadimage("img//Cung.png", des);
	}
	return ret;

}

void Kunai::HandleMove(const int& x_border, const int& y_border)
{
	if (kunai_dir == DIR_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
	}
	else if (kunai_dir == DIR_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
	}
}