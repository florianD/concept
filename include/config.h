#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace rpg
{
    class config
    {
        public:
            static const int SIDE = 32;

            static const int MAP_WIDTH = 10; //  \ doit correspondre au fichier
            static const int MAP_HEIGHT = 10; // /

            static const int WINDOW_W = 800;
            static const int WINDOW_H = 600;

            static const int LEVEL_W = config::SIDE * MAP_WIDTH; // >= WINDOW_W  \ pour la cam, sinon la desactiver
            static const int LEVEL_H = config::SIDE * MAP_HEIGHT; // >= WINDOW_H /
    };
}

#endif // CONFIG_H
