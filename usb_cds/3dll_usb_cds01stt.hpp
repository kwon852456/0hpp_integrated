
#ifndef USB_MMF_STT_H
#define USB_MMF_STT_H

#include <6qtu9.hpp>
#include "QtSerialPort/QSerialPort"
#include <QThread>
#include <QtConcurrent>
#include <QMutex>

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
    //    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
    //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
        T T0("");
    }///

    namespace qmutx{
        typedef QMutex t;
        typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
     }

    namespace s{
        typedef  QList <t> qli; const qli QLI; typedef QList <qli> qlili; typedef const qlili QLILI;
    }

}///

/* */namespace cmd {///
    typedef y::t t[11];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
//    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
//    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
//    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///

/* request y::t[6] */namespace req {///
    typedef y::t t[6];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
//    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
//    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
//    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}///
namespace rep {
    typedef y::t t[12];
    typedef const t T; typedef t(&r); typedef T(&R); typedef t(*p); typedef T(*const P); typedef T(*Tp); typedef t(*const tP); z::T Z(sizeof(t));
    //    typedef std::vector<t> v; typedef const v V; typedef v(&w); typedef V(&W); typedef std::vector<v> vv; typedef const vv VV; typedef vv(&ww); typedef VV(&WW);
    //    typedef std::list  <t> li; typedef const li LI; typedef std::list  <li> lili; typedef const lili LILI;
    //    typedef std::queue <t> qu; typedef const qu QU; typedef std::queue <qu> ququ; typedef const ququ QUQU; //typedef std::map<t,v> vm; typedef std::map<std::string,std::vector<std::string> > vm;
    T T0("");
}


namespace i{
    typedef  QList <t> qli; const qli QLI; typedef QList <qli> qlili; typedef const qlili QLILI;
}
namespace s{
    typedef  QList <t> qli; const qli QLI; typedef QList <qli> qlili; typedef const qlili QLILI;
}




}

qt::qmutx::t mutForSerial;


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

vo::t cmd_id(cmd::t& cmd_,i::R _iDegree,i::R _id ){

    //h::t vel    = (h::t)abs(preset[i][j] - current[i][j]);
    h::t vel    = 32;  //속도 3 rpm 고정

    y::t ccw = ( _iDegree < 0 ? 1 : 0);
    h::t posoff = (h::t) abs(_iDegree);

    y2::u degree2y ,vel2y;

    degree2y.h1    = posoff;
    vel2y.h1       = vel;

    y::t checkSum = ~((y::t)(_id + 0x07 + 0x01 + ccw + degree2y.t2[1] + degree2y.t2[0] + vel2y.t2[1] + vel2y.t2[0]));
    cmd::t command = {0xFF, 0xFE, (y::t)_id, 0x07, checkSum, 0x01, ccw, degree2y.t2[1], degree2y.t2[0], vel2y.t2[1], vel2y.t2[0] };


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



#endif // USB_MMF_STT_H

