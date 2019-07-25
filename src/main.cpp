#include "minesweeper.hpp"

int main(int argc, char** argv)
{
    Minesweeper game;
    
    if (!game.init(36, 36))
    {
        return -1;
    }
    
    game.run();
    
    return 0;
}