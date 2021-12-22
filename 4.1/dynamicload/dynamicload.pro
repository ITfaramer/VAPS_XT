#-------------------------------------------------
#
# Project created by QtCreator 2021-03-08T11:25:40
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dynamicload
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:{
INCLUDEPATH += C:/Presagis/VAPS_XT_4_2_1/src/ThirdParty/glut/3.7.6.3/include
DEPENDPATH += C:/Presagis/VAPS_XT_4_2_1/src/ThirdParty/glut/3.7.6.3/include
INCLUDEPATH += $$PWD/3part
DEPENDPATH += $$PWD/3part

win32: LIBS += -L$$PWD/3part/ -lGlU32 -L$$PWD/3part/ -lOpenGL32 -lglmf32

win32:CONFIG(release, debug|release): LIBS += -LC:/Presagis/VAPS_XT_4_2_1/src/ThirdParty/glut/3.7.6.3/lib/ -lglut64
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Presagis/VAPS_XT_4_2_1/src/ThirdParty/glut/3.7.6.3/lib/ -lglut64
}

unix:{
LIBS += -L/usr/lib/x86_64-linux-gnu -lglut -lOpenGL -lGLU -lGL \
        /home/hyper/VAPS_XT_4_2_1/lib/linux64_so/vxtRTDrawingIntegration.a
}

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myopengl.cpp

HEADERS += \
        mainwindow.h \
    myopengl.h

FORMS += \
        mainwindow.ui
