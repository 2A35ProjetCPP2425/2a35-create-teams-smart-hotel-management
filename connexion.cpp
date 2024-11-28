#include "connexion.h"

Connection::Connection() {}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("CPP_projet");//inserer le nom de la source de données
    db.setUserName("houssaine");//inserer nom de l'utilisateur
    db.setPassword("oracle");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}
