#include<iostream>
#include "totalfunction.h"
#include "coso.h"
#include "map.h"
#include "player.h"
#include "Time.h"
#include "Theats.h"
#include "TextObject.h"
#include "PlayerBlood.h"
#include "Boss.h"
#include "BossBlood.h"

using namespace std;

baseobject g_background;
baseobject menu_background;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // tao cua so window cho game 

    g_window = SDL_CreateWindow("Game SDL2", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_JPG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("font//font.ttf", 30); // set phong chu
        font_menu = TTF_OpenFont("font//font.ttf", 100);
        if (font_time == NULL || font_menu == NULL)
        {
            success = false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.Loadimage("C:\\Users\\HP\\Desktop\\game\\img\\back.jpg",g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

vector<TheatsObject*> MakeTheatList()
{
    vector<TheatsObject*> list_theats;

    TheatsObject* dynamic_theats = new TheatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        TheatsObject* p_theat = dynamic_theats + i;
        if (p_theat != NULL)
        {
            p_theat->LoadImg("img//theat_left.png", g_screen);
            p_theat->set_clip();
            p_theat->set_type_move(TheatsObject::MOVE_IN_SPACE_THEAT);
            p_theat->set_x_pos(500 + i * 1000);
            p_theat->set_y_pos(200);

            int pos1 = p_theat->get_x_pos() - 60;
            int pos2 = p_theat->get_x_pos() + 60;
            p_theat->setAnimationPos(pos1, pos2);
            p_theat->set_input_left(1);
            list_theats.push_back(p_theat);
        }
    }



    TheatsObject* theats_objs = new TheatsObject[20];

    for (int i = 0; i < 20; i++)
    {
        TheatsObject* p_theat = (theats_objs + i);
        if (p_theat != NULL)
        {
            p_theat->LoadImg("img//theat.png", g_screen);
            p_theat->set_clip();
            p_theat->set_x_pos(700+i*1000);
            p_theat->set_y_pos(250);
            p_theat->set_type_move(TheatsObject::STATIC_THEAT);
            p_theat->set_input_left(0);

            Kunai* p_Samurai = new Kunai();
            p_theat->InitSamurai(p_Samurai, g_screen);
            list_theats.push_back(p_theat);
        }
    }
    return list_theats;
}

int main(int argc, char* argv[])
{
    int centerentityonmap = 1;
    Timer fps_timer;

    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);
    
    Player p_player;
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clips();

    PlayerBlood Player_blood;
    Player_blood.Init(g_screen);

    Avatar avatar_;
    avatar_.Init(g_screen);
    avatar_.SetPos(10, 10);

    Back back_;
    back_.Init(g_screen);
    back_.SetPos(100, 23);

    BossBlood Boss_blood;
    Boss_blood.Init(g_screen);

    BossBack Bback_;
    Bback_.Init(g_screen);
    Bback_.SetPos(997, 230);

    vector<TheatsObject*> theats_list = MakeTheatList();
    //boss
    Boss bossobject;
    bool ret = bossobject.LoadImg("img//boss_object.png", g_screen);
    bossobject.set_clip();
    int xPosBoss = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH * 0.1;
    bossobject.set_x_pos(xPosBoss);
    bossobject.set_y_pos(200);
    int positionmap = SCREEN_WIDTH / 2; //diem gap boss

    Text time_game;
    time_game.SetColor(Text::WHITE);

    Text mark_game;
    mark_game.SetColor(255, 0, 255);
    UINT mark_value = 0;


    int num_die = 0;
    int boss_num_die = 0;

    bool is_quit = false;

    int ret_menu = menu_background.ShowMenu(g_screen, font_menu);
    if (ret_menu == 1)
        is_quit = true;
    while (!is_quit)
    {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.HandleKunai(g_screen);
        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.Doplayer(map_data,centerentityonmap);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        avatar_.Show(g_screen);
        back_.Show(g_screen);
        Player_blood.Show(g_screen); 

        for (int i = 0; i < theats_list.size();i++)
        {
            TheatsObject* p_theat = theats_list.at(i);
            if (p_theat != NULL)
            {
                SDL_Rect rect_players = p_player.GetRectFrame();
                SDL_Rect rect_theats = p_theat->GetRectFrame();
                bool bCol3 = SDLCommonFunc::distancePlayerToTheat(rect_players, rect_theats);

                if (bCol3)
                {
                    p_theat->setBOOLdistance();
                }
                else
                {
                    p_theat->resetBOOLdistance();
                }


                p_theat->set_map(map_data.start_x, map_data.start_y);
                p_theat->ImpMoveType(g_screen);
                p_theat->DoPlayer(map_data);
                p_theat->MakeSamurai(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_theat->show(g_screen);
                //check va cham vu khi doi tuong va nhan vat
                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
              
                std::vector<Kunai*> tKunai_list = p_theat->get_samurai_list();
            
                for (int jj = 0; jj < tKunai_list.size(); jj++)
                {
                    Kunai* pt_kunai = tKunai_list.at(jj);
                    if (pt_kunai)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(rect_player, pt_kunai->getrect());
                        if (bCol1)
                        {
                            //p_theat->RemoveKunai(jj);
                            break;
                        }
                    }
                }

                // check va cham nhan vat và doi tuong
                SDL_Rect rect_theat = p_theat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_theat);
             

                if (bCol1 || bCol2 )
                {
                    num_die++;
                    if (num_die <= 3)
                    {
                        p_player.setrect(0, 0);
                        p_player.set_comebacktime(20);
                        SDL_Delay(1000);
                        Player_blood.InitDecrease();
                        Player_blood.Render(g_screen);
                        continue;
                    }
                    else
                    {
                        if (MessageBox(NULL, L"NGU,CHOI LAI DI!", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_theat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }


            }
        }
         
        //check va cham vu khi nhan vat va doi tuong
        std::vector<Kunai*> Kunai_arr = p_player.get_kunai_list();
        for (int r = 0; r < Kunai_arr.size(); r++)
        {
            Kunai* p_kunai = Kunai_arr.at(r);
            if (p_kunai != NULL)
            {
                for (int t = 0; t < theats_list.size(); t++)
                {
                    TheatsObject* obj_theat = theats_list.at(t);
                    if (obj_theat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_theat->getrect().x;
                        tRect.y = obj_theat->getrect().y;
                        tRect.w = obj_theat->get_width_frame();
                        tRect.h = obj_theat->get_height_frame();

                        SDL_Rect BRect;
                        BRect.x = bossobject.getrect().x;
                        BRect.y = bossobject.getrect().y;
                        BRect.w = bossobject.get_width_frame();
                        BRect.h = bossobject.get_height_frame();

                        SDL_Rect bRect = p_kunai->getrect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        bool BCol = SDLCommonFunc::CheckCollision(bRect, BRect);
                        if (bCol)
                        {
                            mark_value++;
                            p_player.RemoveKunai(r);
                            obj_theat->Free();
                            theats_list.erase(theats_list.begin() + t);
                        }
                        
                        if (BCol)
                        {
                            p_player.RemoveKunai(r);
                            boss_num_die++;
                            if (boss_num_die <= 5)
                            {
                                continue;
                            }
                            else
                            {
                                if (MessageBox(NULL, L"May thang roi!", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                                {
                                    close();
                                    SDL_Quit();
                                    return 0;
                                }
                            }

                        }
                        
                    }
                }
            }
        }

        // hien thi thoi gian
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 3000 - time_val;
        if (val_time <= 0)
        {
            if (MessageBox(NULL, L"NGU,CHOI LAI DI!", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;
            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
        }

        // hien thi diem
        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Point: ");
        std::string strtail("/10");
        strMark += val_str_mark;
        strMark += strtail;
        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5, 15);

        //show boss
        int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x + p_player.getrect().x);
        if (val <= positionmap)
        {
            Bback_.Show(g_screen);
            Boss_blood.Show(g_screen);

            positionmap = SCREEN_WIDTH;
            centerentityonmap = 0;
            bossobject.SetMapXY(map_data.start_x, map_data.start_y);
            bossobject.Doplayer(map_data);
            bossobject.MakeKunai(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            bossobject.Show(g_screen);
            // check va cham lua boss và nhan vat
            bool BCol1 = false;
            bool BCol2 = false;
            std::vector<Kunai*> BKunai_list = bossobject.get_kunai_list();

            for (int jj = 0; jj < BKunai_list.size(); jj++)
            {
                if (jj == 0)
                {
                    Kunai* pt_kunai = BKunai_list.at(jj);
                    if (pt_kunai)
                    {
                        BCol1 = SDLCommonFunc::CheckCollision(p_player.GetRectFrame(), pt_kunai->getrect());
                    }
                }
                else
                {
                    Kunai* pt_kunai = BKunai_list.at(jj);
                    Kunai* pt_kunai2 = BKunai_list.at(jj - 1);
                    if (pt_kunai)
                    {
                        BCol1 = SDLCommonFunc::CheckCollision(p_player.GetRectFrame(), pt_kunai->getrect());
                        BCol2 = SDLCommonFunc::CheckCollision(p_player.GetRectFrame(), pt_kunai2->getrect());
                    }
                }
            }
            
            if (BCol1 || BCol2)
            {
                num_die++;
                if (num_die <= 3)
                {
                    p_player.setrect(0, 0);
                    p_player.set_comebacktime(20);
                    SDL_Delay(1000);
                    Player_blood.InitDecrease();
                    Player_blood.Render(g_screen);
                    continue;
                }
                else
                {
                    if (MessageBox(NULL, L"NGU,CHOI LAI DI!", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                    {
                        close();
                        SDL_Quit();
                        return 0;
                    }
                }
            }
            
        }


        SDL_RenderPresent(g_screen);

        int real_time = fps_timer.get_ticks();
        int time_1_frame = 1000 / FRAME_PER_SECOND; // ms

        if (real_time < time_1_frame)
        {
            int delay_time = time_1_frame - real_time;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }

    }

    for (int i = 0; i < theats_list.size(); i++)
    {
        TheatsObject* p_theat = theats_list.at(i);
        if (p_theat)
        {
            p_theat->Free();
            p_theat = NULL;
        }
    }
    theats_list.clear();
    close();
    return 0;
}
