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
            friend ostream& operator<<(ostream&, const Character&);
            //virtual bool move(int x, int y);
            //virtual bool move();
            virtual void walk();
            virtual void walk2();
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
            virtual void pause(int fps);
            virtual bool isMoving() const;
        protected:
            int tmp_velX, tmp_velY;
            bool d_foot, d_timeLapse, d_moving;
            int d_iterateur;
            int d_x, d_y, d_id;
            int d_velX, d_velY, d_vel;
            int d_orientation, d_old_orientation, d_frame, d_next_frame;
            SDL_Rect d_spriteClips[48];
            Image d_spriteSheetTexture;
            string d_name;
    };
}

#endif // CHARACTER_H
