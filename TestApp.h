#ifndef TESTAPP_H
#define TESTAPP_H

#include <QMainWindow>
#include "vtkNDITracker.h"
#include "vtkTracker.h"

namespace Ui {
class TestApp;
}

class TestApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestApp(QWidget *parent = 0);
    ~TestApp();

private:
    Ui::TestApp *ui;
    vtkNDITracker* newtracker;
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
