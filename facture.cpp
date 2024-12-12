#include "facture.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QVariant>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QSqlError>
#include<QDialog>
#include <QDebug>
facture::facture(){
    ref_e=0;
    mode_p="";
    nom_f="";
    date_f=QDate();
    prix_f=0;

}
void facture::fset(int ref ,QString mode,QString nom,QDate date,float prix )
{
    ref_e=ref;
    mode_p=mode;
    nom_f=nom;
    date_f=date;
    prix_f=prix;

}
bool facture::ajout()
{


    QSqlQuery query;
    query.prepare("INSERT INTO FACTURE (REF_FACTURE, MODE_P, NOM_FAC, DATE_FAC,PRIX_FAC) "
                  "VALUES (:ref, :mode, :nom, :date,:prix)");
    query.bindValue(":ref", ref_e);
    query.bindValue(":mode", mode_p);
    query.bindValue(":nom", nom_f);
    query.bindValue(":date", date_f);
    query.bindValue(":prix", prix_f);




    return query.exec();
}
QSqlQueryModel* facture::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();


    model->setQuery("SELECT * FROM FACTURE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REF_FACTURE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MODE_P"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_FAC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_FAC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_FAC"));


    return model;  // Return the model for display in the view
}

bool facture::supprimer(int ref){
    QSqlQuery query;
    QString res = QString::number(ref);
    query.prepare("DELETE FROM FACTURE WHERE REF_FACTURE = :ref");
    query.bindValue(":ref", res);
    return query.exec();
}
bool facture::modifier(int ref)
{
    QSqlQuery query;
    QString res = QString::number(ref);

    query.prepare("UPDATE FACTURE SET MODE_P = :mode, NOM_FAC = :nom, DATE_FAC = :date, PRIX_FAC = :prix WHERE REF_FACTURE = :ref");
    query.bindValue(":ref", res);
    query.bindValue(":mode", mode_p);
    query.bindValue(":nom", nom_f);
    query.bindValue(":date", date_f);
    query.bindValue(":prix", prix_f);


    return query.exec();
}
QSqlQueryModel* facture::rechercher(const QString &partialId) {
    QSqlQuery query;

    // Prepare the SQL query to search for the partial ID in the 'facture' table
    query.prepare("SELECT * FROM FACTURE WHERE TO_CHAR(REF_FACTURE) LIKE :partialId OR nom_fac LIKE :partialId OR mode_p LIKE :partialId OR TO_CHAR(prix_fac) LIKE :partialId");
    query.bindValue(":partialId", partialId + "%");

    // Execute the query and check for errors
    if (!query.exec()) {
        qDebug() << "Search failed, SQL error:" << query.lastError().text();
        return nullptr;
    }

    // Fill the model with results
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    // Set header labels for each column (adjust as needed for your database table)
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FACTURE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MODE_PAIEMENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_FACTURE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_FACTURE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_FACTURE"));


    return model;
}
QSqlQueryModel* facture::afficher2()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Requête SQL pour récupérer les colonnes NUM_REV et PRIX de la table RESERVATION
    model->setQuery("SELECT  NUM_REV, PRIX_FAC, REF_FACTURE FROM FACTURE");

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_REV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX_FAC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("REF_FACTURE"));


    return model; // Retourne le modèle pour l'affichage
}
QMap<QString, int> facture::statistiquesPaiements() {
    QMap<QString, int> stats;
    QSqlQuery query;

    // Requête pour compter les paiements par chèque
    query.prepare("SELECT COUNT(*) FROM FACTURE WHERE MODE_P = 'cheque'");
    if (query.exec()) {
        if (query.next()) {
            stats["cheque"] = query.value(0).toInt();
        }
    } else {
        qDebug() << "Erreur lors de la récupération des statistiques de paiement par chèque : "
                 << query.lastError().text();
    }

    // Requête pour compter les paiements par espèces
    query.prepare("SELECT COUNT(*) FROM FACTURE WHERE MODE_P = 'espece'");
    if (query.exec()) {
        if (query.next()) {
            stats["espece"] = query.value(0).toInt();
        }
    } else {
        qDebug() << "Erreur lors de la récupération des statistiques de paiement par espèces : "
                 << query.lastError().text();
    }

    return stats;
}
