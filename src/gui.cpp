#include "gui.hpp"

GUI::GUI()
{
}

void GUI::init(Renderer& renderer, int screenWidth, int screenHeight)
{
    _renderer = &renderer;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
}

GUI::~GUI()
{
    _renderer = nullptr;
}

int GUI::getScoresPanelHeight() const
{
    return PANEL_HEIGHT * Renderer::TILE_SIZE;
}

void GUI::drawScoresPanel(int score) const
{
    int sizeX = (_screenWidth / Renderer::TILE_SIZE) - 2;
    int sizeY = (_screenHeight / Renderer::TILE_SIZE) - 2;
    
    int x = 0, y = 0;
    
    int rightX = _screenWidth - Renderer::TILE_SIZE;
    int bottomY = (PANEL_HEIGHT * Renderer::TILE_SIZE);
    
    _renderer->drawTile(x, y, Renderer::TILE_SIZE,
                        Renderer::TILE_SIZE,
                        Renderer::TILE::TOP_LEFT);
    _renderer->drawTile(rightX, y, Renderer::TILE_SIZE,
                        Renderer::TILE_SIZE,
                        Renderer::TILE::TOP_RIGHT);
    _renderer->drawTile(x, bottomY, Renderer::TILE_SIZE,
                        Renderer::TILE_SIZE,
                        Renderer::TILE::BOTTOM_LEFT);
    _renderer->drawTile(rightX, bottomY, Renderer::TILE_SIZE,
                        Renderer::TILE_SIZE,
                        Renderer::TILE::BOTTOM_RIGHT);
    
    for (auto xPos = 1; xPos <= sizeX; ++xPos)
    {
        _renderer->drawTile(xPos * Renderer::TILE_SIZE, 0, Renderer::TILE_SIZE,
                            Renderer::TILE_SIZE,
                            Renderer::TILE::TOP);
        _renderer->drawTile(xPos * Renderer::TILE_SIZE, bottomY,
                            Renderer::TILE_SIZE, Renderer::TILE_SIZE, Renderer::TILE::BOTTOM);
    }
    
    for (auto yPos = 1; yPos < PANEL_HEIGHT; ++yPos)
    {
        _renderer->drawTile(0, yPos * Renderer::TILE_SIZE, Renderer::TILE_SIZE,
                            Renderer::TILE_SIZE,
                            Renderer::TILE::LEFT);
        _renderer->drawTile(rightX,
                            yPos * Renderer::TILE_SIZE,
                            Renderer::TILE_SIZE,
                            Renderer::TILE_SIZE,
                            Renderer::TILE::RIGHT);
    }
    
    for (auto xPos = 1; xPos <= sizeX; ++xPos)
    {
        for (auto yPos = 1; yPos < PANEL_HEIGHT; ++yPos)
        {
            _renderer->drawTile(xPos * Renderer::TILE_SIZE, yPos * Renderer::TILE_SIZE,
                                Renderer::TILE_SIZE,
                                Renderer::TILE_SIZE,
                                Renderer::TILE::EMPTY);
        }
    }
    
    _renderer->drawText(0 + Renderer::TILE_SIZE,
                        (bottomY / 2), "RetroSweeper");
    
    _renderer->drawText((rightX / 2) + (2 * Renderer::TILE_SIZE),
                        (bottomY / 2), "Score: " + std::to_string(score));
}