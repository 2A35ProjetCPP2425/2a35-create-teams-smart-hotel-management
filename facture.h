#ifndef FACTURE_H
#define FACTURE_H
#include<QString>
#include<QDate>
#include<QSqlQueryModel>
#include <QTableView>

class facture
{
private:
    int ref_e;
    QString mode_p,nom_f;
    QDate date_f;
    float prix_f;

public:
    facture();
    void fset(int ref ,QString mode,QString nom,QDate date,float prix_f );
    bool ajout();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher2();
    bool supprimer(int ref);
    bool modifier(int ref);
    bool genererPDF(const QTableView* tableView, const QString& filePath);
    QSqlQueryModel* rechercher(const QString &partialId);
    QSqlQueryModel* trier(const QString& methode);
    QMap<QString, int> statistiquesPaiements();






};

#endif // FACTURE_H
