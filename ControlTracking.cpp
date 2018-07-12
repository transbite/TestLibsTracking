#include "ControlTracking.h"

ControlTracking::ControlTracking(QObject *parent) : QObject(parent)
{
    m_newtracker = vtkNDITracker::New();


    //active tools detected on ports 0, 1, 2
    //polaris rom tools could be loaded on 3, 4 ,5...

    for(int i = 0; i < VTK_NDI_NTOOLS; i++)
    {
        m_toolPort[i] = i;
    }

}

void ControlTracking::init(const char* COMPort)
{
    m_newtracker->SetSerialDevice(COMPort);
    m_newtracker->Probe();
}

void ControlTracking::startTracking()
{
    m_newtracker->StartTracking();
    m_newtracker->Update();
}

void ControlTracking::stopTracking()
{
    m_newtracker->StopTracking();
}

QString ControlTracking::getTrackerVersion()
{
    return m_newtracker->GetVersion();
}

int ControlTracking::getSerialPort()
{
    return m_newtracker->GetSerialPort();
}

int ControlTracking::getTrackingStatus()
{
    return m_newtracker->IsTracking();
}


void ControlTracking::loadRomFile(int tool, const char*filename)
{
    m_newtracker->LoadVirtualSROM(tool,filename);
}


int ControlTracking::getToolPort(int tool)
{
    if (tool < VTK_NDI_NTOOLS)
    {
        return m_toolPort[tool];
    }
    else
        return -1;
}

double* ControlTracking::getToolPositions(int tool)
{

    m_newtracker->Update();

    vtkTrackerTool* getTool = m_newtracker->GetTool(tool);
    vtkTransform *toolTransform = getTool->GetTransform();
    double position[3] = { 0.0, 0.0, 0.0 };
    toolTransform->TransformPoint(position, position);
    if (getTool->IsMissing())
     {
        qDebug() << "MISSING" << endl;
     }
    else
    {
        qDebug() << position[0] << " " << position[1] << " " << position[2] << endl;
    }

    return position;
}

int ControlTracking::getUpdateRate()
{
    return m_newtracker->GetInternalUpdateRate();
}

QString ControlTracking::commandResponse(const char* commandStr)
{
    return m_newtracker->Command(commandStr);

}
