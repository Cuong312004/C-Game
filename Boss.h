#ifndef  BOOS_H_
#define  BOOS_H_

#include "totalfunction.h"
#include "coso.h"
#include "Kunai.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 2
#define PLAYER_HIGHT_VAL 18

#define FRAME_NUM_32 32

class Boss : public baseobject
{
	int x_val_;
	int y_val_;
	int x_pos_;
	int y_pos_;
	int width_frame_;
	int height_frame_;
	
	SDL_Rect frame_clip[32];
	Input input_type_;
	int frame_;
	int status_;
	int on_ground_;

	//bien luu vi tri ban do
	int map_x_;
	int map_y_;

	int comebacktime;
	
	std::vector<Kunai*> kunai_list;
public:
	Boss();
	~Boss();
	void set_x_val(int xp) { x_val_ = xp; }
	void set_y_val(int yp) { y_val_ = yp; }
	void set_x_pos(const int& xpos) { x_pos_ = xpos; }
	void set_y_pos(const int& ypos) { y_pos_ = ypos; }
	int get_x_pos() { return x_pos_; }
	int get_y_pos() { return y_pos_; }
	
	void Show(SDL_Renderer* des);
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void set_clip();

	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }

	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	SDL_Rect GetRectFrame();
	void CheckToMap(Map& map_data);
	void CenterEntityOnMap(Map& map_data);
	void Doplayer(Map& map_data);
	void InitPlayer();
	std::vector<Kunai*> get_kunai_list() const { return kunai_list; }
	void set_kunai_list(const std::vector<Kunai*>& am_list) { kunai_list = am_list; }

	void InitKunai(SDL_Renderer* screen);
	void MakeKunai(SDL_Renderer* des, const int& x_limit, const int& y_limit);
};

#endif // ! BOOS_H_
