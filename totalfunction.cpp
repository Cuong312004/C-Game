#include<iostream>
#include "totalfunction.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
        int left_a = object1.x + 20 ;
        int right_a = object1.x + object1.w - 20;
        int top_a = object1.y;
        int bottom_a = object1.y + object1.h;

        int left_b = object2.x + 10;
        int right_b = object2.x + object2.w;
        int top_b = object2.y + 15;
        int bottom_b = object2.y + object2.h;

        // Case 1: size object 1 < size object 2
        if (left_a >= left_b && left_a <= right_b) //3
        {
            if (top_a >= top_b && top_a <= bottom_b)
            {
                return true;
            }
        }

        if (left_a >= left_b && left_a <= right_b) // 2
        {
            if (bottom_a >= top_b && bottom_a <= bottom_b)
            {
                return true;
            }
        }

        if (right_a >= left_b && right_a <= right_b) // 4
        {
            if (top_a >= top_b && top_a <= bottom_b)
            {
                return true;
            }
        }

        if (right_a >= left_b && right_a <= right_b) // 1
        {
            if (bottom_a >= top_b && bottom_a <= bottom_b)
            {
                return true;
            }
        }

        // Case 2: size object 1 < size object 2
        if (left_b >= left_a && left_b <= right_a)
        {
            if (top_b >= top_a && top_b <= bottom_a)
            {
                return true;
            }
        }

        if (left_b >= left_a && left_b <= right_a)
        {
            if (bottom_b >= top_a && bottom_b <= bottom_a)
            {
                return true;
            }
        }

        if (right_b >= left_a && right_b <= right_a)
        {
            if (top_b >= top_a && top_b <= bottom_a)
            {
                return true;
            }
        }

        if (right_b >= left_a && right_b <= right_a)
        {
            if (bottom_b >= top_a && bottom_b <= bottom_a)
            {
                return true;
            }
        }

        // Case 3: size object 1 = size object 2
        if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
        {
            return true;
        }

        return false;
}

bool SDLCommonFunc::distancePlayerToTheat(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // object1 ben trai object2
    if ((left_b - right_a < 80) && (left_b - right_a > -90))
    {
        return true;
    }
    // object1 ben phai object2
    if ((left_a - right_b < 80) && (left_a - right_b > -90))
    {
        return true;
    }

    
    return false;
}


