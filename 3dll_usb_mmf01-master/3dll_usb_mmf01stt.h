#ifndef DLL_USB_MMF01STT_H
#define DLL_USB_MMF01STT_H
#include "QtSerialPort/QSerialPort"
#include <QtConcurrent>
#include <QMutex>
#include <QThread>
#include <6qtu9.hpp>

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
namespace rep {///
    typedef y::t t[12];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
    //    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
    //    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
    //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///

}

i::t debugMode = 0;

qt::srl::p CreateSrl(QObject *parent = nullptr, i::T _portNo = 0){

    QSerialPort* srl = new QSerialPort(parent);
    srl->setPortName("COM"+ qt::s_i(_portNo));
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

qt::thr::p thr_Srl(qt::srl::p _Srl, QObject *parent = nullptr){

     qt::thr::p qthr_ = new qt::thr::t;
    _Srl = CreateSrl(parent);
    _Srl->moveToThread(qthr_);


    return qthr_;

}

qt::yar::li yarl_yar(qt::yar::t _yar){

    qt::yar::li li_;
    qt::yar::t temp;

    for(auto i = _yar.cbegin() ; i != _yar.cend() ; ++i ){
        temp.clear();
        if(*i == '['){
            do{
                temp.append(*i);
                ++i;
            }while(*i != ']');
            temp.append(*i);
            li_.append(temp);
        }
    }

    return li_;
}

vo::t debugMsg(QString _msg){ if(debugMode == 1) qDebug() << _msg << endl; }

void con_yar(qt::yar::t _yar){
    debugMsg("data from Serial..");
    debugMsg(QString::fromStdString(_yar.toStdString()));
    debugMsg("end data from Serial..");
}

qt::yar::li yarl_proc(qt::srl::p _srl){
    debugMsg(__func__);

    qt::yar::t temp;


    while(_srl->waitForReadyRead(100)){ temp.append(_srl->readAll());  }  con_yar(temp);
    qt::yar::li yarl = yarl_yar(temp);

    for(auto i : yarl){
        debugMsg(i);
    }



    return yarl;
}

std::string qs_yar(qt::yar::t _yar){

    return _yar.toStdString();
}

void pai3_vs(pai3::p _pai, std::vector<std::string>& _vs, i::T _row){
    for( z::t i(0) ; i < 3 ; ++i){
        _pai[_row][i] = (i::t)(d_s(_vs.at(i + 3)) * 100);
    }
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

s::v del_basket(s::t _String){
    replace_s(_String,"["," ");
    replace_s(_String,"]"," ");

    return vs_s(_String, ' ');
}

void pai3_yarl(pai3::p pai3_,qt::yar::li _yarl){

    debugMsg(__func__);

    for(z::t i(1) ; i < 7 ; ++i){
            s::v vTemp = del_basket(qs_yar(_yarl[i]));
            pai3_vs(pai3_, vTemp, i - 1);
    }

    con_pai3(pai3_);

}

b::T pai3_srl(pai3::p pai3_,qt::srl::p _srl){

    debugMsg(__func__);

    qt::yar::li yarl = yarl_proc(_srl);

    pai3_yarl(pai3_, yarl);

    return b::T1;
}

void mmf_pai3Val(pai3::p _pai3Val){
    debugMsg(__func__);

    hnd::t handle = create_mmf("mmftest_pchr", 1024);
    mmf_pai3(handle,_pai3Val,6);

    qDebug() << "mmf write result :" << endl;
    con_pai3(_pai3Val);

}

void mmf_encVal(qt::srl::p _srl){
    debugMsg(__func__);

    i::t encVal[6][3] = { {0,},{0,},{0,},{0,},{0,},{0,} };

    pai3::p pai3Val = encVal;

    if(_srl->waitForReadyRead(3000)){

        if(pai3_srl(pai3Val, _srl)){mmf_pai3Val(pai3Val);}

    }else{ debugMsg("read failed..!"); }


}

vo::t req_id(req::t req_,i::R _id ){


    y::t checkSum = ~((y::t)((y::t)_id + 0xA1 + 2));

    req_[0] = 0xFF;
    req_[1] = 0xFE;
    req_[2] = (y::t)_id;
    req_[3] = 2;
    req_[4] = checkSum;
    req_[5] = 0xA1;

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

i::t onWrite_req(qt::srl::p _srl ,qt::yar::t _req, i::t _id){

    //qDebug() <<__func__ << QThread::currentThread() << endl;
    if(_srl->write(_req)){

        if(!_srl->waitForReadyRead(1000)){
            qDebug() << " response time out from id : "+ qt::s_i(_id)  + "..! try again..!";

        }else{

            return encVal_srl(_srl);
        }

    }else{ qDebug() << " write failed on" << __func__ << endl;  return 0; }

}

i::t i_srl(qt::srl::p _srl ,i::t _id){

    //qDebug() << __func__ << endl;

    req::t request; req_id(request, _id);
    c::p pReq = reinterpret_cast<c::p>(request);

    QByteArray arr = QByteArray::fromRawData(pReq,req::Z);


    return onWrite_req(_srl, arr, _id);;
}

void mmf_srl(qt::srl::p _srl,QList<int> _ids, pai3::p _offset){

    i::t tempArr[6][3] = { {0,},{0,},{0,},{0,},{0,},{0,} };
    pai3::p encVal = tempArr;

    for(i::t id : _ids){

        int row = (id / 10) -1;
        int colm = (id % 10) -1;

        encVal[row][colm] = i_srl(_srl,id) + _offset[row][colm];

    }




    mmf_pai3Val(encVal);



}



#endif // DLL_USB_MMF01STT_H
