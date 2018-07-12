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

//    QString versionName;
//    int status;
//    int serialPort;

    //init
//    newtracker->SetSerialDevice("COM5:");
//    newtracker->Probe();

   // m_controlTracking->init("COM5:");

    //load roms file for tools
    //newtracker->LoadVirtualSROM(tool,filename);
    //newtracker->LoadVirtualSROM(tool1,filename1);

    //start tracking
//    newtracker->StartTracking();
//    newtracker->Update();
  //  m_controlTracking->startTracking();

    //get information about tracker
//    versionName = newtracker->GetVersion();
//    status = newtracker->IsTracking();
//    serialPort = newtracker->GetSerialPort();
//    qDebug() << "Version name: " << versionName << "Status: " << status << "Serial Port: " << serialPort;

  //  qDebug() << "Version name: " << m_controlTracking->getTrackerVersion() << "Status: " << m_controlTracking->getTrackingStatus() << "Serial Port: " << m_controlTracking->getSerialPort();

//    //get tools positions
//    vtkTrackerTool* gettool0;
//    vtkTrackerTool* gettool1;
//    gettool0 = newtracker->GetTool(0);
//    gettool1 = newtracker->GetTool(1);

   // for (int k = 0; k < 10000; k++)
//      while (true)
//      {
//       if(m_controlTracking->getTrackingStatus() == 1)
//        {
////
//           m_controlTracking->getToolPositions(1);
//        }
//       else
//       {
//           break;
//       }
//       // newtracker->Update();
//       ::Sleep(200); // wait for 200 milliseconds before trying again
//      //  status = newtracker->IsTracking();
//       // qDebug() << controlTracking->getTrackingStatus();
//      }

      //newtracker->StopTracking();

    /*int t1= this->GetToolFromHandle(tool);
    int t2= this->GetToolFromHandle(tool1);
    int t3= this->GetToolFromHandle(tool2);
    qDebug() << "\n Tools active:\t" << t1 << "\t" << t2 << "\t" << t3 <<"\n";*/


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
    while (true)
    {
        if(m_controlTracking->getTrackingStatus() == 1)
        {
            m_controlTracking->getToolPositions(tool);
        }
        else
        {
            break;
        }

      ::Sleep(200);
    }
}

void TestApp::command()

{
    const char* cmd = "ECHO: test test";
    qDebug() << m_controlTracking->commandResponse(cmd);
}
