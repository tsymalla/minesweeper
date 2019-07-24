#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include <iostream>
#include "game.hpp"
#include "renderer.hpp"
#include "gui.hpp"

class Minesweeper
{
    private:
    constexpr static int CELL_WIDTH = 16;
    constexpr static int CELL_HEIGHT = 16;
    
    Renderer _renderer;
    GUI _gui;
    Game _game;
    bool _isRunning;
    
    public:
    Minesweeper();
    Minesweeper(const Minesweeper& rhs) = delete;
    Minesweeper(Minesweeper&& rhs) = delete;
    
    virtual ~Minesweeper();
    
    bool init(unsigned int width, unsigned int height);
    void tick();
};

#endif