#include "scenewindow.h"
#include "ui_scenewindow.h"

SceneWindow::SceneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);
}

SceneWindow::~SceneWindow()
{
    delete ui;
}
