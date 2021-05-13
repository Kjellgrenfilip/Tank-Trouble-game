#pragma once

int const EXIT_STATE{0};
int const MENU_STATE{1};
int const GAME_STATE{2};
int const PAUSE_STATE{3};
int const WIN_STATE{4};

int const screen_width{1280};
int const screen_height{720};
//tillagda för kartan
//static float resolution_gridsize = 32;

static float pixel_resolution_x = 32;
static float pixel_resolution_y = 18;

static float gridsize_x = screen_width/pixel_resolution_x;
static float gridsize_y = screen_height/pixel_resolution_y;

float const fps{60.0};

int const MENU_ITEMS{3};

float const pi{3.14159265359};
