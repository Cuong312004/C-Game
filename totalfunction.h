
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// screen
const int FRAME_PER_SECOND = 25; // fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

//kunai
static int demsolan = 0 ;
static int nho = 50;		// bien nho truoc do la kunai hay shuriken

static int BOOLdistance = 0;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define SUPPORT 4

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
	int kunai_;
	int kunai_type_;
};


typedef struct Map
{
	int start_x;
	int start_y;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name_;
};

namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool distancePlayerToTheat(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif