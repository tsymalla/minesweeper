#ifndef GAME_HPP
#define GAME_HPP

#include <stdint.h>
#include <iostream>
#include <vector>

constexpr static unsigned short MASK_FIELD_HAS_MINE = 0b10;
constexpr static unsigned short MASK_FIELD_IS_OPEN = 0b01;

struct GameCell
{
    unsigned short _data = 0;
    uint8_t _neighbourMineCount = 0;
    
    bool isOpen() const
    {
        return _data & MASK_FIELD_IS_OPEN;
    }
    
    bool hasMine() const
    {
        return _data & MASK_FIELD_HAS_MINE;
    }
};

struct vec2
{
    int x = 0;
    int y = 0;
};

class Game
{
    private:
    int _width;
    int _height;
    int _totalMineCount;
    int _currentScore;
    GameCell* _gameField;
    
    void _initializeField();
    void _calculateNeighbourMines(const int x, const int y);
    void _gameOver();
    
    public:
    Game();
    Game(const Game& rhs) = delete;
    Game(Game&& rhs) = delete;
    
    virtual ~Game();
    
    void init(int width, int height);
    
    int getWidth() const;
    int getHeight() const;
    
    GameCell getGameCell(int x, int y) const;
    bool openGameCell(int x, int y, bool isNeighbour, std::vector<int>& trackedCells);
    int getScore() const;
};

#endif