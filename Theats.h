#ifndef THEATS_OBJECT_H_
#define THEATS_OBJECT_H_

#include "totalfunction.h"
#include "coso.h"
#include "Kunai.h"

#define THEATS_MAX_FALL_SPEED 10
#define THEATS_FRAME_NUM 8;
#define THEATS_GRAVITY_SPEED 0.8
#define THEATS_SPEED 3

class TheatsObject : public baseobject
{
private:
	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground;
	int comebacktime;
	SDL_Rect frame_clip[8];
	int width_frame_;
	int height_frame_;
	int frame_;

	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;

	int distance;
	std::vector<Kunai*> samurai_list_;
public:
	TheatsObject();
	~TheatsObject();
	
	enum TypeMove
	{
		STATIC_THEAT = 0,
		MOVE_IN_SPACE_THEAT = 1,
	};
	SDL_Rect GetRectFrame();
	void set_x_val(const float& xVal) { x_val_ = xVal; }
	void set_y_val(const float& yVal) { y_val_ = yVal; }

	void set_x_pos(const float& xp) { x_pos_ = xp; }
	void set_y_pos(const float& yp) { y_pos_ = yp; }
	float get_x_pos() const { return x_pos_; }
	float get_y_pos() const { return y_pos_; }

	void set_map(const int& mapX, const int& mapY) { map_x_ = mapX; map_y_ = mapY; }

	void set_clip();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* des);
	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }

	void DoPlayer(Map& gMap);
	void CheckToMap(Map& map_data);
	void InitTheats();
	void set_type_move(const int& typeMove) { type_move_ = typeMove; }
	void setAnimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a; animation_b_ = pos_b; }
	void set_input_left(const int& ipleft) { input_type_.left_ = ipleft; }
	void ImpMoveType(SDL_Renderer* screen);

	std::vector<Kunai*> get_samurai_list() const { return samurai_list_; }
	void set_samurai_list(const std::vector<Kunai*>& sm_list) { samurai_list_ = sm_list; }

	void RemoveKunai(const int& idx);
	void InitSamurai(Kunai* p_Samurai, SDL_Renderer* screen);
	void MakeSamurai(SDL_Renderer* screen, const int& x_limit_, const int& y_limit_);

	void setBOOLdistance();
	void resetBOOLdistance();
};

#endif