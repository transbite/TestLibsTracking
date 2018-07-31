#include "TestApp.h"
#include "globals.h"
#include <QApplication>
#include <QDebug>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    if (logWidget == nullptr)
    {
        // TBD - store messages elsewhere
    }
    else
    {
        QString message;
        switch (type)
        {
        case QtDebugMsg:
            message = QString("[DEBUG] ") + msg;
            break;
        case QtInfoMsg:
            message = QString("[INFO] ") + msg;
            break;
        case QtWarningMsg:
            message = QString("[WARNING] ") + msg;
            break;
        case QtCriticalMsg:
            message = QString("[CRITICAL] ") + msg;
            break;
        case QtFatalMsg:
            message = QString("[FATAL] ") + msg;
            break;
        }
        logWidget->addItem(message);
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    TestApp w;
    w.show();

    return a.exec();
}
