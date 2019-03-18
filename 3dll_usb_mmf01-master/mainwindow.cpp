#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "3dll_usb_mmf01stt.h"

i::t timer_interval = 333;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    sWorker = new SerialWorker;
    sThread = new qt::thr::t;
    mmfTimer = new QTimer(this);

    mmfTimer->setInterval(timer_interval);

    sWorker->moveToThread(sThread);


    connect(this, &MainWindow::mmf_status,           sWorker,&SerialWorker:: onMmfCheck_clicked, Qt::QueuedConnection);
    connect(mmfTimer, &QTimer::timeout,              this,   &MainWindow::   on_btn_mmf_clicked);
    connect(this, &MainWindow::change_offset_sign,   sWorker,&SerialWorker:: change_sign);
    connect(this, &MainWindow::temp_offset,          sWorker,&SerialWorker:: temp_offset);

    sThread->start();


}

MainWindow::~MainWindow()
{
    delete ui;

    sThread->quit();
    sThread->wait();

}

void MainWindow::on_btn_mmf_clicked()
{
    if(sWorker->isSrlFinished){
        emit mmf_status();
    }
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

SerialWorker::SerialWorker(QObject *parent){

    setIds();
    srl = CreateSrl(this,4);

}

SerialWorker::~SerialWorker(){

    srl->close();

}

void SerialWorker::setIds(){
    i::t id[18] = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43, 51, 52, 53, 61, 62, 63 };
    for(i::t i : id){ ids.push_back(i); }
}

void SerialWorker::onMmfCheck_clicked(){
        isSrlFinished = !isSrlFinished;

        if(srl->isOpen()){
            mmf_srl(srl, ids, offset);
        }else{
            qDebug() << "Serial not opened...!" << endl;
        }

        isSrlFinished = !isSrlFinished;

}


void SerialWorker::change_sign(){
    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            offset[i][j] = -offset[i][j];
        }
    }

    qDebug() << "sign changed..!" << endl;
    con_pai3(offset);
}


void SerialWorker::temp_offset(int _stat){


    if(_stat != 0){
        memcpy(offsetTemp, offset, 18 * 4);
        memset(offset, 0x00, 18 * 4);
        qDebug() << "offset won't be applied";

        con_pai3(offset);

    }else{
        memcpy(offset, offsetTemp, 18 * 4);
        memset(offsetTemp, 0x00, 18 * 4);
        qDebug() << "offset will be applied";

        con_pai3(offset);

    }



}



void MainWindow::on_timer_readEnc_stateChanged(int arg1)
{

    if(ui->timer_readEnc->isChecked()){
        mmfTimer->start();

    }else{

        mmfTimer->stop();
    }

    UNUSED(arg1);
}

void MainWindow::on_tbr_delay_valueChanged(int value)
{
    ui->edit_delay->setText(qt::s_i(value));
    mmfTimer->setInterval(value);
}

void MainWindow::on_btn_load_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());

    if(path == qt::s::T0){ return; }

    QFile file(path, this);
    file.open(QIODevice::ReadWrite);
    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');


    for (z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            sWorker->offset[i][j] = i_s(vs.at( (i * 3) + j ));
        }
    }

    qDebug() << "offset loaded..!";

    con_pai3(sWorker->offset);
}

void MainWindow::on_cb_offset_toggled(bool checked)
{
    emit change_offset_sign();
}

void MainWindow::on_cb_releaseOffset_stateChanged(int arg1)
{
    qDebug() << arg1 << endl;
    emit temp_offset(arg1);
}
