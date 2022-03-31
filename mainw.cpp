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
//    progressBarBoundary = 100;
    ui->progressBar->setRange(0, proBarBoundary);
    //初始化显示
    /*
     * %v - 被当前值所取代
     * %m - 被总步数所取代
     */
    ui->progressBar->setFormat(" %v / %m");
    //程序打开，启动进度条
    startProTimer();

    //在子窗口更改昵称，主窗口昵称刷新
    connect(&regWidget, &Register::reNamed, this, &MainW::registered);
    //在丹药子窗口使用混元丹，主窗口增加修炼进度
    connect(&medicineWidget, &Medicine::hunyuanUsed, this, &MainW::hunyuanUse);
}

MainW::~MainW()
{
    delete ui;
}

void MainW::init(){
    //一个配置
//    QSettings * m_psetting = nullptr;
    QCoreApplication::applicationDirPath(); //获取可执行文件所在路径
    QString configFileName = QCoreApplication::applicationDirPath() + "/Config.ini";
    //根据Config.ini路径new QSetting对象
    myConfig = new QSettings(configFileName, QSettings::IniFormat);
    //判断Config.ini是否存在，若不存在则再可执行文件的同级目录下创建一个Config.ini
    QFileInfo fileInfo(configFileName);
    if(!fileInfo.exists())
    {
        //打印创建文件的路径
        qDebug("%s 不存在。", configFileName.toLatin1().data());
        //写入默认值
        myConfig->beginGroup("player");
        myConfig->setValue("name", "未知");
        myConfig->setValue("level", 0);
        myConfig->setValue("progress", 0);
        myConfig->setValue("martialmethod", 0);
        myConfig->setValue("proSpeed", 40);
        myConfig->endGroup();
        myConfig->beginGroup("bag");
        myConfig->setValue("hunyuan", 0);
        myConfig->setValue("ningqi", 0);
        myConfig->setValue("money", 500);
    }

    //读取配置
    QString initName = myConfig->value("player/name").toString();
    int initProgress = myConfig->value("player/progress").toInt();
    int initLevel = myConfig->value("player/level").toInt();
    int initMartialMethod = myConfig->value("player/martialmethod").toInt();
    int initHunyuan = myConfig->value("bag/hunyuan").toInt();
    int initNingqi = myConfig->value("bag/ningqi").toInt();
    int initMoney = myConfig->value("bag/money").toInt();

    //输出日志
    qDebug() << "昵称：" << initName;
    qDebug() << "进度：" << initProgress;
    qDebug() << "境界：" << initLevel;
    qDebug() << "功法：" << initMartialMethod;
    qDebug() << "修炼速度：" << myConfig->value("player/proSpeed").toInt();
    qDebug() << "混元丹：" << initHunyuan;
    qDebug() << "凝气丹：" << initNingqi;
    qDebug() << "钱：" << initMoney;

    //昵称初始化
    ui->name->setText(initName);
    //如果已注册昵称则隐藏注册按钮
    if(initName != "未知")
    {
        ui->regBtn->hide();
    }
    //境界初始化
    newLevel = initLevel;
    if(initLevel == 0)
    {
        ui->stateLabel->setText("炼气");
    }
    else if(initLevel == 1)
    {
        ui->stateLabel->setText("筑基");
    }
    else if(initLevel == 2)
    {
        ui->stateLabel->setText("金丹");
    }
    else if(initLevel == 3)
    {
        ui->stateLabel->setText("元婴");
    }
    else if(initLevel == 4)
    {
        ui->stateLabel->setText("合体");
    }
    else if(initLevel == 5)
    {
        ui->stateLabel->setText("大乘");
    }
    else if(initLevel == 6)
    {
        ui->stateLabel->setText("渡劫");
    }
    else if(initLevel == 7)
    {
        ui->stateLabel->setText("仙");
    }
    else
    {
        qDebug() << "配置出错";
        ui->stateLabel->setText("配置读取出错，请尝试重启本软件");
    }
    //修炼速度初始化
    proSpeed = myConfig->value("player/proSpeed").toInt();
    //练功进度初始化
    ui->progressBar->setValue(initProgress);
    tick = initProgress;
    //功法初始化
    QStringList methods;
    if(initMartialMethod == 1001)
    {
        methods << "晨曦吐纳法";
        proSpeed = int(proSpeed / 1.1);
    }
    else if(initMartialMethod == 0)
    {
        methods << "人族修炼总纲";
    }
    else
    {
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
    if(tick < proBarBoundary+1)
    {
        tick = ui->progressBar->value()+1;
        ui->progressBar->setValue(tick++);
    }
    else
    {
        tick = 1;
        ui->progressBar->reset(); //进度条归零
        //提升境界
        newLevel ++;
        //境界判断，更改显示
        levelJudge();
        //修改修炼速度
//        proSpeed = int(proSpeed * 4);
        //修改进度条边界
        proBarBoundary = proBarBoundary * int(pow(2,newLevel));
        ui->progressBar->setRange(0, proBarBoundary);
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

void MainW::on_regBtn_clicked()
{
    //显示昵称编辑界面
    regWidget.show();
}

void MainW::on_magicWeapons_clicked()
{
    //法宝功能未开发提示
    QMessageBox::information(this, "提示", "暂未开发，敬请期待", QMessageBox::Ok , QMessageBox::Ok);
}

void MainW::levelJudge()
{
    if(newLevel == 0)
    {
        ui->stateLabel->setText("炼气");
    }
    else if(newLevel == 1)
    {
        ui->stateLabel->setText("筑基");
    }
    else if(newLevel == 2)
    {
        ui->stateLabel->setText("金丹");
    }
    else if(newLevel == 3)
    {
        ui->stateLabel->setText("元婴");
    }
    else if(newLevel == 4)
    {
        ui->stateLabel->setText("合体");
    }
    else if(newLevel == 5)
    {
        ui->stateLabel->setText("大乘");
    }
    else if(newLevel == 6)
    {
        ui->stateLabel->setText("渡劫");
    }
    else if(newLevel == 7)
    {
        ui->stateLabel->setText("仙");
    }
    else
    {
        qDebug() << "境界判断出错";
        ui->stateLabel->setText("出错，请尝试重启本软件");
    }
}

//刷新昵称函数
void MainW::registered()
{
    QString Name = myConfig->value("player/name").toString();
    ui->name->setText(Name);
    //隐藏注册按钮
    ui->regBtn->hide();
}

void MainW::hunyuanUse()
{
    //修炼进度增加100
    int proValue = ui->progressBar->value();
    qDebug() << proValue;
    proValue += 100;
    qDebug() << proValue;
    ui->progressBar->setValue(proValue);
}
