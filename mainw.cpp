#include "mainw.h"
#include "ui_mainw.h"

//#include <windows.h>
//#include <QTime>

MainW::MainW(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainW)
{
    //初始化ui
    ui->setupUi(this);
    setFixedSize(260,400);

    //初始化
    init();

    //进度条
    //初始化边界
    int num = 100;
    ui->progressBar->setRange(0, num);
    //程序打开，启动进度条
    startProTimer();
}

MainW::~MainW()
{
    delete ui;
}

void MainW::init(){
    //一个配置
    QSettings * m_psetting = nullptr;
    QCoreApplication::applicationDirPath(); //获取可执行文件所在路径
    QString configFileName = QCoreApplication::applicationDirPath() + "/Config.ini";
    //根据Config.ini路径new QSetting对象
    m_psetting = new QSettings(configFileName, QSettings::IniFormat);
    //判断Config.ini是否存在，若不存在则再可执行文件的同级目录下创建一个Config.ini
    QFileInfo fileInfo(configFileName);
    if(!fileInfo.exists())
    {
        //打印创建文件的路径
        qDebug("%s 不存在。", configFileName.toLatin1().data());
        //写入默认值
        m_psetting->beginGroup("player");
        m_psetting->setValue("level", 0);
        m_psetting->setValue("progress", 0);
        m_psetting->setValue("martialmethod", 0);
        m_psetting->setValue("proSpeed", 10);
        m_psetting->endGroup();
        m_psetting->beginGroup("bag");
        m_psetting->setValue("hunyuan",0);
        m_psetting->setValue("ningqi",0);
    }

    //读取配置
    int initProgress = m_psetting->value("player/progress").toInt();
    int initLevel = m_psetting->value("player/level").toInt();
    int initMartialMethod = m_psetting->value("player/martialmethod").toInt();
    int initHunyuan = m_psetting->value("bag/hunyuan").toInt();
    int initNingqi = m_psetting->value("bag/ningqi").toInt();
    //输出日志
    qDebug() << "进度：" << initProgress;
    qDebug() << "境界：" << initLevel;
    qDebug() << "功法：" << initMartialMethod;
    qDebug() << "修炼速度：" << m_psetting->value("player/proSpeed").toInt();
    qDebug() << "混元丹：" << initHunyuan;
    qDebug() << "凝气丹：" << initNingqi;
    //境界初始化
    if(initLevel == 0){
        ui->stateLabel->setText("炼气");
    }
    else if(initLevel == 1){
       ui->stateLabel->setText("筑基");
    }
    else if(initLevel == 2){
        ui->stateLabel->setText("金丹");
    }
    else if(initLevel == 3){
       ui->stateLabel->setText("元婴");
    }
    else if(initLevel == 4){
        ui->stateLabel->setText("合体");
    }
    else if(initLevel == 5){
       ui->stateLabel->setText("大乘");
    }
    else if(initLevel == 6){
        ui->stateLabel->setText("渡劫");
    }
    else if(initLevel == 7){
       ui->stateLabel->setText("神仙");
    }
    else{
        qDebug() << "配置出错";
        ui->stateLabel->setText("配置读取出错，请尝试重启本软件");
    }
    //修炼速度初始化
    proSpeed = m_psetting->value("player/proSpeed").toInt();
    //练功进度初始化
    ui->progressBar->setValue(initProgress);
    tick = initProgress;
    //功法初始化
    QStringList methods;
    if(initMartialMethod == 1001){
        methods << "晨曦吐纳法";
        proSpeed = int(proSpeed / 1.1);
    }
    else if(initMartialMethod == 0){
        methods << "人族修炼总纲";
    }
    else{
        methods << "未知功法";
    }
    ui->MartialMethodList->addItems(methods);

}

void MainW::startProTimer()
{
    //用qTimer来控制进度条
    proTimer = new QTimer();
    connect(this->proTimer, SIGNAL(timeout()), this, SLOT(start()));
    proTimer->start(proSpeed); //50可以换成其他数值，越大进度条越慢，越小进度条越快
}
void MainW::start()
{
    if (tick < 101){
        ui->progressBar->setValue(tick++);
    }
    else{
        tick = 1;
//        disconnect(this->proTimer, SIGNAL(timeout()), this, SLOT(start())); //若断开链接，进度条会一直重复
        ui->progressBar->reset(); //进度条归零
        proSpeed = int(proSpeed * 1.2);
        proTimer->start(proSpeed);
    }
}

void MainW::on_list_clicked()
{
    //排行榜功能未开发提示
    QMessageBox::information(this, "提示", "暂未开发，敬请期待", QMessageBox::Ok , QMessageBox::Ok);
}

void MainW::on_medicine_clicked()
{
    //显示丹药子窗口
    medicineWidget.show();
}

void MainW::on_magicWeapons_clicked()
{
    //法宝功能未开发提示
    QMessageBox::information(this, "提示", "暂未开发，敬请期待", QMessageBox::Ok , QMessageBox::Ok);
}
