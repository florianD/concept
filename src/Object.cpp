#include "../include/Object.h"

namespace rpg
{
    Object::~Object(){}

    void Object::setCamera(SDL_Rect &camera)
    {
        //Center the camera over the player
        camera.x = (getX() + config::d_side / 2) - config::d_win_w / 2;
        camera.y = (getY() + config::d_side / 2) - config::d_win_h / 2;

        //Keep the camera in bounds
        /*if(camera.x < 0)
        {
            camera.x = 0;
        }
        if(camera.y < 0)
        {
            camera.y = 0;
        }
        if(camera.x > config::d_wrapper_w - camera.w)
        {
            camera.x = config::d_wrapper_w - camera.w;
        }
        if(camera.y > config::d_wrapper_h - camera.h)
        {
            camera.y = config::d_wrapper_h - camera.h;
        }*/
    }
}
