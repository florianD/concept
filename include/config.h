#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace rpg
{
    class config
    {
        public:
            static const int SIDE = 32;

            static const int MAP_WIDTH = 25;
            static const int MAP_HEIGHT = 2;

            static const int WINDOW_W = 800;
            static const int WINDOW_H = 600;

            static const int LEVEL_W = 800 * config::SIDE/16;
            static const int LEVEL_H = 800 * config::SIDE/16;
    };
}

#endif // CONFIG_H
