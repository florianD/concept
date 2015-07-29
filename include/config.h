#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace rpg
{
    class config
    {
        public:
            static int d_side;
            static std::string d_dir;
            static int d_margin;
            static int d_l;
            static int d_c;
            static int d_win_w;
            static int d_win_h;
            static int d_wrapper_w;
            static int d_wrapper_h;
    };
}

#endif // CONFIG_H
