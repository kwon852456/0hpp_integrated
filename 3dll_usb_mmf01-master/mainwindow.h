#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSerialPort/QSerialPort"
#include <QtConcurrent>
#include <QFileDialog>
#include <QMutex>
#include <QThread>


namespace Ui {
class MainWindow;
}

class SerialWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QThread* sThread;
    SerialWorker* sWorker;
    QTimer* mmfTimer;

private slots:
    void on_btn_mmf_clicked();
    void on_actionQuit_triggered();
    void on_timer_readEnc_stateChanged(int arg1);
    void on_tbr_delay_valueChanged(int value);
    void on_btn_load_clicked();
    void on_cb_offset_toggled(bool checked);

    void on_cb_releaseOffset_stateChanged(int arg1);

signals:
    void mmf_status();
    void change_offset_sign();
    void temp_offset(int _stat);


private:
    Ui::MainWindow *ui;
};



class SerialWorker : public QObject{


        Q_OBJECT

    public:
    explicit SerialWorker(QObject *parent = nullptr);
    ~SerialWorker();
    void setIds();

    QSerialPort* srl;
    QList<int> ids;
    int (*offset)[3] = new int[6][3]{{0,}};
    int (*offsetTemp)[3] = new int[6][3]{{0,}};

    bool isSrlFinished = true;

signals:




public slots:
    void onMmfCheck_clicked();
    void change_sign();
    void temp_offset(int _stat);

};



#endif // MAINWINDOW_H
