#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
private:
    int CIN;
    QString NOM;
    QString PRENOM;
    int NUM;
    QString GENRE;
    QString ADRESSE;

public:
    // Constructors
    Client();
    Client(int CIN, const QString& NOM, const QString& PRENOM, int NUM, const QString& ADRESSE, const QString& GENRE);

    // Getters
    int getCIN() const;
    int getNUM() const;
    QString getNOM() const;
    QString getPRENOM() const;
    QString getGENRE() const;
    QString getADRESSE() const;

    // Setters
    void setCIN(int CIN);
    void setNUM(int NUM);
    void setNOM(const QString& NOM);
    void setPRENOM(const QString& PRENOM);
    void setGENRE(const QString& GENRE);
    void setADRESSE(const QString& ADRESSE);

    // Utility Methods
    bool CINExists(int CIN);

    // CRUD Methods
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int CIN, const QString& NOM, const QString& PRENOM, int NUM, const QString& ADRESSE, const QString& GENRE);
    bool supprimer(int CIN);
};

#endif // CLIENT_H
