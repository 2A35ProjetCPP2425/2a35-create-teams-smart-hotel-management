#ifndef METIER_H
#define METIER_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QString>

class Metier {
public:
    // Tri
    QSqlQueryModel* trierParNom();
    QSqlQueryModel* trierParCIN();
    QSqlQueryModel* trierParNumero();



    // Exportation PDF
    bool exporterPDF(const QString& filePath);
};

#endif // METIER_H
