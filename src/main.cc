#include "Game.h"
#include "Constants.h"

int main ()
{
    Game g { "Tank Trouble", screen_width, screen_height };
    g.start ();
}