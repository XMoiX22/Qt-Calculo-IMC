#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "persona.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Persona *nueva_persona = new Persona();

    nueva_persona->setVisible(true);
}
