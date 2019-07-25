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
    
    if (_font != nullptr)
    {
        FC_FreeFont(_font);
        _font = nullptr;
    }
    
    if (_renderer != nullptr)
    {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    
    if (_window != nullptr)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
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
    
    _window = SDL_CreateWindow("RetroSweeper",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    
    if (_renderer == nullptr)
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
    
    _font = FC_CreateFont();
    FC_LoadFont(_font,
                _renderer,
                "early_gameboy.ttf",
                16,
                FC_MakeColor(139, 149, 109, 255),
                TTF_STYLE_NORMAL);
    
    if (_font == nullptr)
    {
        return false;
    }
    
    return true;
}

bool Renderer::_loadTiles()
{
    SDL_Surface* img = IMG_Load("tiles.png");
    
    if (img == nullptr)
    {
        return false;
    }
    
    _tiles = SDL_CreateTextureFromSurface(_renderer, img);
    
    if (_tiles == nullptr)
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

void Renderer::drawTile(int x,
                        int y,
                        int width,
                        int height,
                        TILE tile) const
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


void Renderer::drawText(int x,
                        int y,
                        const std::string& text) const
{
    FC_Draw(_font, _renderer, x, y, text.c_str());
}


void Renderer::present() const
{
    SDL_RenderPresent(_renderer);
}