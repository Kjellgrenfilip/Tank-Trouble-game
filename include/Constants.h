#pragma once

int const MENU_STATE{0};
int const GAME_STATE{1};
int const PAUSE_STATE{2};
int const WIN_STATE{3};

int const screen_width{1080};
int const screen_height{720};
//tillagda för kartan
static float resolution_gridsize = 32;
static float gridsize_x = screen_width/resolution_gridsize;
static float gridsize_y = screen_height/resolution_gridsize;

float const fps{60.0};