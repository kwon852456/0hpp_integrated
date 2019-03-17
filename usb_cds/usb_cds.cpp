#include "usb_cds.hpp"
#include "ui_usb_cds.h"

Usb_cds::Usb_cds(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usb_cds)
{
    ui->setupUi(this);
}

Usb_cds::~Usb_cds()
{
    delete ui;
}
