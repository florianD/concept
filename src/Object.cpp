#include "../include/Object.h"

namespace rpg
{
    Object::~Object(){}

    void Object::setCamera(SDL_Rect &camera)
    {
        if(config::LEVEL_W >= config::WINDOW_W)
        {
            camera.x = (getX() + config::SIDE / 2) - config::WINDOW_W / 2;
            if(camera.x < 0)
            {
                camera.x = 0;
            }
            if(camera.x > config::LEVEL_W - camera.w)
            {
                camera.x = config::LEVEL_W - camera.w;
            }
        }
        if(config::LEVEL_H >= config::WINDOW_H)
        {
            camera.y = (getY() + config::SIDE / 2) - config::WINDOW_H / 2;
            if(camera.y < 0)
            {
                camera.y = 0;
            }
            if(camera.y > config::LEVEL_H - camera.h)
            {
                camera.y = config::LEVEL_H - camera.h;
            }
        }
    }
}
