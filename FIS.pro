#-------------------------------------------------
#
# Project created by QtCreator 2017-06-05T16:08:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FIS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    SimpleSegmentation.cpp \
    SimpleSegmentation2.cpp \
    HarrisCornerPoint.cpp \
    FIS.cpp \
    Utility.cpp

HEADERS += \
    SimpleSegmentation.h \
    utility.h \
    SimpleSegmentation2.h \
    HarrisCornerPoint.h \
    FIS.h

FORMS += \
        fis.ui

INCLUDEPATH += C:\opencv_build\install\include
#LIBS += -L C:\opencv-build\install\x86\mingw\lib\
#    -libopencv_core320.dll.a \
#    -lopencv_highgui320.dll \
#    -lopencv_imgcodecs320.dll \
#    -lopencv_imgproc320.dll \
#    -lopencv_features2d320.dll \
#    -lopencv_calib3d320.dll
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_calib3d320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_core320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_features2d320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_flann320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_highgui320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_imgcodecs320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_imgproc320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_ml320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_objdetect320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_photo320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_shape320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_stitching320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_superres320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_video320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_videoio320.dll.a"
LIBS += "C:\opencv_build\install\x86\mingw\lib\libopencv_videostab320.dll.a"

RESOURCES += \
    resources.qrc
