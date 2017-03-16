#include "Headers/mainwindow_view.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindowView::MainWindowView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    mainWindowModel(new MainWindowModel)
{
    ui->setupUi(this);
    ui->SizePicker->addItem("5x5");
    ui->SizePicker->addItem("7x7");
    ui->SizePicker->addItem("9x9");
    ui->SizePicker->setFocus();

    infoPanel = new InfoPanel();
    connect(ui->quitButton,SIGNAL(clicked()),QApplication::instance(),SLOT(quit()));
    connect(ui->InfoButton,SIGNAL(clicked()),infoPanel,SLOT(show()));
    connect(ui->NewGameButton,SIGNAL(clicked()),this,SLOT(newGameButtonClicked()));
}

void MainWindowView::exitGame()
{
    delete ui;
    delete infoPanel;
    delete mainWindowModel;
    QApplication::instance()->quit();
}

void MainWindowView::newGameButtonClicked()
{

    connect(mainWindowModel,SIGNAL(InitFailed()),this,SLOT(gameInitFailed()));
    connect(mainWindowModel,SIGNAL(GameReady(GameSessionModel*)),this,SLOT(initializeGameView(GameSessionModel*)));
    int index = ui->SizePicker->currentIndex();
    ui->NewGameButton->setEnabled(false);
    ui->NewGameButton->setStyleSheet(ui->NewGameButton->styleSheet());

    switch(index)
    {
     case 0 : mainWindowModel->InitGame(Five); break;
     case 1 : mainWindowModel->InitGame(Seven); break;
     case 2 : mainWindowModel->InitGame(Nine); break;
    }
}

void MainWindowView::gameInitFailed()
{
    QMessageBox* message = new QMessageBox;
    message->setText("Init failed!");
    message->show();
    ui->NewGameButton->setEnabled(true);
    ui->NewGameButton->setStyleSheet(ui->NewGameButton->styleSheet());
    disconnect(mainWindowModel,SIGNAL(InitFailed()),this,SLOT(gameInitFailed()));
    disconnect(mainWindowModel,SIGNAL(GameReady(GameSessionModel*)),this,SLOT(initializeGameView(GameSessionModel*)));
}

void MainWindowView::initializeGameView(GameSessionModel* gameSession)
{
    disconnect(mainWindowModel,SIGNAL(InitFailed()),this,SLOT(gameInitFailed()));
    disconnect(mainWindowModel,SIGNAL(GameReady(GameSessionModel*)),this,SLOT(initializeGameView(GameSessionModel*)));
    gameSessionView=new GameSessionView(this,gameSession);
    connect(gameSessionView,SIGNAL(destroyed()),this,SLOT(returnToMain()));
    close();
}

void MainWindowView::returnToMain()
{
    disconnect(gameSessionView,SIGNAL(destroyed()),this,SLOT(returnToMain()));
    ui->NewGameButton->setEnabled(true);
    ui->NewGameButton->setStyleSheet(ui->NewGameButton->styleSheet());
    ui->SizePicker->setCurrentIndex(0);
    ui->SizePicker->setFocus();
    show();
}
