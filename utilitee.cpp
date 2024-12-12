#include "utilitee.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QThread>

// Constructeurs
Utilitee::Utilitee()
    : idProd(0), prixProd(0.0), qte(0), type("")
{
}

Utilitee::Utilitee(int idProd, double prixProd, int qte, const QString &type)
    : idProd(idProd), prixProd(prixProd), qte(qte), type(type)
{
}

// Fonction pour enregistrer une annulation dans un fichier CSV
void Utilitee::enregistrerAnnulationDansFichier(int idProd, double &prixprod, int qte, const QString &type, QString msg) {
    // Chemin absolu vers le fichier historique
    QString filePath = "C:/Users/jouin/OneDrive/Desktop/jouinMM/jouinMM/historique.txt";


    QFile fichier(filePath);
    if (!fichier.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur : impossible d'ouvrir le fichier pour l'historique des annulations.";
        return;
    }

    QTextStream out(&fichier);

    // Ajouter un en-tête si le fichier est vide
    if (fichier.size() == 0) {
        out << "Message,ID Produit,Prix Produit,Quantité,Type,Date Heure Enregistrement\n";
    }

    // Ajouter les données
    out << msg << ","
        << idProd << ","
        << prixprod << ","
        << qte << ","
        << type << ","
        << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "\n";

    fichier.close();
    qDebug() << "Produit annulé enregistré avec succès dans l'historique.";
}


bool Utilitee::ajouter()
{


    QSqlQuery query;
    query.prepare("INSERT INTO UTILITEE (ID_PROD, PRIX_PROD, QTE, TYPE) "
                  "VALUES (:idProd, :prixProd, :qte, :type)");

    query.bindValue(":idProd", idProd);
    query.bindValue(":prixProd", prixProd);
    query.bindValue(":qte", qte);
    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout : " << query.lastError();
        return false;
    }

    return true;
}

bool Utilitee::supprimer(int idProd)
{
    QSqlQuery query;
    query.prepare("DELETE FROM UTILITEE WHERE ID_PROD = :idProd");
    query.bindValue(":idProd", idProd);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression : " << query.lastError();
        return false;
    }

    return true;
}

bool Utilitee::modifier(int idProd)
{


    QSqlQuery query;
    query.prepare("UPDATE UTILITEE SET PRIX_PROD = :prixProd, QTE = :qte, TYPE = :type "
                  "WHERE ID_PROD = :idProd");

    query.bindValue(":idProd", idProd);
    query.bindValue(":prixProd", prixProd);
    query.bindValue(":qte", qte);
    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour : " << query.lastError();
        return false;
    }

    return true;
}
QSqlQueryModel* Utilitee::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();  // Crée un nouveau modèle de requête

    // Exécute une requête pour récupérer toutes les données de la table UTILITEE
    model->setQuery("SELECT * FROM UTILITEE");

    // Définir les en-têtes pour chaque colonne du modèle
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Produit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix Produit"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));

    return model;  // Retourne le modèle rempli
}
QSqlQueryModel* Utilitee::statistiquesParType()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Requête SQL pour obtenir la somme des quantités et des prix par type
    QString query = "SELECT TYPE, "
                    "SUM(QTE) AS Total_Qte, "
                    "SUM(PRIX_PROD * QTE) AS Total_Prix "
                    "FROM UTILITEE "
                    "GROUP BY TYPE "
                    "ORDER BY TYPE";

    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur dans la requête statistiques par type: " << model->lastError().text();
    }

    return model;
}
