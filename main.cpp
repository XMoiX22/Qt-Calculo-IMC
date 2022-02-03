/*
 * Abdiel Moises Jimenez Perez
 * CI: 1727571752
 * Examen Prorgramacion Orientada a Objetos
 * Grupo 3
 * Calculo Indice Masa Corporal
 */
#include "mainwindow.h"
#include "persona.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Objeto para manejar las traducciones
    QTranslator traducion;
    // Solicitando al usuario que seleccione un idioma
    QStringList idiomas;
    idiomas << "Chino" <<"Español";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                               "Idioma",
                               "Seleccione un idioma",
                               idiomas);
    // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
    if (idiomaSeleccionado == "Chino"){
        traducion.load(":/calculo-imc_ch.qm");
    }else if (idiomaSeleccionado == "Inglés"){
        traducion.load(":/calculo-imc_en.qm");
    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idiomaSeleccionado != "Español"){
        a.installTranslator(&traducion);
    }
    // Muestra la ventana principal
    Persona w;
    w.show();
    return a.exec();
}
