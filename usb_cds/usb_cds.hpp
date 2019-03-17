#ifndef USB_CDS_HPP
#define USB_CDS_HPP
#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include "3dll_usb_cds01stt.hpp"


using namespace rv2;

pai3::p OFFSET = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };
pai3::p OFFSETTEMP = new i::t[6][3]{  {0, },{0, },{0, },{0, },{0, },{0, }  };

QMutex mutForSrl;

class Dll_usb_mmf01stl;

namespace Ui {
class Usb_cds;
}

class QDESIGNER_WIDGET_EXPORT Usb_cds : public QWidget
{
    Q_OBJECT

public:
    explicit Usb_cds(QWidget *parent = nullptr);
    ~Usb_cds();

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

    void on_lineEdit_returnPressed();

    void on_edPath_returnPressed();

    void on_btnClear_clicked();

private:
    Ui::Usb_cds *ui;
};

#endif // USB_CDS_HPP
