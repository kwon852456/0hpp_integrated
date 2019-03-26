#include "usb_log.h"
#include "ui_usb_log.h"

Usb_log::Usb_log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usb_log)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000 * 60);
    connect(timer, &QTimer::timeout, this, &Usb_log::clearLog);
}

Usb_log::~Usb_log()
{
    delete ui;
}

void Usb_log::setlog(QString text){

    ui->edit_log->append(text);
}

void Usb_log::clearLog(){

    qDebug() << __func__;

    ui->edit_log->clear();
}

void Usb_log::changeInterval(int _msTime){

    timer->setInterval(_msTime);

}
