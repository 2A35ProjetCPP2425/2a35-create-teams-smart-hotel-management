#ifndef CHAMBRE_H
#define CHAMBRE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>
#include <QList>
#include <QSerialPort>

class Chambre {
public:
    // Constructors
    Chambre();
    Chambre(int num, const QString& nettoyage, const QString& etage, const QString& tarif, const QString& type);

    // CRUD Methods
    bool ajouter();
    QSqlQueryModel* afficher(const QString& orderBy = "");
    QSqlQueryModel* afficher2(const QString& orderBy = "");
    QSqlQueryModel* afficher3(const QString& orderBy = "");
    bool supprimer(int num);
    bool modifier(int num);
    QSqlQueryModel* rechercher(int num);
    QMap<int, QList<QString>> etatParEtage();

    // LED Control
    void controlLED(int roomNumber);

    // Getters and setters
    int getNum() const;
    QString getNetoyage() const;
    QString getEtage() const;
    QString getTarif() const;
    QString getType() const;

    void setNum(int num);
    void setNetoyage(const QString& nettoyage);
    void setEtage(const QString& etage);
    void setTarif(const QString& tarif);
    void setType(const QString& type);

private:
    int num;
    QString nettoyage;
    QString etage;
    QString tarif;
    QString type;

    QSerialPort serialPort;  // Serial communication with Arduino
};

#endif // CHAMBRE_H
