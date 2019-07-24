#include "game.hpp"
#include <random>
#include <algorithm>

Game::Game(): _width(0), _height(0), _totalMineCount(0), _currentScore(0)
{
}

void Game::init(int width, int height)
{
    _width = width;
    _height = height;
    
    _initializeField();
}

Game::~Game()
{
    if (_gameField != nullptr)
    {
        delete[] _gameField;
        _gameField = nullptr;
    }
}

void Game::_initializeField()
{
    _gameField = new GameCell[_width * _height];
    std::random_device dev;
    std::mt19937 rng(dev());
    
    std::uniform_real_distribution<> dist(0.0f, 1.0f);
    
    std::vector<vec2> nonMinePositions;
    
    // Initialize mines
    for (auto x = 0; x < _width; ++x)
    {
        for (auto y = 0; y < _height; ++y)
        {
            float random = dist(rng);
            
            if (random > 0.9f)
            {
                _totalMineCount++;
                _gameField[y * _width + x]._data |= MASK_FIELD_HAS_MINE;
            }
            else
            {
                nonMinePositions.push_back({x, y});
            }
        }
    }
    
    // calculate neighbour mine count
    // for each cell without mine
    for (const auto nonMine: nonMinePositions)
    {
        _calculateNeighbourMines(nonMine.x, nonMine.y);
    }
}

void Game::_calculateNeighbourMines(const int x, const int y)
{
    int cellNeighbourMineCount = 0;
    
#define INC_NEIGHBOUR_CELL(_x, _y) if (_x >= 0 && _y >= 0 && _x <= _width && _y <= _height) \
    { \
        cellNeighbourMineCount += getGameCell(_x, _y).hasMine() ? 1 : 0; \
    }
    
    INC_NEIGHBOUR_CELL(x - 1, y);
    INC_NEIGHBOUR_CELL(x + 1, y);
    INC_NEIGHBOUR_CELL(x, y - 1);
    INC_NEIGHBOUR_CELL(x, y + 1);
    INC_NEIGHBOUR_CELL(x - 1, y - 1);
    INC_NEIGHBOUR_CELL(x - 1, y + 1);
    INC_NEIGHBOUR_CELL(x + 1, y - 1);
    INC_NEIGHBOUR_CELL(x + 1, y + 1);
    
    _gameField[y * _width + x]._neighbourMineCount = cellNeighbourMineCount;
}

int Game::getWidth() const
{
    return _width;
}

int Game::getHeight() const
{
    return _height;
}

GameCell Game::getGameCell(int x, int y) const
{
    return _gameField[y * _width + x];
}

bool Game::openGameCell(int x, int y, bool isNeighbour, std::vector<int>& trackedCells)
{
    int index = y * _width + x;
    
    if (index < 0 || index > (_width * _height))
    {
        return true;
    }
    
    // stop recursion if necessary
    if (isNeighbour)
    {
        auto it = std::find(trackedCells.begin(), trackedCells.end(), index);
        
        // neighbour cell was already processed
        if (it != trackedCells.end())
        {
            return true;
        }
        
        trackedCells.push_back(index);
    }
    
    if (_gameField[index].isOpen())
    {
        return true;
    }
    
    bool ret = _gameField[index].hasMine();
    
    if (ret)
    {
        if (!isNeighbour)
        {
            _gameOver();
            return false;
        }
    }
    else
    {
        _gameField[index]._data |= MASK_FIELD_IS_OPEN;
        _currentScore++;
    }
    
    ret = false;
    
    if (_gameField[index]._neighbourMineCount == 0)
    {
        ret |= openGameCell(x - 1, y, true, trackedCells);
        ret |= openGameCell(x + 1, y, true, trackedCells);
        ret |= openGameCell(x, y - 1, true, trackedCells);
        ret |= openGameCell(x, y + 1, true, trackedCells);
        ret |= openGameCell(x - 1, y - 1, true, trackedCells);
        ret |= openGameCell(x - 1, y + 1, true, trackedCells);
        ret |= openGameCell(x + 1, y - 1, true, trackedCells);
        ret |= openGameCell(x + 1, y + 1, true, trackedCells);
    }
    
    return ret;
}

/*
Uncover all fields
*/
void Game::_gameOver()
{
    for (unsigned int index = 0; index < _width * _height; ++index)
    {
        if (!_gameField[index].isOpen())
        {
            _gameField[index]._data |= MASK_FIELD_IS_OPEN;
        }
    }
}

int Game::getScore() const
{
    return _currentScore;
}