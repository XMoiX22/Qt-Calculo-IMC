#include "persona.h"
#include "ui_persona.h"
#include <QDateTime>

Persona::Persona(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Persona)
{
    ui->setupUi(this);
}

Persona::~Persona()
{
    delete ui;
}
void Persona::setPeso(float peso)
{
    Persona::peso = peso;
}
void Persona::setAltura(float altura)
{
    Persona::altura = altura;
}
void Persona::setFecha(QDateTime fecha)
{
    Persona::fecha = fecha;
}

QDateTime Persona::getFecha(){
    return Persona::fecha;
}

float Persona::getPeso()
{
    return Persona::peso;
}
float Persona::getAltura()
{
    return Persona::altura;
}
//metodo que calcula el indice de masa corporal
float Persona::calcularIMC()
{
    Persona::IMC = Persona::peso/Persona::altura;

    return Persona::IMC;
}

void Persona::on_pushButton_3_clicked()
{
    ui->lineEdit_4->setEnabled(true);
}

void Persona::on_pushButton_2_clicked()
{
    ui->lineEdit_5->setEnabled(true);
}
