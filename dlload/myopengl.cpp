#include "myopengl.h"

#include <QImage>
#include <QDebug>
#include <QThread>

static int g_nDllNdex =0;
const vxtUInt MOUSE_MOVE_RATIO = 2;

myopenGL::myopenGL(QWidget *parent)
    : QOpenGLWidget(parent)
    ,m_pDrawingIntegration(NULL)
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

void myopenGL::UnLoadDll()
{
    if(lib!=NULL){
        if(VXT_NULL != m_pDrawingIntegration){
            m_pDrawingIntegration->vClose();
            m_pDrawingIntegration = VXT_NULL;

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
                    // The following line sets the VAPS XT drawing area to have the full extent of the MFC Window.
                    m_pDrawingIntegration->vSetSize(0, this->width(), this->height());     
                }else{
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
        qDebug() << "Load library Error";
    }
}

void myopenGL::slotAddNewDll()
{
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("选择动态库"), QString(),QString("*.dll\n*.so\n*"));
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
