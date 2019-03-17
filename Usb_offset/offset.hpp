#ifndef OFFSET_HPP
#define OFFSET_HPP

#include <QWidget>

#include <QtUiPlugin/QDesignerExportWidget>

namespace Ui {
class Offset;
}

class QDESIGNER_WIDGET_EXPORT Offset : public QWidget
{
    Q_OBJECT

public:
    explicit Offset(QWidget *parent = nullptr);
    ~Offset();
    QThread* sThread;


signals:
    void readOffset();
    void saveOffset();
    void loadOffset();

private slots:


    void on_btn_read_clicked();

    void on_btn_save_clicked();

    void on_btn_load_clicked();

private:
    Ui::Offset *ui;
};

#endif // OFFSET_HPP
