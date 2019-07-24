#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <string>

class Renderer
{
    private:
    uint8_t _width;
    uint8_t _height;
    
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Texture* _tiles;
    
    bool _loadTiles();
    
    public:
    constexpr static unsigned int TILE_SIZE = 16;
    
    enum TILE: int
    {
        CLOSED = 0,
        OPEN = 1,
        MINE = 2,
        TOP_LEFT = 3,
        TOP_RIGHT = 4,
        BOTTOM_LEFT = 5,
        BOTTOM_RIGHT = 6,
        LEFT = 7,
        RIGHT = 8,
        TOP = 9,
        BOTTOM = 10,
        EMPTY = 11
    };
    
    Renderer();
    Renderer(const Renderer& renderer) = delete;
    Renderer(Renderer&& renderer) = delete;
    
    virtual ~Renderer();
    
    bool init(unsigned int width, unsigned int height);
    
    void clear() const;
    
    void drawTile(int x, int y, int width, int height, TILE tile);
    void drawSolidRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;
    void drawFilledRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
                             int r = 255,
                             int g = 255,
                             int b = 255,
                             int a = 255) const;
    
    //void drawText(SDL_Font* font, SDL_Rect dst, const std::string& text);
    void present() const;
};

#endif