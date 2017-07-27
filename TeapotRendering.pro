#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T14:51:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeapotRendering
TEMPLATE = app

INCLUDEPATH += $$PWD/Include

#LIBS += -lcuda -lcudart -loptix -loptixu -lsutil -L/usr/local/cuda-6.5/lib64 -L"C:/ProgramData/NVIDIA Corporation/OptiX SDK 4.1.0/lib64"


include (../../Banana/BananaCore/BananaCore.pri)
include (../../Banana/QtAppHelpers/QtAppHelpers.pri)
include (../../Banana/OpenGLHelpers/OpenGLHelpers.pri)
include (../../Banana/RayTracing/RayTracing.pri)

HEADERS += \
    Include/Controller.h \
    Include/MainWindow.h \
    Include/RenderWidget.h \
    Include/Common.h

SOURCES += \
    Source/Controller.cpp \
    Source/Main.cpp \
    Source/MainWindow.cpp \
    Source/RenderWidget.cpp
