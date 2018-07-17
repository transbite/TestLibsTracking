#include "TestApp.h"
#include "ui_TestApp.h"
#include <QDebug>
#include <QThread>




TestApp::TestApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestApp)

{
    ui->setupUi(this);

    QObject::connect( qApp, SIGNAL(lastWindowClosed()), this, SLOT(stop()));

    m_controlTracking = new ControlTracking();

    connect(ui->initButton, &QPushButton::clicked, this, &TestApp::init);
    connect(ui->stopButton, &QPushButton::clicked, this, &TestApp::stop);
    connect(ui->positionsButton, &QPushButton::clicked, this, &TestApp::positions);
    connect(ui->startButton, &QPushButton::clicked, this, &TestApp::start);
    connect(ui->sendCmdButton, &QPushButton::clicked, this, &TestApp::command);

}
void TestApp::init()
{
    m_controlTracking->init();
}

TestApp::~TestApp()
{
    delete ui;
    delete m_controlTracking;
}

void TestApp::stop()
{

   m_controlTracking->stopTracking();
   qDebug() << m_controlTracking->getTrackingStatus();

}
void TestApp::start()
{
   m_controlTracking->startTracking();
}
void TestApp::positions(int tool)
{
    tool = 1;
    //while (true)
    for (int k =0; k < 200; k++)
    {
        //if(m_controlTracking->getTrackingStatus() == 1)
        //{
            m_controlTracking->getToolPositionOrientation(tool);
        //}
//        else
//        {
//            break;
//        }

      ::Sleep(200);
    }
}

void TestApp::command()

{
    int tool = 1;
    const char* cmd = "PHSR:00";
    qDebug() << m_controlTracking->commandResponse(cmd);

    qDebug() << m_controlTracking->getToolManufacturer(tool) << m_controlTracking->getToolType(tool);

}
