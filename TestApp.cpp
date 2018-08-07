#include "TestApp.h"
#include "globals.h"
#include "ui_TestApp.h"
#include <QDebug>
#include <QThread>
#include <QMessageBox>

#include <QVTKOpenGLWidget.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>

QListWidget *logWidget;

TestApp::TestApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestApp)

{
    ui->setupUi(this);

    //vtk - qt setup
//    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
//    ui->vtkWidget->SetRenderWindow(renderWindow);
//    m_renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderWindow->AddRenderer(m_renderer);

    logWidget = ui->logText;
    ui->stopButton->setEnabled(false);
    ui->positionsButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->sendCmdButton->setEnabled(false);
    ui->commandText->setEnabled(false);

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
    int status = m_controlTracking->init();
    qDebug() << "Is NDI working? - " << status;
    if (status > 0)
    {
        ui->initButton->setEnabled(false);
        ui->startButton->setEnabled(true);
        ui->sendCmdButton->setEnabled(true);
        ui->commandText->setEnabled(true);
    }
    else
    {
        int ret = QMessageBox::warning(this, tr("Init"), tr("Initialisation failed!"),QMessageBox::Cancel);
    }
}

TestApp::~TestApp()
{
    delete ui;
    delete m_controlTracking;
}

void TestApp::stop()
{
   m_controlTracking->stopTracking();
   ui->startButton->setEnabled(true);
   ui->positionsButton->setEnabled(false);
   ui->stopButton->setEnabled(false);
   qDebug() << m_controlTracking->getTrackingStatus();
}
void TestApp::start()
{
   m_controlTracking->startTracking();
   ui->startButton->setEnabled(false);
   ui->stopButton->setEnabled(true);
   ui->positionsButton->setEnabled(true);
   qDebug() << m_controlTracking->getTrackerVersion();
   qDebug() << m_controlTracking->getSerialPort();
   qDebug() << m_controlTracking->getTrackingStatus();
}
void TestApp::positions(int tool)
{
    tool = 0;
    //while (true)
    for (int k = 0; k < 10; k++)
    {
        if(m_controlTracking->getTrackingStatus() == 1)
        {
            m_controlTracking->getToolPositionOrientation(tool);
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
    int tool = 1;
    //const char* cmd = "PHSR:00";
    QString itemText = ui->commandText->text();
    qDebug() << m_controlTracking->commandResponse(itemText.toStdString().c_str());

    qDebug() << m_controlTracking->getToolManufacturer(tool) << m_controlTracking->getToolType(tool);

}
