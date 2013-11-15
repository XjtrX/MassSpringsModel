#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <QMainWindow>
#include "sceneglwidget.h"

namespace Ui {
class SceneWindow;
}

class SceneWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SceneWindow(QWidget *parent = 0);
    ~SceneWindow();
    
private slots:
    void MouseMoveSlot();
    void MousePressSlot();
    void MouseReleaseSlot();
    void LeaveSlot();

private:
    Ui::SceneWindow *ui;
};

#endif // SCENEWINDOW_H
