#ifndef FFMPEGUTILSH_H
#define FFMPEGUTILSH_H
#include <QDebug>
#include <QString>
#include <QThread>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>


class ffmpegutilsh:public QThread
{
    Q_OBJECT
public:
    QString ffmpegPath;
    QStringList params;
    float videoSeconds;
protected:
    void run();
signals:
    void CheckSignal(float value);
};

#endif // FFMPEGUTILSH_H
