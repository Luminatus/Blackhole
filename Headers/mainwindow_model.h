#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>
#include "gamesession_model.h"

class MainWindowModel : public QObject
{
    Q_OBJECT
public:
    MainWindowModel();
    ~MainWindowModel();
    void InitGame(int n);

private:
    GameSessionModel* _gameSessionModel;
    bool _InitializeGameSession(int n);

signals:
void InitFailed();
void GameReady(GameSessionModel*);
};

#endif // MAINWINDOWMODEL_H
