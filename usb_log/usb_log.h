#ifndef USB_LOG_H
#define USB_LOG_H
#include <QtUiPlugin/QDesignerExportWidget>
#include <QDebug>
#include <QWidget>
#include <QTimer>

namespace Ui {
class Usb_log;
}

class QDESIGNER_WIDGET_EXPORT Usb_log : public QWidget
{
    Q_OBJECT

public:
    explicit Usb_log(QWidget *parent = nullptr);
    ~Usb_log();

    QTimer* timer;

public slots:
    void setlog(QString text);
    void clearLog();
    void changeInterval(int _msTime);




private:
    Ui::Usb_log *ui;
};

#endif // USB_LOG_H
