#ifndef GAME_H
#define GAME_H

#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "Image.h"
#include "Tile.h"
#include "Logo.h"
#include "Titlescreen.h"
#include "Menu.h"
#include "Map.h"
#include "Object.h"
#include "Character.h"
#include "Player.h"
#include "Sorcerer.h"
#include "Warrior.h"
#include "NPC.h"
#include "Timer.h"

namespace rpg
{
    class Game
    {
        public:
            Game();
            ~Game();
            void start();
        private:
            static int nextLeader;
            void clearChars();
            void initChars();
            void setCamera(SDL_Rect box);
            bool collision(SDL_Rect &r1, SDL_Rect &r2) const;
            Character *getId(int id) const;
            void renderAll();
            void actions();
            void handleEvents();
            bool loadBackgroundImage();
            static const int SCREEN_WIDTH = config::WINDOW_W;
            static const int SCREEN_HEIGHT = config::WINDOW_H;
            Image d_background;
            SDL_Window *d_window;
            SDL_Renderer *d_renderer;
            TTF_Font *d_font;
            bool d_running;
            bool d_inGame;
            Map *m;
            Logo *logo;
            Pentagram *pentagram;
            Titlescreen *titlescreen;
            Menu *menu;
            Player *player;
            Character *leader;
            SDL_Rect camera;
            std::vector<Character*> characters;
            static Image d_textureFPS;
            bool d_fullscreen;
    };
}

#endif // GAME_H
