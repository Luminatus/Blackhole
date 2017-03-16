#include "Headers/infopanel.h"
#include "ui_infopanel.h"

InfoPanel::InfoPanel(QWidget *parent): QWidget(parent), ui(new Ui::InfoPanel)
{
    ui->setupUi(this);
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(close()));
}
