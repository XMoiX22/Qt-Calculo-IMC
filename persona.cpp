#include "persona.h"
#include "ui_persona.h"
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Persona::Persona(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Persona)
{
    ui->setupUi(this);
    this->peso_maximo = -1;
    this->peso_minimo = 99999;
    //actualizamos los pesos desde el archivo
    this->actualizar_pesos();
    //actualizamos los valores en pantalla
    qDebug() << "voy aqu";
    if( peso_maximo < 0){
        ui->label_11->setText("0 Kg");
        ui->label_9->setText("0 Kg");
        ui->label_27->setEnabled(false);
    }else{
        ui->label_11->setText(QString::number(this->peso_maximo)+" Kg");
        ui->label_9->setText(QString::number(this->peso_minimo)+" Kg");

        this->setPeso(this->ultima_linea[1].toDouble());
        this->setAltura(this->ultima_linea[2].toDouble()/100);
        this->setFecha(QDate::fromString(this->ultima_linea[0],"dd-MM-yyyy"));

        //calculamos el IMC actual
        calcularIMC();

        ui->lineEdit_4->setText(this->ultima_linea[1]);
        ui->lineEdit_5->setText(this->ultima_linea[2]);
    }
}
void Persona::actualizar_pesos(){
    //ABRIMOS EL ARCHIVO PARA CARGAR LA INFORMACION

    QFile imc("IMC.txt"); //variable de tipo File para generar un archivo
    imc.open(QIODevice::ReadOnly | QIODevice::Text);


    QStringList ultima_linea;
    //ciclo para recorrer todas los datos del usuario
    while(!imc.atEnd()){
        QByteArray linea = imc.readLine();
        QString str(linea);
        QStringList datos = str.split(" ");

        if( datos[1].toDouble() > this->peso_maximo){
            this->peso_maximo = datos[1].toDouble();
        }
        if( datos[1].toDouble() < this->peso_minimo){
            this->peso_minimo = datos[1].toDouble();
        }
        this->ultima_linea = datos;//guardamos la ultima linea para obtener la fecha peso y altura actuales
    }
    imc.close(); //se cierra el archivo abierto
}
Persona::~Persona()
{
    delete ui;
}
void Persona::setPeso(double peso)
{
    Persona::peso = peso;
}
void Persona::setAltura(double altura)
{
    Persona::altura = altura;
}
void Persona::setFecha(QDate fecha)
{
    Persona::fecha = fecha;
}

QDate Persona::getFecha(){
    return Persona::fecha;
}

double Persona::getPeso()
{
    return Persona::peso;
}
double Persona::getAltura()
{
    return Persona::altura;
}
//metodo que calcula el indice de masa corporal
void Persona::calcularIMC()
{
    Persona::IMC = Persona::peso/(Persona::altura*Persona::altura);

    //cambia los colores de la apreciacion y el texto asi como tmabien ubica la barra del imc, y se agrego (tr) para las traducciones de las palabras.
    if(Persona::IMC < 15 ){
        ui->label_27->setText(tr("Bajo peso"));
        ui->label_27->setStyleSheet("color: rgb(0, 0, 0);");
        ui->line_2->setGeometry(0,280,20,51);
        ui->label_24->setGeometry(0,260,47,13);
    }else if(Persona::IMC < 16 ){
        ui->label_27->setText(tr("Bajo peso"));
        ui->label_27->setStyleSheet("color: rgb(111, 167, 167);");
        ui->line_2->setGeometry(int(Persona::IMC*1.8),280,20,51);
        ui->label_24->setGeometry(int(Persona::IMC*1.8),260,47,13);

    }else if(Persona::IMC < 18.5 ){
        ui->label_27->setText(tr("Bajo peso"));
        ui->label_27->setStyleSheet("color: rgb(33, 33, 99);");
        ui->line_2->setGeometry(int(30+Persona::IMC*1.8),280,20,51);
        ui->label_24->setGeometry(int(30+Persona::IMC*1.8),260,47,13);
    }else if(Persona::IMC < 25 ){
        ui->label_27->setText(tr("Peso Normal"));
        ui->label_27->setStyleSheet("color: rgb(0, 255, 127);");
        ui->line_2->setGeometry(int(60+Persona::IMC*5),280,20,51);
        ui->label_24->setGeometry(int(60+Persona::IMC*5),260,47,13);
    }else if(Persona::IMC < 30 ){
        ui->label_27->setText(tr("Sobrepeso"));
        ui->label_27->setStyleSheet("color: rgb(202, 202, 100);");
        ui->line_2->setGeometry(int(120+Persona::IMC*5),280,20,51);
        ui->label_24->setGeometry(int(120+Persona::IMC*5),260,47,13);
    }else if(Persona::IMC < 35 ){
        ui->label_27->setText(tr("Obesidad"));
        ui->label_27->setStyleSheet("color: rgb(255, 170, 0);");
        ui->line_2->setGeometry(int(180+Persona::IMC*4.4),280,20,51);
        ui->label_24->setGeometry(int(180+Persona::IMC*4.4),260,47,13);
    }else{
        ui->label_27->setText(tr("Obesidad"));
        ui->label_27->setStyleSheet("color: rgb(255, 0, 0);");
        ui->line_2->setGeometry(int(200+Persona::IMC*5.5),280,20,51);
        ui->label_24->setGeometry(int(200+Persona::IMC*5.5),260,47,13);
    }

    ui->label_24->setText(QString::number(Persona::IMC,'f',2));
    ui->label_5->setText(tr("IMC(kg/m^2): ")+QString::number(Persona::IMC,'f',2));
}

void Persona::on_pushButton_3_clicked()
{
    ui->lineEdit_4->setEnabled(true);

}

void Persona::on_pushButton_2_clicked()
{
    ui->lineEdit_5->setEnabled(true);

}
//para controlar cada vez que se actualice el peso

void Persona::on_lineEdit_4_returnPressed()
{
    if( ui->lineEdit_4->text().length() > 0 && ui->lineEdit_5->text().length()){
        QFile imc("IMC.txt"); //variable de tipo File para generar un archivo
        imc.open(QIODevice::ReadWrite | QIODevice::Text);

        QTextStream stream(&imc);
        stream.seek(imc.size());
        QDate date = ui->dateEdit->date();
        this->setFecha(date);

        this->setPeso(ui->lineEdit_4->text().toDouble());
        this->setAltura(ui->lineEdit_5->text().toDouble()/100);
        stream << date.toString("dd-MM-yyyy")+" "+QString::number(this->getPeso())+" "+QString::number(this->getAltura()*100)+"\n";

        this->calcularIMC();
        imc.close();

        //actualizamos los pesos desde el archivo
        this->actualizar_pesos();
        //actualizamos los valores en pantalla
        if( this->peso_maximo > 0){
            ui->label_11->setText(QString::number(this->peso_maximo)+" Kg");
            ui->label_9->setText(QString::number(this->peso_minimo)+" Kg");

            //calculamos el IMC actual
            this->calcularIMC();
        }
    }
}

void Persona::on_lineEdit_5_returnPressed()
{
    if( ui->lineEdit_4->text().length() > 0 && ui->lineEdit_5->text().length()){
        QFile imc("IMC.txt"); //variable de tipo File para generar un archivo
        imc.open(QIODevice::ReadWrite | QIODevice::Text);

        QTextStream stream(&imc);
        stream.seek(imc.size());
        QDate date = ui->dateEdit->date();
        this->setFecha(date);

        this->setPeso(ui->lineEdit_4->text().toDouble());
        this->setAltura(ui->lineEdit_5->text().toDouble()/100);
        stream << date.toString("dd-MM-yyyy")+" "+QString::number(this->getPeso())+" "+QString::number(this->getAltura()*100)+"\n";
        this->calcularIMC();
        imc.close();

        //actualizamos los pesos desde el archivo
        this->actualizar_pesos();
        //actualizamos los valores en pantalla
        if( this->peso_maximo > 0){
            ui->label_11->setText(QString::number(this->peso_maximo)+" Kg");
            ui->label_9->setText(QString::number(this->peso_minimo)+" Kg");

            //calculamos el IMC actual
            this->calcularIMC();
        }
    }
}
