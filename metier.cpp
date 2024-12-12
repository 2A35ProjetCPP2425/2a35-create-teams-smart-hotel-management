#include "metier.h"
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>

// Tri par nom (ordre alphabétique)
QSqlQueryModel* Metier::trierParNom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY NOM ASC");
    return model;
}

// Tri par CIN
QSqlQueryModel* Metier::trierParCIN() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY CIN ASC");
    return model;
}

// Tri par numéro
QSqlQueryModel* Metier::trierParNumero() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client ORDER BY NUM ASC");
    return model;
}

