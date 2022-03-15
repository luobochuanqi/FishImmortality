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
    qDebug() << nameReturn;
}
