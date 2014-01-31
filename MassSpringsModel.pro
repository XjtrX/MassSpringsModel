QT += core gui opengl
SOURCES += \
    main.cpp \
    Model/Scene/Scene.cpp \
    Model/ModelSamples/VerletParticle.cpp \
    Model/ModelSamples/TriangleObstacle.cpp \
    SceneGlWidget.cpp \
    SceneWindow.cpp \
    Model/ModelSamples/RungeKuttaParticle.cpp \
    Model/ModelSamples/Particle.cpp \
    Model/ModelSamples/Spring.cpp \
    Model/SpringsObjects/VerletSpringsObject.cpp \
    Model/SpringsObjects/RectVerletCloth.cpp \
    3DMath/ParticleState.cpp \
    3DMath/ParticlePosition.cpp
HEADERS += \
    Model/ModelSamples/Spring.h \
    Model/Scene/Scene.h \
    Model/SpringsObjects/Cube.h \
    Model/Interfaces/ElasticObject.h \
    Model/Interfaces/VerletObject.h \
    Model/Interfaces/DrawableObject.h \
    Model/ModelSamples/TriangleObstacle.h \
    3DMath/Point2D.h \
    3DMath/Point3D.h \
    SceneGlWidget.h \
    SceneWindow.h \
    3DMath/RotationHolder.h \
    3DMath/MathRotation.h \
    Model/Interfaces/RungeKuttaObject.h \
    Model/ModelSamples/VerletParticle.h \
    Model/ModelSamples/RungeKuttaParticle.h \
    Model/SpringsObjects/VerletSpringsObject.h \
    Model/SpringsObjects/RectVerletCloth.h \
    Model/ModelSamples/Unresolved/Particle.h \
    3DMath/ParticleState.h \
    3DMath/ParticlePosition.h

FORMS += \
    scenewindow.ui

LIBS += -lglut -lGL -lGLU
