#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);  //关闭时自动释放
    setFixedSize(this->width(), this->height());  //使用固定大小
}

About::~About()
{
    delete ui;
}
