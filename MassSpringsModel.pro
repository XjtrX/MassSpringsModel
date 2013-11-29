QT += core gui opengl

SOURCES += \
    main.cpp \
    scenewindow.cpp \
    sceneglwidget.cpp \
    RectCloth.cpp

HEADERS += \
    scenewindow.h \
    sceneglwidget.h \
    Point2D.h \
    RotationHolder.h \
    Point3D.h \
    Mass.h \
    Spring.h \
    RectCloth.h

FORMS += \
    scenewindow.ui

LIBS += -lglut -lGL -lGLU
