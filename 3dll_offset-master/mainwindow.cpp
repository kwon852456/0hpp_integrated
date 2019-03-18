#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "3dll_usb_offset01stt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sWorker = new SerialWorker;
    sThread = new qt::thr::t;

    sWorker->moveToThread(sThread);

    connect(this, &MainWindow::readOffset, sWorker,&SerialWorker::onReadOffset, Qt::QueuedConnection);
    connect(this, &MainWindow::saveOffset, sWorker,&SerialWorker::onSaveOffset, Qt::QueuedConnection);

    sThread->start();
}

MainWindow::~MainWindow()
{

    delete ui;

    sThread->quit();
    sThread->wait();

}





SerialWorker::SerialWorker(QObject *parent){

    srl = CreateSrl(this,8);

}

SerialWorker::~SerialWorker(){

    srl->close();

}


void SerialWorker::onReadOffset(){

    offset =  pai3_srl(srl);

    if(offset != nullptr){

        qDebug() << "offset Read result :" << endl;
        con_pai3(offset);

    }else{

        qDebug() << "Serial read failed" << endl;

    }
}

void SerialWorker::onSaveOffset(){
    save_pai3(offset, 6);
    qDebug() << "save finished.." << endl;
}



void MainWindow::on_btn_read_clicked()
{
    emit readOffset();
}

void MainWindow::on_btn_save_clicked()
{
    emit saveOffset();
}

void MainWindow::on_btn_load_clicked()
{
    if(load_pai3(sWorker->offset, 6)){

        qDebug() << "offset load result : ";

        con_pai3(sWorker->offset);

    }else{ qDebug() <<"file load failed"; };

}

