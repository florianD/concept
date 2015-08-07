#include "../include/Character.h"

namespace rpg
{
    int Character::d_id = 0;

    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    enum
    {
        FRONT=0, BACK=6, LEFT=12, RIGHT=18
    };

    // range dans d_orientation l'entier correspondant au mouvement
    void Character::oriFromDir()
    {
        if(d_velX > 0)
        {
            d_orientation = EAST;
        }
        else if(d_velX < 0)
        {
            d_orientation = WEST;
        }
        else if(d_velY > 0)
        {
            d_orientation = SOUTH;
        }
        else if(d_velY < 0)
        {
            d_orientation = NORTH;
        }
    }

    // range dans d_frame l'entier correspondant à l'orientation
    double Character::frameFromOri(double offset)
    {
        switch(d_orientation)
        {
            case EAST:
                return RIGHT + (int)offset;
            case WEST:
                return LEFT + (int)offset;
            case SOUTH:
                return FRONT + (int)offset;
            case NORTH:
                return BACK + (int)offset;
        }
    }

    Character::Character():d_vel(0), d_velX(0), d_velY(0), d_name(""), d_orientation(SOUTH), d_frame(0.0), d_offset(0.0), d_foot(0), d_moving(0)
    {
        d_id++;
        frameFromOri(0);
        d_box.x = 0;
        d_box.y = 0;
    }

    Character::Character(int x, int y, int vel, int vx, int vy, string name, int orientation):d_vel(vel), d_velX(vx), d_velY(vy), d_name(name), d_orientation(orientation), d_frame(0.0), d_foot(0)
    {
        d_id++;
        frameFromOri(0);
        d_box.x = x;
        d_box.y = y;
    }

    Character::~Character(){}

    int Character::getOrientation() const
    {
        return d_orientation;
    }

    int Character::getX() const
    {
        return d_box.x;
    }

    int Character::getY() const
    {
        return d_box.y;
    }

    string Character::getName() const
    {
        return d_name;
    }

    void Character::rotate(int r)
    {
        d_orientation = r;
    }

    SDL_Rect Character::getRect() const
    {
        return d_box;
    }

    void Character::walk()
    {
        //std::cout << d_frame << std::endl;

        oriFromDir();
        d_moving = true;
        if(d_moving)
        {
            d_frame = frameFromOri((d_foot * 2) % 4 + 2) + d_offset;
            d_offset += 0.1;
            if(d_offset >= 1.0)
            {
                d_offset = 0.0;
                d_foot = !d_foot;
                d_frame = frameFromOri(0);
            }
            d_box.x += d_velX;
            d_box.y += d_velY;
        }
    }

    void Character::moveTo(int x, int y)
    {
        d_box.x = x;
        d_box.y = y;
        d_orientation = SOUTH;
    }

    void Character::render(SDL_Renderer *renderer, SDL_Rect &cam)
    {
        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer, d_box.x - cam.x, d_box.y - cam.y, currentClip);
    }

    void Character::renderT(SDL_Renderer *renderer, SDL_Rect &cam)
    {
        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame + 1];
        d_spriteSheetTexture.render(renderer, d_box.x - cam.x, d_box.y - cam.y - d_box.h, currentClip);
    }

    int Character::getVel() const
    {
        return d_vel;
    }

    int Character::getVelX() const
    {
        return d_velX;
    }

    int Character::getVelY() const
    {
        return d_velY;
    }

    void Character::setVel(int vel)
    {
        d_vel = vel;
    }

    void Character::setVelX(int vel)
    {
        d_velX = vel;
    }

    void Character::setVelY(int vel)
    {
        d_velY = vel;
    }

    bool Character::isMotionless() const
    {
        return (getVelX() == 0 && getVelY() == 0);
    }
}
