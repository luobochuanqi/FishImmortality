#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

    QString nameReturn = "无返回值";

private slots:
    void on_ok_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
