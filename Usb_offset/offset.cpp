#include "offset.hpp"
#include "ui_offset.h"
#include <QDebug>

Offset::Offset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Offset)
{
    ui->setupUi(this);
}

Offset::~Offset()
{
    delete ui;
}
void Offset::on_btn_read_clicked()
{
    qDebug() << __func__;
    emit readOffset();
}

void Offset::on_btn_save_clicked()
{
    qDebug() << __func__;
    emit saveOffset();
}

void Offset::on_btn_load_clicked()
{
    qDebug() << __func__;
    emit loadOffset();
}
