#ifndef CONTROLTRACKING_H
#define CONTROLTRACKING_H

#include <QObject>
#include "vtkNDITracker.h"
#include "vtkTracker.h"
#include "vtkTransform.h"
#include "vtkTrackerTool.h"
#include <QDebug>

#define VTK_NDI_NTOOLS 12

class ControlTracking : public QObject
{
    Q_OBJECT
public:
    explicit ControlTracking(QObject *parent = 0);
    void init(const char* COMPort);
    void startTracking();
    void stopTracking();
    void loadRomFile(int tool, const char *);
    QString getTrackerVersion();
    int getSerialPort();
    int getTrackingStatus();
    int getToolPort(int tool);
    double *getToolPositions(int tool);
    int getUpdateRate();
    QString commandResponse(const char*);


signals:

public slots:


private:
    vtkNDITracker* m_newtracker;
    int  m_toolPort[VTK_NDI_NTOOLS];


};

#endif // CONTROLTRACKING_H
