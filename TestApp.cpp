#include "TestApp.h"
#include "ui_TestApp.h"
#include <QDebug>



TestApp::TestApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestApp)
{
    ui->setupUi(this);

    newtracker = vtkNDITracker::New();
    tool=3;tool1=4;tool2=5;
    filename = "c:\\Users\\User\\work\\projects\\tests\\AIGSApp\\AIGSApp\\AIGSApp\\ToolsROM\\filenama1.rom";
    filename1 = "c:\\Users\\User\\work\\projects\\tests\\AIGSApp\\AIGSApp\\AIGSApp\\ToolsROM\\filename2.rom";
    filename2 = "c:\\Users\\User\\work\\projects\\tests\\AIGSApp\\AIGSApp\\AIGSApp\\ToolsROM\\filename3.rom";
    QString versionname;

    newtracker->SetSerialDevice("COM5:");
    /*newtracker->LoadVirtualSROM(tool,filename);
    newtracker->LoadVirtualSROM(tool1,filename1);
    newtracker->LoadVirtualSROM(tool2,filename2);*/
    newtracker->Probe();
    newtracker->StartTracking();
    versionname = newtracker->GetVersion();

    qDebug() << versionname;

    /*int t1= newtracker->GetToolFromHandle(tool);
    int t2= newtracker->GetToolFromHandle(tool1);
    int t3= newtracker->GetToolFromHandle(tool2);
    qDebug() << "\n Tools active:\t" << t1 << "\t" << t2 << "\t" << t3 <<"\n";*/
}

TestApp::~TestApp()
{
    delete ui;
}
