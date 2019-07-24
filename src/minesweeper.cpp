#include "minesweeper.hpp"
#include <SDL.h>

Minesweeper::Minesweeper(): _isRunning(false)
{
}

Minesweeper::~Minesweeper()
{
    SDL_Quit();
}

bool Minesweeper::init(unsigned int width, unsigned int height)
{
    const int screenWidth = width * CELL_WIDTH;
    const int screenHeight = height * CELL_HEIGHT;
    
    _gui.init(_renderer, screenWidth, screenHeight);
    
    if (!_renderer.init(screenWidth, _gui.getScoresPanelHeight() + screenHeight))
    {
        return false;
    }
    
    _game.init(width, height);
    _isRunning = true;
    
    return true;
}

void Minesweeper::tick()
{
    int mouseX = 0, mouseY = 0;
    
    while (_isRunning)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            
            if (e.type == SDL_QUIT)
            {
                _isRunning = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int tileX = mouseX / CELL_WIDTH;
                int tileY = ((mouseY - _gui.getScoresPanelHeight()) / CELL_HEIGHT);
                
                std::vector<int> trackedCells;
                
                bool hasMine = _game.openGameCell(tileX, tileY, false, trackedCells);
                
                if (hasMine)
                {
                    // game over
                }
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    _isRunning = false;
                }
            }
        }
        
        _renderer.clear();
        
        for (auto x = 0; x < _game.getWidth(); ++x)
        {
            for (auto y = 0; y < _game.getHeight(); ++y)
            {
                const int xCoord = x * CELL_WIDTH;
                const int yCoord = _gui.getScoresPanelHeight() + (y * CELL_HEIGHT);
                
                GameCell cell = _game.getGameCell(x, y);
                
                if (!cell.isOpen())
                {
                    _renderer.drawTile(xCoord, yCoord,
                                       CELL_WIDTH,
                                       CELL_HEIGHT,
                                       Renderer::TILE::CLOSED);
                }
                else
                {
                    if (!cell.hasMine())
                    {
                        _renderer.drawTile(xCoord, yCoord,
                                           CELL_WIDTH,
                                           CELL_HEIGHT,
                                           Renderer::TILE::OPEN);
                    }
                    else
                    {
                        _renderer.drawTile(xCoord, yCoord,
                                           CELL_WIDTH,
                                           CELL_HEIGHT,
                                           Renderer::TILE::MINE);
                    }
                }
            }
        }
        
        _gui.drawScoresPanel(_game.getScore());
        
        _renderer.present();
    }
}