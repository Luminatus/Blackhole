#ifndef INFOPANEL_H
#define INFOPANEL_H
#include <QWidget>
#include "ui_infopanel.h"

class InfoPanel : public QWidget
{
public:
    InfoPanel(QWidget* parent=0);
private:
    Ui::InfoPanel* ui;


};
#endif // INFOPANEL_H
