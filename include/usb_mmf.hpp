#ifndef USB_MMF_HPP
#define USB_MMF_HPP
#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>
#include <QtConcurrent>
#include <QFileDialog>
#include <QMutex>
#include <QThread>
namespace Ui {
class Usb_mmf;
}

class QDESIGNER_WIDGET_EXPORT Usb_mmf : public QWidget
{
    Q_OBJECT

public:
    explicit Usb_mmf(QWidget *parent = nullptr);
    ~Usb_mmf();
    QTimer* mmfTimer;

private slots:
    void on_btn_mmf_clicked();
    void on_timer_readEnc_stateChanged(int arg1);
    void on_tbr_delay_valueChanged(int value);

signals:
    void mmfClicked();

private:
    Ui::Usb_mmf *ui;
};

#endif // USB_MMF_HPP
