#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "QtSerialPort/QSerialPort"
#include <QtConcurrent>
#include <vector>
#include <QMutex>
#include <QThread>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QDesktopServices>



class Dll_usb_mmf01stl;
namespace Ui {

class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void makeConnection();


    bool nativeEvent(const QByteArray &eventType, void *message, long *resultMSG);
    void set_tbrs();
    bool init_tbrs();
    bool init_lv();
    bool offset_fn(QString _path);
    void tbrs_legNo(int _legNo);
    void load_commands(const QString& _sSec);
    void log(QString _text);
    void init_lw();
    void i_cb( QList<int>& ids_ ,QListWidget* _lw,int _startNo, int _endNo);
    void ids_lili(QList<int>& _ids ,QList<int> _li, QList<int> mi);
    void mCommands_vs(QMap<int, int (*)[6]>& _mCommands_, std::vector<std::string> _vs);
    void thsrl_pai36(int (*_commands)[3]);
    void cb_fn(QString _fn);
    QList<int> li_legsVal();
    void thsrl_pai6(int (*_commands)[6]);



    QThread* wThread;
    QTimer* sendTimer;
    QTimer* srl_fileTimer;
    std::map<std::string, std::map<std::string, std::string>> kmsmCommands;



    Dll_usb_mmf01stl* stl;
    bool isSended = false;
    bool tbrEnded = true;
    QMap<int, int (*)[6]> mCommands;
    int idxSizeCommands;


signals:
    void thsrl_cds(int** _cmd);
    void thsrl_file(int** _cmd);

    void send_clicked(QList<int> _qai3, int _legNo);
    void readOffset();
    void saveOffset();
    void mmfClicked();
    void write_log(QString _text);
    void openFirstSerial(QString _text);
    void openSecondSerial(QString _text);
    void setIds(QList<int> _rows, QList<int> _cols);
    void tempSave(QString _fn);



private slots:

    void srl_ai3();

    void fileTimerTimeOut();

    void thsri_qai36End();

    void on_edit_min_firstleg_returnPressed();

    void on_edit_min_secondleg_returnPressed();

    void on_edit_min_thirdLeg_returnPressed();

    void on_edit_max_firstLeg_returnPressed();

    void on_edit_max_secondLeg_returnPressed();

    void on_edit_max_thirdLeg_returnPressed();

    void on_tbr_firstLeg_valueChanged(int value);

    void on_tbr_secondLeg_valueChanged(int value);

    void on_tbr_thirdLeg_valueChanged(int value);

    void on_btn_send_clicked();

    void on_btn_load_clicked();

    void on_lv_legs_itemClicked(QListWidgetItem *item);

    void on_cb_sign_toggled(bool checked);

    void on_cb_offset_toggled(bool checked);

    void on_btn_commands_clicked();

    void on_lv_commands_doubleClicked(const QModelIndex &index);

    void on_cb_timer_toggled(bool checked);

    void on_Edit_timerDelay_returnPressed();

    void on_tbr_delay_sliderMoved(int position);

    void on_edPath_returnPressed();

    void on_btnClear_clicked();

    void on_offset_readOffset();

    void on_offset_saveOffset();

    void on_usb_mmf_mmfClicked();

    void on_edit_firstSerial_returnPressed();

    void on_edit_secondSerial_returnPressed();

    void onShowOffset();

    void on_pushButton_clicked();

    void on_btn_reset_clicked();

    void on_actionE_xit_triggered();

    void on_actionOpen_App_Folder_triggered();

    void on_btn_tempSave_clicked();

    void on_cb_commands_activated(const QString &arg1);

    void on_cb_release_clicked(bool checked);

    void timeTaken(int _time);


    void on_btn_timeClear_clicked();

private:
    Ui::MainWindow *ui;
};




class SerialWorker;
class OffsetWorker;

class Dll_usb_mmf01stl : public QObject{


        Q_OBJECT

    public:
        explicit Dll_usb_mmf01stl(QObject *parent = nullptr);
        ~Dll_usb_mmf01stl();

    void srl_i(const int _iDegree, const int _id,const int _velocity);
    int  i_srl(int _id);

    void thread_pai6(QFutureSynchronizer<bool> & _synchronizer ,  const int _qai6[6], int _id , int _row);
    bool thsri_pai6(const int _ai6[6],const unsigned short _row);

    void thread_qai3(QFutureSynchronizer<bool> & _synchronizer ,  QList<int> _qai3,   int _id , int _row);
    void thread_qai36(QFutureSynchronizer<bool>& _synchronizer ,  QList<int> _qai3,   int _id , int _row);

    void thread_pai3(QFutureSynchronizer<bool>& _synchronizer, const int _ai3[3], int _id, int _row);

    bool Dll_usb_mmf01stl::thsri_pai3(const int _ai3[3], unsigned short _row);

    SerialWorker* sWorker;
    OffsetWorker* oWorker;

    QThread* sThread;
    QThread* mThread;

    QList<int> rows;
    QList<int> cols;

    QElapsedTimer timer;

    bool isFinished = true;



signals:
    void write_cmd(char* _cmd);
    void write_req(char* _req);
    void readOffset();
    void mmfClicked();
    void log(const QString _text);
    void openFirstSerial(QString _text);
    void openSecondSerial(QString _text);
    void showOffset();
    void tempSave(QString _fn);
    void thsri_qai36End();
    void timeTaken(int _time);


public slots:
    bool srl_pai6(int** _cmd);

    void OnReadOffset();
    void onMmfClicked();
    void setIds(QList<int> _rows, QList<int> _cols);
    void thsri_qai36(QList<int> _qai3, int _legNo);

};










class SerialWorker : public QObject{


        Q_OBJECT

    public:
        explicit SerialWorker(QObject *parent = nullptr);
        ~SerialWorker();

    void setIds();
    bool isSrlFinished = true;
    void onLegClick_pushEncVal(QList<int>& leg_Enc, QSerialPort* _port, int _id);


    QSerialPort* port;
    QList<int> ids;


signals:
    void log(const QString _text);
    void showOffset();


public slots:
    void onWrite_cmd(char* _cmd);
    int  onWrite_req(QByteArray _req, int _id);
    QList<int> onLv_clicked(int legNo);

    void onMmfCheck_clicked();
    void setSerialPort(QString _port);
    void tempSave(QString _fn);

};


class OffsetWorker : public QObject{


        Q_OBJECT

    public:
        explicit OffsetWorker(QObject *parent = nullptr);
        ~OffsetWorker();


    QSerialPort* srl;

signals:
    void log(QString _text);


public slots:
    void onReadOffset();
    void setSerialPort(QString _port);

};



#endif // MAINWINDOW_HPP
