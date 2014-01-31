#include "SceneGlWidget.h"
#include <GL/glut.h>

#include <math.h>
#include <iostream>
using namespace std;
#define PI 3.14159265

#include "Model/SpringsObjects/RectCloth.h"
#include "Model/ModelSamples/TriangleObstacle.h"
#include "3DMath/MathRotation.h"

#include <ctime>
using namespace std;

SceneGLWidget::SceneGLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    _timeInterval = 1.0 / 24;
    connect(&_timer, SIGNAL(timeout()), this, SLOT(UpdateScene()));
    //_timer.start(_timeInterval * 1000);


    RectCloth* rC = new RectCloth(  10, 10, 30, 30
                                  , 1, 1, 1
                                  , Point3D<float>(90, 0, 0)
                                  , Point3D<float>(-15, 0, 15));
    rC->_particles[90]->setStatic(1);
    rC->_particles[99]->setStatic(1);
    rC->_particles[0]->setStatic(1);
    rC->_particles[9]->setStatic(1);
    SpringsObject* sO = rC;
    _scene.AddSprongsObject(sO);

    /*
    rC = new RectCloth(  10, 10, 30, 30
                                  , 1, 1, 1.44
                                  , Point3D<float>(90, 0, 0)
                                  , Point3D<float>(-15, 8, 15));
    rC->_particles[90]->setStatic(1);
    rC->_particles[99]->setStatic(1);
    //rC->_particles[0]->setStatic(1);
    //rC->_particles[9]->setStatic(1);
    sO = rC;
    _scene.AddSprongsObject(sO);
    */

    TriangleObstacle* tO = new TriangleObstacle(1, 1, Point3D<float>(45.0, 0.0, 0.0)
                                                , Point3D<float>(0, 0 , 0));
    _scene.AddTriangleObstacle(tO);

    /*
    Particle* p = new Particle(Point3D<float>(0, 15, 4), 1, 2, 0);
    _scene.AddParticle(p);

    p = new Particle(Point3D<float>(-5, 15, 4), 1, 2, 0);
    _scene.AddParticle(p);

    p = new Particle(Point3D<float>(5, 15, 4), 1, 2, 0);
    _scene.AddParticle(p);

    p = new Particle(Point3D<float>(0, 15, -4), 1, 2, 0);
    _scene.AddParticle(p);

    p = new Particle(Point3D<float>(-5, 15, -4), 1, 2, 0);
    _scene.AddParticle(p);

    p = new Particle(Point3D<float>(5, 15, -4), 1, 2, 0);
    _scene.AddParticle(p);
    */

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
    glLineWidth(1.5);
    _scene.Draw();
}

void SceneGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    UpdateViewPoint();
}

void SceneGLWidget::mousePressEvent(QMouseEvent *ev)
{
    this->_mousePosX = ev->x();
    this->_mousePosY = ev->y();
    emit MousePressSignal();
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

    Point3D<float> eye;
    eye.set(0, 0, 50);
    eye = m.RotatePoint(eye, rotMatr);
    Point3D<float> center;
    center.set(0, 0, 0);
    center = m.RotatePoint(center, rotMatr);
    Point3D<float> up;
    up.set(0, 1, 0);
    up = m.RotatePoint(up, rotMatr);
    gluLookAt(eye.getX(), eye.getY(), eye.getZ()
              , center.getX(), center.getY(), center.getZ()
              , up.getX(), up.getY(), up.getZ());
    delete[] rotMatr;
}

void SceneGLWidget::UpdateScene()
{
//    clock_t t1, t2;
//    t1 = clock();

    /*
    _rectCloth.RecalculateSprings();
    _rectCloth.ApplyForce(0, -9.8, 0);
    _rectCloth.Move();
    _rectCloth.Accelerate(1.0 / 24);
    */
    _scene.ApplyAcceleration(0, -9.8, 0);
    _scene.RecalculateSprings();
    _scene.Accelerate(_timeInterval);
    _scene.Collide(false);
    _scene.Move();
    _scene.Collide(true);
    //_scene.RecalculateSprings();
    //_scene.Accelerate(1.0 / 24);
    this->repaint();

//    t2 = clock();
//    double difference = (t2 - t1) / (double)(CLOCKS_PER_SEC / 1000);
//    cout << "difference " << difference << endl;
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
    if (0 == _timer.isActive())
    {
        this->UpdateScene();
    }
}
