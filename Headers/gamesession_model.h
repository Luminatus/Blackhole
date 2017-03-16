#ifndef GAMESESSIONMODEL_H
#define GAMESESSIONMODEL_H
#include <QObject>
#include <QVector>
#include "datastructures.h"

struct GameTile
{
    const int PosX;
    const int PosY;
    int State;

    GameTile(int PosX, int PosY, int State=Unoccupied);
};

class GameSessionModel : public QObject
{
    Q_OBJECT
public:
    GameSessionModel(int tableSize);
    ~GameSessionModel();
    int GetTileState(int posX, int posY);
    int GetTableSize();
    void GameStep(int posX, int posY, int direction);
    void GetDirections(int posX, int posY);
    bool IsGameWon();
    GameStats GetGameStats();

private:
    QVector<QVector<GameTile*> > _gameTable;
    const int _tableSize;
    const int _pointsToWin;
    int _redPoints;
    int _bluePoints;
    int _activePlayer;
    bool isValidPosition(int posX, int posY);
    bool canStep(int posX, int posY);

signals:
    void GameWon(int);
    void MakeStep(int, int);
    void ActiveTileChanged(ActiveTile*);

};

#endif // GAMESESSIONMODEL_H
