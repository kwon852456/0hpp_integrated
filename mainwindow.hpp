#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "QtSerialPort/QSerialPort"
#include <QtConcurrent>
#include <QMutex>
#include <QThread>
#include <QFileDialog>
#include <QListWidgetItem>

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

    bool nativeEvent(const QByteArray &eventType, void *message, long *resultMSG);
    int (*pai_msg(void* _message))[3];
    void set_tbrs();
    bool init_tbrs();
    bool init_lv();
    bool offset_fn(QString _path);
    void tbrs_legNo(int _legNo);
    void load_offset(const QString& _fn);


    QThread* wThread;
    QTimer* sendTimer;
    QTimer* srl_fileTimer;

    Dll_usb_mmf01stl* stl;
    bool isSended = false;
    QMap<int, int (*)[3]> mCommands;
    int idxSizeCommands;


signals:
    void thsrl_cds(int** _cmd);
    void send_clicked(QList<int> _qai3, int _legNo);

private slots:

    void srl_ai3();

    void fileTimerTimeOut();

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

private:
    Ui::MainWindow *ui;
};


class SerialWorker;

class Dll_usb_mmf01stl : public QObject{


        Q_OBJECT

    public:
        explicit Dll_usb_mmf01stl(QObject *parent = nullptr);
        ~Dll_usb_mmf01stl();

    bool srl_i(const int _iDegree, const int _id);
    int i_srl(int _id);
    void cmd_id(unsigned char cmd_[11],const int& _iDegree,const int& _id );
    void req_id(unsigned char req_[6],const int& _id );
    bool thsri_pai3(const int _ai3[3],const unsigned short _row);



    SerialWorker* sWorker;
    SerialWorker* mWorker;
    QThread* sThread;
    QThread* mThread;

signals:
    void write_cmd(char* _cmd);
    void write_req(char* _req);


public slots:
    bool srl_pai3(int** _cmd);
    bool thsri_qai3(QList<int> _qai3, int _legNo);
};










class SerialWorker : public QObject{


        Q_OBJECT

    public:
        explicit SerialWorker(QObject *parent = nullptr);
        ~SerialWorker();

    QSerialPort* port;



signals:



public slots:
    void onWrite_cmd(char* _cmd);
    int  onWrite_req(QByteArray _req, int _id);
    QList<int> onLv_clicked(int legNo);



};

#endif // MAINWINDOW_HPP
