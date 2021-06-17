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

#ifdef Q_OS_WIN
#include "C:\Presagis\VAPS_XT_4_2_1\src\Integration\include\vxtRTDrawingIntegrationI.h"
#include "c:\Presagis\VAPS_XT_4_2_1\src\Ports\OS\win32\include\vxtPLBasicTypes.h"
#endif

#ifdef Q_OS_LINUX
#include "/home/hyper/VAPS_XT_4_2_1/src/Integration/include/vxtRTDrawingIntegrationI.h"
#include "/home/hyper/VAPS_XT_4_2_1/src/Ports/OS/linux/include/vxtPLBasicTypes.h"
#endif

const vxtChar g_BufferNameHUD[]   = "HUDBuffer";
const vxtChar g_BufferNameFloat50[] = "Float50";

struct HudStruct
{
   vxtDouble latitude;
   vxtDouble longitude;
   vxtFloat ind_air_spd;
   vxtFloat true_air_spd;
   vxtFloat vertical_spd;
   vxtFloat ground_spd;
   vxtFloat ground_track;
   vxtFloat baro_altitude;
   vxtFloat radar_altitude;
   vxtFloat accel;
   vxtFloat vel_body_x;
   vxtFloat vel_body_y;
   vxtFloat vel_body_z;
   vxtFloat mach_number;
   vxtFloat g_load;
   vxtFloat angle_of_attack;
   vxtFloat sideslip;
   vxtFloat roll;
   vxtFloat pitch;
   vxtFloat true_heading;
   vxtFloat mag_heading;
   vxtFloat roll_rate;
   vxtFloat pitch_rate;
   vxtFloat heading_rate;
   vxtFloat total_mass;
   vxtFloat fuel_mass;
   vxtFloat fuel_mass_ratio;
   vxtFloat fuel_tank_1;
   vxtFloat fuel_tank_2;
   vxtFloat fuel_tank_3;
   vxtFloat fuel_tank_4;
   vxtUShort flap_in_transit;
   vxtUShort slat_in_transit;
   vxtUShort stall_warning;
   vxtUShort on_ground;
   vxtFloat selected_course;
   vxtFloat gear_pos_1;
   vxtFloat gear_pos_2;
   vxtFloat gear_pos_3;
   vxtFloat gear_pos_4;
   vxtFloat gear_pos_5;
   vxtFloat wheel_angle_1;
   vxtFloat wheel_angle_2;
   vxtFloat wheel_angle_3;
   vxtFloat wheel_angle_4;
   vxtFloat wheel_angle_5;
   vxtUShort gear_on_ground_1;
   vxtUShort gear_on_ground_2;
   vxtUShort gear_on_ground_3;
   vxtUShort gear_on_ground_4;
   vxtUShort gear_on_ground_5;
   vxtUShort gear_status_1;
   vxtUShort gear_status_2;
   vxtUShort gear_status_3;
   vxtUShort gear_status_4;
   vxtUShort gear_status_5;
   vxtFloat pitch_trim;
   vxtFloat roll_trim;
   vxtFloat yaw_trim;
   vxtFloat flap;
   vxtFloat flap_percent;
   vxtFloat slat;
   vxtFloat slat_percent;
   vxtFloat spoiler;
   vxtFloat spd_brake;
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
    HudStruct*                 m_pHudStruct = NULL;
    Float50*                   m_pFloat50 = NULL;
    vxtRTDrawingIntegrationI*  m_pDrawingIntegration = NULL;

    QLibrary *lib;
    QFile file;
};

#endif // MYOPENGL_H
