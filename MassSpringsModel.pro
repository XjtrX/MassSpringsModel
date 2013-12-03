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
    RectCloth.h \
    Mass_old.h \
    Spring_old.h \
    Particle.h \
    Spring.h

FORMS += \
    scenewindow.ui

LIBS += -lglut -lGL -lGLU
