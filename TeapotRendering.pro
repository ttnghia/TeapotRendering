#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#
#  Copyright (c) 2017 by
#       __      _     _         _____
#    /\ \ \__ _| |__ (_) __ _  /__   \_ __ _   _  ___  _ __   __ _
#   /  \/ / _` | '_ \| |/ _` |   / /\/ '__| | | |/ _ \| '_ \ / _` |
#  / /\  / (_| | | | | | (_| |  / /  | |  | |_| | (_) | | | | (_| |
#  \_\ \/ \__, |_| |_|_|\__,_|  \/   |_|   \__,_|\___/|_| |_|\__, |
#         |___/                                              |___/
#
#  <nghiatruong.vn@gmail.com>
#  All rights reserved.
#
#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

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
    Include/Common.h \
    CUDA/Common.cuh \
    CUDA/Helpers.cuh \
    CUDA/IntersectionRefinement.cuh \
    CUDA/Random.cuh \
    CUDA/Diffuse.cu \
    CUDA/Glass.cu \
    CUDA/GradientBG.cu \
    CUDA/ParallelogramIterative.cu \
    CUDA/PathTraceCamera.cu \
    CUDA/TriangleMesh.cu \
    Include/TeapotRayTracer.h

SOURCES += \
    Source/Controller.cpp \
    Source/Main.cpp \
    Source/MainWindow.cpp \
    Source/RenderWidget.cpp \
    Source/TeapotRayTracer.cpp
