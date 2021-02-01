#include "work_form.h"
#include "ui_work_form.h"
#include "ffmpegutilsh.h"
#include <QFileDialog>
#include <QDebug>
#include <QProgressBar>

work_form::work_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::work_form)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);  //关闭时自动释放
    ffhelp=NULL;
    setFixedSize(this->width(), this->height());  //使用固定大小
    get_file();
}

work_form::~work_form()
{
    if(ffhelp!=NULL)
    {
        delete ffhelp;
        ffhelp=NULL;
    }
    delete ui;
}

void work_form::convert()
{
    QString ffmpegPath;  //ffmpeg路径
    QString outputVideoPath;  //视频输出目录
    QStringList params;  //视频参数列表
    QFileInfo fileinfo;  //文件信息
    QString file_name;  //不含后缀的文件名

    fileinfo = QFileInfo(file);
    file_name = fileinfo.fileName().section(".",0,0);
    if(out2src==true)
    {
        outputVideoPath = fileinfo.path()+'/'+file_name+'.'+ui->comboBox->currentText();
    }
    else
    {
        outputVideoPath = outpath+'/'+file_name+'.'+ui->comboBox->currentText();
    }

    ffmpegPath = "ffmpeg.exe";
    params<<"-y"<<"-i"<<file<<outputVideoPath;

    ffhelp = new ffmpegutilsh();
    ffhelp->ffmpegPath=ffmpegPath;
    ffhelp->params=params;
    connect(ffhelp,&ffmpegutilsh::CheckSignal,this,&work_form::SetProgressBar);
    ffhelp->start();
}
void work_form::SetProgressBar(float value)
{
    ui->progressBar->setValue(value*100);
    if(value==1)
    {
        this->close();
    }
}

void work_form::on_convert_btn_clicked()
{
    convert();
}

void work_form::set_audio(void)
{
    ui->comboBox->clear();
    ui->comboBox->addItem("mp3");
    ui->comboBox->addItem("wav");
}

void work_form::get_file()
{
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
    }
    else
    {
        delete fileDialog;
        this->close();
        return;
    }
    delete fileDialog;
}
