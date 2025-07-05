#ifndef KUNAI_H_
#define KUNAI_H_

#include "coso.h"
#include "totalfunction.h"

class Kunai : public baseobject
{
public:
	Kunai();
	~Kunai();

	enum KunaiDir
	{
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
	};

	enum KunaiType
	{
		KUNAI = 50,
		SHURIKEN = 51, 
		CungTen = 52,
	};

	void Set_x_val(const int& xVal) { x_val_ = xVal; }
	void Set_y_val(const int& yVal) { y_val_ = yVal; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void Set_is_move(const bool& isMove) { is_move_ = isMove; }
	int get_is_move() const { return is_move_; }
	
	void HandleMove(const int& x_border, const int& y_border);

	void set_kunai_dir(const unsigned int& kunaiDir) { kunai_dir = kunaiDir; }
	unsigned int get_kunai_dir() const { return kunai_dir; }

	void set_kunai_type(const unsigned int& kunaiType) { kunai_type_ = kunaiType; }
	unsigned int get_kunai_type() const { return kunai_type_; }

	bool LoadImgKunai(SDL_Renderer* des ,int status);

	void ChangeKunai();

private:
	int x_val_;
	int y_val_;
	bool is_move_;
	unsigned int kunai_dir;
	unsigned int kunai_type_ ;
};

#endif