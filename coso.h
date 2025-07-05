#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "totalfunction.h"
#include "TextObject.h"

class baseobject
{
protected:
	SDL_Texture* p_object;//bien luu hinh anh
	SDL_Rect rect_;//bien luu kich thuoc anh

public:
	baseobject();
	~baseobject();
	void setrect(const int& x, const int& y)//ham set kich thuoc anh 
	{
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect getrect() const //ham lay kich thuoc anh
	{
		return rect_;
	}
	SDL_Texture* getobject() const //ham lay anh
	{
		return p_object;
	}
	int ShowMenu(SDL_Renderer* des, TTF_Font* font);
	virtual bool Loadimage(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
	bool CheckFocuswithRect(const int& x, const int& y, int& rectx, int& recty, Text textmenu);

};

#endif