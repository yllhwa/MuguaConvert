#ifndef AUDIO_FORM_H
#define AUDIO_FORM_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QProgressBar>
#include "ffmpegutilsh.h"

namespace Ui {
class audio_form;
}

class audio_form : public QWidget
{
    Q_OBJECT

public:
    explicit audio_form(QWidget *parent = nullptr);
    bool use_multithreading;
    bool use_hardware;
    bool out2src;
    QString outpath;
    void convert();
    void SetProgressBar(float value);
    ~audio_form();


private slots:
    void on_convert_btn_clicked();

private:
    Ui::audio_form *ui;
    QString file;
};

#endif // AUDIO_FORM_H
