#ifndef GUI_HPP
#define GUI_HPP

#include "renderer.hpp"

class GUI
{
    private:
    Renderer* _renderer;
    int _screenWidth;
    int _screenHeight;
    
    constexpr static const int PANEL_HEIGHT = 4;
    
    public:
    GUI();
    GUI(const GUI& gui) = delete;
    GUI(GUI&& gui) = delete;
    
    virtual ~GUI();
    
    void init(Renderer& renderer, int screenWidth, int screenHeight);
    
    int getScoresPanelHeight() const;
    void drawScoresPanel(int score) const;
};

#endif