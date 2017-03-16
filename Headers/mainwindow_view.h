#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <ui_mainwindow.h>
#include "infopanel.h"
#include "mainwindow_model.h"
#include "datastructures.h"
#include "gamesession_view.h"


class MainWindowView : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowView(QWidget *parent = 0);

private:
    Ui::MainWindow* ui;
    InfoPanel* infoPanel;
    MainWindowModel* mainWindowModel;
    GameSessionView* gameSessionView;

public slots:
    void newGameButtonClicked();
    void gameInitFailed();
    void initializeGameView(GameSessionModel* gameSession);
    void returnToMain();
    void exitGame();
};

#endif // MAINWINDOW_H
