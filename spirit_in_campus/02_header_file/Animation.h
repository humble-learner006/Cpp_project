#pragma once 

struct  Animation
{
    /* data */
    int index;
    int frames;
    int speed;

    Animation(){};
    Animation (int i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
    }
};
