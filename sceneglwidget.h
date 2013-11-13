#ifndef SCENEGLWIDGET_H
#define SCENEGLWIDGET_H

#include <QGLWidget>

class SceneGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit SceneGLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


};

#endif // SCENEGLWIDGET_H
