#include "SceneGlWidget.h"
#include <GL/glut.h>

#include <math.h>
#include <iostream>
using namespace std;
#define PI 3.14159265

#include "Model/SpringsObjects/Cloth/RectRungeKuttaCloth.h"
#include "Model/SpringsObjects/Cloth/RectVerletCloth.h"
#include "Model/ModelSamples/TriangleObstacle.h"
#include "3DMath/MathRotation.h"
#include "Model/ModelSamples/VerletParticle.h"

#include <ctime>
using namespace std;

#include <iostream>
using namespace std;

SceneGLWidget::SceneGLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    _timeInterval = 1.0 / 25;
    _repaintDelay = 0.04;
    _timeToFrame = 0;
    _perspectiveAngle = 45;
    connect(&_timer, SIGNAL(timeout()), this, SLOT(UpdateScene()));

    int rows = 10;
    int cols = 10;
    float width = 30;
    float heigth = 30;
    float massVolume = 1;
    float stiffness = 1;
    float borderRadius = 1;

    SpringsObject* rC = new RectRungeKuttaCloth(cols, rows
                                                , width, heigth
                                                , massVolume, stiffness, borderRadius
                                  , Point3D<float>(90, 0, 0)
                                  , Point3D<float>(-10, 0, 0), 0);
//    rC->_particles[0]->setStatic(1);
    rC->_particles[cols-1]->setStatic(1);
    rC->_particles[(rows-1)*cols]->setStatic(1);
//    rC->_particles[rows * cols -1]->setStatic(1);
    _scene.AddSpringsObject(rC);
}

void SceneGLWidget::initializeGL()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
}
void SceneGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0.6, 0);
    glLineWidth(1);
    _scene.Draw();
}

void SceneGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    _width = w;
    _height = h;
    glLoadIdentity();
    gluPerspective(_perspectiveAngle, (float)_width/_height, 0.01, 100.0);
    UpdateViewPoint();
    this->repaint();
}

void SceneGLWidget::mousePressEvent(QMouseEvent *ev)
{
    this->_mousePosX = ev->x();
    this->_mousePosY = ev->y();
    emit MousePressSignal(ev);
}

void SceneGLWidget::mouseMoveEvent(QMouseEvent *ev)
{
    this->_mousePosX = ev->x();
    this->_mousePosY = ev->y();
    emit MouseMoveSignal();
}

void SceneGLWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit MouseReleaseSignal();
}

void SceneGLWidget::leaveEvent(QEvent *)
{
    emit LeaveSignal();
}

void SceneGLWidget::UpdateViewPoint()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    MathRotation m;
    float* rotMatr = m.RotationMatrix(-1 * _rotation.getX()
                                    , -1 * _rotation.getY()
                                    , _rotation.getZ());

    Point3D<float> eye = Point3D<float>(_transition);
    eye.PlusZ(40);
    eye = m.RotatePoint(eye, rotMatr);
    Point3D<float> center = Point3D<float>(_transition);
    //center.set(0, 0, 0);
    center = m.RotatePoint(center, rotMatr);
    Point3D<float> up;
    up.set(0, 1, 0);
    up = m.RotatePoint(up, rotMatr);
    gluLookAt(eye.getX(), eye.getY(), eye.getZ()
              , center.getX(), center.getY(), center.getZ()
              , up.getX(), up.getY(), up.getZ());
    //delete (&center);
    delete[] rotMatr;
}

void SceneGLWidget::UpdateScene()
{
    _scene.Iteration(_timeInterval);
    _scene.Collide(0);
    //this->repaint();
    //return;
    _timeToFrame += _timeInterval;
    if (_timeToFrame >= _repaintDelay)
    {
        //this->_scene.Collide(0);
        _timeToFrame = 0;
        this->repaint();
    }
}

int SceneGLWidget::mousePosX()
{
    return _mousePosX;
}

int SceneGLWidget::mousePosY()
{
    return _mousePosY;
}

void SceneGLWidget::Rotate(int x, int y, int z)
{
    _rotation.PlusX(x);
    _rotation.PlusY(y);
    _rotation.PlusZ(z);
    UpdateViewPoint();
}

void SceneGLWidget::Translate(float x, float y, float z)
{
    _transition.PlusX(x);
    _transition.PlusY(y);
    _transition.PlusZ(z);
    UpdateViewPoint();
}

int SceneGLWidget::getSimulationStatus()
{
    return _timer.isActive();
}

void SceneGLWidget::StartSimulation()
{
    _timer.start(_timeInterval * 1000);
}

void SceneGLWidget::StopSimulation()
{
    _timer.stop();
}

void SceneGLWidget::NextIteration()
{
//    VerletParticle p(ParticlePosition(Point3D<float>( 0, 1,  0)), 1);
//    VerletParticle a(ParticlePosition(Point3D<float>( 2, 0, -1)), 1);
//    VerletParticle b(ParticlePosition(Point3D<float>(-2, 0, -1)), 1);
//    VerletParticle c(ParticlePosition(Point3D<float>( 0, 0,  2)), 1);
//    ClothTriangle t(&a, &b, &c);
//    PointTriangleMainfold m(&p, &t);
//    m.ResolveCollision();
//    m._p->_appliedForce.Print("force P");
//    m._t->_p[0]->_appliedForce.Print("force A");
//    m._t->_p[1]->_appliedForce.Print("force B");
//    m._t->_p[2]->_appliedForce.Print("force C");
    if (0 == _timer.isActive())
    {
        _timeToFrame = _repaintDelay;
        this->UpdateScene();
    }
}

void SceneGLWidget::ChangePerspective(int val)
{
    _perspectiveAngle += val;
    this->resizeGL(_width, _height);
}

void SceneGLWidget::Collide()
{
    this->_scene.Collide(0);
}
