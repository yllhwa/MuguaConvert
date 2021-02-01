#ifndef WORK_FORM_H
#define WORK_FORM_H

#include <QWidget>
#include "ffmpegutilsh.h"
namespace Ui {
class work_form;
}

class work_form : public QWidget
{
    Q_OBJECT

public:
    explicit work_form(QWidget *parent = nullptr);
    bool out2src;
    QString outpath;
    ffmpegutilsh *ffhelp;
    void set_audio(void);
    void get_file();
    void convert();
    void SetProgressBar(float value);

    ~work_form();

private slots:
    void on_convert_btn_clicked();

private:
    Ui::work_form *ui;
    QString file;
};

#endif // WORK_FORM_H
