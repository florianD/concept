#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "Image.h"
#include "Tile.h"
#include "Map.h"
#include "Object.h"
#include "Character.h"
#include "Player.h"
#include "NPC.h"

namespace rpg
{
    class Game
    {
        public:
            Game();
            ~Game();
            void start();
        private:
            void renderAll();
            void actions();
            void handleEvents();
            bool loadBackgroundImage();
            static const int SCREEN_WIDTH = 800;
            static const int SCREEN_HEIGHT = 600;
            Image d_background;
            SDL_Window *d_window;
            SDL_Renderer *d_renderer;
            bool d_running;
            Map *m;
            Player *player;
            Character *leader;
            SDL_Rect camera;
            std::vector<Character*> characters;
    };
}

#endif // GAME_H
