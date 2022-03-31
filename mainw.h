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
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainW; }
QT_END_NAMESPACE

class MainW : public QWidget
{
    Q_OBJECT

public:
    MainW(QWidget *parent = nullptr);
    ~MainW();

    //昵称修改信号
    void registered();
    //使用混元丹
    void hunyuanUse();
    //使用凝气丹
    void ningqiUse();

private slots:

    void start();

    void on_list_clicked();

    void on_medicine_clicked();

    void on_magicWeapons_clicked();

    void on_regBtn_clicked();

private:
    Ui::MainW *ui;
    void startProTimer();
    void init();
    //进度条计时器
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
    //保存配置函数
    void saveAllConfig();
    //配置
    QSettings * myConfig = nullptr;
    //进度条边界
    int proBarBoundary = 1500;
};
#endif // MAINW_H
