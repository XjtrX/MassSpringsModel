QT += core gui opengl
SOURCES += \
    main.cpp \
    scenewindow.cpp \
    sceneglwidget.cpp \
    Model/SpringsObjects/RectCloth.cpp \
    Model/SpringsObjects/SpringsObject.cpp \
    Model/Scene/Scene.cpp \
    Model/SpringsObjects/Cube.cpp \
    Model/ModelSamples/Particle.cpp \
    Model/ModelSamples/Spring.cpp

HEADERS += \
    scenewindow.h \
    sceneglwidget.h \
    RotationHolder.h \
    Point3D.h \
    Model/SpringsObjects/RectCloth.h \
    Model/SpringsObjects/SpringsObject.h \
    Model/ModelSamples/Spring.h \
    Point2D.h \
    Model/Scene/Scene.h \
    Model/SpringsObjects/Cube.h \
    Model/ModelSamples/Particle.h \
    Model/Interfaces/ElasticObject.h \
    Model/Interfaces/VerletObject.h

FORMS += \
    scenewindow.ui

LIBS += -lglut -lGL -lGLU
