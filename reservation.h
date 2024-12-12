#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Reservation
{
private:
    int NUM_RES;
    QDate CHECK_IN;
    QDate CHECK_OUT;
    int NUM_ENFANT;
    int NUM_CHAMBRE;
    int ETAGE;
    int NUM_ADULT;
    QString OPTIONS;
    int FEED_BACK;

public:
    // Constructeurs
    Reservation();
    Reservation(int numRes, const QDate& checkIn, const QDate& checkOut,
                int numEnfant, int numChambre, int etage, int numAdult, const QString& options,int feedBack);

    // Getters
    int getNUM_RES() const;
    QDate getCHECK_IN() const;
    QDate getCHECK_OUT() const;
    int getNUM_ENFANT() const;
    int getNUM_CHAMBRE() const;
    int getETAGE() const;
    int getNUM_ADULT() const;
    QString getOPTIONS() const;  // Getter pour OPTIONS
    int getFEED_BACK() const;

    // Setters
    void setNUM_RES(int numRes);
    void setCHECK_IN(const QDate& checkIn);
    void setCHECK_OUT(const QDate& checkOut);
    void setNUM_ENFANT(int numEnfant);
    void setNUM_CHAMBRE(int numChambre);
    void setETAGE(int etage);
    void setNUM_ADULT(int numAdult);
    void setOPTIONS(const QString& options);  // Setter pour OPTIONS
    void setFEED_BACK(int feedBack);

    // Méthodes utilitaires
    bool NUM_RESExists(int numRes);

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher1();
    bool modifier(int numRes, const QDate& checkIn, const QDate& checkOut,
                  int numEnfant, int numChambre, int etage, int numAdult, const QString& options,int feed_Back);
    bool supprimer(int numRes);
    bool modifierFeedback(int numRes, int feedback);

    bool modifier1(int NUM_RES, int new_FEED_BACK) ;


};

#endif // RESERVATION_H

