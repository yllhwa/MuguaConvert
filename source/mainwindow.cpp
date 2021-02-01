//主窗口头文件
#include "mainwindow.h"
#include "ui_mainwindow.h"
//子窗口头文件
#include "about.h"
#include "video_form.h"
//依赖头文件
#include <QFileDialog>
#include <QDesktopServices>
//#include <QCheckBox>
//调试输出头文件
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);  //设置工具栏图标下显示文字
    setFixedSize(this->width(), this->height());  //使用固定大小

    outpath = QDir::currentPath();
    out2src=false;

    setSuitableText(ui->outputdir_display,QDir::currentPath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSuitableText(QLabel *lable, QString string)
{
    QFontMetrics fontWidth(lable->font());  //得到每个字符的宽度
    QString elideNote = fontWidth.elidedText(string, Qt::ElideMiddle, lable->width());
    lable->setText(elideNote);  //显示省略好的字符串
    lable->setToolTip(string);  //设置tooltips
}

void MainWindow::on_out2src_checkbox_stateChanged(int arg1)
{
    out2src=arg1;
}

void MainWindow::on_change_outputdir_btn_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开文件"));
    //设置为选择文件夹
    fileDialog->setFileMode( QFileDialog::DirectoryOnly );
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList out_dir;
    if (fileDialog->exec())
    {
      out_dir = fileDialog->selectedFiles();
      outpath=out_dir[0];
      setSuitableText(ui->outputdir_display,out_dir[0]);
      delete fileDialog;
      return;
    }
    delete fileDialog;
}

void MainWindow::on_output_dir_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(outpath.toStdString().c_str()));
}

void MainWindow::on_about_triggered()
{
    About *sub_about = new About;
    sub_about->show();
    //About中设置了WA_DeleteOnClose，不用管delete
}

void MainWindow::on_video_btn_clicked()
{
    video_form *sub_video = new video_form;
    sub_video->out2src = this->out2src;
    sub_video->outpath = this->outpath;
    sub_video->show();
}

void MainWindow::on_audio_btn_clicked()
{
    video_form *sub_audio = new video_form;
    sub_audio->out2src = this->out2src;
    sub_audio->outpath = this->outpath;
    sub_audio->set_audio();
    sub_audio->setWindowTitle("音频格式转换");
    sub_audio->show();
}
