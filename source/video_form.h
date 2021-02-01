#ifndef VIDEO_FORM_H
#define VIDEO_FORM_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QProgressBar>
#include "ffmpegutilsh.h"

namespace Ui {
class video_form;
}

class video_form : public QWidget
{
    Q_OBJECT

public:
    explicit video_form(QWidget *parent = nullptr);
    bool out2src;
    QString outpath;
    void convert();
    void SetProgressBar(float value);
    Ui::video_form *ui;
    ~video_form();
    void set_audio(void);


private slots:
    void on_convert_btn_clicked();

private:
    QString file;
};

#endif // VIDEO_FORM_H
