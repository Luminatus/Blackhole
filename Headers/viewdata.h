#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "datastructures.h"
#include "gamesession_model.h"

struct ViewData
{
    bool showActive;
    ViewData(GameSessionModel* model);
    const int tableSize;
    int tileSize;
    int windowWidth;
    int windowHeight;
    ActiveTile* activeTile;
    int activePlayer;
    int goX;
    int goY;
    int offsetX;
    int offsetY;
    int GetTileState(int posX, int posY);
private:
    GameSessionModel* _gameSessionModel;
};

#endif // VIEWDATA_H
