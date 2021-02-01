#include "ffmpegutilsh.h"

void ffmpegutilsh::run()
{
    QProcess process;
    qint64 bufferLength;
    char buffer[1024];
    bool waitResult;
    QString output;
    float processedSeconds;

    process.start(ffmpegPath,params);
    waitResult = process.waitForStarted();
    process.setReadChannel(QProcess::StandardError);
    if(!waitResult)
    {
        emit CheckSignal(-1);
    }
    while(true)
    {
        waitResult=process.waitForReadyRead();
        if(!waitResult)
        {
            break;
        }
        while(true)
        {
            bufferLength=process.readLine(buffer,1024);
            if(bufferLength<=0)
            {
                break;
            }
            output = QString::fromLocal8Bit(buffer);
            if(output.indexOf("Duration:")!=-1)
            {
                videoSeconds = output.mid(12,2).toInt()*60*60+output.mid(15,2).toInt()*60+output.mid(18,2).toInt();
            }
            if(output.indexOf("time=")!=-1)
            {
                processedSeconds = output.mid(output.indexOf("time=")+5,2).toInt()*60*60+output.mid(output.indexOf("time=")+8,2).toInt()*60+output.mid(output.indexOf("time=")+11,2).toInt();
                emit CheckSignal(processedSeconds/videoSeconds);
            }
        }
    }
    emit CheckSignal(1);
    process.close();
}
