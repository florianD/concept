#ifndef CHARACTER_H
#define CHARACTER_H
#include "Object.h"
#include "Image.h"

namespace rpg
{
    class Character : public Object
    {
        public:
            Character();
            Character(int x, int y, int vel, int vx, int vy, int id, string name, int orientation);
            virtual ~Character();
            virtual int getX() const;
            virtual int getY() const;
            void rotate(int r);
            string getName() const;
            int getOrientation() const;
            virtual bool loadSpriteSheet(SDL_Renderer *renderer) = 0;
            virtual void render(SDL_Renderer *renderer, int camx, int camy);
            virtual void renderT(SDL_Renderer *renderer, int camx, int camy);
            virtual void walk();
            virtual void moveTo(int x, int y);
            virtual int getVel() const;
            virtual int getVelX() const;
            virtual int getVelY() const;
            virtual bool isMotionless() const;
            virtual void setVel(int vel);
            virtual void setVelX(int vel);
            virtual void setVelY(int vel);
            virtual void oriFromDir();
            virtual void frameFromOri(int offset);
        protected:
            int d_frame;
            bool d_foot;
            int d_x, d_y, d_id;
            int d_velX, d_velY, d_vel;
            int d_orientation;
            SDL_Rect d_spriteClips[48];
            Image d_spriteSheetTexture;
            string d_name;
    };
}

#endif // CHARACTER_H