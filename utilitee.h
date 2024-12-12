// utilitee.h
#ifndef UTILITEE_H
#define UTILITEE_H

#include <QString>
#include <QSqlQueryModel>

class Utilitee
{
public:
    // Constructeurs
    Utilitee();
    Utilitee(int idProd, double prixProd, int qte, const QString &type);

    // Getters et Setters
    void setIdProd(int value);
    void setPrixProd(double value);
    void setQte(int value);
    void setType(const QString &value);

    // Méthodes
    bool isValid() const;
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* statistiquesParType();
    bool supprimer(int idProd);
    bool modifier(int idProd);
    QString msg;

    // Méthode pour enregistrer un historique
    void enregistrerAnnulationDansFichier(int idProd, double &prixprod, int qte, const QString &type, QString msg);
      // Déclaration de la méthode historique

private:
    int idProd;
    double prixProd;
    int qte;
    QString type;
};

#endif // UTILITEE_H
