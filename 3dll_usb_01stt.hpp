#ifndef DLL_USB_OFFSET01STT_H
#define DLL_USB_OFFSET01STT_H

#include "QtSerialPort/QSerialPort"
#include <QMainWindow>
#include <QtConcurrent>
#include <QFileDialog>
#include <QMutex>
#include <QThread>
#include <6qtu9.hpp>
#include "ui_mainwindow.h"

using namespace rv2;

namespace rv2{
namespace qt {///

    namespace srl {///
        typedef QSerialPort t;
        typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
    //    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
    //    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
    //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
        T T0("");
    }///
    ///
    namespace yar {///
        typedef QByteArray t;
        typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
    //    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
        typedef QByteArrayList li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
    //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
        T T0("");
    }///

    namespace qmutx{//
        typedef QMutex t;
        typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
     }///

    namespace thr {///

        typedef QThread t;
        typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
        //    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
        //    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
        //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
        T nill;
    }///

}///

namespace cmd {///
    typedef y::t t[11];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
//    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
//    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
//    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///

namespace req {///
    typedef y::t t[6];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
//    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
//    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
//    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///
namespace res {///
    typedef y::t t[6];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
//    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
//    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
//    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///

namespace rep {///
    typedef y::t t[12];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
    //    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
    //    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
    //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///

}
qt::qmutx::t mutForSerial;
i::t debugMode = 1;

qt::srl::p CreateSrl(QObject *parent = nullptr, i::T _portNo = 0){

    QSerialPort* srl = new QSerialPort(parent);
    srl->setPortName("COM"+ qt::s_i(_portNo));
    srl->setBaudRate(QSerialPort::Baud115200);
    srl->setDataBits(QSerialPort::Data8);
    srl->setParity(QSerialPort::NoParity);
    srl->setStopBits(QSerialPort::OneStop);
    srl->setFlowControl(QSerialPort::NoFlowControl);

    if(!srl->open(QIODevice::ReadWrite)){

        qDebug() << "Serial Worker Created.." << endl;

    }else{

        qDebug() << "Serial opened" << endl;

    }

    return srl;

}

qt::thr::p thr_Srl(qt::srl::p _Srl, QObject *parent = nullptr){

     qt::thr::p qthr_ = new qt::thr::t;
    _Srl = CreateSrl(parent);
    _Srl->moveToThread(qthr_);


    return qthr_;

}




qt::yar::li yarl_yar(qt::yar::t _yar){

    qDebug() << __func__;

    qt::yar::li li_;
    qt::yar::t temp;
    i::t count = 0;

    for(auto i = _yar.cbegin() ; i != _yar.cend() ; ++i ){
        temp.clear();
        if(*i == '['){
            do{
                temp.append(*i);
                if(i != _yar.cend() - 1) ++i;
                else break;

            }while(*i != ']' );

            if(*i == ']'){
                temp.append(*i);
                li_.append(temp);
            }
        }
    }

    qDebug()<< "end yarl_yar ";
    return li_;
}

vo::t debugMsg(QString _msg){ if(debugMode == 1) qDebug() << _msg << endl; }

void con_yar(qt::yar::t _yar){

    debugMsg("data from Serial..");

    debugMsg(QString::fromStdString(_yar.toStdString()));

    debugMsg("end data from Serial..");
}



std::string qs_yar(qt::yar::t _yar){

    return _yar.toStdString();

}



void con_pai3(pai3::p _pai3){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < 6 ; ++i){
        temp.clear(); msg.clear();

        for(z::t j(0) ; j < 3 ; ++j){
            temp.sprintf("%d ", _pai3[i][j]);
            msg += temp;
        }

        qDebug() << msg;
    }
}

void con_pai6(pai6::p _pai6){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < 6 ; ++i){
        temp.clear(); msg.clear();
        for(z::t j(0) ; j < 6 ; ++j){
            temp.sprintf("%d ", _pai6[i][j]);
            msg += temp;
        }

        qDebug() << msg;
    }
}



QString qs_pai3(pai3::p _pai3){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < 6 ; ++i){
        temp.clear();
        for(z::t j(0) ; j < 3 ; ++j){
            temp.sprintf("%d ", _pai3[i][j]);
            msg += temp;
        }
        msg += "\n";
    }
    return msg;
}

qt::s::t s_pai3(pai3::p _pai3, h::T _h){

     qt::s::t text = qt::s::T0;
     qt::s::t temp = qt::s::T0;

     for(z::t i(0) ; i < 6 ; ++i){
         for(z::t j(0) ; j < 3 ; ++j){
            text += temp.sprintf("%d ", _pai3[i][j]);
         }
     }

     return text;
}


QString qs_pai6(pai6::p _pai6){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < 6 ; ++i){
        temp.clear();
        for(z::t j(0) ; j < 6 ; ++j){
            temp.sprintf("%d ", _pai6[i][j]);
            msg += temp;
        }
        msg += "\n";
    }
    return msg;
}

i::t (*pai3_qs(qt::s::t _sPai3))[3]{

    pai3::p pai3_ = new i::t[6][3]{ {0,},{0,},{0,},{0,},{0,},{0,}  };

    s::v vsTemp = vs_s( qt::s_qs(_sPai3), ' ' );

    qDebug() << "size of vsTemp : " << vsTemp.size();

    for (z::t i(0) ; i < 6 ; ++i){

        for(z::t j(0) ; j < 3 ; ++j){
            pai3_[i][j] = i_s(vsTemp.at( (i * 3) + j ));
        }

    }

    return pai3_;
}


QString qs_pai3H(pai3::p _pai3){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < 6 ; ++i){
        temp.clear();
        for(z::t j(0) ; j < 3 ; ++j){
            temp.sprintf("%d ", _pai3[i][j]);
            msg += temp;
        }
    }
    return msg;
}



i::t (*pai3_fn(qt::s::t _path, QObject* _parent))[3] {

    pai3::p pai3_ = new i::t[6][3]{ {0},{0},{0},{0},{0},{0} };

    if(_path == qt::s::T0){ return false; }
    QFile file(_path, _parent);

    file.open(QIODevice::ReadWrite);

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');

    for (z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai3_[i][j] = i_s(vs.at( (i * 3) + j ));
        }
    }

    return pai3_;
}





void mmf_pai3Val(mmf_cp::writer::l* _writer ,pai3::p _pai3Val){

    debugMsg(__func__);

    _writer->writ_pai3(_pai3Val,6);

    qDebug() << "mmf write result :" << endl;
    con_pai3(_pai3Val);

}


void OFFSET_pai3Val(pai3::p OFFSET_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){

        for(z::t j(0) ; j < 3 ; j++){
            OFFSET_[i][j] = _pai3[i][j];
        }

    }
}



qt::yar::li yarl_proc(qt::srl::p _srl){
    debugMsg(__func__);

    qt::yar::t temp;


    while(_srl->waitForReadyRead(1000)){ temp.append(_srl->readAll());  con_yar(temp); }
    qDebug() << "total data from second serial";
    con_yar(temp);

    qt::yar::li yarl = yarl_yar(temp);

    for(auto i : yarl){
        debugMsg(i);
    }

    return yarl;

}




s::v del_basket(s::t _String){

    replace_s(_String,"["," ");
    replace_s(_String,"]"," ");

    return vs_s(_String, ' ');

}

void pai3_vs(pai3::p _pai, std::vector<std::string>& _vs, i::T _row){

    for( z::t i(0) ; i < 3 ; ++i){
        _pai[_row][i] = (i::t)(d_s(_vs.at(i + 3)) * 100);
    }

}

void pai3_yarl(pai3::p pai3_,qt::yar::li _yarl){

    debugMsg(__func__);

    for(z::t i(1) ; i < 7 ; ++i){
            s::v vTemp = del_basket(qs_yar(_yarl[i]));
            pai3_vs(pai3_, vTemp, i - 1);
    }

}



void ai6_vs(i::a6& _ai6 , std::vector<std::string>& _vs){

    if(_vs.size() == 0 ){ qDebug() << "_vs.size() == 0"; return; }



    for(z::t i(0) ; i < 6 ; ++i){

        c::t ct = _vs[2][i];
        _ai6[i] = ct - '0';
    }

}






qt::yar::t yarl_srl(qt::srl::p _srl){
    debugMsg(__func__);

    qt::yar::t temp;

    do{ temp.append(_srl->readAll());  con_yar(temp); if( temp.size() > 30 ){ break; } }

    while(_srl->waitForReadyRead(100));

    qt::yar::li yarl = yarl_yar(temp);

    for(auto i : yarl){

        qDebug() << (i);

    }

    if(yarl.size() > 0)
        return yarl[yarl.size() - 1];
    else{
        return nil;
    }

}


void ai6_yar(i::a6& _ai6 ,qt::yar::t _yar){

    debugMsg(__func__);
    s::v vTemp = del_basket(qs_yar(_yar));
    ai6_vs(_ai6, vTemp);

}


b::T ai6_srl(i::a6& _ai6, qt::srl::p _srl){
    qDebug() << __func__;

    if(!_srl->isOpen()){ qDebug() << "srl closed..!"; return b::T0; }

    if(_srl->waitForReadyRead(1000)){

        qt::yar::t yar = yarl_srl(_srl);
        ai6_yar(_ai6, yar);

    }else{ qDebug() <<"no response from second board";  return b::T0; }

    return b::T1;

}

b::T pai3_srl(pai3::p pai3_,qt::srl::p _srl){

    debugMsg(__func__);

    qt::yar::li yarl = yarl_proc(_srl);

    pai3_yarl(pai3_, yarl);

    return b::T1;
}


int (*pai3_encVal(qt::srl::p _srl))[3]{

    debugMsg(__func__);

    qDebug() << __func__;

    pai3::p pai3Val = new i::t[6][3]{  {0 ,},{0 ,},{0 ,},{0 ,},{0 ,},{0 ,}  };

    if(_srl->waitForReadyRead(10000)){  // 2번 엔코더 읽는 대기시간

        qDebug() << "_srl->waitForReadyRead(10000)" ;
        if(pai3_srl(pai3Val, _srl)){ return pai3Val; }

    }else{ qDebug() << "read Failed"; return nullptr; }

    return nullptr;
}

int (*pai3_srl(qt::srl::p _srl))[3]{

    if(!_srl->isOpen()){ qDebug() << "offset Serial is closed.." ; return nil; }


    !_srl->write("S",1);
    _srl->readAll();

    if(_srl->write("e",1)){

        while(true)
            if(!_srl->waitForReadyRead(500))
            {
                break;
            }

            else{ qt::yar::t yar=  _srl->readAll(); qDebug() << yar; }

        pai3::p pai3_ = pai3_encVal(_srl);

        _srl->write("s",1); // 멈춘 스위치 신호 다시시작
        _srl->write("s",1);

        return pai3_;

    }else{

        debugMsg("write failed....!");
        return nullptr;

    }

}




qt::yar::li qsBattery_proc(qt::srl::p _srl){
    debugMsg(__func__);

    qt::yar::t temp;

    do{
        temp.append(_srl->readAll());  con_yar(temp);  qDebug() << temp;
    }

    while(_srl->waitForReadyRead(1000));
    qDebug() << "total data from second serial";

    con_yar(temp);
    qt::yar::li yarl = yarl_yar(temp);

    for(auto i : yarl){
        debugMsg(i);
    }

    return yarl;
}

void qsBettary_vs(qt::s::r qsBattery_, std::vector<std::string>& _vs){
    for( z::t i(2) ; i < 3 ; ++i){
        qDebug() << "_vs[i] : " << qt::qs_s(_vs[i]);
        qsBattery_ += qt::qs_s(_vs[i]);
    }

    qDebug() << __func__;
    qDebug() << "qsBattery_ : " << qsBattery_;
}

void qsBattery_yarl(qt::s::r qsBattery_ ,qt::yar::li _yarl){

    debugMsg(__func__);

    if(_yarl.size() > 0){

        s::v vTemp = del_basket(qs_yar(_yarl[_yarl.size() - 1]));
        qsBettary_vs(qsBattery_ , vTemp);

    }
}


b::T qs_srl(qt::s::r qsBattery_,qt::srl::p _srl){


    debugMsg(__func__);


    qt::yar::li yarl = qsBattery_proc(_srl);

    qsBattery_yarl(qsBattery_, yarl);

    return b::T1;
}


QString qs_BValue( qt::srl::p _srl ){

    debugMsg(__func__);

    qDebug() << __func__;
    qt::s::t qsBattery_;



    if(qs_srl(qsBattery_, _srl)){ return qsBattery_; }

    return nullptr;

}


QString qsBattery_srl(qt::srl::p _srl){

    qDebug() << __func__;

    if(!_srl->isOpen()){ qDebug() << "offset Serial is closed.." ; return nil; }

    _srl->write("S",1);
    _srl->write("b",1);


        _srl->write("S",1);
        if(!_srl->waitForReadyRead(1000)){ };

    qt::yar::t yar = _srl->readAll();  qDebug() << "first : " << yar;
    _srl->write("b",1);

    if(_srl->write("b",1)){

        if(_srl->waitForReadyRead(3000)){

            qt::s::t BValue = qs_BValue(_srl);
            _srl->write("s",1); // 멈춘 스위치 신호 다시시작

            return BValue;

        }else{

            _srl->write("s",1); // 멈춘 스위치 신호 다시시작
            qDebug() << "Serial not respond.."; return nullptr;

        }


    }else{

        debugMsg("write failed....!");
        return nullptr;

    }

}

bool isResponded(qt::srl::p _srl){

    qDebug() << __func__;

    if(_srl->waitForReadyRead(1000)){  // 2번 엔코더 읽는 대기시간

        _srl->readAll();
        return b::T1;

    }else{

        qDebug() << "'s' has been sent to srl but no response arrived..." ;
        return b::T0;

    }

}

bool ping_srl(qt::srl::p _srl){
    qDebug() << __func__;

    if( !_srl->isOpen() ){ qDebug() << "second srl is closed.. "; return b::T0 ; }

    _srl->readAll();

    if(_srl->write("s",1)){

        return isResponded(_srl);

    }else{

        debugMsg("write failed....!");
        return b::T0;
    }

}






i::t (*pai6_pai3( pai3::p _pai3))[6]{

    pai6::p pai6_ = new i::t[6][6]{  {0},{0},{0},{0},{0},{0}  };

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){

            pai6_[i][j] = j < 3 ? _pai3[i][j] : 32;

        }
    }

    delete[] _pai3;
    return pai6_;
}




qt::s::t save_pai3(pai3::p _pai3, h::T _h, qt::s::T _fn = "OFFSET.txt"){

    QFile file(_fn);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File read failed"; return false;
    }


    QTextStream out(&file);
    qDebug() << s_pai3(_pai3,_h) << endl;
    out << s_pai3(_pai3,_h);

    return s_pai3(_pai3,_h);

}


bool load_pai3(pai3::p _offset_,h::t _h ,QWidget*parent = nullptr){

    QString path = QFileDialog::getOpenFileName(parent,"Find Files",QDir::currentPath());

    if(path == qt::s::T0){ return false; }

    QFile file(path, parent);
    file.open(QIODevice::ReadWrite);

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            _offset_[i][j] = i_s(vs.at( (i * 3) + j ));
        }
    }

    qDebug() << "offset loaded..!";

    return true;
}



void con_12bytes(y::p yData) {

    qt::s::t msg(qt::s::T0);
    qt::s::t temp(qt::s::T0);

    for(z::t i(0) ; i < 12 ; ++i) {

        temp.sprintf("0x%02x ", yData[i]);
        msg += temp;

    }

    qDebug() << msg;
}

void con_11bytes(y::p yData) {

    qt::s::t msg(qt::s::T0);
    qt::s::t temp(qt::s::T0);

    for(z::t i(0) ; i < 11 ; ++i) {

        temp.sprintf("0x%02x ", yData[i]);
        msg += temp;
    }
    qDebug() << msg;

}

vo::t cmd_id(cmd::t& cmd_ ,i::R _iDegree,i::R _id ){

    qDebug() << "cmd_id without vel" ;

    h::t vel    = 32;  //속도 3 rpm 고정

    y::t ccw = ( _iDegree < 0 ? 1 : 0);
    h::t posoff = (h::t) abs(_iDegree);

    y2::u degree2y ,vel2y;

    degree2y.h1    = posoff;
    vel2y.h1       = vel;

    y::t checkSum = ~( (y::t)(_id + 0x07 + 0x01 + ccw + degree2y.t2[1] + degree2y.t2[0] + vel2y.t2[1] + vel2y.t2[0]) );
    cmd::t command = { 0xFF, 0xFE, (y::t)_id, 0x07, checkSum, 0x01, ccw, degree2y.t2[1], degree2y.t2[0], vel2y.t2[1], vel2y.t2[0] };


    for(z::t i(0) ; i < cmd::Z ; ++i){
        cmd_[i] = command[i] ;

    }

}

vo::t req_id(req::t& req_,i::R _id ){

    y::t checkSum = ~((y::t)((y::t)_id + 0xA1 + 2));

    req_[0] = 0xFF;
    req_[1] = 0xFE;
    req_[2] = (y::t)_id;
    req_[3] = 2;
    req_[4] = checkSum;
    req_[5] = 0xA1;


}


void co_pai3(pai3::p pai3) {

    qt::s::t msg(qt::s::T0);
    qt::s::t temp(qt::s::T0);

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){

            temp.sprintf("%d ", pai3[i][j]);
            msg += temp;

        }
        msg += "\n";
    }

    QMessageBox box;
    box.setText(msg);
    box.exec();

}


void co_pai6(pai6::p pai6 , h::R _h = 6) {

    qt::s::t msg(qt::s::T0);
    qt::s::t temp(qt::s::T0);

    for(z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){

            temp.sprintf("%d ", pai6[i][j]);
            msg += temp;

        }
        msg += "\n";
    }

    QMessageBox box;
    box.setText(msg);
    box.exec();

}


b::t srl_i(qt::srl::p srl_ ,i::R _iDegree, i::R _id){

    cmd::t command;  cmd_id(command, _iDegree,  _id);

    qt::yar::t send_Data_Bytes = qt::yar::t::fromRawData(reinterpret_cast<c::p>(command), cmd::Z);

    srl_->write(send_Data_Bytes);

    return true;
}


i::t i_srl(qt::srl::p _srl, i::t _id){



    req::t request; req_id(request, _id);

    qt::yar::t send_Data_Bytes = qt::yar::t::fromRawData(reinterpret_cast<c::p>(request), 6);

    QString temp = "";
    QString msg = "";

    for(int i = 0 ; i < 6 ; ++i){
        temp.sprintf("%02X ", request[i]);
        msg += temp;
    }


    if(_srl->write(send_Data_Bytes)){

        qt::yar::t dataFromSri = _srl -> read(12);
        y::p yDataFromSri = reinterpret_cast<y::p>(dataFromSri.data());

        for(int i = 0 ; i < 12 ; ++i){
            temp.sprintf("%02X ", yDataFromSri[i]);
            msg += temp;
        }



        y2::u y2;

        y2.t2[0] = yDataFromSri[8];
        y2.t2[1] = yDataFromSri[7];

        return y2.h1;
    }

}





pai3::p pai_msg(void* _message){

    MSG* msg = reinterpret_cast<MSG*>(_message);

    if((msg)->message == WM_COPYDATA) {

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

i::t** pp_pai6(pai6::p pai6){ i::t** pp = reinterpret_cast<i::t**>(pai6);  return pp;  }

i::t** pp_pai3(pai3::p pai3){ i::t** pp = reinterpret_cast<i::t**>(pai3);  return pp;  }

pai6::p pai6_pp(i::t** pp){  pai6::p pai6 = reinterpret_cast<i::t (*)[6]>(pp);  return pai6;  }

pai3::p pai3_pp(i::t** pp){  pai3::p pai3 = reinterpret_cast<i::t (*)[3]>(pp);  return pai3;  }

b::t free_pai6(pai6::p pai6){  delete[] pai6;  pai6 = nil; return true;  }

b::t free_pai3(pai3::p pai3){  delete[] pai3;  pai3 = nil; return true;  }

b::t thsri_pai3(qt::srl::p _srl ,i::A3 _ai3, h::T _row){

    QFutureSynchronizer<b::t> synchronizer;

    for(z::t i(0) ; i < 3 ; ++i ){

        int id = (_row + 1) * 10 + (i + 1);

        synchronizer.addFuture(QtConcurrent::run([=](){


                mutForSerial.lock();
            if(srl_i( _srl, _ai3[i], id)){

                  while( _ai3[i] != i_srl(_srl,id) ){ qDebug() << "_ai3[i]" << _ai3[i] << "i_srl(_srl,id)" << i_srl(_srl,id) << endl;  Sleep(100); }

                return b::T1;

            }
                mutForSerial.unlock();

        }));
    }

    synchronizer.waitForFinished();

    return b::T0;
}

b::t srl_pai3(qt::srl::p _srl ,pai3::p _pai3, h::R _h){

    QFutureSynchronizer<b::t> synchronizer;

    for(z::t i(0) ; i < _h ; ++i){ synchronizer.addFuture(QtConcurrent::run([=](){ thsri_pai3(_srl, _pai3[i], i); return b::T1; })); }

    synchronizer.waitForFinished();
    return b::T1;
}

int encVal_srl(qt::srl::p _srl){


    qt::yar::t dataFromSri = _srl -> read(12);

    y::p yDataFromSri = reinterpret_cast<y::p>(dataFromSri.data());


    y2::u y2;

    y2.t2[0] = yDataFromSri[8];
    y2.t2[1] = yDataFromSri[7];

    i::t degree_ = (i::t)y2.h1;

    y::t checkSum = ~(yDataFromSri[2] + yDataFromSri[3] + yDataFromSri[5] + yDataFromSri[6] + yDataFromSri[7] + yDataFromSri[8] + yDataFromSri[9] + yDataFromSri[10] + yDataFromSri[11]);

    if(yDataFromSri[6] == 0x01) { degree_ = -degree_; }

    if( !(yDataFromSri[0] == 0xFF && yDataFromSri[1] == 0xFE && yDataFromSri[3] == 0x08 && yDataFromSri[4] == checkSum) ){ _srl->readAll(); return 99999; }


    return degree_;
}



i::t onWrite_req(qt::srl::p _srl ,qt::yar::t _req, i::t _id){

    if(_srl->write(_req)){

        if(!_srl->waitForReadyRead(1000)){
            qDebug() << " response time out from id : "+ qt::s_i(_id)  + "..! try again..!";

        }else{

            return encVal_srl(_srl);

        }

    }else{ qDebug() << " write failed on" << __func__ << endl;  return 0; }

}

i::t i_srl_mmf(qt::srl::p _srl ,i::t _id){

    req::t request; req_id(request, _id);
    c::p pReq = reinterpret_cast<c::p>(request);

    QByteArray arr = QByteArray::fromRawData(pReq,req::Z);


    return onWrite_req(_srl, arr, _id);;

}



void mmf_srl(rv2::mmf_cp::writer::l* _mmfwriter, qt::srl::p _srl, QList<int> _ids, pai3::p _offset){

    qDebug() << __func__ << endl;

    i::t tempArr[6][3] = { {0,},{0,},{0,},{0,},{0,},{0,} };
    pai3::p encVal = tempArr;

    for(i::t id : _ids){

        int row = (id / 10) -1;
        int colm = (id % 10) -1;

        encVal[row][colm] = i_srl_mmf(_srl,id) + _offset[row][colm];

    }

    mmf_pai3Val(_mmfwriter, encVal);

}

void save_srl(qt::srl::p _srl,QList<int> _ids, pai3::p _offset, qt::s::t _fn = "temp"){

    qDebug() << __func__ << endl;

    i::t tempArr[6][3] = { {0,},{0,},{0,},{0,},{0,},{0,} };
    pai3::p encVal = tempArr;

    for(i::t id : _ids){

        int row = (id / 10) -1;
        int colm = (id % 10) -1;

        encVal[row][colm] = i_srl_mmf(_srl,id) + _offset[row][colm];
    }

    save_pai3(encVal,6, _fn + ".txt");

}


void lv_no(QListWidget*_lv, i::t startNo, i::t endNo){

    for(z::t i(startNo) ; i < endNo ; ++i){
        _lv->addItem(qt::s_i(i));
    }

}


void add_pai33(pai3::p pai_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] += _pai3[i][j];
        }
    }

}



void sub_pai33(pai3::p pai_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] -= _pai3[i][j];
        }
    }

}

void sub_pai36(pai6::p pai_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] -= _pai3[i][j];
        }
    }


}

void add_pai66(pai6::p pai_, pai6::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] += _pai3[i][j];
        }
    }

}


void add_pai63(pai6::p pai_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] += _pai3[i][j];
        }
    }

}


void lw_cb(QListWidget* lv_, i::t startNo, i::t endNo){


        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, qt::s_i(startNo));
        item->setData(Qt::CheckStateRole, Qt::Unchecked);

        lv_->addItem(item);

        if(startNo == endNo){return;}


        return lw_cb(lv_, ++startNo, endNo);

}


void sub_pai36(pai3::p pai_, pai3::p _pai3){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] -= _pai3[i][j];
        }
    }

}



qt::s::t qs_li(QList<int> _li){

    QString msg;
    QString temp;

    for(i::t i : _li){
        temp.sprintf("%d ", i);
        msg += temp;
    }

    qDebug() << msg;

    return msg;

}

b::t check_commandValid(pai3::p _command, i::t _first_max , i::t _first_min, i::t _second_max, i::t _second_min, i::t _third_max, i::t _third_min ){


    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){

            if(j == 0){

                if((_command[i][j] > _first_max)){
                    _command[i][j] = _first_max;
                }

                if((_command[i][j] < _first_min)){
                    _command[i][j] = _first_min;
                }

            }else if(j == 1){

                if((_command[i][j] > _second_max)){
                    _command[i][j] = _second_max ;
                }

                if((_command[i][j] < _second_min)){
                    _command[i][j] = _second_min;
                }

            }else if(j == 2){

                if((_command[i][j] > _third_max)){
                    _command[i][j] = _third_max;
                }

                if((_command[i][j] < _third_min)){
                    _command[i][j] = _third_min;
                }
            }
        }
    }

    return true;
}

b::t check_commandValid(pai6::p _command, i::t _first_max , i::t _first_min, i::t _second_max, i::t _second_min, i::t _third_max, i::t _third_min ){


    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){

            if(j == 0){

                if((_command[i][j] > _first_max)){
                    _command[i][j] = _first_max;
                }

                if((_command[i][j] < _first_min)){
                    _command[i][j] = _first_min;
                }

            }else if(j == 1){

                if((_command[i][j] > _second_max)){
                    _command[i][j] = _second_max ;
                }

                if((_command[i][j] < _second_min)){
                    _command[i][j] = _second_min;
                }

            }else if(j == 2){

                if((_command[i][j] > _third_max)){
                    _command[i][j] = _third_max;
                }

                if((_command[i][j] < _third_min)){
                    _command[i][j] = _third_min;
                }
            }
        }
    }

    return true;
}




namespace m_to {

    void vs(ks::M& _mks, s::w vs_) { ; vs_ = ks::vs_m(_mks); }
    void fn(ks::M& _mks, s::R fn_) { ; rv2::vs_to::fn(ks::vs_m(_mks), fn_); }

}///



ks::m mNo_vs(s::W _vs) {///
    ks::m mks_;
    i::t i(0);
    for (
#if __cplusplus < 199711L
        z::t i(0); i < _vs.size(); ++i) {
        s::T s(_vs[i]);
#else
        const auto& s:_vs) {
#endif
        mks_.insert(make_pair(s_i(i), s));
        i += 1;
    }
    return mks_;
}///

kms::m kmNo_vs(s::W _vs) {///
            kms::m mkms_;
            s::t sSec(s::T0);
            s::v vs;
            for (
#if __cplusplus < 199711L
                z::t i(0); i < _vs.size(); ++i) {
                s::T s(_vs[i]);
#else
                const auto& s:_vs) {
#endif
                if (s == "" || s == "\n" || s == "=")continue;
                if (s[0] == '[') {
                    if (sSec != s::T0) {

                        ks::m  mks(mNo_vs(vs));
                        kms::t     tkms(sSec, mks);
                        mkms_.insert(tkms);

                    }
                    sSec = s; vs.clear();
                }
                else {

                    vs.push_back(s);

                }
            }

            if (sSec != s::T0) {
                ks::m  mks(mNo_vs(vs));
                kms::t     tkms(sSec, mks);
                mkms_.insert(tkms);
            }

            return mkms_;
}///



QList<int> li_legsValStt(Ui::MainWindow* _ui){

    QList<int> li;

    li.push_back(qt::i_s(_ui ->edit_max_firstLeg->text())  * 100);
    li.push_back(qt::i_s(_ui ->edit_min_firstleg->text())  * 100);

    li.push_back(qt::i_s(_ui ->edit_max_secondLeg->text()) * 100);
    li.push_back(qt::i_s(_ui ->edit_min_secondleg->text()) * 100);

    li.push_back(qt::i_s(_ui ->edit_max_thirdLeg->text())  * 100);
    li.push_back(qt::i_s(_ui ->edit_min_thirdLeg->text())  * 100);

    return li;

}

b::t addOffset(pai3::p _command_, pai3::p _offset){

    add_pai33(_command_, _offset);
    return b::T1;

}

b::t addOffset(pai6::p _command_, pai3::p _offset){

    add_pai63(_command_, _offset);
    return b::T1;

}

b::t subOffset(pai3::p _command_, pai3::p _offset){

    sub_pai33(_command_, _offset);
    return b::T1;

}


b::t subOffset(pai6::p _command_, pai3::p _offset){

    sub_pai36(_command_, _offset);
    return b::T1;

}






i::p* ipp_pai66(pai6::p _commands, pai3::p _offset , Ui::MainWindow* _ui){

    addOffset( _commands, _offset );

    QList<int> li_Val = li_legsValStt(_ui);

    pai6::p temp_pai3 = new i::t[6][6]{  {0},{0},{0},{0},{0} };

    memcpy(  temp_pai3,  _commands,  36 * 4); // 실제 멤버변수에 있는 pai3에는 변화가 가지 않도록 한다.

    check_commandValid( temp_pai3, li_Val[0],  li_Val[1], li_Val[2], li_Val[3], li_Val[4], li_Val[5] );

    return pp_pai6(temp_pai3);

}

bool ia3_pai3(i::a3 ia3_ ,pai3::p _pai3, i::T _iRow){

    for(z::t i(0) ; i < 3 ; ++i){
        ia3_[i] = _pai3[_iRow][i];
    }

    return b::T1;
}


void ia6_pai6(i::a6 ia6_ ,pai6::p _pai6, i::T _iRow){

    for(z::t i(0) ; i < 6 ; ++i){
        ia6_[i] = _pai6[_iRow][i];
    }

}

void ip6_pai6(pai6::p& ip6_,pai6::p _pai6, i::T _iRow){

    ip6_ = (_pai6 + _iRow);

}

vo::t cmd_id(cmd::t cmd_,i::R _iDegree, i::R _id, i::R _iVelocity = 30){

    h::t vel    = _iVelocity;
    y::t ccw = ( _iDegree < 0 ? 1 : 0);
    h::t posoff = (h::t) abs(_iDegree);
    y2::u degree2y ,vel2y;

    degree2y.h1    = posoff;
    vel2y.h1       = vel;

    y::t checkSum = ~((y::t)(_id + 0x07 + 0x01 + ccw + degree2y.t2[1] + degree2y.t2[0] + vel2y.t2[1] + vel2y.t2[0]));
    cmd::t command = {  0xFF, 0xFE, (y::t)_id, 0x07, checkSum, 0x01, ccw, degree2y.t2[1], degree2y.t2[0], vel2y.t2[1], vel2y.t2[0] };

    for(z::t i(0) ; i < cmd::Z ; ++i){
        cmd_[i] = command[i] ;
    }

    qDebug() << "id : " << _id << "vel : " << vel << "posoff" << posoff << endl;

}

pai3::p pai3_msg(vo::p _message){

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








b::T mNo_fn(s::R _fn, kms::m& mkms_){ ; s::v vs; b::T b_(rv2::fn_to::vs(_fn, vs)); if (b_) mkms_ = kmNo_vs(vs); else mkms_.clear(); return b_; }

kms::m kmNo_fn(s::R _fn) { ; kms::m mkms_; mNo_fn(_fn, mkms_); return mkms_; }


void pai3_pai6(pai3::p pai3_, pai6::p _pai6){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){

            pai3_[i][j] = _pai6[i][j];

        }
    }

}


qt::yar::t yar_req(i::t _id){

    req::t request; req_id(request, _id);
    c::p pReq = reinterpret_cast<c::p>(request);

    return qt::yar::t::fromRawData(pReq,req::Z);

}


b::t check_cds(pai6::p _cdsCmd){
    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            if(_cdsCmd[i][j] > 10000 || _cdsCmd[i][j] < -10000) return false;
        }
    }

    return true;
}



#endif // DLL_USB_OFFSET01STT_H
/*

 각도 함수 옮길것..!

function rng360_ang(const _f: single): single;
begin
  result := _f;
  while result < 0.0 do result := result + 360.0;
  while result >= 360.0 do result := result - 360.0;
  result := (trunc(result) mod 360) + frac(_f);
end;

function rng180_ang(const _f: single): single;
begin
  result := rng360_ang(_f + 180.0) - 180.0
end;
*/
