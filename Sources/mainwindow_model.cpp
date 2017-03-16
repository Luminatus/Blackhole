#include "Headers/mainwindow_model.h"
#include "Headers/datastructures.h"

MainWindowModel::MainWindowModel()
{

}

MainWindowModel::~MainWindowModel()
{
    if(_gameSessionModel != NULL)
    {
        delete _gameSessionModel;
    }
}


void MainWindowModel::InitGame(int n)
{
    bool ret = true;
    switch(n)
    {
    case Five : case Seven : case Nine: ret &= _InitializeGameSession(n); break;
    default: ret = false;
    }
    if(!ret) emit InitFailed();
    else emit GameReady(_gameSessionModel);
}

bool MainWindowModel::_InitializeGameSession(int n)
{
    _gameSessionModel = new GameSessionModel(n);
    return true;
}
