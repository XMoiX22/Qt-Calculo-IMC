/*
 * -Examen-
 * Abdiel Jimenez ->ajimenezp4@est.ups.edu.ec<-
 * Calculo IMC
 * ID: <1727571752>
 * Grupo 3 Programacion Orientada a Objetos
 * Ingeniero Rodrigo Tufiño
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
