#include "Game.h"
#include "Constants.h"

int main ()
{
    Game g { "Crazy Tanks!", screen_width, screen_height };
    g.start ();
}