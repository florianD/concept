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
            Character(int x, int y, int vel, int vx, int vy, std::string name, int orientation);
            virtual ~Character();
            virtual int getX() const;
            virtual int getY() const;
            void rotate(int r);
            std::string getName() const;
            int getOrientation() const;
            virtual void walk() = 0;
            virtual void moveTo(int x, int y);
            virtual int getId() const;
            virtual int getVel() const;
            virtual int getVelX() const;
            virtual int getVelY() const;
            virtual bool isMotionless() const;
            virtual void setVel(int vel);
            virtual void setVelX(int vel);
            virtual void setVelY(int vel);
            virtual void oriFromDir();
            virtual double frameFromOri(double offset) = 0;
            virtual SDL_Rect getRect() const;
        protected:
            virtual void resetAnimation() = 0;
            static int d_num;
            int d_id;
            SDL_Rect d_box;
            double d_frame, d_offset;
            int d_velX, d_velY, d_vel, d_clip;
            int d_orientation;
            std::string d_name;
            //enum {SOUTH, NORTH, WEST, EAST, DSOUTH, DNORTH, DWEST, DEAST};
            enum {DSOUTH, SOUTH, DWEST, WEST, DNORTH, NORTH, DEAST, EAST};
    };
}

#endif // CHARACTER_H
