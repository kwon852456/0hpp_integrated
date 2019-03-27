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

    connect(this,          &MainWindow::thsrl_cds,        stl,         &Dll_usb_mmf01stl::srl_pai6           );
    connect(this,          &MainWindow::thsrl_file,       stl,         &Dll_usb_mmf01stl::srl_pai6           );

    connect(this,          &MainWindow::send_clicked,     stl,         &Dll_usb_mmf01stl::thsri_qai36        );
    connect(this,          &MainWindow::readOffset,       stl,         &Dll_usb_mmf01stl::OnReadOffset       );
    connect(this,          &MainWindow::mmfClicked,       stl,         &Dll_usb_mmf01stl::onMmfClicked       );
    connect(this,          &MainWindow::openFirstSerial,  stl,         &Dll_usb_mmf01stl::openFirstSerial    );
    connect(this,          &MainWindow::openSecondSerial, stl,         &Dll_usb_mmf01stl::openSecondSerial   );
    connect(this,          &MainWindow::setIds,           stl,         &Dll_usb_mmf01stl::setIds             );
    connect(this,          &MainWindow::tempSave,         stl,         &Dll_usb_mmf01stl::tempSave           );
    connect(this,          &MainWindow::saveHomeSet,      stl,         &Dll_usb_mmf01stl::saveHomeSet        );
    connect(this,          &MainWindow::loadHomeset,      stl,         &Dll_usb_mmf01stl::loadHomeset        );
    connect(this,          &MainWindow::legsToOrigin,     stl,         &Dll_usb_mmf01stl::legsToOrigin       );
    connect(this,          &MainWindow::connectSixSrlNo,  stl,         &Dll_usb_mmf01stl::connectSixSrlNo    );
    connect(this,          &MainWindow::write_log,        ui->usb_log, &Usb_log::setlog);


    connect(stl,           &Dll_usb_mmf01stl::showOffset,     this,    &MainWindow::onShowOffset       );
    connect(stl,           &Dll_usb_mmf01stl::log,            this,    &MainWindow::write_log          );
    connect(stl,           &Dll_usb_mmf01stl::thsri_qai36End, this,    &MainWindow::thsri_qai36End     );
    connect(stl,           &Dll_usb_mmf01stl::timeTaken,      this,    &MainWindow::timeTaken          );
    connect(stl,           &Dll_usb_mmf01stl::setHomeSet,     this,    &MainWindow::setHomeSet         );
    connect(srl_fileTimer, &QTimer::timeout,                  this,    &MainWindow::fileTimerTimeOut   );
    connect(sendTimer,     &QTimer::timeout,                  this,    &MainWindow::srl_ai3            );

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
    else    delete[] command;

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

        sThreadLeg1 = new QThread();
        sThreadLeg2 = new QThread();
        sThreadLeg3 = new QThread();
        sThreadLeg4 = new QThread();
        sThreadLeg5 = new QThread();
        sThreadLeg6 = new QThread();


        sWorker = new SerialWorker();
        oWorker = new OffsetWorker();

        sWorkerLeg1 = new SerialWorker();
        sWorkerLeg2 = new SerialWorker();
        sWorkerLeg3 = new SerialWorker();
        sWorkerLeg4 = new SerialWorker();
        sWorkerLeg5 = new SerialWorker();
        sWorkerLeg6 = new SerialWorker();


        sWorker->moveToThread(sThread);
        oWorker->moveToThread(mThread);

        sWorkerLeg1->moveToThread(sThreadLeg1);
        sWorkerLeg2->moveToThread(sThreadLeg2);
        sWorkerLeg3->moveToThread(sThreadLeg3);
        sWorkerLeg4->moveToThread(sThreadLeg4);
        sWorkerLeg5->moveToThread(sThreadLeg5);
        sWorkerLeg6->moveToThread(sThreadLeg6);



        connect(this,    &Dll_usb_mmf01stl::write_cmd ,              sWorker,     &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);

        connect(this,    &Dll_usb_mmf01stl::write_cmdToFirstLeg  ,   sWorkerLeg1, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::write_cmdToSecondLeg ,   sWorkerLeg2, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::write_cmdToThirdLeg  ,   sWorkerLeg3, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::write_cmdToFourthLeg ,   sWorkerLeg4, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::write_cmdToFifthLeg  ,   sWorkerLeg5, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);
        connect(this,    &Dll_usb_mmf01stl::write_cmdToSixthLeg  ,   sWorkerLeg6, &SerialWorker::onWrite_cmd, Qt::BlockingQueuedConnection);

        connect(this,    &Dll_usb_mmf01stl::openFirstSerial  , sWorker    , &SerialWorker::setSerialPort  );

        connect(this,    &Dll_usb_mmf01stl::openFirstLegPort , sWorkerLeg1, &SerialWorker::setSerialPort  );
        connect(this,    &Dll_usb_mmf01stl::openSecondLegPort, sWorkerLeg2, &SerialWorker::setSerialPort  );
        connect(this,    &Dll_usb_mmf01stl::openThirdLegPort , sWorkerLeg3, &SerialWorker::setSerialPort  );
        connect(this,    &Dll_usb_mmf01stl::openFourthLegPort, sWorkerLeg4, &SerialWorker::setSerialPort  );
        connect(this,    &Dll_usb_mmf01stl::openFifthLegPort , sWorkerLeg5, &SerialWorker::setSerialPort  );
        connect(this,    &Dll_usb_mmf01stl::openSixthLegPort , sWorkerLeg6, &SerialWorker::setSerialPort  );



        connect(this,    &Dll_usb_mmf01stl::mmfClicked,       sWorker, &SerialWorker::onMmfCheck_clicked  );
        connect(this,    &Dll_usb_mmf01stl::tempSave,         sWorker, &SerialWorker::tempSave            );


        connect(this,    &Dll_usb_mmf01stl::readOffset,       oWorker, &OffsetWorker::onReadOffset        );
        connect(this,    &Dll_usb_mmf01stl::openSecondSerial, oWorker, &OffsetWorker::setSerialPort       );
        connect(this,    &Dll_usb_mmf01stl::saveHomeSet,      oWorker, &OffsetWorker::saveHomeSet         );
        connect(this,    &Dll_usb_mmf01stl::loadHomeset,      oWorker, &OffsetWorker::loadHomeset         );

        connect(sWorkerLeg1, &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(sWorkerLeg2, &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(sWorkerLeg3, &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(sWorkerLeg4, &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(sWorkerLeg5, &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(sWorkerLeg6, &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(sWorker,     &SerialWorker::log,                 this, &Dll_usb_mmf01stl::log             );
        connect(oWorker,     &OffsetWorker::log,                 this, &Dll_usb_mmf01stl::log             );

        connect(sWorker, &SerialWorker::showOffset,              this, &Dll_usb_mmf01stl::showOffset      );
        connect(oWorker, &OffsetWorker::setHomeSet,              this, &Dll_usb_mmf01stl::setHomeSet      );



        sThread->start();
        mThread->start();

        sThreadLeg1->start();
        sThreadLeg2->start();
        sThreadLeg3->start();
        sThreadLeg4->start();
        sThreadLeg5->start();
        sThreadLeg6->start();
}

Dll_usb_mmf01stl::~Dll_usb_mmf01stl(){

    sThread->quit();
    sThread->wait();

};

vo::t Dll_usb_mmf01stl::srl_i(i::T _iDegree, i::T _id, i::T _velocity = 32){

    cmd::t command;
    cmd_id(command, _iDegree,  _id, _velocity);

    c::p pCmd = reinterpret_cast<c::p>(command);

    i::T legNo = _id / 10;

    switch (legNo){

    case 1:

        emit write_cmdToFirstLeg(pCmd);  //id에 따라서 다른 시그널 발생. 해당 함수는 현재 마지막 스레드(모터 하나 담당) 안에서 돌고 있음..!
        break;

    case 2:

        emit write_cmdToSecondLeg(pCmd);
        break;

    case 3:

        emit write_cmdToThirdLeg(pCmd);
        break;

    case 4:

        emit write_cmdToFourthLeg(pCmd);
        break;

    case 5:

        emit write_cmdToFifthLeg(pCmd);
        break;

    case 6:

        emit write_cmdToSixthLeg(pCmd);
        break;

    default :
        qDebug() << "legNo in srl_i is wrong..!";

    }
}

qt::yar::t yar_req(i::t _id){

    req::t request; req_id(request, _id);
    c::p pReq = reinterpret_cast<c::p>(request);

    return qt::yar::t::fromRawData(pReq,req::Z);

}

i::t Dll_usb_mmf01stl::i_srl(i::t _id){

    qDebug() << "i_srl" << " _id " << _id << " Thread " << QThread::currentThread();

    isIsrlFinished = false;
    int recvEncVal;
    qt::yar::t arr = yar_req(_id);


    i::T legNo = _id / 10;

    switch (legNo) {

    case 1:

        QMetaObject::invokeMethod(sWorkerLeg1, "onWrite_req", Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(int, recvEncVal),
                                  Q_ARG(QByteArray, arr),
                                  Q_ARG(int, _id));

        break;

    case 2:

        QMetaObject::invokeMethod(sWorkerLeg2, "onWrite_req", Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(int, recvEncVal),
                                  Q_ARG(QByteArray, arr),
                                  Q_ARG(int, _id));

        break;

    case 3:

        QMetaObject::invokeMethod(sWorkerLeg3, "onWrite_req", Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(int, recvEncVal),
                                  Q_ARG(QByteArray, arr),
                                  Q_ARG(int, _id));

        break;

    case 4:

        QMetaObject::invokeMethod(sWorkerLeg4, "onWrite_req", Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(int, recvEncVal),
                                  Q_ARG(QByteArray, arr),
                                  Q_ARG(int, _id));

        break;

    case 5:

        QMetaObject::invokeMethod(sWorkerLeg5, "onWrite_req", Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(int, recvEncVal),
                                  Q_ARG(QByteArray, arr),
                                  Q_ARG(int, _id));

        break;

    case 6:

        QMetaObject::invokeMethod(sWorkerLeg6, "onWrite_req", Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(int, recvEncVal),
                                  Q_ARG(QByteArray, arr),
                                  Q_ARG(int, _id));

        break;

    default :

        qDebug() << "legNo in srl_i is wrong..!";

    }

    qDebug() << "recvEncVal : " << recvEncVal;

    if(recvEncVal == 99999){ qDebug() << "checkSum has been broken...!"; };

    isIsrlFinished = true;

    return recvEncVal;

}

vo::t Dll_usb_mmf01stl::thread_pai6(QFutureSynchronizer<b::t>& _synchronizer, i::A6 _ai6, i::t _id, i::t _col){

    if(_ai6[_col + 3] == 0){ qDebug() << " Motor speed zero on id : " << _id;  return; }

    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

        i::t i = 0;
        while(1){

            i::t current = i_srl(_id);

            if( !( (_ai6[_col] - 100) < current && (_ai6[_col] + 100) >  current) ){  srl_i(_ai6[_col], _id, _ai6[_col + 3]);  }
            else {   break;  }

            qDebug() << "_ai6[_col]" << _ai6[_col] << "current" << current;

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



vo::t Dll_usb_mmf01stl::thread_cmd(QFutureSynchronizer<b::t>& _synchronizer, i::A6 _ai6, i::t _id, i::t _col){


}


b::t Dll_usb_mmf01stl::thsri_cmd(i::A6 _ai6, h::T _row){




    QFutureSynchronizer<void> synchronizer;

    const QList<int> col = cols;

    for(i::T motor : col){

        qDebug() << "col : " << motor << " current Thread : " << QThread::currentThread();
        int id = (((_row + 1) * 10) + (motor + 1));

        synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

            qDebug() << "current Thread : " << QThread::currentThread();
            srl_i(_ai6[motor], id, _ai6[motor + 3]);

            emit log("CMD ->  id  " + qt::s_i(id) + "  send val : " + qt::s_i(_ai6[motor]) + " _ai6[_col + 3] " + qt::s_i(_ai6[motor + 3]));


        }));


    Sleep(10);
    }

    synchronizer.waitForFinished();

    return b::T0;

}

b::t Dll_usb_mmf01stl::srl_commands(pai6::p _commands){


    qDebug() << __func__;

    QFutureSynchronizer<b::t> synchronizer;


    for(i::T row : rows){

        synchronizer.addFuture(QtConcurrent::run([=](){

                qDebug() << "one leg row : " << row << QThread::currentThread();

                i::a6 ia6 = {0, };
                ia6_pai6(ia6, _commands, row);
                if(ia6[3] + ia6[4] + ia6[5] == 0){ qDebug() << "speed for three legs are all zero"; return b::T0; }
                thsri_cmd(ia6, row);

                return b::T1;

        }));
        Sleep(10);
    }

    synchronizer.waitForFinished();

    return true;

}


vo::t Dll_usb_mmf01stl::thread_motorArrived(QFutureSynchronizer<b::t>& _synchronizer, pai6::p& _ai6, i::t _id, i::t _col){


    if(_ai6[_col + 3] == 0){ qDebug() << " Motor speed zero on id : " << _id;  return; }

    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드

        i::t encVal = i_srl(_id);



        emit log("id  " + qt::s_i(_id) + "  motor Encoder value : " + qt::s_i(encVal) );

        if((*_ai6)[_col] - 100 < encVal && encVal < (*_ai6)[_col] + 100){ (*_ai6)[_col + 3] = 0; }
        qDebug() << "(*_ai6)[_col] : " << (*_ai6)[_col] << "encVal : " << encVal << "(*_ai6)[_col + 3] = 0 : " << (*_ai6)[_col + 3] ;

    return b::T1;

    }));


}




b::t Dll_usb_mmf01stl::thsri_motorArrived(pai6::p& _ai6, h::T _row){


    QFutureSynchronizer<b::t> synchronizer;


    for(i::t col : cols){

        int id = (_row + 1) * 10 + (col + 1);
        thread_motorArrived(synchronizer, _ai6, id, col);

    }

    synchronizer.waitForFinished();

    return b::T0;

}

vo::t Dll_usb_mmf01stl::thread_qai36(QFutureSynchronizer<b::t>& _synchronizer, QList<int> _qai3, i::t _id, i::t _row){

    _synchronizer.addFuture(QtConcurrent::run([=](){  // 3번 도는 쓰레드


        //리셋은 보내고 끝
        srl_i(_qai3[_row], _id);
        emit log("reset sented ID: "+ qt::s_i(_id) +" ..value is : " + qt::s_i(_qai3[_row]));

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


b::t Dll_usb_mmf01stl::check_motorArrived(pai6::p _commands){


    qDebug() << __func__;

    QFutureSynchronizer<b::t> synchronizer;


    for(i::T row : rows){
        synchronizer.addFuture(QtConcurrent::run([=](){

                pai6::p ia6 = nil;
                ip6_pai6(ia6, _commands, row);

                if((*ia6)[3] + (*ia6)[4] + (*ia6)[5] == 0){ qDebug() << "speed for three legs are all zero"; return b::T0; }
                thsri_motorArrived(ia6, row);

                return b::T1;
        }));
    }

    synchronizer.waitForFinished();

    return true;
}

b::t Dll_usb_mmf01stl::isSpeedZero_cmd(pai6::p _pai6){
    i::t sum = 0;

    for(i::T row : rows){
        for(i::t colm : cols){
            sum += _pai6[row][colm + 3];
        }
    }


    return sum == 0;
}

b::t Dll_usb_mmf01stl::srl_pai6(int** _pai6){

    qDebug() << __func__ ;

    pai6::p cmd = pai6_pp(_pai6);

    timer.restart();
    isFinished = !isFinished;


    i::t tryCounter = 0;

    while(1){


        srl_commands(cmd);
        check_motorArrived(cmd);

        con_pai6(cmd);

        if(isSpeedZero_cmd(cmd)) { break; };

        qDebug() << "isSpeedZero_cmd(cmd) : false";


        if(tryCounter++ > 0) { qDebug() << "tryCounter : " << tryCounter ;  }


    }

    emit timeTaken(timer.elapsed());
    isFinished = !isFinished;

    emit log("");
    delete[] cmd;
    return b::T1;

}



vo::t Dll_usb_mmf01stl::OnReadOffset(){

    emit log(__func__);
    emit readOffset();
}

bool checkValid_pai3(pai3::p _pai6){
    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            if(_pai6[i][j] > 50000){ return false; }
        }
    }

    return true;

}

vo::t Dll_usb_mmf01stl::onMmfClicked(){
    if(!isIsrlFinished) return;
    QFuture<void> mmfResult = QtConcurrent::run([this](){

        QList<int> ids = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43, 51, 52, 53, 61, 62, 63 };
        i::t tempArr[6][3] = { {0,},{0,},{0,},{0,},{0,},{0,} };
        pai3::p encVal = tempArr;

        for(i::t id : ids){
             int row = (id / 10) -1;
             int colm = (id % 10) -1;

             encVal[row][colm] = i_srl(id) + OFFSET[row][colm];
        }

        con_pai3(encVal);
        emit log(qs_pai3(encVal));

        if(checkValid_pai3(encVal)){

            mmf_pai3Val(encVal);

        }else{

            for(z::t i(0) ; i < 5 ; ++i){ qDebug() << "BROKEN CHECK SUM HAS BEEN DETECTED WRTING PAI3 TO MMF PAUSED.....!"; }

        }
    });
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

    if(vs_s(qt::s_qs(sDiff),' ').size() < 18){ qDebug() << ("size of diff < 18");  return; }

    pai6::p diff = pai6_pai3(pai3_qs(sDiff), 10);

    pai3_pai6(OFFSET, diff);  // OFFSET에다가 diff를 할당..!


    srl_pai6(pp_pai6(diff));
}


vo::t Dll_usb_mmf01stl::connectSixSrlNo(QList<int> _legsPortNo){

    qDebug() << __func__;

    qDebug() << "_legsPortNo : " << _legsPortNo;

    emit openFirstLegPort ("COM" + qt::s_i(_legsPortNo[0]));
    emit openSecondLegPort("COM" + qt::s_i(_legsPortNo[1]));
    emit openThirdLegPort ("COM" + qt::s_i(_legsPortNo[2]));
    emit openFourthLegPort("COM" + qt::s_i(_legsPortNo[3]));
    emit openFifthLegPort ("COM" + qt::s_i(_legsPortNo[4]));
    emit openSixthLegPort ("COM" + qt::s_i(_legsPortNo[5]));

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

    //qDebug() << __func__ << "in MainWindow ";
    if(!port->isOpen()) return 99999;
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

    port->close();
    port->setPortName(_comPort);

    if(!port->open(QIODevice::ReadWrite)){

        qDebug() << "Serial connect failed : " + _comPort << endl;
        emit log("Serial connect failed : " + _comPort);

    }else{

        qDebug() << "Serial opened : " + _comPort << endl;
        emit log("Serial opened : " + _comPort);

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

    if(tempHomeset == nil){ emit log("Second Encoder Timeout..! "); return;}

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

    srl->close();
    srl->setPortName(_comPort);

    if(!srl->open(QIODevice::ReadWrite)){

        emit log("Serial connect falled : " + _comPort);

    }else{

        emit log("Serial opened : " + _comPort);
    }

}



b::t check_diffValid(pai3::p _diff){
    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            if(abs(_diff[i][j]) > 8000){
                return false;
            }
        }
    }
    return true;
}

qt::s::t OffsetWorker::calc_diff(){
    pai3::p tempHomeSet =  pai3_srl(srl);

    if(tempHomeSet == nil){ emit log("Second Encoder TimeOut In Fuc calc_diff...!"); return nil; }



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

    if(!check_diffValid(diff)){ memset(diff, 0x00, 4 * 18); emit log("at least one (value > 8000) detected in diff "); return nil; }

    return qs_pai3H(diff);


}
qt::s::t OffsetWorker::qs_diff(){

    return qs_pai3H(diff);

}


























//ui 세팅 관련 메소드 //

vo::t MainWindow::set_tbrs(){

    ui->tbr_firstLeg->setMinimum( qt::i_s(ui->edit_min_firstleg->text()) );
    ui->tbr_secondLeg->setMinimum(qt::i_s(ui->edit_min_secondleg->text()));
    ui->tbr_thirdLeg->setMinimum( qt::i_s(ui->edit_min_thirdLeg->text()) );

    ui->tbr_firstLeg->setMaximum( qt::i_s(ui->edit_max_firstLeg->text()) );
    ui->tbr_secondLeg->setMaximum(qt::i_s(ui->edit_max_secondLeg->text()));
    ui->tbr_thirdLeg->setMaximum( qt::i_s(ui->edit_max_thirdLeg->text()) );

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

    if( ui->lv_legs->currentItem() != nullptr ){

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
    //qDebug() << __func__;
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
    if(path == qt::s::T0){ return; }
    emit loadHomeset(path);

}

vo::t MainWindow::tbrs_legNo(i::T _legNo){


    QList<int> recvEncVal;
    switch (_legNo){

    case 1:

        QMetaObject::invokeMethod(stl->sWorkerLeg1, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                            Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                              Q_ARG(int, _legNo));
        break;

    case 2:

        QMetaObject::invokeMethod(stl->sWorkerLeg2, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                            Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                              Q_ARG(int, _legNo));
        break;

    case 3:

        QMetaObject::invokeMethod(stl->sWorkerLeg3, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                            Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                              Q_ARG(int, _legNo));
        break;

    case 4:

        QMetaObject::invokeMethod(stl->sWorkerLeg4, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                            Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                              Q_ARG(int, _legNo));
        break;

    case 5:

        QMetaObject::invokeMethod(stl->sWorkerLeg5, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                            Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                              Q_ARG(int, _legNo));
        break;

    case 6:

        QMetaObject::invokeMethod(stl->sWorkerLeg6, "onLv_clicked", Qt::BlockingQueuedConnection,
                                                            Q_RETURN_ARG(QList<int>, recvEncVal),
                                                                              Q_ARG(int, _legNo));
        break;

    default :

        qDebug() << "legNo in srl_i is wrong..!";

    }

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

    ui->cb_commands->clear();
    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());
    if(path == qt::s::T0){ return; }
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

void MainWindow::on_btn_legCon_clicked()
{
    QList<int> srlNo;

    srlNo.append(qt::i_s(ui->cb_leg1->currentText()));
    srlNo.append(qt::i_s(ui->cb_leg2->currentText()));
    srlNo.append(qt::i_s(ui->cb_leg3->currentText()));
    srlNo.append(qt::i_s(ui->cb_leg4->currentText()));
    srlNo.append(qt::i_s(ui->cb_leg5->currentText()));
    srlNo.append(qt::i_s(ui->cb_leg6->currentText()));

    emit openSecondSerial("COM" + ui->cb_enc2->currentText());

    emit connectSixSrlNo(srlNo);
}

void MainWindow::on_btn_portSave_clicked()
{
    QString temp;
    QString port;

    port.append(ui->cb_leg1->currentText() + " ");
    port.append(ui->cb_leg2->currentText() + " ");
    port.append(ui->cb_leg3->currentText() + " ");
    port.append(ui->cb_leg4->currentText() + " ");
    port.append(ui->cb_leg5->currentText() + " ");
    port.append(ui->cb_leg6->currentText() + " ");
    port.append(ui->cb_enc2->currentText() + " ");

    QFile file("ports.ini");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File read failed";
    }

    QTextStream out(&file);
    qDebug() << port << endl;
    out << port;

}

void clearComboBox(QComboBox* _box){

    _box->clear();

}

void setComboBox(QComboBox* _box, qt::s::T _text){
    _box->addItem(_text);
}

void MainWindow::on_btn_portLoad_clicked()
{

    QString path = QFileDialog::getOpenFileName(this,"Find Files",QDir::currentPath());

    if(path == qt::s::T0){ return; }

    QFile file(path, this);

    file.open(QIODevice::ReadWrite);

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');

    for(std::string s : vs){
        qDebug() << QString::fromStdString(s);
    }

    clearComboBox(ui->cb_leg1);
    clearComboBox(ui->cb_leg2);
    clearComboBox(ui->cb_leg3);
    clearComboBox(ui->cb_leg4);
    clearComboBox(ui->cb_leg5);
    clearComboBox(ui->cb_leg6);
    clearComboBox(ui->cb_enc2);


    setComboBox(ui->cb_leg1, qt::qs_s(vs[0]));
    setComboBox(ui->cb_leg2, qt::qs_s(vs[1]));
    setComboBox(ui->cb_leg3, qt::qs_s(vs[2]));
    setComboBox(ui->cb_leg4, qt::qs_s(vs[3]));
    setComboBox(ui->cb_leg5, qt::qs_s(vs[4]));
    setComboBox(ui->cb_leg6, qt::qs_s(vs[5]));
    setComboBox(ui->cb_enc2, qt::qs_s(vs[6]));


}

void MainWindow::on_btn_serialSearch_clicked()
{

    liPorts.clear();
    clearComboBox(ui->cb_leg1);
    clearComboBox(ui->cb_leg2);
    clearComboBox(ui->cb_leg3);
    clearComboBox(ui->cb_leg4);
    clearComboBox(ui->cb_leg5);
    clearComboBox(ui->cb_leg6);
    clearComboBox(ui->cb_enc2);


    QSerialPort* srl = new QSerialPort(this);
    srl->setBaudRate    (QSerialPort::Baud115200);
    srl->setDataBits    (QSerialPort::Data8);
    srl->setParity      (QSerialPort::NoParity);
    srl->setStopBits    (QSerialPort::OneStop);
    srl->setFlowControl (QSerialPort::NoFlowControl);

    liPorts.append(-1);

    for(z::t i(0) ; i < 50 ; ++i){
        srl->setPortName    ("COM" +  qt::s_i(i));

        if(!srl->open       (QIODevice  ::ReadWrite)){


        }else{

            qDebug() << "Serial opened" << endl;
            liPorts.append(i);

        }
        srl->close();

    }

    for(i::T port : liPorts){

        ui->cb_leg1->addItem(qt::s_i(port));
        ui->cb_leg2->addItem(qt::s_i(port));
        ui->cb_leg3->addItem(qt::s_i(port));
        ui->cb_leg4->addItem(qt::s_i(port));
        ui->cb_leg5->addItem(qt::s_i(port));
        ui->cb_leg6->addItem(qt::s_i(port));
        ui->cb_enc2->addItem(qt::s_i(port));

    }

    ui->edit_serialPorts->setText(qs_li(liPorts));


}

void MainWindow::on_btn_logClear_clicked()
{
    ui->usb_log->clearLog();
}

void MainWindow::on_edit_serialPorts_returnPressed()
{
    qDebug() << __func__;

    qt::s::T serialPorts = ui->edit_serialPorts->text();

    std::vector<std::string> vs = vs_s(qt::s_qs(serialPorts), ' ');

    for(std::string s : vs ){
        qDebug() << QString::fromStdString(s);
    }

    if(vs.size() == 7 ){

        liPorts.clear();
        clearComboBox(ui->cb_leg1);
        clearComboBox(ui->cb_leg2);
        clearComboBox(ui->cb_leg3);
        clearComboBox(ui->cb_leg4);
        clearComboBox(ui->cb_leg5);
        clearComboBox(ui->cb_leg6);
        clearComboBox(ui->cb_enc2);


        ui->cb_leg1->addItem(qt::qs_s(vs[0]));
        ui->cb_leg2->addItem(qt::qs_s(vs[1]));
        ui->cb_leg3->addItem(qt::qs_s(vs[2]));
        ui->cb_leg4->addItem(qt::qs_s(vs[3]));
        ui->cb_leg5->addItem(qt::qs_s(vs[4]));
        ui->cb_leg6->addItem(qt::qs_s(vs[5]));
        ui->cb_enc2->addItem(qt::qs_s(vs[6]));

    }else{
        log(" serial port names != 7 ");
    }




}
