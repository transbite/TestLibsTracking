#ifndef _VTK_SCENE_WIDGET_H_
#define _VTK_SCENE_WIDGET_H_

#include <QVTKWidget2.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <QVTKWidget.h>

typedef vtkSmartPointer<vtkRenderer> RendererPtr;

//#if defined (NV_APPLE) || defined (NV_LINUX) || defined (NV_WINDOWS)
    #include <QVTKOpenGLWidget.h>
    #define VTKSceneWidgetSuperclass QVTKOpenGLWidget
    #define USE_QVTKOpenGLWidget
//#else
//    #define VTKSceneWidgetSuperclass QVTKWidget2
//#endif
//#define VTKSceneWidgetSuperclass QVTKWidget

class VTKSceneWidget : public VTKSceneWidgetSuperclass
{
    Q_OBJECT

public:
    VTKSceneWidget(QWidget* parent = nullptr);
    ~VTKSceneWidget();

	RendererPtr renderer();
    void UpdateScene();

signals:
    void resized(QRect);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
//    void onCustomContextMenuRequested(const QPoint& point);
    
private:
	RendererPtr	m_renderer;

};

#endif //_VTK_SCENE_WIDGET_H_
