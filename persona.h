#ifndef PERSONA_H
#define PERSONA_H

#include <QWidget>
#include <QDate>

namespace Ui {
class Persona;
}

class Persona : public QWidget
{
    Q_OBJECT

public:
    explicit Persona(QWidget *parent = nullptr);
    ~Persona();
    void setFecha(QDate fecha);
    void setPeso(double peso);
    void setAltura(double altura);
    QDate getFecha();
    double getAltura();
    double getPeso();
    void calcularIMC();
    void actualizar_pesos();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_4_returnPressed();

    void on_lineEdit_5_returnPressed();

private:
    Ui::Persona *ui;
    QDate fecha;
    double peso;
    double altura;
    double IMC;
    double peso_maximo;
    double peso_minimo;
    QStringList ultima_linea;

};

#endif // PERSONA_H
