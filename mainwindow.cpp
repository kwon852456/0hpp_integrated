#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "3dll_usb_01stt.h"

pai3::p OFFSET = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };
pai3::p OFFSETTEMP = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };

QMutex mutForOffset;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<QList<int>>("QList<int>");



    wThread       = new QThread();
    sendTimer     = new QTimer (this);
    srl_fileTimer = new QTimer (this);
    stl           = new Dll_usb_mmf01stl();

    stl->moveToThread(wThread);
    wThread->start();

    makeConnection();


    sendTimer    -> setInterval (1000);
    srl_fileTimer-> setInterval (1000);

    init_tbrs ();
    init_lv   ();

}


MainWindow::~MainWindow()
{
    delete ui;

    wThread->quit();
    wThread->wait();
}

void MainWindow::makeConnection(){

    connect(this,          &MainWindow::thsrl_cds,        stl,        &Dll_usb_mmf01stl::srl_pai3);
    connect(this,          &MainWindow::send_clicked,     stl,        &Dll_usb_mmf01stl::thsri_qai3);
    connect(srl_fileTimer, &QTimer::timeout,             this,        &MainWindow::fileTimerTimeOut);
    connect(sendTimer,     &QTimer::timeout,             this,        &MainWindow::srl_ai3);
    connect(this,          &MainWindow::readOffset,       stl,        &Dll_usb_mmf01stl::OnReadOffset);
    connect(this,          &MainWindow::mmfClicked,       stl,        &Dll_usb_mmf01stl::mmfClicked);
    connect(this,          &MainWindow::write_log,       ui->usb_log, &Usb_log::setlog);
    connect(stl,           &Dll_usb_mmf01stl::log,       this,        &MainWindow::write_log);
    connect(this,          &MainWindow::openFirstSerial,  stl,        &Dll_usb_mmf01stl::openFirstSerial);
    connect(this,          &MainWindow::openSecondSerial, stl,        &Dll_usb_mmf01stl::openSecondSerial);

}

void MainWindow::log(qt::s::T _text){
    emit write_log(_text);
}

b::t MainWindow::init_tbrs(){
    set_tbrs();
    return b::T1;
}

b::t MainWindow::init_lv(){  lv_no(ui->lv_legs, 1, 7);   return b::T1;   }

void add_pai36(pai3::p pai_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] += _pai3[i][j];
        }
    }

}

b::t addOffset(pai3::p _command){


    add_pai36(_command, OFFSET);

    return b::T1;

}

vo::t MainWindow::fileTimerTimeOut(){

    qDebug() <<" row idx " << ui->lv_commands->currentRow() << endl;
    log(" row idx " + ui->lv_commands->currentRow());



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
        mThread = new QThread();

        sWorker = new SerialWorker();
        oWorker = new OffsetWorker();

        sWorker->moveToThread(sThread);
        oWorker->moveToThread(mThread);


        connect(this,    &Dll_usb_mmf01stl::write_cmd , sWorker , &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::mmfClicked, sWorker , &SerialWorker::onMmfCheck_clicked);
        connect(this,    &Dll_usb_mmf01stl::readOffset, oWorker , &OffsetWorker::onReadOffset);
        connect(sWorker, &SerialWorker::log,                this, &Dll_usb_mmf01stl::log);
        connect(oWorker, &OffsetWorker::log,                this, &Dll_usb_mmf01stl::log);
        connect(this,    &Dll_usb_mmf01stl::openFirstSerial,  sWorker, &SerialWorker::setSerialPort);
        connect(this,    &Dll_usb_mmf01stl::openSecondSerial, oWorker, &OffsetWorker::setSerialPort);

        sThread->start();
        mThread->start();
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


b::t Dll_usb_mmf01stl::thsri_qai3(QList<int> _qai3, i::t _legNo){
    qDebug() << __func__ << endl;
    emit log(__func__);

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

                emit log("id  " + qt::s_i(id) + "  _qai3[i]  " + qt::s_i(_qai3[i]) + "  i_srl(id)  " + qt::s_i(i_srl(id)));

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
            emit log("id  " + qt::s_i(id) + "  _ai3[i]  " + qt::s_i(_ai3[i]) + "  i_srl(id)  " + qt::s_i(i_srl(id)));
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

void Dll_usb_mmf01stl::OnReadOffset(){

    qDebug() << __func__ << endl;
    emit log(__func__);

    emit readOffset();
}















SerialWorker::SerialWorker(QObject *parent ){

    port = CreateSrl(this,0);

}

SerialWorker::~SerialWorker(){
    port->close();

}

void SerialWorker::onWrite_cmd(c::p _cmd){

    y::p cmd = reinterpret_cast<y::p>(_cmd);
    qt::yar::t send_Data_Bytes = qt::yar::t::fromRawData(reinterpret_cast<c::p>(cmd), cmd::Z);

    if(port->isOpen()){
        port->write(send_Data_Bytes);
    }else emit log("serial not opned..");

}


int SerialWorker::onWrite_req(qt::yar::t _req, i::t _id){

    //qDebug() <<__func__ << QThread::currentThread() << endl;

    if(port->isOpen()){



    }else emit log("serial not opned..");
    if(port->write(_req)){

        if(!port->waitForReadyRead(1000)){

            qDebug() << " response time out from id : "   + qt::s_i(_id)  +    "..! try again..!"   ;
            emit log   (" response time out from id : "   + qt::s_i(_id)  +    "..! try again..!"   );

        }else{

            return encVal_srl(port);
        }

    }else{ qDebug() << " write failed on" << __func__ << endl;  return 0; emit log( qt::qs_s(" write failed on") + qt::qs_s("onWrite_req") );}

}

void SerialWorker::setIds(){

    i::t id[18] = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43, 51, 52, 53, 61, 62, 63 };
    for(i::t i : id){ ids.push_back(i); }

}

void SerialWorker::onMmfCheck_clicked(){

    qDebug() << __func__ << endl;
    emit log(__func__ );

    isSrlFinished = !isSrlFinished;

    if(port->isOpen()){

        mmf_srl(port, ids, OFFSET);

    }else{

        qDebug() << "Serial not opened...!" << endl;
        emit    log("Serial not opened...!");
    }

    isSrlFinished = !isSrlFinished;
}


qt::yar::t yar_id(i::t _id){

    req::t request;

    req_id(request, _id);

    c::p pReq = reinterpret_cast<c::p>(request);

    return QByteArray::fromRawData(pReq, req::Z);
}

QList<int> SerialWorker::onLv_clicked(int _legNo){

    QList<int> leg_Enc;

    for(z::t i(0) ; i < 3 ; ++i){

        i::t id = (_legNo * 10) + (i + 1);
        if(port->isOpen()){

            if(port->write(yar_id(id))){

                if(!port->waitForReadyRead(1000)){

                    qDebug() << " response time out from id : "  + qt::s_i(id)  + "..! try again..!";
                    emit log(" response time out from id : "     + qt::s_i(id)  + "..! try again..!");

                }else{

                    leg_Enc.push_back(encVal_srl(port));
                }


            }else{ qDebug() << " write failed on" << __func__ << endl;   emit log("write failed");}

        }else emit log("Serial not opened..!");

    }

    return leg_Enc;

}

void SerialWorker::setSerialPort(QString _comPort){
    emit log("comport" + _comPort);
    port->close();
    port->setPortName(_comPort);

    if(!port->open(QIODevice::ReadWrite)){

        qDebug() << "Serial connect failed" << endl;
        emit log("Serial connect failed");

    }else{

        qDebug() << "Serial opened" << endl;
        emit log("Serial opened");
    }
}










OffsetWorker::OffsetWorker(QObject *parent){
    srl = CreateSrl(this,0);
}
OffsetWorker::~OffsetWorker(){
    srl->close();
}





void OffsetWorker::onReadOffset(){

    qDebug() << __func__ << endl;
    emit log(__func__);


    pai3::p offset =  pai3_srl(srl);

    mutForOffset.lock();
    memcpy(OFFSET, offset, 18*4);
    mutForOffset.unlock();

    if(offset != nullptr){

        qDebug() << "offset Read result :" << endl;
        emit log("offset Read result :" );



        con_pai3(OFFSET);
        emit log(qs_pai3(OFFSET));

    }else{

        qDebug() << "Serial read failed" << endl;

    }
}


void OffsetWorker::setSerialPort(QString _comPort){
    emit log("comport" + _comPort);
    srl->close();
    srl->setPortName(_comPort);

    if(!srl->open(QIODevice::ReadWrite)){

        qDebug() << "Serial connect falled" << endl;
        emit log("Serial connect falled");

    }else{

        qDebug() << "Serial opened" << endl;
        emit log("Serial opened");
    }
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

    }else { qDebug() << "click item on list view " << endl; emit log("click item on list view "); }


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

    if(offset_fn(path)){qDebug() << "offset loaded..!"; emit log("offset loaded..!"); emit log(qs_pai3(OFFSET)); con_pai3(OFFSET);}
    else{ qDebug() << " offset load Failed..! "; emit log(" offset load Failed..! "); }

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
    emit log("vs size() : " + vs.size());

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
    emit log("size of map : " + mCommands.size());

}

void MainWindow::on_btn_commands_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());
    ui->edPath->setText(path);
    load_offset(path);
}

void MainWindow::on_lv_commands_doubleClicked(const QModelIndex &index){

    qDebug() << "index " << index.row() << endl;
    emit log("index " + index.row());

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
    emit log(" retrun pressed ");
    srl_fileTimer->setInterval(qt::i_s(ui->Edit_timerDelay->text()));
    ui->tbr_delay->setValue(qt::i_s(ui->Edit_timerDelay->text()));

}

void MainWindow::on_tbr_delay_sliderMoved(int position)
{

    qDebug() << "position" << position << endl;
    emit log("position" + position);

    ui->Edit_timerDelay->setPlaceholderText(qt::s_i(position));
    srl_fileTimer->setInterval(position);

}

void MainWindow::on_edPath_returnPressed()
{

    qDebug() << __func__ << endl;
    emit log(__func__);

    load_offset(ui->edPath->text());

}

void MainWindow::on_btnClear_clicked()
{

    ui->lv_commands->clear();

}



void MainWindow::on_offset_readOffset()
{

    emit readOffset();

}

void MainWindow::on_offset_saveOffset()
{

    emit log(save_pai3(OFFSET, 6));

}

void MainWindow::on_usb_mmf_mmfClicked()
{
    emit mmfClicked();
}

void MainWindow::on_edit_firstSerial_returnPressed()
{
    emit openFirstSerial(ui->edit_firstSerial->text());
}

void MainWindow::on_edit_secondSerial_returnPressed()
{
    emit openSecondSerial(ui->edit_secondSerial->text());
}
