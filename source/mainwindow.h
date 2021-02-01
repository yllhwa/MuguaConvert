#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
//#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class: MainWindow
 * @version: 1.0
 * @author: yll
 * @brief：主窗口类
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //是否输出到源文件夹
    bool out2src;
    //输出路径
    QString outpath;

    /**
     * @method: setSuitableText
     * @param_1: 要修改的文本框
     * @param_2: 填入文本框的字符串
     * @func: 将过长的字符串中间用省略号代替，填入文本框
     */
    void setSuitableText(QLabel *lable,QString string);

private slots:
    void on_out2src_checkbox_stateChanged(int arg1);

    void on_change_outputdir_btn_clicked();

    void on_output_dir_triggered();

    void on_about_triggered();

    void on_video_btn_clicked();

    void on_audio_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
