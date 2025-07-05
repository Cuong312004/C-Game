#ifndef  PLAYER_H_
#define PLAYER_H_

#include <vector>

#include "totalfunction.h"
#include "coso.h"
#include "Kunai.h"

using namespace std;

#define GRAVITY_SPEED 2
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP 17

class Player : public baseobject
{
public:
	Player();
	
	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void set_clips();

	void HandelInputAction(SDL_Event events, SDL_Renderer* screen); // nhan vat di chuyen 

	void Doplayer(Map & map_data,int centerentityonmap); // kiemtra va cham
	void CheckToMap(Map& map_data);

	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void CenterEntityOnMap(Map& map_data);//tinh thong so map khi di chuyen
	void UpdateImagePlayer(SDL_Renderer* des);
	SDL_Rect GetRectFrame();
	void HandleKunai(SDL_Renderer* des);

	void set_kunai_list(vector<Kunai*> kunai_list)
	{
		p_kunai_list = kunai_list;
	}
	vector<Kunai*> get_kunai_list() const { return p_kunai_list; }

	void RemoveKunai(const int& idx);
	void countSupport();
	void set_comebacktime(const int& c_time) { comebacktime = c_time; }
private:
	int count_support;

	vector<Kunai*>  p_kunai_list;

	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;
	
	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip[11];
	Input input_type_;
	int frame_;
	int status_;
	int on_ground_;

	//bien luu vi tri ban do
	int map_x_;
	int map_y_;

	int comebacktime;
	
	// cac bien dem ngu
	int dem;
};

#endif // ! PLAYER_H_

