QT += core gui opengl
SOURCES += \
    main.cpp \
    Model/SpringsObjects/RectCloth.cpp \
    Model/SpringsObjects/SpringsObject.cpp \
    Model/Scene/Scene.cpp \
    Model/SpringsObjects/Cube.cpp \
    Model/ModelSamples/Particle.cpp \
    Model/ModelSamples/Spring.cpp \
    Model/ModelSamples/TriangleObstacle.cpp \
    SceneGlWidget.cpp \
    SceneWindow.cpp
HEADERS += \
    Model/SpringsObjects/RectCloth.h \
    Model/SpringsObjects/SpringsObject.h \
    Model/ModelSamples/Spring.h \
    Model/Scene/Scene.h \
    Model/SpringsObjects/Cube.h \
    Model/ModelSamples/Particle.h \
    Model/Interfaces/ElasticObject.h \
    Model/Interfaces/VerletObject.h \
    Model/Interfaces/DrawableObject.h \
    Model/ModelSamples/TriangleObstacle.h \
    3DMath/Point2D.h \
    3DMath/Point3D.h \
    SceneGlWidget.h \
    SceneWindow.h \
    3DMath/RotationHolder.h \
    3DMath/MathRotation.h

FORMS += \
    scenewindow.ui

LIBS += -lglut -lGL -lGLU
