#include "scenewindow.h"
#include "ui_scenewindow.h"

#include "iostream"
using namespace std;

SceneWindow::SceneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);
    connect(ui->widget, SIGNAL(MousePress()), this, SLOT(MousePress()));
    connect(ui->widget, SIGNAL(MouseMove()), this, SLOT(MouseMove()));
    connect(ui->widget, SIGNAL(MouseRelease()), this, SLOT(MouseRelease()));
    connect(ui->widget, SIGNAL(Leave()), this, SLOT(Leave()));
}

SceneWindow::~SceneWindow()
{
    delete ui;
}

void SceneWindow::MouseMove()
{
    cout << this->ui->widget->x << " " << this->ui->widget->y << endl;
}

void SceneWindow::MousePress()
{
    cout << "Mouse Pressed\n";
}

void SceneWindow::MouseRelease()
{
    cout << "Mouse Release\n";
}


void SceneWindow::Leave()
{
    cout << "Leave\n";
}
