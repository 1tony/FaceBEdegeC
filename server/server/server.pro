TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Listen.cpp \
        Soc.cpp \
        main.cpp
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
LIBS += -l pthread
HEADERS += \
    Listen.h \
    Soc.h \
    head.h
