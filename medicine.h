#ifndef MEDICINE_H
#define MEDICINE_H

#include <QWidget>
#include <QMenu>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>
//#include <mainw.h>
#include <QSettings>

namespace Ui {
class Medicine;
}

class Medicine : public QWidget
{
    Q_OBJECT

public:
    explicit Medicine(QWidget *parent = nullptr);
    ~Medicine();
public slots:
    //处理鼠标右键事件，弹出菜单
    void onCustomContextMenuRequested(const QPoint &pos);
    //处理弹出菜单上的Use事件
    void onActionUse();
    void onActionBuy();



private:
    Ui::Medicine *ui;

    void init();

    QMenu *popMenuInListWidget;/*弹出菜单*/
    QAction *actionUseInListWidget;/*菜单上的Action*/
    QAction *actionBuyInListWidget;/*菜单上的Action*/
};

#endif // MEDICINE_H
