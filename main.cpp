#include "TestApp.h"
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
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
            logWidget->addItem(msg);
            break;
        }
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
