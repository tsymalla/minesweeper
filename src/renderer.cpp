#include "renderer.hpp"
#include <iostream>

#define PRINT_SDL_ERROR std::cerr << SDL_GetError() << std::endl;

#define PRINT_IMG_ERROR std::cerr << IMG_GetError() << std::endl;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    if (_tiles != nullptr)
    {
        SDL_DestroyTexture(_tiles);
        _tiles = nullptr;
    }
    
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
    
    SDL_DestroyWindow(_window);
    _window = nullptr;
}

bool Renderer::init(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        PRINT_SDL_ERROR;
        return false;
    }
    
    _window = SDL_CreateWindow("Minesweeper",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!_renderer)
    {
        PRINT_SDL_ERROR;
        return false;
    }
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        PRINT_IMG_ERROR;
        return false;
    }
    
    if (!_loadTiles())
    {
        PRINT_IMG_ERROR;
        return false;
    }
    
    return true;
}

bool Renderer::_loadTiles()
{
    SDL_Surface* img = IMG_Load("tiles.png");
    
    if (!img)
    {
        return false;
    }
    
    _tiles = SDL_CreateTextureFromSurface(_renderer, img);
    
    if (!_tiles)
    {
        return false;
    }
    
    SDL_FreeSurface(img);
    
    return true;
}

void Renderer::clear() const
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
}

void Renderer::drawTile(int x, int y, int width, int height, TILE tile)
{
    SDL_Rect src = {tile * TILE_SIZE, 0, 16, 16};
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(_renderer, _tiles,  &src, &dst);
}

void Renderer::drawSolidRectangle(int x,
                                  int y,
                                  int width,
                                  int height) const
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(_renderer, &rect);
}

void Renderer::drawFilledRectangle(int x,
                                   int y,
                                   int width,
                                   int height,
                                   int r,
                                   int g,
                                   int b,
                                   int a) const
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(_renderer, &rect);
}

/*
void Renderer::drawText(SDL_Font* font, SDL_Rect dst,
                        const std::string& text)
{
}
*/

void Renderer::present() const
{
    SDL_RenderPresent(_renderer);
}