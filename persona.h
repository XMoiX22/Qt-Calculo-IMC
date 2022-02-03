#ifndef PERSONA_H
#define PERSONA_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class Persona;
}

class Persona : public QWidget
{
    Q_OBJECT

public:
    explicit Persona(QWidget *parent = nullptr);
    ~Persona();
    void setFecha(QDateTime fecha);
    void setPeso(float peso);
    void setAltura(float altura);
    QDateTime getFecha();
    float getAltura();
    float getPeso();
    float calcularIMC();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Persona *ui;
    QDateTime fecha;
    float peso;
    float altura;
    float IMC;

};

#endif // PERSONA_H
