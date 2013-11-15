#ifndef SCENEGLWIDGET_H
#define SCENEGLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QEvent>

class SceneGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit SceneGLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    int x();
    int y();

signals:
    void MousePressSignal();
    void MouseMoveSignal();
    void MouseReleaseSignal();
    void LeaveSignal();

private:
    QTimer _timer;
    int _x;
    int _y;

};

#endif // SCENEGLWIDGET_H
