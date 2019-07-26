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
    _screenWidth = width * CELL_WIDTH;
    _screenHeight = height * CELL_HEIGHT;
    
    _gui.init(_renderer, _screenWidth, _screenHeight);
    
    if (!_renderer.init(_screenWidth, _gui.getScoresPanelHeight() + _screenHeight))
    {
        return false;
    }
    
    _game.init(width, height);
    _isRunning = true;
    _currentState = GAMESTATE::GAME;
    
    return true;
}

void Minesweeper::_restart()
{
    _game.restart();
    _currentState = GAMESTATE::GAME;
}

void Minesweeper::run()
{
    int mouseX = 0, mouseY = 0;
    
    while (_isRunning)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                _isRunning = false;
            }
            
            if (_currentState == GAMESTATE::GAME)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    
					if (mouseY > _gui.getScoresPanelHeight())
					{
						int tileX = mouseX / CELL_WIDTH;
						int tileY = ((mouseY - _gui.getScoresPanelHeight()) / CELL_HEIGHT);

						std::vector<int> trackedCells;
						bool hasMine = _game.openGameCell(tileX, tileY, false, trackedCells);
                    
						if (hasMine)
						{
							// game over
							_currentState = GAMESTATE::GAMEOVER;
						}
					}
                }
            }
            
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    _isRunning = false;
                }
                else if (_currentState == GAMESTATE::GAMEOVER &&
                         e.key.keysym.sym == SDLK_RETURN)
                {
                    _restart();
                }
            }
        }
        
        _renderer.clear();
        
        _drawGameField();
        
        if (_currentState == GAMESTATE::GAMEOVER)
        {
            _drawGameOver();
        }
        
        _renderer.present();
    }
}

void Minesweeper::_drawGameField()
{
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
}

void Minesweeper::_drawGameOver()
{
    _renderer.drawFilledRectangle((_screenWidth / 4) - 20,
                                  (_screenHeight / 4) - 20,
                                  (_screenWidth / 2) + 64,
                                  80,
                                  196,
                                  207,
                                  161);
    
    _renderer.drawText(_screenWidth / 4,
                       _screenHeight / 4,
                       "You lost.");
    
    _renderer.drawText(_screenWidth / 4,
                       (_screenHeight / 4) + 20,"Press RETURN to retry.");
}