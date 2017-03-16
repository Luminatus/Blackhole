#include "Headers/gamesession_model.h"

GameSessionModel::GameSessionModel(int tableSize) :
    _tableSize(tableSize),
    _pointsToWin(tableSize/2),
    _redPoints(0),
    _bluePoints(0),
    _activePlayer(BluePlayer)
{
    //Setting up _gameTable
    for(int i=0; i<_tableSize;i++)
    {
        QVector<GameTile*> column;
        for(int j=0;j<_tableSize;j++)
        {
            GameTile* tile = new GameTile(i,j);
            column.append(tile);
        }
        if(i<_tableSize/2)
        {
            column[i]->State=OccupiedByRed;
            column[_tableSize-1-i]->State=OccupiedByBlue;
        }
        else if(i>_tableSize/2)
        {
            column[i]->State=OccupiedByBlue;
            column[_tableSize-1-i]->State=OccupiedByRed;

        }
        else
        {
            column[i]->State = OccupiedByBlackHole;
        }
        _gameTable.append(column);
    }
}

GameSessionModel::~GameSessionModel()
{
    for(int i=0; i<_tableSize; i++)
    {
        for(int j=0; j<_tableSize; j++)
        {
            delete _gameTable[i][j];
        }
    }
}

int GameSessionModel::GetTableSize()
{
    return _tableSize;
}

int GameSessionModel::GetTileState(int posX, int posY)
{
    if (isValidPosition(posX,posY))
    {
        return _gameTable[posX][posY]->State;
    }
    else return ErrorState;
}

void GameSessionModel::GameStep(int posX, int posY, int direction)
{
    int moveX = direction%2;
    int moveY = (direction-1)%2;
    if(    !(direction>= RightDirection)
        || !(direction<=DownDirection)
        || GetTileState(posX, posY) != _activePlayer
        || !canStep(posX+moveX,posY+moveY)
       )
        {
          GetDirections(posX+moveX,posY+moveY);
          return;
        }
    int i = posX, j = posY;
    bool keepMoving = true;
    while (keepMoving)
    {
        GameTile* currentTile = _gameTable[i][j];
        keepMoving=canStep(i+moveX,j+moveY) && currentTile->State!=OccupiedByBlackHole;
        if(keepMoving)
        {
            GameTile* nextTile = _gameTable[i+moveX][j+moveY];
            nextTile->State= nextTile->State==OccupiedByBlackHole ? OccupiedByBlackHole : currentTile->State;
            currentTile->State = Unoccupied;
            i+=moveX;
            j+=moveY;
        }
    }
    if(_gameTable[i][j]->State == OccupiedByBlackHole)
    {
        switch(_activePlayer)
        {
            case BluePlayer: _bluePoints++;break;
            case RedPlayer:  _redPoints++;break;
        }
    }

    _activePlayer=(_activePlayer+1)%2;
    emit MakeStep(i,j);

}

bool GameSessionModel::IsGameWon()
{
    if(_bluePoints >= _tableSize/2) emit GameWon(BluePlayer);
    else if(_redPoints >= _tableSize/2) emit GameWon(RedPlayer);
    else return false;
    return true;
}

bool GameSessionModel::canStep(int posX, int posY)
{
    int tileState = GetTileState(posX,posY);
    return tileState == Unoccupied || tileState == OccupiedByBlackHole;

}

bool GameSessionModel::isValidPosition(int posX, int posY)
{
    return (posX >=0 && posX < _tableSize && posY>=0 && posY < _tableSize);
}

void GameSessionModel::GetDirections(int posX, int posY)
{
    bool isValid = GetTileState(posX,posY) == _activePlayer;
    if(isValid)
    {
        bool isUp = canStep(posX,posY-1);
        bool isRight = canStep(posX+1,posY);
        bool isDown = canStep(posX,posY+1);
        bool isLeft = canStep(posX-1, posY);
        ActiveTile* tile = new ActiveTile(posX,posY,isUp,isRight,isDown,isLeft);
        emit ActiveTileChanged(tile);
    }
    else
    {
        emit ActiveTileChanged(new ActiveTile());
    }
}

GameTile::GameTile(int PosX, int PosY, int State): PosX(PosX),PosY(PosY),State(State){}

GameStats GameSessionModel::GetGameStats()
{
    return GameStats(_activePlayer,_bluePoints,_redPoints,_tableSize/2);
}
