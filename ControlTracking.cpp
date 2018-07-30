#include "ControlTracking.h"

ControlTracking::ControlTracking(QObject *parent) : QObject(parent)
{
    m_newtracker = vtkNDITracker::New();


//    For the vtkNDITracker, the ports start at index "0" and the first three
//    ports (0, 1, 2) are reserved for active/wired tools.  So you need to load the
//    sroms into ports (3, 4, 5) for passive tools.

    for(int i = 0; i < VTK_NDI_NTOOLS; i++)
    {
        m_toolPort[i] = i;
    }
}

int ControlTracking::init()
{
    /*const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if (QString::compare(info.manufacturer(), "ndi", Qt::CaseInsensitive) == 0)
        {
            QString port = info.portName() + ":";
            m_newtracker->SetSerialDevice(port.toStdString().c_str());
            //Returns 1 if the tracking system was found and is working.
            return m_newtracker->Probe();
        }
    }*/
    return m_newtracker->Probe();
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

double* ControlTracking::getToolPositionOrientation(int tool)
{

    m_newtracker->Update();

    vtkTrackerTool* getTool = m_newtracker->GetTool(tool);
    vtkTransform *toolTransform = getTool->GetTransform();
    double position_t[3] = { 0.0, 0.0, 0.0 };
    toolTransform->TransformPoint(position_t, position_t);

    double position[3];
    double orientation[3];
    double PositionsOrientations[6] ={ 0.0, 0.0, 0.0,0.0, 0.0, 0.0 };
    toolTransform->GetPosition(position);
    toolTransform->GetOrientation(orientation);
    for (int i = 0; i < 3; i++ )
    {
        PositionsOrientations[i] = position[i];
        PositionsOrientations[i+2] = orientation[i];
    }


    if (getTool->IsMissing())
     {
        qDebug() << "MISSING" << endl;
     }
    else
    {

        qDebug() << PositionsOrientations[0] << " " << PositionsOrientations[1] << " " << PositionsOrientations[2];
        qDebug() << PositionsOrientations[3] <<" " << PositionsOrientations[4] <<  " " << PositionsOrientations[5] << endl;
    }

    return PositionsOrientations;

}

int ControlTracking::getBaudRate()
{
    return m_newtracker->GetBaudRate();
}

QString ControlTracking::commandResponse(const char* commandStr)
{
    return m_newtracker->Command(commandStr);

}

QString ControlTracking::getToolSerialNumber(int tool)
{
    vtkTrackerTool* getTool = m_newtracker->GetTool(tool);

    QString toolSerialNumber = getTool->GetToolSerialNumber();


    return toolSerialNumber;
}

QString ControlTracking::getToolManufacturer(int tool)
{
    vtkTrackerTool* getTool = m_newtracker->GetTool(tool);

    QString toolManufacturer = getTool->GetToolManufacturer();

    return toolManufacturer;
}

QString ControlTracking::getToolType(int tool)
{
    vtkTrackerTool* getTool = m_newtracker->GetTool(tool);

    QString toolType = getTool->GetToolType();

    return toolType ;
}
