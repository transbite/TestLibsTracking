#ifndef TESTAPP_H
#define TESTAPP_H

#include <QMainWindow>
#include "vtkNDITracker.h"
#include "vtkTracker.h"
#include <vtkTransform.h>
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
    ControlTracking *m_controlTracking;
};

#endif // TESTAPP_H
