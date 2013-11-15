QT += core gui opengl

SOURCES += \
    main.cpp \
    scenewindow.cpp \
    sceneglwidget.cpp

HEADERS += \
    scenewindow.h \
    sceneglwidget.h \
    Point2D.h \
    RotationHolder.h \
    Point3D.h

FORMS += \
    scenewindow.ui

LIBS += -lglut -lGL -lGLU -lGLEW
