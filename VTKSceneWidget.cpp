#include "VTKSceneWidget.h"

//#include <vtkRenderWindow.h>
#include <vtkGenericOpenGLRenderWindow.h>

VTKSceneWidget::VTKSceneWidget(QWidget* parent)
    : VTKSceneWidgetSuperclass(parent)
{
    //vtkRenderWindow* renWin = this->GetRenderWindow();
    //vtkNew<vtkGenericOpenGLRenderWindow> renWin;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renWin = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    this->SetRenderWindow(renWin);
    m_renderer = RendererPtr::New();
    renWin->AddRenderer(m_renderer);
    //m_renderer->SetBackground(0.1, 0.3, 0.5);
    m_renderer->SetBackground(0.35, 0.4, 0.45);
    m_renderer->SetGradientBackground(true);
    m_renderer->SetBackground2(0.4, 0.45, 0.5);
    int lfc = m_renderer->GetLightFollowCamera();
    if(lfc == 0)
    {
        m_renderer->SetLightFollowCamera(1);
    }
    else
    {
        m_renderer->SetLightFollowCamera(0);
    }
//    this->setContextMenuPolicy(Qt::CustomContextMenu);
//    bool b = connect(this, &QWidget::customContextMenuRequested,
//                     this, &VTKSceneWidget::onCustomContextMenuRequested);
//    Q_ASSERT(b);
    
    this->setAttribute(Qt::WA_DontCreateNativeAncestors);
}

VTKSceneWidget::~VTKSceneWidget()
{

}

RendererPtr VTKSceneWidget::renderer()
{
	return m_renderer;
}

void VTKSceneWidget::resizeEvent(QResizeEvent *event)
{
    VTKSceneWidgetSuperclass::resizeEvent(event);
    QRect geom = this->geometry();
    emit resized(geom);
}

void VTKSceneWidget::UpdateScene()
{
#ifdef USE_QVTKOpenGLWidget
    //this->update();
    this->renderVTK();
#else
    this->updateGL();
#endif
}

//#include <QDebug>
//void VTKSceneWidget::onCustomContextMenuRequested(const QPoint &point)
//{
//    qDebug() << "VTKSceneWidget::onCustomContextMenuRequested.";
//}
