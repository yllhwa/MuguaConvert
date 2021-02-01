#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);  //设置工具栏图标下显示文字
    setFixedSize(this->width(), this->height());  //使用固定大小
    outpath = QDir::currentPath();
    QFontMetrics fontWidth(ui->outputdir_display->font());//得到每个字符的宽度
    QString elideNote = fontWidth.elidedText(QDir::currentPath(), Qt::ElideMiddle, ui->outputdir_display->width());//最大宽度150像素
    ui->outputdir_display->setText(elideNote);//显示省略好的字符串
    ui->outputdir_display->setToolTip(QDir::currentPath());//设置tooltips

    /*
    //设置状态栏 多线程和硬件加速 默认选中
    multi_thread = new QCheckBox("使用多线程", this);
    hardware_speedup = new QCheckBox("使用硬件加速", this);
    multi_thread->setCheckState(Qt::Checked);
    hardware_speedup->setCheckState(Qt::Checked);
    statusBar()->addWidget(multi_thread);
    statusBar()->addWidget(hardware_speedup);
    use_multithreading=true;
    use_hardware=true;
    connect(multi_thread,&QCheckBox::stateChanged,this,&MainWindow::c_multithreading);
    connect(hardware_speedup,&QCheckBox::stateChanged,this,&MainWindow::c_hardware);
    */
    out2src=false;
    //设置是否输出到原地址
    connect(ui->out2src_checkbox,&QCheckBox::stateChanged,this,&MainWindow::c_out2src);

    //更改输出目录
    connect(ui->change_outputdir_btn,&QPushButton::clicked,this,&MainWindow::on_c_outdir);

    //点击工具栏 输出文件夹
    connect(ui->output_dir,&QAction::triggered,this,&MainWindow::on_output_dir_toggled);

    //点击工具栏 关于
    connect(ui->about,&QAction::triggered,this,&MainWindow::on_about);

    //点击视频按钮
    connect(ui->video_btn,&QPushButton::clicked,this,&MainWindow::on_video);
    //点击音频按钮
    connect(ui->audio_btn,&QPushButton::clicked,this,&MainWindow::on_audio);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::c_multithreading(void)
{
    use_multithreading=!use_multithreading;
    //qDebug()<<"thread"<<use_multithreading;
}

void MainWindow::c_hardware(void)
{
    use_hardware=!use_hardware;
    //qDebug()<<"hardware"<<use_hardware;
}

void MainWindow::c_out2src(void)
{
    out2src=!out2src;
    //qDebug()<<"out2src"<<out2src;
}

void MainWindow::on_c_outdir(void)
{
      QFileDialog *fileDialog = new QFileDialog(this);
      fileDialog->setWindowTitle(tr("打开文件"));
      //设置为选择文件夹
      fileDialog->setFileMode( QFileDialog::DirectoryOnly );
      //设置视图模式
      fileDialog->setViewMode(QFileDialog::Detail);
      //打印所有选择的文件的路径
      QStringList out_dir;
      if (fileDialog->exec())
      {
        out_dir = fileDialog->selectedFiles();
        outpath=out_dir[0];
        //qDebug() << outpath;
      }
      QFontMetrics fontWidth(ui->outputdir_display->font());//得到每个字符的宽度
      QString elideNote = fontWidth.elidedText(out_dir[0], Qt::ElideMiddle, ui->outputdir_display->width());//最大宽度150像素
      ui->outputdir_display->setText(elideNote);//显示省略好的字符串
      ui->outputdir_display->setToolTip(QDir::currentPath());//设置tooltips
}

void MainWindow::on_output_dir_toggled(void)
{
    qDebug() << outpath;
    QDesktopServices::openUrl(QUrl::fromLocalFile(outpath.toStdString().c_str()));
}

void MainWindow::on_about(void)
{
    About *sub_about = new About;
    sub_about->show();
}

void MainWindow::on_video(void)
{
    video_form *sub_video = new video_form;
    sub_video->use_multithreading = this->use_multithreading;
    sub_video->use_hardware = this->use_hardware;
    sub_video->out2src = this->out2src;
    sub_video->outpath = this->outpath;
    sub_video->show();
}


void MainWindow::on_audio(void)
{
    video_form *sub_audio = new video_form;
    sub_audio->set_audio();
    sub_audio->use_multithreading = this->use_multithreading;
    sub_audio->use_hardware = this->use_hardware;
    sub_audio->out2src = this->out2src;
    sub_audio->outpath = this->outpath;
    sub_audio->setWindowTitle("音频格式转换");
    sub_audio->show();
}
