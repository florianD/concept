#include "../include/config.h"

namespace rpg
{
    int config::d_side = 32;
    std::string config::d_dir = "img32";
    int config::d_margin = 0;
    int config::d_c = 25;
    int config::d_l = 2;

    int config::d_wrapper_w = config::d_c * config::d_side;
    int config::d_wrapper_h = config::d_l * config::d_side;

    int config::d_win_w = 800;
    int config::d_win_h = 600;
}
