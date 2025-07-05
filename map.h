#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "totalfunction.h"
#include "coso.h"

#define MAX_TILES 20
class TileMat : public baseobject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screeen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; };
	void SetMap(Map& map_data) { game_map_ = map_data; };
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];

};


#endif 
