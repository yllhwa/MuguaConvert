#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QDebug>
#include <QFileDialog>
#include <QDesktopServices>
#include <string>
#include "about.h"
#include "video_form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool use_multithreading;
    bool use_hardware;
    bool out2src;
    QString outpath;
    void c_multithreading(void);
    void c_hardware(void);
    void c_out2src(void);
    void on_c_outdir(void);
    void on_output_dir_toggled(void);
    void on_about(void);
    void on_video(void);
    void on_audio(void);

private:
    Ui::MainWindow *ui;
    QCheckBox *multi_thread;
    QCheckBox *hardware_speedup;
};
#endif // MAINWINDOW_H
