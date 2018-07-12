#ifndef TESTAPP_H
#define TESTAPP_H

#include <QMainWindow>
#include "vtkNDITracker.h"
#include "vtkTracker.h"
#include "vtkTransform.h"
#include "vtkTrackerTool.h"
#include "ControlTracking.h"

namespace Ui {
class TestApp;
}

class TestApp : public QMainWindow, public vtkNDITracker
{
    Q_OBJECT

public:
    explicit TestApp(QWidget *parent = 0);

    ~TestApp();

public slots:
    void stop();
    void init();
    void start();
    void positions(int tool);
    void command();

private:
    Ui::TestApp *ui;
    vtkNDITracker* newtracker;
    ControlTracking *m_controlTracking;
    int x;
    int tool;
    const char * filename;
    int tool1;
    const char * filename1;
    int tool2;
    const char * filename2;
    int beepn;
};

#endif // TESTAPP_H
