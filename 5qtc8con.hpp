#ifndef QTC8CON_HPP
#define QTC8CON_HPP

#include "QtSerialPort/QSerialPort"
#include <QMainWindow>
#include <QtConcurrent>
#include <QFileDialog>
#include <QListWidget>
#include <QMutex>
#include <QThread>
#include <5qtc9.hpp>

using namespace rv2;
using namespace std;

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



vo::t con_yar(qt::yar::t _yar){

qDebug() << QString::fromStdString(_yar.toStdString()) ;

}

string qs_yar(qt::yar::t _yar){  return _yar.toStdString();  }

qt::s::T qs_pai3V(pai3::p _pai3, h::T _h){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < _h ; ++i){
        temp.clear();
        for(z::t j(0) ; j < 3 ; ++j){
            temp.sprintf("%d ", _pai3[i][j]);
            msg += temp;
        }
        msg += "\n";
    }

    return msg;
}

qt::s::T qs_pai6V(pai6::p _pai6, h::T _h){
    qt::s::t temp = qt::s::T0;
    qt::s::t msg = qt::s::T0;

    for(z::t i(0) ; i < _h ; ++i){
        temp.clear();
        for(z::t j(0) ; j < 6 ; ++j){
            temp.sprintf("%d ", _pai6[i][j]);
            msg += temp;
        }

        msg += "\n";
    }

    return msg;
}

qt::s::T qs_pai3H(pai3::p _pai3, h::T _h){

    qt::s::t qsPai3 = qt::s::T0;
    qt::s::t temp   = qt::s::T0;

    for(z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
           qsPai3 += temp.sprintf("%d ", _pai3[i][j]);
        }
    }

    return qsPai3;

}

qt::s::T qs_pai6H(pai6::p _pai6, h::T _h){

    qt::s::t qsPai6 = qt::s::T0;
    qt::s::t temp   = qt::s::T0;

    for(z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){
           qsPai6 += temp.sprintf("%d ", _pai6[i][j]);
        }
    }

    return qsPai6;
}

qt::s::T qs_yp(y::p _yData, h::T _h){

    qt::s::t msg(qt::s::T0);
    qt::s::t temp(qt::s::T0);

    for(z::t i(0) ; i < _h ; ++i) {

        temp.sprintf("0x%02x ", _yData[i]);
        msg += temp;

    }

    return msg;
}

vo::t con_pai3(pai3::p _pai3, h::T _h){  qDebug() << qs_pai3V(_pai3, _h);  }

vo::t con_pai6(pai6::p _pai6, h::T _h){  qDebug() << qs_pai6V(_pai6, _h);  }

void  con_yp  (y::p _yData, h::T _h)  {  qDebug() << qs_yp  (_yData, _h); }

vo::t pai3_qs(pai3::p pai3_ ,qt::s::t _sPai3, h::T _h){

    s::v vsTemp = vs_s( qt::s_qs(_sPai3), ' ' );

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai3_[i][j] = i_s(vsTemp.at( (i * 3) + j ));
        }
    }

}

vo::t pai6_qs( pai6::p pai6_ ,qt::s::t _sPai6, h::T _h){

    s::v vsTemp = vs_s( qt::s_qs(_sPai6), ' ' );

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){
            pai6_[i][j] = i_s(vsTemp.at( (i * 6) + j ));
        }
    }

}

vo::t pai3_vs(pai3::p pai3_, s::V _vs, h::T _h){

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai3_[i][j] = i_s(_vs.at( (i * 3) + j ));
        }
    }
}

s::V vs_pai3(pai3::p _pai3,h::T _h){

    s::v vs_;
    vs_.reserve(3 * _h * i::Z);

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            vs_.at( (i * 3) + j ) = s_i(_pai3[i][j]);
        }
    }

}

vo::t pai6_vs(pai6::p pai6_, s::V _vs, h::T _h){

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){
            pai6_[i][j] = i_s(_vs.at( (i * 6) + j ));
        }
    }
}

s::V vs_pai6(pai6::p _pai6,h::T _h){

    s::v vs_;
    vs_.reserve(6 * _h * i::Z);

    for (z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){
            vs_.at( (i * 6) + j ) = s_i(_pai6[i][j]);
        }
    }

}

b::T pai3_fn(pai3::p pai3_, qt::s::t _path, h::T _h ,QObject* _parent){


    if(_path == qt::s::T0){  return false; }
    QFile file(_path, _parent);

    if(file.open(QIODevice::ReadWrite)){ return false; };

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');
    pai3_vs(pai3_, vs, _h);

    return true;
}

b::T pai6_fn(pai6::p pai6_, qt::s::t _path, h::T _h ,QObject* _parent){


    if(_path == qt::s::T0){  return false; }
    QFile file(_path, _parent);

    if(file.open(QIODevice::ReadWrite)){ return false; };

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');
    pai6_vs(pai6_, vs, _h);



    return true;
}

i::t pai6_pai3(pai6::p pai6_ ,pai3::p _pai3, i::T rightPai3Val){

    for(z::t i(0) ; i < 6 ; ++i){
        for(z::t j(0) ; j < 6 ; ++j){
            pai6_[i][j] = j < 3 ? _pai3[i][j] : rightPai3Val;
        }
    }

}

b::T save_pai3(pai3::p _pai3, h::T _h, qt::s::T _fn = "pai3.txt"){

    QFile file(_fn);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){   return false;   }

    QTextStream out(&file);
    out << qs_pai3H(_pai3,_h);

    return true;

}

b::T save_pai6(pai6::p _pai6, h::T _h, qt::s::T _fn = "pai6.txt"){

    QFile file(_fn);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){   return false;  }

    QTextStream out(&file);
    out << qs_pai6H(_pai6,_h);

    return true;
}

b::T load_pai3(pai3::p _pai3_,h::t _h ,QWidget*parent = nullptr, qt::s::T _fn = "pai3.txt"){

    QFile file(_fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){   return false;   }

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');
    pai3_vs(_pai3_, vs, _h);

    return true;

}

b::T load_pai6(pai6::p _pai6_,h::t _h ,QWidget*parent = nullptr, qt::s::T _fn = "pai6.txt"){

    QFile file(_fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){   return false;   }

    qt::yar::t sOffset = file.readAll();
    s::v vs = vs_s(sOffset.toStdString(), ' ');
    pai6_vs(_pai6_, vs, _h);

    return true;

}

i::t** pp_pai6(pai6::p pai6){ i::t** pp = reinterpret_cast<i::t**>(pai6);  return pp;  }

i::t** pp_pai3(pai3::p pai3){ i::t** pp = reinterpret_cast<i::t**>(pai3);  return pp;  }

pai6::p pai6_pp(i::t** pp){  pai6::p pai6 = reinterpret_cast<i::t (*)[6]>(pp);  return pai6;  }

pai3::p pai3_pp(i::t** pp){  pai3::p pai3 = reinterpret_cast<i::t (*)[3]>(pp);  return pai3;  }

b::t free_pai6(pai6::p pai6){  delete[] pai6;  pai6 = nil; return true;  }

b::t free_pai3(pai3::p pai3){  delete[] pai3;  pai3 = nil; return true;  }




void add_pai3(pai3::p pai_, pai3::p _pai3 , h::T _h){

    for(z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] += _pai3[i][j];
        }
    }

}

void sub_pai33(pai3::p pai_, pai3::p _pai3 , h::T _h){

    for(z::t i(0) ; i < _h ; ++i){
        for(z::t j(0) ; j < 3 ; ++j){
            pai_[i][j] -= _pai3[i][j];
        }
    }

}


s::v vs_li(QList<int> _li){
    s::v vs_;
    QString temp;

    for(i::t i : _li){
        vs_.push_back(qt::s_qs(temp.sprintf("%d", i)));
    }

    return vs_;
}

QList<int> li_vs(s::v _vs){
    QList<int> li_;

    for(s::T s : _vs){
        li_.push_front(qt::i_s(qt::qs_s(s)));
    }

}

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

qt::yar::T yar_yp(y::p _yp, h::T _h){
    return qt::yar::t::fromRawData(reinterpret_cast<c::p>(_yp), _h);
}

qt::yar::T yar_qs(qt::s::T qs){

}


namespace Serial {
    class l{

        public:
        l( i::T _portNo = 0, QObject *parent = nullptr ){

            QSerialPort* srl_ = new QSerialPort(parent);
            srl->setPortName("COM"+ qt::s_i(_portNo));
            srl->setBaudRate(QSerialPort::Baud115200);
            srl->setDataBits(QSerialPort::Data8);
            srl->setParity(QSerialPort::NoParity);
            srl->setStopBits(QSerialPort::OneStop);
            srl->setFlowControl(QSerialPort::NoFlowControl);

            if(!srl->open(QIODevice::ReadWrite))
                qDebug() << "Serial open failed...!" << endl;

            srl = srl_;

        };

        ~l();

        b::T srl_yar(qt::yar::t _yar){

            if( !srl->isOpen() ) return b::T0;

            srl->write(_yar);
            return b::T1;

        }

        b::T srl_s(qt::s::T _qs){

            if( !srl->isOpen() ) return b::T0;

            srl->write(cp_s(qt::s_qs(_qs)),_qs.size());
            return b::T1;

        }

        qt::yar::T yar_srl(){

            if( !srl->isOpen() ) return nil;

            qt::yar::t yar_ = srl->readAll();

            return yar_;
        }


        qt::s::T s_srl(){

            if( !srl->isOpen() ) return nil;

            qt::yar::t yar_ = srl->readAll();
            qt::s::T str(yar_);

            return str;
        }

        b::T isArrived(){
            srl->waitForReadyRead(1000);
        }


        b::T resetSrl( i::T _portNo = 0, QObject *parent = nullptr ){

            delete [] srl;

            srl = new QSerialPort(parent);
            srl->setPortName("COM"+ qt::s_i(_portNo));
            srl->setBaudRate(QSerialPort::Baud115200);
            srl->setDataBits(QSerialPort::Data8);
            srl->setParity(QSerialPort::NoParity);
            srl->setStopBits(QSerialPort::OneStop);
            srl->setFlowControl(QSerialPort::NoFlowControl);

            if(!srl->open(QIODevice::ReadWrite))
                qDebug() << "Serial open failed...!" << endl;

        }


        qt::srl::p srl;

    };
}





















void lv_no(QListWidget*_lv, i::t startNo, i::t endNo){

    for(z::t i(startNo) ; i < endNo ; ++i){
        _lv->addItem(qt::s_i(i));
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


#endif // QTC8CON_HPP
