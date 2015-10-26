#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace rpg
{
    class config
    {
        public:
            static const int SIDE_X = 128; // MAP CLIP SIZE X
            static const int SIDE_Y = 64; // MAP CLIP SIZE Y

            static const int OFFSET_X = 24;
            static const int OFFSET_Y = 72;

            static const int MAP_WIDTH = 50; //  \ MUST MATCH FILE
            static const int MAP_HEIGHT = 50; //  /

            static const int WINDOW_W = 800;
            static const int WINDOW_H = 600;

            static const int LEVEL_W = config::SIDE_X * MAP_WIDTH;
            static const int LEVEL_H = config::SIDE_Y * MAP_HEIGHT;
    };
}

#endif // CONFIG_H
