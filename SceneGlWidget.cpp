#include "SceneGlWidget.h"
#include <GL/glut.h>

#include <math.h>
#include <iostream>
using namespace std;
#define PI 3.14159265

#include "Model/SpringsObjects/RungeKuttaSpringsObject.h"
#include "Model/SpringsObjects/VerletSpringsObject.h"
#include "Model/ModelSamples/TriangleObstacle.h"
#include "3DMath/MathRotation.h"

#include <QFileDialog>


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

    int rows = 11;
    int cols = 11;
    float width = 30;
    float heigth = 30;
    float massVolume = 1;
    float stiffness = 2;
    float thickness = 1;
    int withBendSpring = 0;

    SpringsObject* rC = new VerletSpringsObject(cols, rows
                                                , width, heigth
                                                , massVolume, stiffness, thickness
                                  , Point3D<float>(90, 0, 0)
                                  , Point3D<float>(-10, 0, 0)
                                  , withBendSpring);
//    rC->_particles[0]->setStatic(1)
    rC->_particles[cols-1]->setStatic(1);
    rC->_particles[(rows-1)*cols]->setStatic(1);
//    rC->_particles[rows * cols -1]->setStatic(1);
//    rC->_particles[(rows / 2) * cols]->setStatic(1);
//    rC->_particles[(rows / 2 + 1) * cols - 1]->setStatic(1);
    _scene.AddSpringsObject(rC);

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory")
                                                    , "/home"
                                                    ,   QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    string directory = dir.toUtf8().constData();
    _scene.setDirectory(directory);
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
    _scene.Draw(lines);
/*
prev
 -3.32059 -22.2249 -10.9535
 1.88671 -26.545 -12.1133
 3.04649 -22.2249 -17.3205
curr
 -3.13175 -22.1173 -10.7655
 2.30141 -26.1831 -11.6986
 3.23455 -22.1173 -17.1317
triangle j 6
prev
 0.953551 -22.2249 -6.67942
 2.11332 -26.545 -11.8867
 7.32061 -22.2249 -13.0464
curr
 0.765492 -22.1173 -6.86826
 1.69862 -26.1831 -12.3014
 7.13177 -22.1173 -13.2345
 */
/*
    Point3D<float> a0p( -3.32059, -22.2249, -10.9535);
    Point3D<float> a1p(1.88671, -26.545, -12.1133);
    Point3D<float> a2p(3.04649, -22.2249, -17.3205);

    Point3D<float> a0n( -3.13175, -22.1173, -10.7655);
    Point3D<float> a1n(2.30141, -26.1831, -11.6986);
    Point3D<float> a2n(3.23455, -22.1173, -17.1317);

    Point3D<float> b0p(0.953551, -22.2249, -6.67942);
    Point3D<float> b1p(2.11332, -26.545, -11.8867);
    Point3D<float> b2p(7.32061, -22.2249 ,-13.0464);

    Point3D<float> b0n( 0.765492, -22.1173, -6.86826);
    Point3D<float> b1n(1.69862, -26.1831, -12.3014);
    Point3D<float> b2n( 7.13177, -22.1173 ,-13.2345);

    glBegin(GL_LINES);

    glColor3f(0, 0.5, 0);
    DrawableObject::DrawLine(a0p, a1p);
    DrawableObject::DrawLine(a1p, a2p);
    DrawableObject::DrawLine(a2p, a0p);
    glColor3f(0, 1, 0);
    DrawableObject::DrawLine(a0n, a1n);
    DrawableObject::DrawLine(a1n, a2n);
    DrawableObject::DrawLine(a2n, a0n);

    glColor3f(0, 0, 0.5);
    DrawableObject::DrawLine(b0p, b1p);
    DrawableObject::DrawLine(b1p, b2p);
    DrawableObject::DrawLine(b2p, b0p);
    glColor3f(0, 0, 1);
    DrawableObject::DrawLine(b0n, b1n);
    DrawableObject::DrawLine(b1n, b2n);
    DrawableObject::DrawLine(b2n, b0n);

//    VerletParticle p(a1n, 1);
//    VerletParticle b0(b0n, 1);
//    VerletParticle b1(b1n, 1);
//    VerletParticle b2(b2n, 1);
//    ClothTriangle b(&b0, &b1, &b2);
//    b.RecalculatePlane();
//    Point3D<float> prN = b.CalculateProjection(a1n);
//    cout << "isInTriangle " << b.isInTriangle(prN) << endl;

//    Point3D<fVerletClothloat> vecN = prN;
//    vecN -= a1n;

//    glColor3f(1, 0, 0);
//    DrawableObject::DrawLine(prN, a1n);
    glEnd();setVelocity
*/
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
    _scene.FlushHighlighting();
    _scene.Iteration(_timeInterval);
    _scene.ResolveSelfCollision(_timeInterval);
    this->repaint();
//    _scene.WriteToFile();
    return;
    _timeToFrame += _timeInterval;
    if (_timeToFrame >= _repaintDelay)
    {
        //this->_scene.Collide(_timeInterval);
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
/*
prev
1.88671, -26.545, -12.1133
0.953551, -22.2249, -6.67942
2.11332, -26.545, -11.8867
7.32061, -22.2249, -13.0464
curr
2.30141, -26.1831, -11.6986
0.765492, -22.1173, -6.86826
1.69862, -26.1831, -12.3014
7.13177, -22.1173, -13.2345
*/

//    VerletParticle p(ParticlePosition(Point3D<float>( 0, 1,  2)), 1);
//    VerletParticle a(ParticlePosition(Point3D<float>( 2, 0, -1)), 1);
//    VerletParticle b(ParticlePosition(Point3D<float>(-2, 0, -1)), 1);
//    VerletParticle c(ParticlePosition(Point3D<float>( 0, 0,  2)), 1);
//    ClothTriangle t(&a, &b, &c);
//    PointTriangleManifold m(&p, &t);
//    t.RecalculatePlane();
//    Point3D<float> pr = t.CalculateProjection(p._position._position);
//    pr.Print("projection ");
//    cout << "isInTriangle " << t.isInTriangle(pr) << endl;
////    m.ResolveCollision();
////    m._p->_appliedForce.Print("force P");
////    m._t->_p[0]->_appliedForce.Print("force A");
////    m._t->_p[1]->_appliedForce.Print("force B");
////    m._t->_p[2]->_appliedForce.Print("force C");
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
