QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include \ /usr/local/include/opencv \ /usr/local/include/opencv2
LIBS += /usr/local/lib/libopencv_core.so.3.4
LIBS += /usr/local/lib/libopencv_highgui.so.3.4
LIBS += /usr/local/lib/libopencv_core.so.3.4
LIBS += /usr/local/lib/libopencv_highgui.so.3.4
LIBS += /usr/local/lib/libopencv_calib3d.so.3.4
LIBS += /usr/local/lib/libopencv_features2d.so.3.4
LIBS += /usr/local/lib/libopencv_flann.so.3.4
LIBS += /usr/local/lib/libopencv_imgcodecs.so.3.4
LIBS += /usr/local/lib/libopencv_imgproc.so.3.4
LIBS += /usr/local/lib/libopencv_ml.so.3.4
LIBS += /usr/local/lib/libopencv_objdetect.so.3.4
LIBS += /usr/local/lib/libopencv_video.so.3.4
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_videoio


SOURCES += \
    FaceRec.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    FaceRec.h \
    head.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
