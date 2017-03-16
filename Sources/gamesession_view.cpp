#include "Headers/gamesession_view.h"
#include <QPainter>
#include <QPaintEngine>
#include <QPaintEvent>
#include <QMessageBox>
#include <QTimer>

GameSessionView::GameSessionView(QWidget* mainWindowView, GameSessionModel* gameSessionModel):
    _mainWindowView(mainWindowView),
    _gameSessionModel(gameSessionModel),
    ui(new Ui::GameSessionUI)
{
    GameStats stats = _gameSessionModel->GetGameStats();
    _viewData = new ViewData(_gameSessionModel);
    _viewData->tileSize = 60;
    _viewData->showActive = true;
    _activeTile = new ActiveTile();
    _viewData->activeTile = _activeTile;
    _viewData->activePlayer = stats.ActivePlayer;
    _inactiveFont = new QFont("Arial",10,0,false);
    _activeFont = new QFont("Arial",11,QFont::Bold,true);

    ui->setupUi(this);
    ui->gameTable->setViewData(_viewData);
    ui->BluePlayerLabel->setFont(*_activeFont);
    ui->RedPlayerLabel->setFont(*_inactiveFont);
    setMinimumSize(ui->gameTable->width()+10,ui->gameTable->height()+160);
    setMaximumSize(ui->gameTable->width()+10,ui->gameTable->height()+160);
    ui->BluePlayerPoints->display(stats.BluePoints);
    ui->RedPlayerPoints->display(stats.RedPoints);
    ui->PointsToWin->setText(QString::number(stats.PointsToWin));

    _timer = new QTimer(this);
    _timer->setInterval(20);
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(backToMainMenu()));
    connect(ui->gameTable,SIGNAL(TileClicked(int,int)),this,SLOT(processClick(int,int)));
    connect(_gameSessionModel,SIGNAL(GameWon(int)),this,SLOT(gameWon(int)));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
show();
}

GameSessionView::~GameSessionView()
{
    disconnect(ui->closeButton,SIGNAL(clicked()),this,SLOT(backToMainMenu()));
    disconnect(ui->gameTable,SIGNAL(TileClicked(int,int)),this,SLOT(processClick(int,int)));
    disconnect(_gameSessionModel,SIGNAL(GameWon(int)),this,SLOT(gameWon(int)));

    delete _timer;
    delete _activeTile;
    delete _activeFont;
    delete _inactiveFont;
    delete _viewData;
    delete _gameSessionModel;
    delete ui;
}


void GameSessionView::backToMainMenu()
{
    close();
    delete this;
}

void GameSessionView::processClick(int posX, int posY)
{

    ui->gameTable->setEnabled(false);
    bool isGameStep=false;
    int stepDirection;
    if(_activeTile->PosX !=-1)
    {
        if(posX == _activeTile->PosX)
        {
            int diff = posY - _activeTile->PosY;
            switch(diff)
            {
                case 1: isGameStep=true; stepDirection = DownDirection; break;
                case -1:isGameStep=true; stepDirection = UpDirection;  break;
                default: break;
            }
        }
        else if(posY == _activeTile->PosY)
        {
            int diff = posX - _activeTile->PosX;
            switch(diff)
            {
                case 1: isGameStep=true; stepDirection = LeftDirection; break;
                case -1:isGameStep=true; stepDirection = RightDirection;  break;
                default: break;
            }

        }
    }

    if(isGameStep)
    {
        connect(_gameSessionModel,SIGNAL(MakeStep(int,int)),this,SLOT(makeStep(int, int)));
        connect(_gameSessionModel,SIGNAL(ActiveTileChanged(ActiveTile*)),this,SLOT(changeActiveTile(ActiveTile*)));
        _gameSessionModel->GameStep(_activeTile->PosX,_activeTile->PosY,stepDirection);
    }
    else
    {
        connect(_gameSessionModel,SIGNAL(ActiveTileChanged(ActiveTile*)),this,SLOT(changeActiveTile(ActiveTile*)));
        _gameSessionModel->GetDirections(posX, posY);

    }
}


void GameSessionView::changeActiveTile(ActiveTile* tile)
{
    disconnect(_gameSessionModel,SIGNAL(ActiveTileChanged(ActiveTile*)),this,SLOT(changeActiveTile(ActiveTile*)));

    delete _activeTile;
    _activeTile = tile;
    _viewData->activeTile =tile;

    ui->gameTable->setEnabled(true);
    update();

}

void GameSessionView::makeStep(int posX, int posY)
{
    disconnect(_gameSessionModel,SIGNAL(MakeStep(int,int)),this,SLOT(makeStep(int, int)));
    disconnect(_gameSessionModel,SIGNAL(ActiveTileChanged(ActiveTile*)),this,SLOT(changeActiveTile(ActiveTile*)));

    _viewData->showActive=false;
    _viewData->offsetX = _activeTile->PosX<posX ?
                         _viewData->tileSize/10 :
                         _activeTile->PosX>posX ?
                         -_viewData->tileSize/10 :
                         0;
    _viewData->offsetY = _activeTile->PosY<posY ?
                          _viewData->tileSize/10 :
                         _activeTile->PosY>posY ?
                         - _viewData->tileSize/10 :
                         0;

    _viewData->goX = _activeTile->PosX*_viewData->tileSize;
    _viewData->goY = _activeTile->PosY*_viewData->tileSize;

    delete _activeTile;
    _activeTile=new ActiveTile(posX,posY);
    _viewData->activeTile = _activeTile;

    connect(_timer,SIGNAL(timeout()),this,SLOT(moveTile()));
    _timer->start();
}

void GameSessionView::updateWindow()
{
    GameStats stat = _gameSessionModel->GetGameStats();
    ui->BluePlayerPoints->display(stat.BluePoints);
    ui->RedPlayerPoints->display(stat.RedPoints);
    _viewData->activePlayer = stat.ActivePlayer;
    if(stat.ActivePlayer==BluePlayer)
    {
        ui->BluePlayerLabel->setFont(*_activeFont);
        ui->RedPlayerLabel->setFont(*_inactiveFont);
    }
    else
    {
        ui->RedPlayerLabel->setFont(*_activeFont);
        ui->BluePlayerLabel->setFont(*_inactiveFont);

    }
    update();
}

void GameSessionView::gameWon(int player)
{
    updateWindow();
    ui->gameTable->setEnabled(false);
    QMessageBox* message = new QMessageBox();
    QString winnerColour= player==BluePlayer? "kék":"vörös";
    message->setText("A "+winnerColour+" játékos nyert!");
    message->show();
    connect(message,SIGNAL(finished(int)),SLOT(backToMainMenu()));
}

void GameSessionView::moveTile()
{
    if (_viewData->goX == _viewData->activeTile->PosX * _viewData->tileSize
        && _viewData->goY == _viewData->activeTile->PosY * _viewData->tileSize)
       {
        finishRound();
        return;
        }
    _viewData->goX += _viewData->offsetX;
    _viewData->goY += _viewData->offsetY;
    ui->gameTable->update();
}


void GameSessionView::finishRound()
{
disconnect(_timer,SIGNAL(timeout()),this,SLOT(moveTile()));
_viewData->showActive = true;
_timer->stop();
updateWindow();
if(!_gameSessionModel->IsGameWon())
    ui->gameTable->setEnabled(true);

}
