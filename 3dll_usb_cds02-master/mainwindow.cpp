#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "3dll_usb_cds01stt.hpp"


pai3::p OFFSET = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };
pai3::p OFFSETTEMP = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };

QMutex mutForSrl;






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wThread = new QThread();
    sendTimer = new QTimer(this);
    srl_fileTimer = new QTimer(this);


    stl = new Dll_usb_mmf01stl();

    stl->moveToThread(wThread);

    wThread->start();

    connect(this,          &MainWindow::thsrl_cds,    stl,   &Dll_usb_mmf01stl::srl_pai3);
    connect(this,          &MainWindow::send_clicked, stl,   &Dll_usb_mmf01stl::thsri_qai3);
    connect(srl_fileTimer, &QTimer::timeout,         this,   &MainWindow::fileTimerTimeOut);
    connect(sendTimer,     &QTimer::timeout,         this,   &MainWindow::srl_ai3);
    connect(wThread,       &QThread::finished,        stl,   &Dll_usb_mmf01stl::deleteLater);

    qRegisterMetaType<QList<int>>("QList<int>");

    sendTimer->setInterval(1000);
    srl_fileTimer->setInterval(1000);

    init_tbrs();
    init_lv();
}

MainWindow::~MainWindow()
{
    delete ui;

    wThread->quit();
    wThread->wait();
}

b::t MainWindow::init_tbrs(){
    set_tbrs();
    return b::T1;
}

b::t MainWindow::init_lv(){

    for(z::t i(1) ; i < 7 ; ++i){

        ui->lv_legs->addItem(qt::s_i(i));

    }



    return b::T1;
}

b::t addOffset(pai3::p _command){
    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            _command[i][j] -= OFFSET[i][j];
        }
    }

    return b::T1;
}

vo::t MainWindow::fileTimerTimeOut(){

    qDebug() <<" row idx " << ui->lv_commands->currentRow() << endl;

    if(ui->lv_commands->currentRow() != -1){

        if(ui->lv_commands->currentRow() <= idxSizeCommands ){

            pai3::p command = mCommands.find(ui->lv_commands->currentRow()).value();

            addOffset(command);

            emit thsrl_cds(pp_pai3(command));

            ui->lv_commands->setCurrentRow(ui->lv_commands->currentRow() + 1);
        }

    }

}

pai3::p MainWindow::pai_msg(void* _message){

    MSG* msg = reinterpret_cast<MSG*>(_message);

    if((msg)->message == WM_COPYDATA){

        pai3::p pai3 = new i::a3[6]{{0,},{0,},{0,}};

        HWND reciverhwnd = (HWND)msg->wParam;
        PCOPYDATASTRUCT pcds = (PCOPYDATASTRUCT)msg->lParam;
        UNUSED(reciverhwnd);

        y::p yHdr = (y::p) pcds ->lpData;
        pai3_yHdr(pai3, yHdr);

        return pai3;
    }
    return nil;

}



b::t MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *resultMSG) {

    pai3::p command = pai_msg(message);

    if(command != nil){

        addOffset(command);
        emit thsrl_cds(pp_pai3(command));

    }
    else
        delete[] command;

    *resultMSG = 0;

    UNUSED(eventType);

    return b::T0;

}































Dll_usb_mmf01stl::Dll_usb_mmf01stl(QObject *parent){


        sThread = new QThread();
        sWorker = new SerialWorker();
        sWorker->moveToThread(sThread);


        connect(this, &Dll_usb_mmf01stl::write_cmd, sWorker , &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);


        sThread->start();
}

Dll_usb_mmf01stl::~Dll_usb_mmf01stl(){
    sThread->quit();
    sThread->wait();
};



b::t Dll_usb_mmf01stl::srl_i(i::t _iDegree, i::t _id){

    //qDebug() << __func__ << endl;

    cmd::t command;

    cmd_id(command, _iDegree,  _id);
    c::p pCmd = reinterpret_cast<c::p>(command);

    emit write_cmd(pCmd);

    return true;

}


i::t Dll_usb_mmf01stl::i_srl(i::t _id){

    //qDebug() << __func__ << endl;

    req::t request; req_id(request, _id);
    c::p pReq = reinterpret_cast<c::p>(request);

    int recvEncVal;
    QByteArray arr = QByteArray::fromRawData(pReq,req::Z);


    QMetaObject::invokeMethod(sWorker, "onWrite_req", Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, recvEncVal),
                              Q_ARG(QByteArray, arr),
                              Q_ARG(int, _id));


    return recvEncVal;
}


vo::t Dll_usb_mmf01stl::cmd_id(cmd::t cmd_,i::R _iDegree,i::R _id ){

    //qDebug() << __func__ << endl;

    //h::t vel    = (h::t)abs(preset[i][j] - current[i][j]);
    h::t vel    = 32;  //속도 3 rpm 고정
    y::t ccw = ( _iDegree < 0 ? 1 : 0);
    h::t posoff = (h::t) abs(_iDegree);
    y2::u degree2y ,vel2y;

    degree2y.h1    = posoff;
    vel2y.h1       = vel;


    y::t checkSum = ~((y::t)(_id + 0x07 + 0x01 + ccw + degree2y.t2[1] + degree2y.t2[0] + vel2y.t2[1] + vel2y.t2[0]));
    cmd::t command = {0xFF, 0xFE, (y::t)_id, 0x07, checkSum, 0x01, ccw, degree2y.t2[1], degree2y.t2[0], vel2y.t2[1], vel2y.t2[0] };

//    con_11bytes(command);
    for(z::t i(0) ; i < cmd::Z ; ++i){
        cmd_[i] = command[i] ;
    }

}

vo::t Dll_usb_mmf01stl::req_id(req::t req_,i::R _id ){

    y::t checkSum = ~((y::t)((y::t)_id + 0xA1 + 2));

    req_[0] = 0xFF;
    req_[1] = 0xFE;
    req_[2] = (y::t)_id;
    req_[3] = 2;
    req_[4] = checkSum;
    req_[5] = 0xA1;

}

b::t Dll_usb_mmf01stl::thsri_qai3(QList<int> _qai3, i::t _legNo){
    qDebug() << __func__ << endl;

    QFutureSynchronizer<b::t> synchronizer;
    for(z::t i(0) ; i < 3 ; ++i ){

        int id = (_legNo * 10) + (i + 1);

        if(_qai3[i] != -1){

            synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

                while(1){

                    if(  !((_qai3[i] - 100) < i_srl(id) && (_qai3[i] + 100) >  i_srl(id))  ){ qDebug("_ai3[i] != i_srl(id)"); srl_i(_qai3[i], id);}
                    else { break; }

                }
                qDebug() << "id" << id << "_qai3[i]" << _qai3[i] << "i_srl(id)" << i_srl(id) << endl;

            return b::T1;

            }));
        }

    }

    synchronizer.waitForFinished();

    return b::T0;
}



b::t Dll_usb_mmf01stl::thsri_pai3(i::A3 _ai3, h::T _row){
    //qDebug() << __func__ << endl;

    QFutureSynchronizer<b::t> synchronizer;
    for(z::t i(0) ; i < 3 ; ++i ){

        int id = (_row + 1) * 10 + (i + 1);

        synchronizer.addFuture(QtConcurrent::run([=](){  // 18번 도는 쓰레드

            while(1){

                if(  !((_ai3[i] - 100) < i_srl(id) && (_ai3[i] + 100) >  i_srl(id))  ){ /*qDebug("Waiting for correct response.. _ai3[i] != i_srl(id)"); */ srl_i(_ai3[i], id);}
                else { break; }

            }
            qDebug() << "id" << id << "_ai3[i]" << _ai3[i] << "i_srl(id)" << i_srl(id) << endl;

        return b::T1;

        }));
    }

    synchronizer.waitForFinished();

    return b::T0;
}

bool ia3_pai3(i::a3 ia3_ ,pai3::p _pai3, i::T _iRow){

    for(z::t i(0) ; i < 3 ; ++i){
        ia3_[i] = _pai3[_iRow][i];
    }

    return b::T1;
}



b::t Dll_usb_mmf01stl::srl_pai3(int** _pai3){

    //qDebug() << __func__ << endl;

    pai3::p cmd = pai3_pp(_pai3);

    QFutureSynchronizer<b::t> synchronizer;


    for(z::t i(0) ; i < 6 ; ++i){ synchronizer.addFuture(QtConcurrent::run([=](){

            i::a3 ia3 = {0, };

            ia3_pai3(ia3, cmd, i);

            thsri_pai3(ia3, i);

            return b::T1;

        }));
    }

    synchronizer.waitForFinished();
    return b::T1;

}

qt::srl::p CreateSrl(QObject *parent = nullptr){

    QSerialPort* srl = new QSerialPort(parent);
    srl->setPortName("COM8");
    srl->setBaudRate(QSerialPort::Baud115200);
    srl->setDataBits(QSerialPort::Data8);
    srl->setParity(QSerialPort::NoParity);
    srl->setStopBits(QSerialPort::OneStop);
    srl->setFlowControl(QSerialPort::NoFlowControl);

    if(!srl->open(QIODevice::ReadWrite)){

        qDebug() << "Serial connect fialed" << endl;

    }else{

        qDebug() << "Serial opened" << endl;

    }

    return srl;
}

SerialWorker::SerialWorker(QObject *parent ){

    port = CreateSrl(this);

}



void SerialWorker::onWrite_cmd(c::p _cmd){

    y::p cmd = reinterpret_cast<y::p>(_cmd);
    qt::yar::t send_Data_Bytes = qt::yar::t::fromRawData(reinterpret_cast<c::p>(cmd), cmd::Z);

    port->write(send_Data_Bytes);

}



int encVal_srl(qt::srl::p _srl){

    qt::yar::t dataFromSri = _srl -> read(12);
    y::p yDataFromSri = reinterpret_cast<y::p>(dataFromSri.data());


    y2::u y2;

    y2.t2[0] = yDataFromSri[8];
    y2.t2[1] = yDataFromSri[7];

    int degree = (i::t)y2.h1;

    if(yDataFromSri[6] == 0x01) { degree = -degree; }



    return degree;
}

int SerialWorker::onWrite_req(qt::yar::t _req, i::t _id){

    //qDebug() <<__func__ << QThread::currentThread() << endl;
    if(port->write(_req)){

        if(!port->waitForReadyRead(1000)){
            qDebug() << " response time out from id : "+ qt::s_i(_id)  + "..! try again..!";

        }else{

            return encVal_srl(port);
        }

    }else{ qDebug() << " write failed on" << __func__ << endl;  return 0; }

}

QList<int> SerialWorker::onLv_clicked(int _legNo){
    //qDebug() << __func__ << endl;

    QList<int> leg_Enc;

    for(z::t i(0) ; i < 3 ; ++i){

        i::t id = (_legNo * 10) + (i + 1);



        req::t request; req_id(request, id);
        c::p pReq = reinterpret_cast<c::p>(request);

        int recvEncVal;
        QByteArray arr = QByteArray::fromRawData(pReq,req::Z);

        if(port->write(arr)){

            if(!port->waitForReadyRead(1000)){

                qDebug() << " response time out from id : "+ qt::s_i(id)  + "..! try again..!";

            }else{

                leg_Enc.push_back(encVal_srl(port));
            }

        }else{ qDebug() << " write failed on" << __func__ << endl;  }

    }

    return leg_Enc;


}



SerialWorker::~SerialWorker(){
    port->close();

}





//ui 세팅 관련 메소드 //

void MainWindow::set_tbrs(){

    ui->tbr_firstLeg->setMinimum(qt::i_s(ui->edit_min_firstleg->text()) );
    ui->tbr_secondLeg->setMinimum(qt::i_s(ui->edit_min_secondleg->text()));
    ui->tbr_thirdLeg->setMinimum(qt::i_s(ui->edit_min_thirdLeg->text()) );

    ui->tbr_firstLeg->setMaximum(qt::i_s(ui->edit_max_firstLeg->text()) );
    ui->tbr_secondLeg->setMaximum(qt::i_s(ui->edit_max_secondLeg->text()));
    ui->tbr_thirdLeg->setMaximum(qt::i_s(ui->edit_max_thirdLeg->text()) );

}

void MainWindow::on_edit_min_firstleg_returnPressed()
{
    set_tbrs();
}

void MainWindow::on_edit_min_secondleg_returnPressed()
{
    set_tbrs();
}

void MainWindow::on_edit_min_thirdLeg_returnPressed()
{
    set_tbrs();
}

void MainWindow::on_edit_max_firstLeg_returnPressed()
{
    set_tbrs();
}

void MainWindow::on_edit_max_secondLeg_returnPressed()
{
    set_tbrs();
}

void MainWindow::on_edit_max_thirdLeg_returnPressed()
{
    set_tbrs();
}

void MainWindow::on_tbr_firstLeg_valueChanged(int value)
{
    ui->edit_firstLeg->setText(qt::s_i(value));
    if(ui->cb_send->checkState())
        srl_ai3();
}

void MainWindow::on_tbr_secondLeg_valueChanged(int value)
{
    ui->edit_secondLeg->setText(qt::s_i(value));
    if(ui->cb_send->checkState())
        srl_ai3();
}

void MainWindow::on_tbr_thirdLeg_valueChanged(int value)
{
    ui->edit_thirdLeg->setText(qt::s_i(value));
    if(ui->cb_send->checkState())
        srl_ai3();
}



void MainWindow::srl_ai3(){

    if(ui->lv_legs->currentItem() != nullptr){

        int legNo = qt::i_s(ui->lv_legs->currentItem()->text());

        int row   = legNo - 1;

        int iFirstLeg = -1;
        int iSecondLeg = -1;
        int iThirdLeg = -1;


        if(ui->cb_firstLeg->isChecked()) iFirstLeg  = ui->tbr_firstLeg->value()  * 100 - OFFSET[row][0];

        if(ui->cb_secondLeg->isChecked()) iSecondLeg  = ui->tbr_secondLeg->value()  * 100 - OFFSET[row][1];

        if(ui->cb_thirdLeg->isChecked()) iThirdLeg  = ui->tbr_thirdLeg->value()  * 100 - OFFSET[row][2];

        QList<int> qai3 = { iFirstLeg, iSecondLeg, iThirdLeg };

        emit send_clicked(qai3,legNo);

    }else { qDebug() << "click item on list view " << endl;}


}

void MainWindow::on_btn_send_clicked()
{
    srl_ai3();

}



b::t MainWindow::offset_fn(qt::s::t _path){

    if(_path == qt::s::T0){ return false; }
    QFile file(_path, this);

    file.open(QIODevice::ReadWrite);
    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');

    for (z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            OFFSET[i][j] = i_s(vs.at( (i * 3) + j ));
        }
    }
    return true;
}

void MainWindow::on_btn_load_clicked()
{

    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());

    if(offset_fn(path)){qDebug() << "offset loaded..!"; con_pai3(OFFSET);}
    else{ qDebug() << " offset load Failed..! "; }

    if(ui->lv_legs->isItemSelected(ui->lv_legs->currentItem()))
        tbrs_legNo(qt::i_s(ui->lv_legs->currentItem()->text()) );

}

void MainWindow::tbrs_legNo(i::T _legNo){

    QList<int> recvEncVal;

    QMetaObject::invokeMethod(stl->sWorker, "onLv_clicked", Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QList<int>, recvEncVal),
                              Q_ARG(int, _legNo));

    i::t row = _legNo - 1;


    if(!(recvEncVal.size() < 3)){

        ui->tbr_firstLeg->setValue(recvEncVal.at(0)  / 100 + OFFSET[row][0] / 100);
        ui->tbr_secondLeg->setValue(recvEncVal.at(1) / 100 + OFFSET[row][1] / 100);
        ui->tbr_thirdLeg->setValue(recvEncVal.at(2)  / 100 + OFFSET[row][2] / 100);

    }
}

void MainWindow::on_lv_legs_itemClicked(QListWidgetItem *item)
{

    tbrs_legNo(qt::i_s(item->text()));

}




void MainWindow::on_cb_sign_toggled(bool checked)
{

        for(z::t i(0) ; i < 6 ; ++i){
            for(z::t j(0) ; j < 3 ; ++j){
                OFFSET[i][j] = -OFFSET[i][j];
            }
        }

        if(ui->lv_legs->isItemSelected(ui->lv_legs->currentItem()))
            tbrs_legNo(qt::i_s(ui->lv_legs->currentItem()->text()) );

}


void MainWindow::on_cb_offset_toggled(bool checked)
{

    if(checked){
        memcpy(OFFSETTEMP, OFFSET, 18 * 4);
        memset(OFFSET, 0x00, 18 * 4);

        if(ui->lv_legs->isItemSelected(ui->lv_legs->currentItem()))
            tbrs_legNo(qt::i_s(ui->lv_legs->currentItem()->text()) );
    }else{
        memcpy(OFFSET, OFFSETTEMP, 18 * 4);
        memset(OFFSETTEMP, 0x00, 18 * 4);

        if(ui->lv_legs->isItemSelected(ui->lv_legs->currentItem()))
            tbrs_legNo(qt::i_s(ui->lv_legs->currentItem()->text()) );
    }

}

void MainWindow::load_offset(const QString& _fn)
{
    if(_fn == qt::s::T0){ return; }

    QFile file(_fn, this);
    file.open(QIODevice::ReadWrite);
    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), '\n');

    for(auto s : vs){
        ui->lv_commands->addItem(qt::qs_s(s));
    }


    qDebug() << "vs size() : " << vs.size() << endl;
    idxSizeCommands = vs.size() - 1;

    pai3::p temp;


    for(z::t i(0) ; i < vs.size() ; ++i){
        temp = new i::t[6][3]{};
        s::v vsTemp = vs_s(vs.at(i), ' ');

        for(z::t j(0) ; j < vsTemp.size() ; ++j){

            *((*temp) + j) = i_s(vsTemp.at(j));

        }
        mCommands.insert(i, temp);
    }

    qDebug() << "size of map : " << mCommands.size() << endl;

}


void MainWindow::on_lineEdit_returnPressed()
{

}

void MainWindow::on_btn_commands_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());
    ui->edPath->setText(path);
    load_offset(path);
}

void MainWindow::on_lv_commands_doubleClicked(const QModelIndex &index){

    qDebug() << "index " << index.row() << endl;

    pai3::p command = mCommands.find(index.row()).value();

    addOffset(command);

    emit thsrl_cds(pp_pai3(command));

}

void MainWindow::on_cb_timer_toggled(bool checked)
{
    if(checked){
        srl_fileTimer->start();
    }else{
        srl_fileTimer->stop();
    }
}

void MainWindow::on_Edit_timerDelay_returnPressed()
{

    qDebug() <<" retrun pressed " << endl;
    srl_fileTimer->setInterval(qt::i_s(ui->Edit_timerDelay->text()));
    ui->tbr_delay->setValue(qt::i_s(ui->Edit_timerDelay->text()));

}

void MainWindow::on_tbr_delay_sliderMoved(int position)
{

    qDebug() << "position" << position << endl;
    ui->Edit_timerDelay->setPlaceholderText(qt::s_i(position));
    srl_fileTimer->setInterval(position);

}


void MainWindow::on_edPath_returnPressed()
{
    qDebug() << __func__ << endl;
    load_offset(ui->edPath->text());
}

void MainWindow::on_btnClear_clicked()
{
    ui->lv_commands->clear();
}

void MainWindow::on_btn_home_clicked()
{
    if(ui->lv_legs->currentItem() != nullptr){

        int legNo = qt::i_s(ui->lv_legs->currentItem()->text());

        int row   = legNo - 1;

        QList<int> qai3 = { 0 + OFFSET[row][0], 0 + OFFSET[row][1], 0 + OFFSET[row][2]};
        emit send_clicked(qai3,legNo);
    }


}

void MainWindow::on_pushButton_clicked()
{
    wThread->terminate();
    wThread->wait();

//        wThread = new QThread();
//        stl = new Dll_usb_mmf01stl();

//        stl->moveToThread(wThread);

//        wThread->start();
}
