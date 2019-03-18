#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSerialPort/QSerialPort"
#include <QtConcurrent>
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

private slots:
    void on_btn_read_clicked();

    void on_btn_save_clicked();

    void on_btn_load_clicked();

signals:
    void readOffset();
    void saveOffset();
    void loadOffset();

private:
    Ui::MainWindow *ui;
};



class SerialWorker : public QObject{


        Q_OBJECT
    public:
    explicit SerialWorker(QObject *parent = nullptr);
    ~SerialWorker();

    QSerialPort* srl;
    int (*offset)[3] = new int[6][3]{{0,}};


signals:



public slots:
    void onReadOffset();
    void onSaveOffset();

};

















#endif // MAINWINDOW_H
