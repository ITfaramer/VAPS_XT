#include "myopengl.h"

#include <QImage>
#include <QDebug>
#include <QThread>

static int g_nDllNdex =0;
const vxtUInt MOUSE_MOVE_RATIO = 2;

myopenGL::myopenGL(QWidget *parent)
    : QOpenGLWidget(parent)
    ,m_Roll(0)
    ,m_pDrawingIntegration(NULL)
    ,m_RenderingContextId(0)
    ,mReadyMouseMove(false)
    ,mPrePos(QPoint(0,0))
    ,mCurPos(QPoint(0,0))
{
    mName.clear();
    mMenu = new QMenu(this);
    QAction* actAdd = mMenu->addAction(QStringLiteral("添加动态库"));
    QAction* actDel = mMenu->addAction(QStringLiteral("删除动态库"));

    connect(actAdd, SIGNAL(triggered()), this, SLOT(slotAddNewDll()));
    connect(actDel, SIGNAL(triggered()), this, SLOT(slotDelCurDll()));
}

myopenGL::~myopenGL()
{
    delete mMenu;
    UnLoadDll();
}

bool myopenGL::isLoadDll()
{
    return NULL == m_pDrawingIntegration ? false : true;
}

void myopenGL::UnLoadDll()
{
    if(lib!=NULL){
        if(VXT_NULL != m_pDrawingIntegration){
            m_pDrawingIntegration->vClose();

            m_pDrawingIntegration = VXT_NULL;
            m_pHudStruct = VXT_NULL;
            m_pFloat50 = VXT_NULL;

            lib->unload();
            lib = NULL;
        }
    }
}

void myopenGL::loadDll(QString fileName)
{
    UnLoadDll();

    lib=new QLibrary(fileName);
    if(lib->load()){
        fCreateTopIntegrator fun = (fCreateTopIntegrator)lib->resolve("vxtGetDrawingIntegrationI");
        if(fun){
            m_pDrawingIntegration = fun();
            if(NULL != m_pDrawingIntegration){
                const char *argv[4];
                argv[0] = "VAPSXT.exe";
                argv[1] = "-alwaysdraw";
                argv[2] = "-fit";
                argv[3] = "-displayupdaterate";

                const int size = sizeof(argv) / sizeof(argv[0]);
                if(VXT_TRUE == m_pDrawingIntegration->vInit(size, (char **)argv, VXT_FALSE)){
                    unsigned int Size = 0;

                    m_pHudStruct = static_cast<HudStruct*>(m_pDrawingIntegration->pGetBuffer(g_BufferNameHUD, Size));
                    m_pFloat50   = static_cast<Float50*>(m_pDrawingIntegration->pGetBuffer(g_BufferNameFloat50, Size));

                    // The following line sets the VAPS XT drawing area to have the full extent of the MFC Window.
                    m_pDrawingIntegration->vSetSize(0, this->width(), this->height());     
                }else{
                    unsigned int Size = 0;
                    m_pHudStruct = static_cast<HudStruct*>(m_pDrawingIntegration->pGetBuffer(g_BufferNameHUD, Size));
                    m_pFloat50   = static_cast<Float50*>(m_pDrawingIntegration->pGetBuffer(g_BufferNameFloat50, Size));

                    // The following line sets the VAPS XT drawing area to have the full extent of the MFC Window.
                    m_pDrawingIntegration->vSetSize(0, this->width(), this->height());
                    qDebug() << "Cannot initialize the vxtRTDrawingIntegrationI";
                }
            }else{
                qDebug() << "m_pDrawingIntegration is NULL";
            }
        }else{
            qDebug() << "Get fun Error";
        }
    }else{
        qDebug() << "Load library Error"<<lib->errorString();
    }
}

void myopenGL::slotAddNewDll()
{
#ifdef Q_OS_WIN
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("选择动态库"), QString(),QString("*.dll\n*.so\n*"));
#endif

#ifdef Q_OS_LINUX
    QString fileName;
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptOpen);
    filedialog.setViewMode(QFileDialog::List);
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setWindowTitle(tr("选择动态库"));
    filedialog.setDefaultSuffix("*.dll\n*.so\n*");
    filedialog.setOption(QFileDialog::DontUseNativeDialog);
    if(filedialog.exec()==  QDialog::Accepted )
    {
        QStringList filePaths = filedialog.selectedFiles();
        fileName =filePaths[0];
        qDebug() << fileName;
    }
#endif
    loadDll(fileName);
}

void myopenGL::slotDelCurDll()
{
    UnLoadDll();
}

//初始化opengl窗口部件
void myopenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0);
    glShadeModel(GL_SMOOTH);

    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

//绘制opengl窗口
void myopenGL::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //绘制操作：
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    glOrtho ( 0, this->width(), 0, this->height(), -1, 1 );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

    if (NULL != m_pDrawingIntegration){
        if (VXT_NULL != m_pHudStruct){
           m_Roll += 0.01 + g_nDllNdex*0.005;

           vxtFloat CosRollValue = cosf(m_Roll);
           vxtFloat SinRollValue = sinf(m_Roll);

           m_pHudStruct->baro_altitude  = CosRollValue * 20;
           m_pHudStruct->radar_altitude = SinRollValue * 60;
           m_pHudStruct->true_heading   = CosRollValue * 30;
           m_pHudStruct->ind_air_spd    = SinRollValue * 110 + 220;
           m_pHudStruct->pitch          = CosRollValue * 30;
           m_pHudStruct->roll           = SinRollValue * 45;
           m_pHudStruct->stall_warning  = static_cast<vxtUShort>(CosRollValue) * 2;
           m_pHudStruct->vertical_spd   = SinRollValue * 30;
           m_pHudStruct->vel_body_x     = CosRollValue * 75;
           m_pHudStruct->vel_body_y     = SinRollValue * 85;
           m_pHudStruct->vel_body_z     = CosRollValue * 25;
           m_pDrawingIntegration->vUpdateBuffer(g_BufferNameHUD);
        }

        m_pDrawingIntegration->vExecuteIteration();
    }

    glFlush();
    update();
}

//处理窗口大小
void myopenGL::resizeGL(int width, int height)
{
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    glOrtho ( 0, this->width(), 0, this->height(), -1, 1 );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

   if (NULL != m_pDrawingIntegration){
      m_pDrawingIntegration->vSetSize(0, this->width(), this->height());
   }

   glViewport(0, 0, this->width(), this->height());                  //重置模型观察矩阵
}

void myopenGL::contextMenuEvent(QContextMenuEvent *event)
{
    mMenu->exec(event->globalPos());
}

void myopenGL::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->x()<<":"<<event->y();
//    if(event->button() == Qt::LeftButton){
//        //qDebug()<<"Left button";
//    }else if(event->button()==Qt::RightButton){
//        //qDebug()<<"Right button";
//    }
//    vxtBool consumed = VXT_FALSE;
//    if(NULL != m_pDrawingIntegration){
//        consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
//                                                              VXT_RT_DI_EVT_POINTER_PRESSED,
//                                                              VXT_RT_DI_BUTTON_LEFT,
//                                                              VXT_RT_DI_MODIFIER_NONE,
//                                                              0,
//                                                              event->x(),
//                                                              event->y());
//    }
//    if(VXT_FALSE==consumed){
//    }
    mReadyMouseMove = true;
    mPrePos=event->pos();
    mWidgetPos = QPoint(this->x(),this->y());
}

void myopenGL::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"move "<<event->x()<<":"<<event->y();
//    if(m_NumberOfMouseMove==0){
//        vxtBool consumed = VXT_FALSE;
//        if(NULL!=m_pDrawingIntegration){
//            consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
//                                                                  VXT_RT_DI_EVT_POINTER_MOVED,
//                                                                  VXT_RT_DI_BUTTON_LEFT,
//                                                                  VXT_RT_DI_MODIFIER_NONE,
//                                                                  0,
//                                                                  event->x(),
//                                                                  event->y());
//        }
//        if(VXT_FALSE == consumed){
//            if(event->button()==Qt::LeftButton){
//            }
//        }
//    }

//    m_NumberOfMouseMove++;
//    if(MOUSE_MOVE_RATIO <= m_NumberOfMouseMove){
//        m_NumberOfMouseMove=0;
//    }
    if(mReadyMouseMove){
        mCurPos=event->pos();
        QPoint newWidgetPos = QPoint(mWidgetPos.x()+mCurPos.x()-mPrePos.x(),mWidgetPos.y()+mCurPos.y()-mPrePos.y());
        this->move(newWidgetPos);
        mWidgetPos=newWidgetPos;
        mPrePos=mCurPos;
    }
}

void myopenGL::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug()<<"Release "<<event->x()<<":"<<event->y();
//    vxtBool consumed = VXT_FALSE;
//    if(NULL != m_pDrawingIntegration){
//        consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
//                                                              VXT_RT_DI_EVT_POINTER_RELEASED,
//                                                              VXT_RT_DI_BUTTON_LEFT,
//                                                              VXT_RT_DI_MODIFIER_NONE,
//                                                              0,
//                                                              event->x(),
//                                                              event->y());
//    }
//    if(VXT_FALSE==consumed){
//    }
    mReadyMouseMove=false;
}

void myopenGL::mouseDoubleClickEvent(QMouseEvent *event)
{
    //qDebug()<<"Double clicked";
    vxtBool consumed = VXT_FALSE;
    if(NULL != m_pDrawingIntegration){
        consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
                                                              VXT_RT_DI_EVT_POINTER_DBLCLK,
                                                              (vxtRTDrawingIntegrationEvtButtons)VXT_RT_DI_BUTTON_LEFT,
                                                              VXT_RT_DI_MODIFIER_NONE,
                                                              0,
                                                              event->x(),
                                                              event->y());
    }
    if(VXT_FALSE==consumed){
    }
}

void myopenGL::wheelEvent(QWheelEvent *event)
{
    vxtBool consumed = VXT_FALSE;

    if(NULL != m_pDrawingIntegration){
        consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
                                                              VXT_RT_DI_EVT_POINTER_ROTATED,
                                                              (vxtRTDrawingIntegrationEvtButtons)VXT_RT_DI_BUTTON_WHEEL,
                                                              VXT_RT_DI_MODIFIER_NONE,
                                                              event->delta(),
                                                              event->x(),
                                                              event->y());
    }
    if(VXT_FALSE == consumed){
        if(event->delta()>0){
            mZ+=event->delta();
        }else{
            mZ-=event->delta();
        }
    }
    event->accept();
}

void myopenGL::keyPressEvent(QKeyEvent *event)
{
    //qDebug()<<"Key press"<<event->key();
    vxtBool consumed = VXT_FALSE;
    if(NULL!=m_pDrawingIntegration){
        consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
                                                              VXT_RT_DI_EVT_POINTER_PRESSED,
                                                              event->key(),
                                                              (vxtRTDrawingIntegrationModifier)event->modifiers(),
                                                              0,0,0);
    }
    if(VXT_FALSE==consumed){
    }
}

void myopenGL::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug()<<"Key release"<<event->key();
    vxtBool consumed = VXT_FALSE;
    if(NULL!=m_pDrawingIntegration){
        consumed = m_pDrawingIntegration->ProcessPointerEvent(m_RenderingContextId,
                                                              VXT_RT_DI_EVT_POINTER_RELEASED,
                                                              event->key(),
                                                              VXT_RT_DI_MODIFIER_NONE,
                                                              0,
                                                              0,0);
    }
    if(VXT_FALSE==consumed){
    }
}
