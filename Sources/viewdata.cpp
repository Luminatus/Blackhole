#include "Headers/viewdata.h"

int ViewData::GetTileState(int posX, int posY)
{
    return _gameSessionModel->GetTileState(posX,posY);
}

TileState GetTileState(int posX, int posY);
ViewData::ViewData(GameSessionModel *model) : _gameSessionModel(model), tableSize(model->GetTableSize()){}
