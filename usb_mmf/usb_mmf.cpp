#include "usb_mmf.hpp"
#include "ui_usb_mmf.h"
#include "6qtu9.hpp"

using namespace rv2;

i::t timer_interval = 333;

Usb_mmf::Usb_mmf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usb_mmf)
{
    ui->setupUi(this);
     mmfTimer = new QTimer(this);

     mmfTimer->setInterval(timer_interval);
     connect(mmfTimer, &QTimer::timeout,              this,   &Usb_mmf::   on_btn_mmf_clicked);

}


Usb_mmf::~Usb_mmf()
{
    delete ui;
}

void Usb_mmf::on_timer_readEnc_stateChanged(int arg1)
{

    if(ui->timer_readEnc->isChecked()){
        mmfTimer->start();

    }else{

        mmfTimer->stop();
    }

    UNUSED(arg1);
}


void Usb_mmf::on_tbr_delay_valueChanged(int value)
{
    ui->edit_delay->setText(qt::s_i(value));
    mmfTimer->setInterval(value);
}

void Usb_mmf::on_btn_mmf_clicked()
{
    qDebug() << __func__ << endl;
    emit mmfClicked();
}
