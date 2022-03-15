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
#include <register.h>

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

    void on_register__clicked();

private:
    Ui::MainW *ui;
    void startProTimer();
    void init();
    QTimer *proTimer;
    int tick;
    int proSpeed;
    //丹药子窗口对象
    Medicine medicineWidget;
    //昵称编辑子窗口对象
    Register regWidget;
    //境界判断，改变显示境界
    void levelJudge();
    //境界改变
    int newLevel = 0;
};
#endif // MAINW_H
