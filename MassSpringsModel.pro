QT += core gui opengl
SOURCES += \
    main.cpp \
    Model/ModelSamples/VerletParticle.cpp \
    Model/ModelSamples/TriangleObstacle.cpp \
    SceneGlWidget.cpp \
    SceneWindow.cpp \
    Model/ModelSamples/RungeKuttaParticle.cpp \
    Model/ModelSamples/Spring.cpp \
    Model/SpringsObjects/VerletSpringsObject.cpp \
    3DMath/ParticleState.cpp \
    3DMath/ParticlePosition.cpp \
    Model/SpringsObjects/Scene/Scene.cpp \
    Model/SpringsObjects/RungeKuttaSpringsObject.cpp \
    Model/SpringsObjects/SpringsObject.cpp \
    Model/SpringsObjects/Cloth/RectVerletCloth.cpp \
    Model/SpringsObjects/Cloth/RectRungeKuttaCloth.cpp \
    Model/Collision/PointTriangleManifold.cpp \
    exact-ccd/expansion.cpp \
    exact-ccd/interval.cpp \
    exact-ccd/rootparitycollisiontest.cpp \
    Model/ModelSamples/Unresolved/Particle.cpp \
    Model/Collision/TrianglesManifold.cpp

HEADERS += \
    Model/ModelSamples/Spring.h \
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
    Model/SpringsObjects/Scene/Scene.h \
    Model/SpringsObjects/VerletSpringsObject.h \
    Model/ModelSamples/Unresolved/Particle.h \
    3DMath/ParticleState.h \
    3DMath/ParticlePosition.h \
    Model/SpringsObjects/RungeKuttaSpringsObject.h \
    Model/SpringsObjects/SpringsObject.h \
    Model/SpringsObjects/Cloth/RectVerletCloth.h \
    Model/SpringsObjects/Cloth/RectRungeKuttaCloth.h \
    Model/Interfaces/MovableObject.h \
    Model/ModelSamples/ClothTriangle.h \
    Model/Collision/PointTriangleManifold.h \
    exact-ccd/expansion.h \
    exact-ccd/interval_base.h \
    exact-ccd/interval.h \
    exact-ccd/vec.h \
    exact-ccd/rootparitycollisiontest.h \
    Model/Collision/TrianglesManifold.h \
    3DMath/Matrix3x3D.h \
    CustomException.h \
    Model/Collision/ResolveCollision.h

FORMS += \
    scenewindow.ui

#QMAKE_LIBDIR += /home/user/MassSpringsModel/exact-ccd
#INCLUDEPATH += /home/user/MassSpringsModel/exact-ccd
#QMAKE_LIBDIR += /home/lord/projects/qt/MassSpringsModel/exact-ccd
#INCLUDEPATH += /home/lord/projects/qt/MassSpringsModel/exact-ccd

INCLUDEPATH += "./glm"

LIBS += -lglut -lGL -lGLU# -lexact-ccd


QMAKE_CXXFLAGS += -fopenmp
QMAKE_LIBS += -lgomp
