#ifndef MAINW_H
#define MAINW_H

#include <QWidget>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <QTimer>
#include <QMessageBox>
#include <medicine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainW; }
QT_END_NAMESPACE

class MainW : public QWidget
{
    Q_OBJECT

public:
    MainW(QWidget *parent = nullptr);
    ~MainW();

private slots:

    void start();

    void on_list_clicked();

    void on_medicine_clicked();

    void on_magicWeapons_clicked();

private:
    Ui::MainW *ui;
    void startProTimer();
    void init();
    QTimer *proTimer;
    int tick;
    int proSpeed;
    //丹药子窗口对象
    Medicine medicineWidget;
};
#endif // MAINW_H
