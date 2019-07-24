#include "minesweeper.hpp"

int main(int argc, char** argv)
{
    Minesweeper game;
    
    if (!game.init(32, 32))
    {
        return -1;
    }
    
    game.tick();
    
    return 0;
}