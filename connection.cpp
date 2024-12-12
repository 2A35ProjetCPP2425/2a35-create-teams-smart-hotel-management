#include "connection.h"

connection::connection(){}

bool connection::createconnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("CPP_PROJECTT");//CPP_PROJECT
    db.setUserName("Amine"); //ilyes
    db.setPassword("oracle"); //oracle
    if (db.open()) test=true;
    return test;
}

void connection::closeconnection(){db.close();}
