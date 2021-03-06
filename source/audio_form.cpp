#include "audio_form.h"
#include "ui_audio_form.h"
#include "ffmpegutilsh.h"
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QProgressBar>

audio_form::audio_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::audio_form)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开文件"));
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //设置文件类型过滤器
    //fileDialog->setNameFilter(tr("VideoFile(*.ui *.cpp)"));
    QStringList file_list;
    if (fileDialog->exec())
    {
        file_list = fileDialog->selectedFiles();
        file = file_list[0];
        //qDebug() << outpath;
    }
    else
    {
        this->close();
    }

    setFixedSize(this->width(), this->height());  //使用固定大小

}

audio_form::~audio_form()
{
    delete ui;
}

void audio_form::convert()
{
    QProcess process;
    QString output;
    QString ffmpegPath;  //ffmpeg路径
    QString resWidth;  //视频宽度
    QString resHeight;  //视频高度
    QString outputVideoPath;  //视频输出目录
    QStringList params;  //视频参数列表
    QFileInfo fileinfo;  //文件信息
    QString file_name;  //不含后缀的文件名

    fileinfo = QFileInfo(file);
    file_name = fileinfo.fileName().section(".",0,0);;
    if(out2src==true)
    {
        outputVideoPath = fileinfo.path()+'/'+file_name+'.'+ui->comboBox->currentText();
        qDebug()<<outputVideoPath;
    }
    else
    {
        outputVideoPath = outpath+'/'+file_name+'.'+ui->comboBox->currentText();
    }

    /*test_case*/
    ffmpegPath = "C:\\Users\\yll20\\Desktop\\work\\c++\\2021_1_23\\3\\ffmpeg.exe";
    params<<"-y"<<"-i"<<file<<outputVideoPath;
    /*end_test_case*/

    ffmpegutilsh *ffhelp = new ffmpegutilsh();
    ffhelp->ffmpegPath=ffmpegPath;
    ffhelp->params=params;
    connect(ffhelp,&ffmpegutilsh::CheckSignal,this,&audio_form::SetProgressBar);
    ffhelp->start();
}
void audio_form::SetProgressBar(float value)
{
    ui->progressBar->setValue(value*100);
    if(value==1)
    {
        this->close();
    }
}

void audio_form::on_convert_btn_clicked()
{
    convert();
}
