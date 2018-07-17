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

    connect(ui->initBut, &QPushButton::clicked, this, &TestApp::init);
    connect(ui->stopBut, &QPushButton::clicked, this, &TestApp::stop);
    connect(ui->positionBut, &QPushButton::clicked, this, &TestApp::positions);
    connect(ui->startBut, &QPushButton::clicked, this, &TestApp::start);
    connect(ui->sendCmdBut, &QPushButton::clicked, this, &TestApp::command);


    //newtracker = vtkNDITracker::New();


    //tool=3;tool1=4;tool2=5;

    //filename = "c:\\Users\\User\\work\\projects\\tests\\AIGSApp\\AIGSApp\\AIGSApp\\ToolsROM\\8700338.rom";
    //filename1 = "c:\\Users\\User\\work\\projects\\tests\\AIGSApp\\AIGSApp\\AIGSApp\\ToolsROM\\8700340.rom";


    //load roms file for tools
    //newtracker->LoadVirtualSROM(tool,filename);
    //newtracker->LoadVirtualSROM(tool1,filename1);



}
void TestApp::init()
{
    m_controlTracking->init("COM5:");
}

TestApp::~TestApp()
{
    delete ui;
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
