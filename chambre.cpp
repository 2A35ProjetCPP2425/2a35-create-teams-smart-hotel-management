#include "chambre.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

// Constructors
Chambre::Chambre() : num(0), nettoyage(""), etage(""), tarif(""), type("") {}

Chambre::Chambre(int num, const QString& nettoyage, const QString& etage, const QString& tarif, const QString& type)
    : num(num), nettoyage(nettoyage), etage(etage), tarif(tarif), type(type) {}

// CRUD Methods
bool Chambre::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO CHAMBRE (NUM, NETOYAGE, ETAGE, TARIF, TYPE) "
                  "VALUES (:num, :netoyage, :etage, :tarif, :type)");
    query.bindValue(":num", num);
    query.bindValue(":netoyage", nettoyage);
    query.bindValue(":etage", etage);
    query.bindValue(":tarif", tarif);
    query.bindValue(":type", type);

    return query.exec();
}

QSqlQueryModel* Chambre::afficher(const QString& orderBy) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM CHAMBRE";
    if (!orderBy.isEmpty()) {
        queryStr += " ORDER BY " + orderBy;
    }
    model->setQuery(queryStr);
    return model;
}

QSqlQueryModel* Chambre::afficher2(const QString& orderBy) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM CHAMBRE WHERE TYPE = 'Standard'";
    if (!orderBy.isEmpty()) {
        queryStr += " ORDER BY " + orderBy;
    }
    model->setQuery(queryStr);
    return model;
}

QSqlQueryModel* Chambre::afficher3(const QString& orderBy) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM CHAMBRE WHERE NETOYAGE = '1'";
    if (!orderBy.isEmpty()) {
        queryStr += " ORDER BY " + orderBy;
    }
    model->setQuery(queryStr);
    return model;
}

bool Chambre::supprimer(int num) {
    QSqlQuery query;
    query.prepare("DELETE FROM CHAMBRE WHERE NUM = :num");
    query.bindValue(":num", num);
    return query.exec();
}

bool Chambre::modifier(int num) {
    QSqlQuery query;
    query.prepare("UPDATE CHAMBRE SET NETOYAGE = :netoyage, ETAGE = :etage, TARIF = :tarif, TYPE = :type "
                  "WHERE NUM = :num");
    query.bindValue(":netoyage", nettoyage);
    query.bindValue(":etage", etage);
    query.bindValue(":tarif", tarif);
    query.bindValue(":type", type);
    query.bindValue(":num", num);
    return query.exec();
}

QSqlQueryModel* Chambre::rechercher(int num) {
    QSqlQuery query;
    query.prepare("SELECT * FROM CHAMBRE WHERE NUM = :num");
    query.bindValue(":num", num);

    if (query.exec()) {
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        return model;
    } else {
        return nullptr;
    }
}

QMap<int, QList<QString>> Chambre::etatParEtage() {
    QMap<int, QList<QString>> etat;
    QSqlQuery query("SELECT NUM, TYPE, ETAGE, TARIF, NETOYAGE FROM CHAMBRE");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la requête: " << query.lastError();
        return etat;
    }

    while (query.next()) {
        int etage = query.value("ETAGE").toInt();
        QString chambreInfo = QString("NUM: %1, NETOYAGE: %2, TARIF: %3, TYPE: %4")
                                  .arg(query.value("NUM").toString())
                                  .arg(query.value("NETOYAGE").toString())
                                  .arg(query.value("TARIF").toString())
                                  .arg(query.value("TYPE").toString());

        etat[etage].append(chambreInfo);
    }

    return etat;
}

// LED Control Method
void Chambre::controlLED(int roomNumber) {
    QSqlQuery query;
    query.prepare("SELECT NETOYAGE FROM CHAMBRE WHERE NUM = :num");
    query.bindValue(":num", roomNumber);

    if (query.exec() && query.next()) {
        int nettoyageStatus = query.value("NETOYAGE").toInt();

        if (!serialPort.isOpen()) {
            serialPort.setPortName("COM5");  // Adjust the port name as needed
            serialPort.setBaudRate(QSerialPort::Baud9600);
            serialPort.setDataBits(QSerialPort::Data8);
            serialPort.setParity(QSerialPort::NoParity);
            serialPort.setStopBits(QSerialPort::OneStop);
            serialPort.setFlowControl(QSerialPort::NoFlowControl);

            if (!serialPort.open(QIODevice::WriteOnly)) {
                qDebug() << "Failed to open serial port:" << serialPort.errorString();
                return;
            }
        }

        if (nettoyageStatus == 1) {
            serialPort.write("G");  // Send signal to turn on the green LED
            qDebug() << "Green LED ON for room" << roomNumber;
        } else if (nettoyageStatus == 0) {
            serialPort.write("R");  // Send signal to turn on the red LED
            qDebug() << "Red LED ON for room" << roomNumber;
        }
    } else {
        qDebug() << "Error fetching room cleaning status:" << query.lastError();
    }

    serialPort.close();
}

// Getters
int Chambre::getNum() const { return num; }
QString Chambre::getNetoyage() const { return nettoyage; }
QString Chambre::getEtage() const { return etage; }
QString Chambre::getTarif() const { return tarif; }
QString Chambre::getType() const { return type; }

// Setters
void Chambre::setNum(int num) { this->num = num; }
void Chambre::setNetoyage(const QString& nettoyage) { this->nettoyage = nettoyage; }
void Chambre::setEtage(const QString& etage) { this->etage = etage; }
void Chambre::setTarif(const QString& tarif) { this->tarif = tarif; }
void Chambre::setType(const QString& type) { this->type = type; }
