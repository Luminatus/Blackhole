#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QWidget>
#include <QPainter>
#include "viewdata.h"
#include <QMouseEvent>

class TableView: public QWidget
{
    Q_OBJECT
public:
    TableView(QWidget* parent=0);
    ~TableView();
    void setViewData(ViewData* viewData);
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent * event);
private:
    ViewData* _viewData;
    QPixmap getArrows();
    void getPixmaps();
    QPixmap* _blue;
    QPixmap* _red;
    QPixmap* _blackhole;
signals:
    void TileClicked(int,int);
};

#endif // TABLEVIEW_H
