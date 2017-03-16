#ifndef GAMESESSION_VIEW_H
#define GAMESESSION_VIEW_H
#include <QWidget>
#include "ui_gamesession.h"
#include "gamesession_model.h"
#include "viewdata.h"

class GameSessionView : public QWidget
{
    Q_OBJECT
public:
    GameSessionView(QWidget* mainWindowView,GameSessionModel* gameSessionModel);
    ~GameSessionView();
private:
    void updateWindow();
    void finishRound();

    QWidget* _mainWindowView;
    GameSessionModel* _gameSessionModel;
    Ui::GameSessionUI* ui;
    ActiveTile* _activeTile;
    ViewData* _viewData;
    QTimer* _timer;
    QFont* _activeFont;
    QFont* _inactiveFont;

public slots:
    void backToMainMenu();
    void processClick(int posX, int posY);
    void changeActiveTile(ActiveTile* tile);
    void makeStep(int posX, int posY);
    void gameWon(int player);
    void moveTile();
};

#endif // GAMESESSION_VIEW_H
