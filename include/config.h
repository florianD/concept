#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace rpg
{
    class config
    {
        public:
            static const int SIDE = 32; // MAP CLIP SIZE

            static const int MAP_WIDTH = 50; //  \ MUST MATCH FILE
            static const int MAP_HEIGHT = 20; //  /

            static const int WINDOW_W = 800;
            static const int WINDOW_H = 600;

            static const int LEVEL_W = config::SIDE * MAP_WIDTH;
            static const int LEVEL_H = config::SIDE * MAP_HEIGHT;
    };
}

#endif // CONFIG_H
