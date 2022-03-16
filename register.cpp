#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    //设置窗口标题
    setWindowTitle("请输入你的昵称");
}

Register::~Register()
{
    delete ui;
}

void Register::on_ok_clicked()
{
    nameReturn = ui->nameedit->text();
    qDebug() << "修改的昵称：" << nameReturn;

    //一个配置
    QSettings * m_psetting = nullptr;
    QCoreApplication::applicationDirPath(); //获取可执行文件所在路径
    QString configFileName = QCoreApplication::applicationDirPath() + "/Config.ini";
    //根据Config.ini路径new QSetting对象
    m_psetting = new QSettings(configFileName, QSettings::IniFormat);
    //存储昵称配置
    m_psetting->setValue("player/name",nameReturn);
    //发送昵称更改信号
    emit reNamed();
}
