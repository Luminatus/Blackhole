#include "Headers/tableview.h"

TableView::TableView(QWidget* parent): QWidget(parent)
{
}


void TableView:: setViewData(ViewData* viewData)
{
   _viewData = viewData;
    int tableSize = _viewData->tableSize;
    int tileSize = _viewData->tileSize;
   setMinimumSize(tableSize*tileSize+10,tableSize*tileSize+10);
   setBaseSize(tableSize*tileSize,tableSize*tileSize);
   getPixmaps();
}


void TableView::paintEvent(QPaintEvent*)
{
    int tableSize = _viewData->tableSize;
    int tileSize = _viewData->tileSize;
    setMinimumSize(tableSize*tileSize,tableSize*tileSize);
    setBaseSize(tableSize*tileSize,tableSize*tileSize);
    QPixmap* activePixmap;
    QPainter painter(this);
    QPen tilePen;
    tilePen.setWidth(1);
    tilePen.setColor(QColor(30,40,40));
    painter.setPen(tilePen);
    QColor bgColor;
    QColor activeColor;
    activeColor.setRgb(50,60,85);
    QBrush normalBrush;
    normalBrush.setStyle(Qt::SolidPattern);
    normalBrush.setColor(Qt::transparent);
    QBrush activeBrush;
    activeBrush.setColor(activeColor);
    activeBrush.setStyle(Qt::SolidPattern);
    bgColor.setRgb(40,50,60);
    painter.fillRect(0,0,tableSize*tileSize,tableSize*tileSize,bgColor);
    for (int i=0; i<tableSize; i++)
    {
        for (int j=0; j<tableSize; j++)
        {
            int tileIndex = _viewData->GetTileState(i,j);
            if(_viewData->showActive || i!=_viewData->activeTile->PosX || j!=_viewData->activeTile->PosY || tileIndex==OccupiedByBlackHole)
            {
                switch(tileIndex)
                {
                case OccupiedByBlue: normalBrush.setColor(Qt::transparent); activePixmap=_blue; break;
                case OccupiedByRed: normalBrush.setColor(Qt::transparent); activePixmap=_red; break;
                case OccupiedByBlackHole: normalBrush.setColor(Qt::transparent); activePixmap=_blackhole; break;
                case Unoccupied: normalBrush.setColor(Qt::transparent); activePixmap=NULL; break;
                default: break;
                }
                if(i==_viewData->activeTile->PosX && j==_viewData->activeTile->PosY && tileIndex!=OccupiedByBlackHole)
                    painter.setBrush(activeBrush);
                else
                    painter.setBrush(normalBrush);
            }
            else
            {
                normalBrush.setColor(Qt::transparent);
                painter.setBrush(normalBrush);
                activePixmap=NULL;
            }

            painter.drawRect(i*tileSize,j*tileSize,tileSize,tileSize);
            if(activePixmap!=NULL)
                painter.drawPixmap(i*tileSize,j*tileSize,tileSize,tileSize,*activePixmap);

        }
    }
    if(_viewData->showActive){
    QPixmap pixmap= getArrows();
    painter.setBrush(Qt::NoBrush);
    painter.drawPixmap(_viewData->activeTile->PosX*tileSize-tileSize,_viewData->activeTile->PosY*tileSize-tileSize,tileSize*3,tileSize*3,pixmap);
    }
    else
    {
        switch(_viewData->activePlayer)
        {
            case BluePlayer: activePixmap=_blue; break;
            case RedPlayer: activePixmap=_red; break;
            default: painter.setBrush(Qt::NoBrush); break;
        }
        //painter.drawRect(_viewData->goX,_viewData->goY,tileSize,tileSize);
        painter.drawPixmap(_viewData->goX,_viewData->goY,tileSize,tileSize,*activePixmap);
    }

}

    QPixmap TableView::getArrows()
    {
        int tileSize = _viewData->tileSize;
        QVector<QPoint> trianglevector;
        QPoint pointA(-tileSize/4,tileSize*0.6);
        QPoint pointB(tileSize/4,tileSize*0.6);
        QPoint pointC(0,tileSize*0.9);
        trianglevector.append(pointA);
        trianglevector.append(pointB);
        trianglevector.append(pointC);
        QPolygon triangle(trianglevector);

        QPixmap pixmap(tileSize*3,tileSize*3);
        pixmap.fill(Qt::NoBrush);
        pixmap.fill(Qt::transparent);
        QPainter trianglePainter(&pixmap);
        trianglePainter.setPen(Qt::darkGray);
        trianglePainter.setBrush(Qt::lightGray);
        int translateSize = tileSize*1.5;
        trianglePainter.translate(translateSize,translateSize);
        ActiveTile* activeTile = _viewData->activeTile;
        if(activeTile->Down) trianglePainter.drawPolygon(triangle);
        trianglePainter.rotate(90);
        if(activeTile->Left) trianglePainter.drawPolygon(triangle);
        trianglePainter.rotate(90);
        if(activeTile->Up) trianglePainter.drawPolygon(triangle);
        trianglePainter.rotate(90);
        if(activeTile->Right) trianglePainter.drawPolygon(triangle);
        trianglePainter.resetTransform();
        return pixmap;
        }

void TableView::getPixmaps()
{
    int tileSize = _viewData->tileSize;
    QPixmap* blueShip=new QPixmap(tileSize,tileSize);
    QPixmap* redShip=new QPixmap(tileSize,tileSize);
    QPixmap* blackhole = new QPixmap(tileSize,tileSize);
    if(!(blueShip->load(":/pixmaps/blueship.png")))
        blueShip->fill(Qt::blue);
    if(!(redShip->load(":/pixmaps/redship.png")))
        redShip->fill(Qt::red);
    if(!(blackhole->load(":/pixmaps/blackhole.png")))
        redShip->fill(Qt::red);
    _blue = blueShip;
    _red = redShip;
    _blackhole = blackhole;
}


void TableView::mousePressEvent(QMouseEvent* event)
{
    int posX = event->x() / _viewData->tileSize;
    int posY = event->y() / _viewData->tileSize;
    emit TileClicked(posX,posY);
}

TableView::~TableView()
{
    delete _red;
    delete _blue;
    delete _blackhole;
}
