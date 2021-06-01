#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLWindow>
#include <QGLWidget>
#include <QGLFunctions>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

#include <QMenu>
#include <QAction>
#include <QFile>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPointF>

#include "GL/gl.h"

#include "C:\Presagis\VAPS_XT_4_2_1\src\Integration\include\vxtRTDrawingIntegrationI.h"
#include "c:\Presagis\VAPS_XT_4_2_1\src\Ports\OS\win32\include\vxtPLBasicTypes.h"

const vxtChar g_BufferNameMultiWindow[]   = "MultiWindowBuffer";
const vxtChar g_BufferNameFloat50[] = "Float50";

struct MultiWindowStruct{
    vxtInt mode;
};

struct Float50
{
   vxtFloat float_array[50];
};

typedef vxtRTDrawingIntegrationI* (*fCreateTopIntegrator)();
typedef vxtRTDrawingIntegration_V2I* (*fCreateTopIntegrator_V2)();
typedef vxtRTDrawingIntegration_V3I* (*fCreateTopIntegrator_V3)();

class myopenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit myopenGL(QWidget *parent = 0);
    ~myopenGL();

    bool isLoadDll();
    void UnLoadDll();
    void loadDll(QString fileName);

    void setMode(int mode);

public slots:
    void slotAddNewDll();
    void slotDelCurDll();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public:
    int m_mode=0;

private:
    QMenu*                     mMenu;
    QString                    mName;
    QString                    mPreName;
    QPoint                     mPrePos;
    QPoint                     mCurPos;
    QPoint                     mWidgetPos;

    bool                       mReadyMouseMove;
    uint                       m_NumberOfMouseMove=0;
    int                        mZ=0;

    QTimer*                    m_timer;
    vxtFloat                   m_Roll = 0;
    vxtInt                     m_RenderingContextId;
    MultiWindowStruct*         m_pMultiWindowStruct = NULL;
    Float50*                   m_pFloat50 = NULL;
    vxtRTDrawingIntegrationI*  m_pDrawingIntegration = NULL;

    QLibrary *lib;
    QFile file;
};

#endif // MYOPENGL_H
