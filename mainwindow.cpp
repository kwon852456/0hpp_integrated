﻿#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "3dll_usb_01stt.hpp"


pai3::p OFFSET     = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };
pai3::p OFFSETTEMP = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };

QMutex mutForOffset;

QElapsedTimer timer;

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
    init_lw   ();


}


MainWindow::~MainWindow()
{
    delete ui;

    wThread->quit();
    wThread->wait();
}

vo::t MainWindow::init_lw(){

    lw_cb(ui->lw_legs,   1, 6);
    lw_cb(ui->lw_motors, 1, 3);

}

vo::t MainWindow::makeConnection(){

    connect(this,          &MainWindow::thsrl_cds,        stl,         &Dll_usb_mmf01stl::srl_pai6);
    connect(this,          &MainWindow::thsrl_file,       stl,         &Dll_usb_mmf01stl::srl_pai6);

    connect(this,          &MainWindow::send_clicked,     stl,         &Dll_usb_mmf01stl::thsri_qai36);
    connect(this,          &MainWindow::readOffset,       stl,         &Dll_usb_mmf01stl::OnReadOffset);
    connect(this,          &MainWindow::mmfClicked,       stl,         &Dll_usb_mmf01stl::onMmfClicked);
    connect(this,          &MainWindow::openFirstSerial,  stl,         &Dll_usb_mmf01stl::openFirstSerial);
    connect(this,          &MainWindow::openSecondSerial, stl,         &Dll_usb_mmf01stl::openSecondSerial);
    connect(this,          &MainWindow::setIds,           stl,         &Dll_usb_mmf01stl::setIds);
    connect(this,          &MainWindow::tempSave,         stl,         &Dll_usb_mmf01stl::tempSave);
    connect(this,          &MainWindow::saveHomeSet,      stl,         &Dll_usb_mmf01stl::saveHomeSet);
    connect(this,          &MainWindow::loadHomeset,      stl,         &Dll_usb_mmf01stl::loadHomeset);
    connect(this,          &MainWindow::legsToOrigin,     stl,         &Dll_usb_mmf01stl::legsToOrigin);
    connect(this,          &MainWindow::write_log,        ui->usb_log, &Usb_log::setlog);

    connect(stl,           &Dll_usb_mmf01stl::showOffset,     this,    &MainWindow::onShowOffset);
    connect(stl,           &Dll_usb_mmf01stl::log,            this,    &MainWindow::write_log);
    connect(stl,           &Dll_usb_mmf01stl::thsri_qai36End, this,    &MainWindow::thsri_qai36End);
    connect(stl,           &Dll_usb_mmf01stl::timeTaken,      this,    &MainWindow::timeTaken);
    connect(stl,           &Dll_usb_mmf01stl::setHomeSet,     this,    &MainWindow::setHomeSet);
    connect(srl_fileTimer, &QTimer::timeout,                  this,    &MainWindow::fileTimerTimeOut);
    connect(sendTimer,     &QTimer::timeout,                  this,    &MainWindow::srl_ai3);

}

vo::t MainWindow::log(qt::s::t _text){
    emit write_log(_text);
}

b::t MainWindow::init_tbrs(){

    set_tbrs();
    return b::T1;

}

b::t MainWindow::init_lv(){  lv_no(ui->lv_legs, 1, 7);   return b::T1;   }

QList<int> MainWindow::li_legsVal(){

    QList<int> li;

    li.push_back(qt::i_s(ui->edit_max_firstLeg->text())  * 100);
    li.push_back(qt::i_s(ui->edit_min_firstleg->text())  * 100);

    li.push_back(qt::i_s(ui->edit_max_secondLeg->text()) * 100);
    li.push_back(qt::i_s(ui->edit_min_secondleg->text()) * 100);

    li.push_back(qt::i_s(ui->edit_max_thirdLeg->text())  * 100);
    li.push_back(qt::i_s(ui->edit_min_thirdLeg->text())  * 100);

    return li;

}

vo::t MainWindow::thsrl_pai6(pai6::p _commands){


    QList<int> li_Val = li_legsVal();

    pai6::p temp_pai6 = new i::t[6][6]{ {0},{0},{0},{0},{0},{0} };

    memcpy(temp_pai6, _commands, 18 * 4 * 2); // 실제 멤버변수에 있는 pai3에는 변화가 가지 않도록 한다.

    subOffset(temp_pai6, OFFSET);

    check_commandValid(temp_pai6, li_Val[0],  li_Val[1], li_Val[2], li_Val[3], li_Val[4], li_Val[5]);

    emit thsrl_file(pp_pai6(temp_pai6));

}

vo::t MainWindow::fileTimerTimeOut(){

    if(stl->isFinished){

        if(ui->lv_commands->currentRow() != -1  && ui->lv_commands->currentRow() <= idxSizeCommands ){

            pai6::p command = mCommands.find(ui->lv_commands->currentRow()).value();

            thsrl_pai6(command);

            ui->lv_commands->setCurrentRow(ui->lv_commands->currentRow() + 1);

        }

    }else{ qDebug() << "Serial is busy..! wait for unlock "; }

}

pai6::p pai6_msg(vo::p _message){

    MSG* msg = reinterpret_cast<MSG*>(_message);

    if((msg)->message == WM_COPYDATA){

        pai6::p pai6 = new i::a6[6]{{0,},{0,},{0,},{0,},{0,},{0,}};

        HWND reciverhwnd = (HWND)msg->wParam;
        PCOPYDATASTRUCT pcds = (PCOPYDATASTRUCT)msg->lParam;
        UNUSED(reciverhwnd);

        y::p yHdr = (y::p) pcds ->lpData;
        pai6_yHdr(pai6, yHdr);

        return pai6;
    }

    return nil;

}

b::t MainWindow::nativeEvent(const qt::yar::t &eventType, vo::p message, long *resultMSG){

    pai6::p command = pai6_msg(message);

    if(command != nil){

        emit thsrl_cds(ipp_pai66(command, OFFSET, ui));

    }
    else
        delete[] command;

    *resultMSG = 0;

    UNUSED(eventType);

    return b::T0;

}

vo::t MainWindow::onShowOffset(){

    write_log("offset read result : ");

    hnd::t handle = open_mmf("mmftest_pchr");

    pai3::p pai;
    pai3_mmf(pai, handle);

    write_log(qs_pai3(pai));

};

vo::t MainWindow::thsri_qai36End(){
    tbrEnded = true;
}

vo::t MainWindow::timeTaken(i::t _time){


    ui->edit_time->append(qt::s_i(_time) );

}

vo::t MainWindow::setHomeSet(qt::s::t _homeSet){

    qDebug() << __func__ ;
    ui->edit_homeSet->setText(_homeSet);

}
















Dll_usb_mmf01stl::Dll_usb_mmf01stl(QObject *parent){


        sThread = new QThread();
        mThread = new QThread();

        sWorker = new SerialWorker();
        oWorker = new OffsetWorker();

        sWorker->moveToThread(sThread);
        oWorker->moveToThread(mThread);


        connect(this,    &Dll_usb_mmf01stl::write_cmd ,       sWorker, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::mmfClicked,       sWorker, &SerialWorker::onMmfCheck_clicked);
        connect(this,    &Dll_usb_mmf01stl::openFirstSerial,  sWorker, &SerialWorker::setSerialPort);
        connect(this,    &Dll_usb_mmf01stl::tempSave,         sWorker, &SerialWorker::tempSave);
        connect(this,    &Dll_usb_mmf01stl::readOffset,       oWorker, &OffsetWorker::onReadOffset);
        connect(this,    &Dll_usb_mmf01stl::openSecondSerial, oWorker, &OffsetWorker::setSerialPort);
        connect(this,    &Dll_usb_mmf01stl::saveHomeSet,      oWorker, &OffsetWorker::saveHomeSet);
        connect(this,    &Dll_usb_mmf01stl::loadHomeset,      oWorker, &OffsetWorker::loadHomeset);


        connect(sWorker, &SerialWorker::log,                     this, &Dll_usb_mmf01stl::log);
        connect(sWorker, &SerialWorker::showOffset,              this, &Dll_usb_mmf01stl::showOffset);
        connect(oWorker, &OffsetWorker::log,                     this, &Dll_usb_mmf01stl::log);
        connect(oWorker, &OffsetWorker::setHomeSet,              this, &Dll_usb_mmf01stl::setHomeSet);


        sThread->start();
        mThread->start();
}

Dll_usb_mmf01stl::~Dll_usb_mmf01stl(){
    sThread->quit();
    sThread->wait();
};

vo::t Dll_usb_mmf01stl::srl_i(i::T _iDegree, i::T _id, i::T _velocity = 32){



    cmd::t command;
    cmd_id(command, _iDegree,  _id, _velocity);

    c::p pCmd = reinterpret_cast<c::p>(command);
    emit write_cmd(pCmd);

}

qt::yar::t yar_req(i::t _id){

    req::t request; req_id(request, _id);
    c::p pReq = reinterpret_cast<c::p>(request);

    return qt::yar::t::fromRawData(pReq,req::Z);

}

i::t Dll_usb_mmf01stl::i_srl(i::t _id){

    int recvEncVal;
    qt::yar::t arr = yar_req(_id);

    QMetaObject::invokeMethod(sWorker, "onWrite_req", Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, recvEncVal),
                              Q_ARG(QByteArray, arr),
                              Q_ARG(int, _id));


    return recvEncVal;
}

vo::t Dll_usb_mmf01stl::thread_pai6(QFutureSynchronizer<b::t>& _synchronizer, i::A6 _ai6, i::t _id, i::t _col){


    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

        i::t i = 0;
        while(1){

            i::t current = i_srl(_id);

            if( !( (_ai6[_col] - 100) < current && (_ai6[_col] + 100) >  current) ){  srl_i(_ai6[_col], _id, _ai6[_col + 3]);}
            else {  break; }


            if(i > 0)
                qDebug() << " waiting for motor to be placed where it should be... try : " + i;
            i++;
        }

        emit log("id  " + qt::s_i(_id) + "  send val : " + qt::s_i(_ai6[_col]) + "  motor Encoder value : " + qt::s_i(i_srl(_id)));

    return b::T1;

    }));
}

b::t Dll_usb_mmf01stl::thsri_pai6(i::A6 _ai6, h::T _row){


    QFutureSynchronizer<b::t> synchronizer;


    for(i::t col : cols){

        int id = (_row + 1) * 10 + (col + 1);

        thread_pai6(synchronizer, _ai6, id, col);

    }

    synchronizer.waitForFinished();

    return b::T0;

}

b::t Dll_usb_mmf01stl::srl_pai6(int** _pai6){

    qDebug() << __func__ ;

    isFinished = !isFinished;

    pai6::p cmd = pai6_pp(_pai6);
    QFutureSynchronizer<b::t> synchronizer;
    timer.restart();

    for(i::t row : rows){
        synchronizer.addFuture(QtConcurrent::run([=](){

                i::a6 ia6 = {0, };

                ia6_pai6(ia6, cmd, row);
                thsri_pai6(ia6, row);

                return b::T1;
        }));
    }

    synchronizer.waitForFinished();
    emit timeTaken(timer.elapsed());

    isFinished = !isFinished;




    emit log("");
    delete[] cmd;
    return b::T1;

}

vo::t Dll_usb_mmf01stl::thread_qai36(QFutureSynchronizer<b::t>& _synchronizer, QList<int> _qai3, i::t _id, i::t _row){

    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

        while(1){

            if( !((_qai3[_row] - 100) < i_srl(_id) && (_qai3[_row] + 100) >  i_srl(_id))  ){ qDebug("_ai3[i] != i_srl(id)"); srl_i(_qai3[_row], _id);}
            else { break; }

        }

        emit log("id  " + qt::s_i(_id) + "  _qai3[i]  " + qt::s_i(_qai3[_row]) + "  i_srl(id)  " + qt::s_i(i_srl(_id)));

    return b::T1;

    }));

}

vo::t Dll_usb_mmf01stl::thsri_qai36(QList<int> _qai3, i::t _legNo){

    qDebug() << __func__;

    QFutureSynchronizer<b::t> synchronizer;

    for(z::t i(0) ; i < 3 ; ++i ){
        int id = (_legNo * 10) + (i + 1);

        if(_qai3[i] != -1){
            thread_qai36(synchronizer, _qai3, id, i);
        }
    }

    synchronizer.waitForFinished();

    emit thsri_qai36End();
}

vo::t Dll_usb_mmf01stl::OnReadOffset(){

    emit log(__func__);
    emit readOffset();
}

vo::t Dll_usb_mmf01stl::onMmfClicked(){

    if(sWorker->isSrlFinished){
        emit mmfClicked();
    }
}

vo::t Dll_usb_mmf01stl::setIds(QList<int> _rows, QList<int> _cols){

    rows.swap(_rows);
    cols.swap(_cols);

    qDebug()<< "_rows : " << rows;
    qDebug()<< "_cols : " << cols;

    emit log("_rows : " + qs_li(rows));
    emit log("_cols : " + qs_li(cols));

}

i::t (*pai6_pai3( pai3::p _pai3, i::t _velocity = 10 ))[6]{

    pai6::p pai6_ = new i::t[6][6]{  {0},{0},{0},{0},{0},{0},  };


    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){

            pai6_[i][j] = j < 3 ? _pai3[i][j] : 32;

        }
    }

    delete[] _pai3;
    return pai6_;
}

vo::t Dll_usb_mmf01stl::legsToOrigin(){
    qt::s::t sDiff = qt::s::T0;
    QMetaObject::invokeMethod(oWorker,"qs_diff",Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QString, sDiff));

    if(vs_s(qt::s_qs(sDiff),' ').size() < 18){ qDebug() << ("size of diff < 18");  return;}
    pai6::p diff = pai6_pai3(pai3_qs(sDiff), 10);
    srl_pai6(pp_pai6(diff));
}



















SerialWorker::SerialWorker(QObject *parent ){

    port = CreateSrl(this,0);
    setIds();

}

SerialWorker::~SerialWorker(){

    port->close();

}

vo::t SerialWorker::onWrite_cmd(c::p _cmd){

    qt::yar::t send_Data_Bytes = qt::yar::t::fromRawData(reinterpret_cast<c::p>(_cmd), cmd::Z);

    port->write(send_Data_Bytes);

    if(port->isOpen()){

        port->write(send_Data_Bytes);

    }else emit log("serial not opned..");

}

int SerialWorker::onWrite_req(qt::yar::t _req, i::t _id){

    if(port->write(_req)){

        if(!port->waitForReadyRead(1000)){

            qDebug() << " response time out from id : "   + qt::s_i(_id)  +    "..! try again..!"   ;
            emit log   (" response time out from id : "   + qt::s_i(_id)  +    "..! try again..!"   );

        }else{

            return encVal_srl(port);
        }

    }else{ return 0; emit log( qt::qs_s(" write failed on") + qt::qs_s("onWrite_req") );}

}

vo::t SerialWorker::setIds(){

    i::t id[18] = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43, 51, 52, 53, 61, 62, 63 };
    for(i::t i : id){ ids.push_back(i); }

}

vo::t SerialWorker::onMmfCheck_clicked(){

    isSrlFinished = !isSrlFinished;

    if(port->isOpen()){

        mmf_srl(port, ids, OFFSET);

    }else{

        qDebug() << "Serial not opened...!" << endl;
        emit    log("Serial not opened...!");

    }

    isSrlFinished = !isSrlFinished;

    emit showOffset();

}

qt::yar::t yar_id(i::t _id){

    req::t request;

    req_id(request, _id);

    c::p pReq = reinterpret_cast<c::p>(request);

    return qt::yar::t::fromRawData(pReq, req::Z);

}

void SerialWorker::onLegClick_pushEncVal(QList<int>& leg_Enc_,qt::srl::p _port, i::t _id){


    if(port->write(yar_id(_id))){

        if(!port->waitForReadyRead(1000)){

            emit log("onLegClick response time out from id : "  + qt::s_i(_id)  + "..! try again..!");

        }else{

            i::t encVal = encVal_srl(port);

            emit log("encVal : " + qt::s_i(encVal));

            leg_Enc_.push_back(encVal);

        }


    }else{ emit log("write failed"); }

}

QList<int> SerialWorker::onLv_clicked(int _legNo){

    emit log(__func__);

    QList<int> leg_Enc;

    for(z::t i(0) ; i < 3 ; ++i){

        i::t id = (_legNo * 10) + (i + 1);
        if(port->isOpen()){

            onLegClick_pushEncVal(leg_Enc, port, id);

        }else emit log( "Serial not opened..!" );

    }

    qDebug() << "leg_Enc" << leg_Enc ;

    return leg_Enc;

}

vo::t SerialWorker::setSerialPort(QString _comPort){

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

vo::t SerialWorker::tempSave(qt::s::t _fn){

    save_srl(port, ids, OFFSET, _fn);

    log("saved..!");

}























OffsetWorker::OffsetWorker(QObject *parent){

    srl = CreateSrl(this,0);

}

OffsetWorker::~OffsetWorker(){

    srl->close();

}

vo::t OffsetWorker::onReadOffset(){

    emit log(__func__);

    pai3::p tempHomeset =  pai3_srl(srl);

    memcpy(homeSet, tempHomeset, 18*4);

    if(tempHomeset != nullptr){

        emit log("offset Read result :" );
        emit log(qs_pai3H(homeSet));

        emit setHomeSet(qs_pai3H(homeSet));

    }else{

        emit log("Serial read failed");
    }
}

vo::t OffsetWorker::saveHomeSet(){
    save_pai3(homeSet,6, "homeSet.ini");
}

vo::t OffsetWorker::loadHomeset(qt::s::t _path){

    homeSet = pai3_fn(_path, this);

    if(homeSet != nullptr){qDebug() << "homeSet loaded..!"; emit log("homeSet loaded..!"); emit log(qs_pai3(homeSet)); con_pai3(homeSet);}
    else{ qDebug() << " homeSet load Failed..! "; emit log(" homeSet load Failed..! "); }

    emit setHomeSet(qs_pai3H(homeSet));

}


vo::t OffsetWorker::setSerialPort(QString _comPort){

    emit log("comport" + _comPort);

    srl->close();
    srl->setPortName(_comPort);

    if(!srl->open(QIODevice::ReadWrite)){

        emit log("Serial connect falled");

    }else{

        emit log("Serial opened");
    }
}





qt::s::t OffsetWorker::calc_diff(){
    //pai3::p tempHomeSet =  pai3_srl(srl);

    pai3::p tempHomeSet = new i::t[6][3]{ {8000,8000,8000 },{8000,8000,8000 },{8000,8000,8000 },{8000,8000,8000 },{8000,8000,8000 },{8000,8000,8000 } };



    //타겟 엔코더 값은 homeSet에 있고 현재 엔코더 값은 tempHomeSet에 있다

    for(z::t i(0) ; i < 6 ; ++i){

        for(z::t j(0) ; j < 3 ; ++j){

            i::T current = tempHomeSet[i][j];
            i::T target  = homeSet[i][j];
            i::t dif     = current - target;

            if(abs(dif) > 18000){

                if(current < target)  {   dif = (current +  36000     - target);    }
                else                  {   dif = (current -  target  - 36000);       }

            }

            diff[i][j] = dif;

        }

    }

    qDebug() << "diff : ";
    con_pai3(diff);




    return qs_pai3H(diff);


}
qt::s::t OffsetWorker::qs_diff(){
    return qs_pai3H(diff);
}


























//ui 세팅 관련 메소드 //

vo::t MainWindow::set_tbrs(){

    ui->tbr_firstLeg->setMinimum(qt::i_s(ui->edit_min_firstleg->text()) );
    ui->tbr_secondLeg->setMinimum(qt::i_s(ui->edit_min_secondleg->text()));
    ui->tbr_thirdLeg->setMinimum(qt::i_s(ui->edit_min_thirdLeg->text()) );

    ui->tbr_firstLeg->setMaximum(qt::i_s(ui->edit_max_firstLeg->text()) );
    ui->tbr_secondLeg->setMaximum(qt::i_s(ui->edit_max_secondLeg->text()));
    ui->tbr_thirdLeg->setMaximum(qt::i_s(ui->edit_max_thirdLeg->text()) );

}

vo::t MainWindow::on_edit_min_firstleg_returnPressed()
{
    set_tbrs();
}

vo::t MainWindow::on_edit_min_secondleg_returnPressed()
{
    set_tbrs();
}

vo::t MainWindow::on_edit_min_thirdLeg_returnPressed()
{
    set_tbrs();
}

vo::t MainWindow::on_edit_max_firstLeg_returnPressed()
{
    set_tbrs();
}

vo::t MainWindow::on_edit_max_secondLeg_returnPressed()
{
    set_tbrs();
}

vo::t MainWindow::on_edit_max_thirdLeg_returnPressed()
{
    set_tbrs();
}

vo::t MainWindow::on_tbr_firstLeg_valueChanged(int value)
{
    ui->edit_firstLeg->setText(qt::s_i(value));
    if(ui->cb_send->checkState() && tbrEnded)
        srl_ai3();
}

vo::t MainWindow::on_tbr_secondLeg_valueChanged(int value)
{
    ui->edit_secondLeg->setText(qt::s_i(value));
    if(ui->cb_send->checkState() && tbrEnded)
        srl_ai3();
}

vo::t MainWindow::on_tbr_thirdLeg_valueChanged(int value)
{
    ui->edit_thirdLeg->setText(qt::s_i(value));
    if(ui->cb_send->checkState() && tbrEnded)
        srl_ai3();
}

vo::t MainWindow::srl_ai3(){

    tbrEnded = false;

    qDebug() << __func__;

    if(ui->lv_legs->currentItem() != nullptr){

        int legNo = qt::i_s(ui->lv_legs->currentItem()->text());

        int row   =  legNo - 1;

        int iFirstLeg = -1,        iSecondLeg = -1,         iThirdLeg = -1;

        if(ui->cb_firstLeg->isChecked())  iFirstLeg  =  ui->tbr_firstLeg->value()     * 100 - OFFSET[row][0];
        if(ui->cb_secondLeg->isChecked()) iSecondLeg = ui->tbr_secondLeg->value()     * 100 - OFFSET[row][1];
        if(ui->cb_thirdLeg->isChecked())  iThirdLeg  =  ui->tbr_thirdLeg->value()     * 100 - OFFSET[row][2];

        QList<int> qai3 = { iFirstLeg, iSecondLeg, iThirdLeg };

        qDebug() << "qai3" << qai3;

        emit send_clicked(qai3,legNo);

    }else { emit log("click item on list view "); }

}

vo::t MainWindow::on_btn_send_clicked()
{
    qDebug() << __func__;
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

vo::t MainWindow::on_btn_load_clicked()
{

    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());
    emit loadHomeset(path);


}

vo::t MainWindow::tbrs_legNo(i::T _legNo){


    QList<int> recvEncVal;


    QMetaObject::invokeMethod(stl->sWorker, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                        Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                          Q_ARG(int, _legNo));
    i::t row = _legNo - 1;
    if(!(recvEncVal.size() < 3)){

        ui->tbr_firstLeg ->setValue (recvEncVal.at(0)  / 100 + OFFSET[row][0] / 100 );
        ui->tbr_secondLeg->setValue (recvEncVal.at(1)  / 100 + OFFSET[row][1] / 100 );
        ui->tbr_thirdLeg ->setValue (recvEncVal.at(2)  / 100 + OFFSET[row][2] / 100 );

    }
}

vo::t MainWindow::on_lv_legs_itemClicked(QListWidgetItem *item)
{

    ui->cb_send->setCheckState(Qt::CheckState::Unchecked);
    tbrs_legNo(qt::i_s(item->text()));

}

vo::t MainWindow::on_cb_sign_toggled(bool checked)
{

        for(z::t i(0) ; i < 6 ; ++i){
            for(z::t j(0) ; j < 3 ; ++j){
                OFFSET[i][j] = -OFFSET[i][j];
            }
        }

        if(ui->lv_legs->isItemSelected(ui->lv_legs->currentItem()))
            tbrs_legNo(qt::i_s(ui->lv_legs->currentItem()->text()) );

}

vo::t MainWindow::on_cb_offset_toggled(bool checked)
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

vo::t MainWindow::mCommands_vs(QMap<int, int (*)[6]>& _mCommands_, s::v _vs){

    qDebug() << __func__;

    pai6::p temp;

    for(z::t i(0) ; i < _vs.size() ; ++i){

        temp = new i::t[6][6]{};

        s::v vsTemp = vs_s( _vs.at(i), ' ' );

        qDebug() << "size of vsTemp : " << vsTemp.size();

        for(z::t j(0) ; j < vsTemp.size() / 6 ; ++j){
            for(z::t x(0) ; x < 6 ; ++x){
                *((*temp) + ((j * 6) + x)) = x < 3 ? i_s(vsTemp.at((j * 3) + x)) : i_s(vsTemp.at((j * 3) + (x - 3) + 18));
            }
        }

        mCommands.insert(i, temp);
    }
}

s::v vs_mNo(ks::m _mNo){

    s::v vs_;

    for(z::t i(0) ; i < _mNo.size() ; ++i){

        vs_.push_back(_mNo.find(s_i(i))->second)  ;

    }

    return vs_;

}

vo::t MainWindow::load_commands(const QString& _sSec)  //
{
    qDebug() << __func__;

    ui->lv_commands->clear();

    ks::m commands = kmsmCommands.find(qt::s_qs(_sSec))->second;

    for(z::t i(0) ; i < commands.size() ; ++i){

        ui->lv_commands->addItem(qt::qs_s( commands.find(s_i(i))->second ));

    }


    s::v vsCommands = vs_mNo(commands);

    idxSizeCommands = commands.size() - 1;
    mCommands_vs(mCommands, vsCommands);

    log("size of map : " + qt::s_i(mCommands.size()));

}

vo::t MainWindow::cb_fn(qt::s::t _fn){

    ui->edPath->setText(_fn);

    kmsmCommands = kmNo_fn(qt::s_qs(_fn));

    for(auto i = kmsmCommands.begin() ; i != kmsmCommands.end() ; ++i ){

        ui->cb_commands->addItem(qt::qs_s(i->first));

    }

}

vo::t MainWindow::on_btn_commands_clicked()
{

    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());
    cb_fn(path);

}

vo::t MainWindow::on_lv_commands_doubleClicked(const QModelIndex &index){

    log("index " + qt::s_i(index.row()));

    pai6::p command = mCommands.find(index.row()).value();

    thsrl_pai6(command);


}

vo::t MainWindow::on_cb_timer_toggled(bool checked)
{
    if(checked){
        srl_fileTimer->start();
    }else{
        srl_fileTimer->stop();
    }

}

vo::t MainWindow::on_Edit_timerDelay_returnPressed()
{

    qDebug() <<" retrun pressed " << endl;
    emit log(" retrun pressed ");

    srl_fileTimer->setInterval(qt::i_s(ui->Edit_timerDelay->text()));
    ui->tbr_delay->setValue(qt::i_s(ui->Edit_timerDelay->text()));

}

vo::t MainWindow::on_tbr_delay_sliderMoved(int position)
{

    qDebug() << "position" << position << endl;
    emit log("position" + position);

    ui->Edit_timerDelay->setPlaceholderText(qt::s_i(position));
    srl_fileTimer->setInterval(position);

}

vo::t MainWindow::on_edPath_returnPressed()
{

    log(__func__);

    cb_fn(ui->edPath->text());

}

vo::t MainWindow::on_btnClear_clicked()
{

    ui->lv_commands->clear();

}

vo::t MainWindow::on_offset_readOffset()
{

    emit readOffset();

}

vo::t MainWindow::on_offset_saveOffset()
{

    //log(save_pai3(OFFSET, 6));
    emit saveHomeSet();

}

vo::t MainWindow::on_usb_mmf_mmfClicked()
{

    emit mmfClicked();
}

vo::t MainWindow::on_edit_firstSerial_returnPressed()
{
    emit openFirstSerial("COM" + ui->edit_firstSerial->text());
}

vo::t MainWindow::on_edit_secondSerial_returnPressed()
{
    emit openSecondSerial("COM" + ui->edit_secondSerial->text());
}

vo::t MainWindow::i_cb(QList<int>& ids_ ,QListWidget* _lw, i::t endNo, i::t startNo = 0){

    if(startNo == endNo) return;

    if(_lw->item(startNo)->checkState() == Qt::Checked)    ids_.push_back(startNo);

    return i_cb(ids_, _lw, endNo, ++startNo);
}

vo::t MainWindow::ids_lili(QList<int>& ids_ ,QList<int> _ilLeg, QList<int> _ilMotor){

    for(i::t i : _ilLeg){
        for(i::t j : _ilMotor){
            ids_.push_back(i * 3 + j);
        }
    }

}

vo::t MainWindow::on_pushButton_clicked()
{
    QList<int> ilLeg;
    QList<int> ilMotor;

    i_cb(ilLeg, ui->lw_legs, 6);
    i_cb(ilMotor, ui->lw_motors, 3);

    emit setIds(ilLeg, ilMotor);

}

vo::t MainWindow::on_btn_reset_clicked()
{
    for(z::t i(1) ; i < 7 ; ++i){

        int row   = i - 1;

        i::t iFirstLeg  =  0  -  OFFSET[row][0];
        i::t iSecondLeg =  0  -  OFFSET[row][1];
        i::t iThirdLeg  =  0  -  OFFSET[row][2];

        QList<int> qai3 = { iFirstLeg , iSecondLeg , iThirdLeg };

        emit send_clicked( qai3,i );
   }
}

vo::t MainWindow::on_actionE_xit_triggered()
{
    close();
}

vo::t MainWindow::on_actionOpen_App_Folder_triggered()
{
    qDebug() << "open app folder";
    QDesktopServices::openUrl( QUrl::fromLocalFile(QDir::currentPath()) );
}

vo::t MainWindow::on_btn_tempSave_clicked()
{

    emit tempSave(ui->edit_saveName->text());

}

void MainWindow::on_cb_commands_activated(const QString &arg1)
{

    qDebug() << arg1 << endl;
    load_commands(arg1);

}

void MainWindow::on_cb_release_clicked(bool checked)
{
    qDebug() << checked;

    if(checked){
        for(z::t i(0) ; i < ui->lw_legs->count() ; ++i){

            ui->lw_legs->item(i)->setCheckState(Qt::CheckState::Checked);
            qDebug() << "checked..!" << endl;

        }
        for(z::t i(0) ; i < ui->lw_motors->count() ; ++i){

            ui->lw_motors->item(i)->setCheckState(Qt::CheckState::Checked);
            qDebug() << "checked..!" << endl;
        }

    }else{
        for(z::t i(0) ; i < ui->lw_legs->count() ; ++i){

            ui->lw_legs->item(i)->setCheckState(Qt::CheckState::Unchecked);
            qDebug() << "unchecked..!" << endl;
        }
        for(z::t i(0) ;  i < ui->lw_motors->count() ; ++i){

            ui->lw_motors->item(i)->setCheckState(Qt::CheckState::Unchecked);
            qDebug() << "unchecked..!" << endl;
        }
    }

    qDebug() << __func__ << "end" ;

}

void MainWindow::on_btn_timeClear_clicked()
{
    ui->edit_time->clear();
}



























////////////////////////////////////////HOME////////////////////////////////////////////























/////////////////////버린 함수 //////////////////////////////////////
/*

b::t Dll_usb_mmf01stl::srl_pai3(int** _pai3){


    isFinished = !isFinished;

    pai3::p cmd = pai3_pp(_pai3);

    QFutureSynchronizer<b::t> synchronizer;

    for(i::t row : rows){
        synchronizer.addFuture(QtConcurrent::run([=](){

                i::a3 ia3 = {0, };

                ia3_pai3(ia3, cmd, row);
                thsri_pai3(ia3, row);

                return b::T1;
        }));
    }

    emit log("");
    emit log("end loop...");
    emit log("");

    synchronizer.waitForFinished();

    isFinished = !isFinished;

    delete[] cmd;

    return b::T1;

}




b::t Dll_usb_mmf01stl::thsri_pai3(i::A3 _ai3, h::T _row){

    QFutureSynchronizer<b::t> synchronizer;

    for(i::t col : cols){

        int id = (_row + 1) * 10 + (col + 1);

        thread_pai3(synchronizer, _ai3, id, col);
    }

    synchronizer.waitForFinished();
    return b::T0;

}


vo::t Dll_usb_mmf01stl::thread_pai3(QFutureSynchronizer<b::t>& _synchronizer, i::A3 _ai3, i::t _id, i::t _row){

    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

        while(1){

            if( !((_ai3[_row] - 100) < i_srl(_id) && (_ai3[_row] + 100) >  i_srl(_id))  ){ qDebug("_ai3[i] != i_srl(id)"); srl_i(_ai3[_row], _id);}
            else { break; }

        }

        emit log("id  " + qt::s_i(_id) + "  _ai3[i]  " + qt::s_i(_ai3[_row]) + "  i_srl(id)  " + qt::s_i(i_srl(_id)));

    return b::T1;

    }));

}

vo::t MainWindow::thsrl_pai36(pai3::p _commands){


    QList<int> li_Val = li_legsVal();

    pai3::p temp_pai3 = new i::t[6][3]{{0},{0},{0},{0},{0} };

    memcpy(temp_pai3, _commands, 18 * 4); // 실제 멤버변수에 있는 pai3에는 변화가 가지 않도록 한다.

    subOffset(temp_pai3, OFFSET);

    check_commandValid(temp_pai3, li_Val[0],  li_Val[1], li_Val[2], li_Val[3], li_Val[4], li_Val[5]);

    emit thsrl_file(pp_pai3(temp_pai3));

}


vo::t Dll_usb_mmf01stl::thread_pai3(QFutureSynchronizer<b::t>& _synchronizer, i::A3 _ai3, i::t _id, i::t _row){

    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

        while(1){

            if( !((_ai3[_row] - 100) < i_srl(_id) && (_ai3[_row] + 100) >  i_srl(_id))  ){ qDebug("_ai3[i] != i_srl(id)"); srl_i(_ai3[_row], _id);}
            else { break; }

        }

        emit log("id  " + qt::s_i(_id) + "  _ai3[i]  " + qt::s_i(_ai3[_row]) + "  i_srl(id)  " + qt::s_i(i_srl(_id)));
    return b::T1;

    }));

}


b::t Dll_usb_mmf01stl::thsri_pai3(i::A3 _ai3, h::T _row){

    QFutureSynchronizer<b::t> synchronizer;

    for(i::t col : cols){

        int id = (_row + 1) * 10 + (col + 1);

        thread_pai3(synchronizer, _ai3, id, col);

    }

    synchronizer.waitForFinished();
    return b::T0;

}

b::t Dll_usb_mmf01stl::srl_pai3(int** _pai3){

    isFinished = !isFinished;

    pai3::p cmd = pai3_pp(_pai3);
    QFutureSynchronizer<b::t> synchronizer;

    for(i::t row : rows){
        synchronizer.addFuture(QtConcurrent::run([=](){

                i::a3 ia3 = {0, };

                ia3_pai3(ia3, cmd, row);
                thsri_pai3(ia3, row);

                return b::T1;
        }));
    }

    emit log("");
    emit log("end loop...");
    emit log("");

    synchronizer.waitForFinished();
    isFinished = !isFinished;

    delete[] cmd;

    return b::T1;

}



*/



void MainWindow::on_btn_CalcDiff_clicked()
{
    QString diff;
    QMetaObject::invokeMethod(stl->oWorker, "calc_diff", Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QString, diff));

    qDebug() << "diff : " << diff;
    ui->edit_diff->setText(diff);

}



void MainWindow::on_btn_setLegsToZero_clicked()
{
    emit legsToOrigin();
}
