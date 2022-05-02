#include "medicine.h"
#include "ui_medicine.h"

Medicine::Medicine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Medicine)
{
    ui->setupUi(this);
    //初始化
    init();
    //固定窗口大小
    setFixedSize(230,240);

    //设置窗口标题
    setWindowTitle("丹药");

    //设置窗口图标
    setWindowIcon(QIcon(":/ico.ico"));

    //listwidget右键菜单
    //重要：设置QListWidget的contextMenuPolicy属性，不然不能显示右键菜单
    ui->bagList->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    //添加一个菜单
    popMenuInListWidget = new QMenu(this);
    //使用动作
    actionUseInListWidget = new QAction(tr("使用"), this);
    //购买动作
    actionBuyInListWidget = new QAction(tr("购买"), this);
    //把动作添加到菜单里
    popMenuInListWidget->addAction(actionUseInListWidget);
    popMenuInListWidget->addAction(actionBuyInListWidget);

    //为菜单上的Use选项添加响应函数
    connect(this->actionUseInListWidget, SIGNAL(triggered()), this, SLOT(onActionUse()));
    //为菜单上的Buy选项添加响应函数
    connect(this->actionBuyInListWidget, SIGNAL(triggered()), this, SLOT(onActionBuy()));

    //绑定右键显示菜单：在单击右键之后会执行槽函数， 槽函数中负责弹出右键菜单
    connect(ui->bagList, SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(onCustomContextMenuRequested(const QPoint &)));

}

void Medicine::init()
{
    //一个配置
    QSettings * myConfig = nullptr;
    QCoreApplication::applicationDirPath(); //获取可执行文件所在路径
    QString configFileName = QCoreApplication::applicationDirPath() + "/Config.ini";
    //根据Config.ini路径new QSetting对象
    myConfig = new QSettings(configFileName, QSettings::IniFormat);
    //读取配置
    QString initHunyuan = myConfig->value("bag/hunyuan").toString();
    QString initNingqi = myConfig->value("bag/ningqi").toString();
    QString initMoney = myConfig->value("bag/money").toString();
    //添加库存
    //丹药库存
    QTreeWidgetItem * hunyuan = new QTreeWidgetItem(QStringList()<< "混元丹" << initHunyuan);
    QTreeWidgetItem * ningqi = new QTreeWidgetItem(QStringList()<< "凝气丹" << initNingqi);
    ui->bagList->addTopLevelItem(hunyuan);
    ui->bagList->addTopLevelItem(ningqi);
    //剩余灵石
    ui->money->setText(initMoney);
}

Medicine::~Medicine()
{
    delete ui;
}

void Medicine::onCustomContextMenuRequested(const QPoint &pos)
{
    //弹出右键菜单
    popMenuInListWidget->exec(QCursor::pos());
}

//右键菜单使用事件
void Medicine::onActionUse()
{
    //获取当前选中的Item
    QTreeWidgetItem * item = ui->bagList->currentItem();

    //弹出询问对话框
    if(QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("使用丹药"),
        QStringLiteral("使用1个%1？").arg((item->text(0))), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        //如果选择Yes
        int count = item->text(1).toInt();
        qDebug() << "使用前丹药数量：" << count;
        if(count < 1)
        {
            //如果丹药数量为零，弹窗报错
            QMessageBox::warning(this, "错误", "没有足够的丹药", QMessageBox::Ok , QMessageBox::Ok);
        }
        else
        {
            //减去一个丹药库存
            count--;
            //int -> QString
            QString strCount = QString::number(count);
            item->setText(1,strCount);
            if(item->text(0) == "混元丹")
            {
                //向主窗口发送使用丹药的信号
                emit hunyuanUsed();
            }
            else if(item->text(0) == "凝气丹")
            {
                //向主窗口发送使用丹药的信号
                emit ningqiUsed();
            }
        }
    }
}

//右键菜单购买事件
void Medicine::onActionBuy()
{
    //获取当前选中的Item
    QTreeWidgetItem * item = ui->bagList->currentItem();

    //弹出询问对话框
    if(QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("购买丹药"),
        QStringLiteral("花费100灵石\n购买1个%1？").arg((item->text(0))), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        //如果选择Yes
        //获取购买前数量
        int count = item->text(1).toInt();
        qDebug() << "购买前丹药数量：" << count;
        //获取余额
        balance = ui->money->text().toInt();
        if(balance >= 100)
        {
            //余额足够
            //扣钱
            balance -= 100;
            //int -> QString
            QString strBalance = QString::number(balance);
            ui->money->setText(strBalance);
            //增加一个丹药库存
            count++;
            //int -> QString
            QString strCount = QString::number(count);
            item->setText(1,strCount);
        }
    }
}
