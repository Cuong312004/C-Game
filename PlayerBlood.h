#ifndef PLAYER_BLOOD_H_
#define PLAYER_BLOOD_H_

#include "totalfunction.h"
#include "coso.h"

class PlayerBlood : public baseobject
{
	int number_;
	std::vector<int> pos_list_;
public:
	PlayerBlood();
	~PlayerBlood();
	void SetNum(const int& num) { number_ = num; }
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);

	void InitCrease();
	void InitDecrease();
};

class Avatar : public baseobject
{
	int x_pos_;
	int y_pos_;
public:
	Avatar();
	~Avatar();

	void Init(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void SetPos(const int& x, const int& y) { x_pos_ = x; y_pos_ = y; }
};

class Back :public baseobject
{
	int x_pos_;
	int y_pos_;
public:
	Back();
	~Back();

	void Init(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void SetPos(const int& x, const int& y) { x_pos_ = x; y_pos_ = y; }
};


#endif