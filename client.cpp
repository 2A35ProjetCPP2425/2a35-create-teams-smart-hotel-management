#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructeur par défaut
Client::Client() {
    // Initialiser les attributs avec des valeurs par défaut
    CIN = 0;
    NOM = "";
    PRENOM = "";
    NUM = 0;
    ADRESSE = "";
    GENRE = "";
}

// Constructeur avec paramètres
Client::Client(int CIN, const QString& NOM, const QString& PRENOM, int NUM, const QString& ADRESSE, const QString& GENRE)
    : CIN(CIN), NOM(NOM), PRENOM(PRENOM), NUM(NUM),GENRE(GENRE), ADRESSE(ADRESSE) {}

// Getters
int Client::getCIN() const { return CIN; }
QString Client::getNOM() const { return NOM; }
QString Client::getPRENOM() const { return PRENOM; }
int Client::getNUM() const { return NUM; }
QString Client::getADRESSE() const { return ADRESSE; }
QString Client::getGENRE() const { return GENRE; }

// Setters
void Client::setCIN(int CIN) { this->CIN = CIN; }
void Client::setNOM(const QString& NOM) { this->NOM = NOM; }
void Client::setPRENOM(const QString& PRENOM) { this->PRENOM = PRENOM; }
void Client::setNUM(int NUM) { this->NUM = NUM; }
void Client::setADRESSE(const QString& ADRESSE) { this->ADRESSE = ADRESSE; }
void Client::setGENRE(const QString& GENRE) { this->GENRE = GENRE; }

bool Client::CINExists(int CIN) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM client WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// Méthode pour ajouter un client
#include <QMessageBox> // Pour afficher des messages d'erreur

bool Client::ajouter() {

    if (CIN <= 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le CIN doit être un entier positif.");
        return false;
    }
    if (CINExists(CIN)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Ce CIN existe déjà. Veuillez entrer un CIN unique.");
        return false;
    }
    if (NOM.isEmpty() || PRENOM.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nom et le prénom doivent être renseignés.");
        return false;
    }
    if (NUM <= 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le numéro de téléphone doit être un entier positif.");
        return false;
    }
    if (ADRESSE.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'adresse ne peut pas être vide.");
        return false;
    }
    if (GENRE.isEmpty() || (GENRE != "Masculin" && GENRE != "Feminin")) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le genre doit être 'Masculin' ou 'Féminin'.");
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO client (CIN, NOM, PRENOM, NUM, ADRESSE, GENRE) "
                  "VALUES (:CIN, :NOM, :PRENOM, :NUM, :ADRESSE, :GENRE)");

    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":NUM", NUM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":GENRE", GENRE);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du client:" << query.lastError().text();
        return false;
    }

    return true;
}



// Méthode pour afficher les clients
QSqlQueryModel* Client::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));

    return model;
}

// Méthode pour modifier un client
bool Client::modifier(int CIN, const QString& NOM, const QString& PRENOM, int NUM, const QString& ADRESSE, const QString& GENRE) {
    if (CIN <= 0) {
        qDebug() << "CIN non valide.";
        return false;
    }

    QStringList updateFields;

    if (NOM != "") { updateFields << "NOM = :NOM"; }
    if (PRENOM != "") { updateFields << "PRENOM = :PRENOM"; }
    if (NUM > 0) { updateFields << "NUM = :NUM"; }
    if (ADRESSE != "") { updateFields << "ADRESSE = :ADRESSE"; }
    if (GENRE != "") { updateFields << "GENRE = :GENRE"; }

    if (updateFields.isEmpty()) {
        qDebug() << "Aucun champ à mettre à jour.";
        return false;
    }

    QString queryString = "UPDATE client SET " + updateFields.join(", ") + " WHERE CIN = :CIN";

    QSqlQuery query;
    query.prepare(queryString);

    if (NOM != "") query.bindValue(":NOM", NOM);
    if (PRENOM != "") query.bindValue(":PRENOM", PRENOM);
    if (NUM > 0) query.bindValue(":NUM", NUM);
    if (ADRESSE != "") query.bindValue(":ADRESSE", ADRESSE);
    if (GENRE != "") query.bindValue(":GENRE", GENRE);

    query.bindValue(":CIN", CIN);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification du client:" << query.lastError().text();
        return false;
    }
    return true;
}

// Méthode pour supprimer un client
bool Client::supprimer(int CIN) {
    QSqlQuery query;
    query.prepare("DELETE FROM client WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du client:" << query.lastError().text();
        return false;
    }
    return true;
}
