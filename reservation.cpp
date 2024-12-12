#include "reservation.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructeur par défaut
Reservation::Reservation() {
    // Initialiser les attributs avec des valeurs par défaut
    NUM_RES = 0;
    CHECK_IN = QDate();
    CHECK_OUT = QDate();
    NUM_ENFANT = 0;
    NUM_CHAMBRE = 0;
    ETAGE = 0;
    NUM_ADULT = 0;
    OPTIONS = "";
    FEED_BACK =0;
}

// Constructeur avec paramètres
Reservation::Reservation(int numRes, const QDate& checkIn, const QDate& checkOut,
                         int numEnfant, int numChambre, int etage, int numAdult, const QString& options,int feedBack )
    : NUM_RES(numRes), CHECK_IN(checkIn), CHECK_OUT(checkOut),
      NUM_ENFANT(numEnfant), NUM_CHAMBRE(numChambre), ETAGE(etage), NUM_ADULT(numAdult), OPTIONS(options),FEED_BACK(feedBack) {}

// Getters
int Reservation::getNUM_RES() const { return NUM_RES; }
QDate Reservation::getCHECK_IN() const { return CHECK_IN; }
QDate Reservation::getCHECK_OUT() const { return CHECK_OUT; }
int Reservation::getNUM_ENFANT() const { return NUM_ENFANT; }
int Reservation::getNUM_CHAMBRE() const { return NUM_CHAMBRE; }
int Reservation::getETAGE() const { return ETAGE; }
int Reservation::getNUM_ADULT() const { return NUM_ADULT; }
QString Reservation::getOPTIONS() const { return OPTIONS; }  // Getter pour OPTIONS
int Reservation::getFEED_BACK() const { return FEED_BACK; }

// Setters
void Reservation::setNUM_RES(int numRes) { NUM_RES = numRes; }
void Reservation::setCHECK_IN(const QDate& checkIn) { CHECK_IN = checkIn; }
void Reservation::setCHECK_OUT(const QDate& checkOut) { CHECK_OUT = checkOut; }
void Reservation::setNUM_ENFANT(int numEnfant) { NUM_ENFANT = numEnfant; }
void Reservation::setNUM_CHAMBRE(int numChambre) { NUM_CHAMBRE = numChambre; }
void Reservation::setETAGE(int etage) { ETAGE = etage; }
void Reservation::setNUM_ADULT(int numAdult) { NUM_ADULT = numAdult; }
void Reservation::setOPTIONS(const QString& options) { OPTIONS = options; }  // Setter pour OPTIONS
void Reservation::setFEED_BACK(int feedBack ) { FEED_BACK = feedBack; }

bool Reservation::NUM_RESExists(int numRes) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM reservation WHERE NUM_RES = :NUM_RES");
    query.bindValue(":NUM_RES", numRes);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// Méthode pour ajouter une réservation
#include <QMessageBox> // Pour afficher des messages d'erreur

bool Reservation::ajouter() {

    if (NUM_RES <= 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le numéro de réservation doit être un entier positif.");
        return false;
    }

    if (NUM_RESExists(NUM_RES)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Ce numéro de réservation existe déjà. Veuillez entrer un numéro unique.");
        return false;
    }
    if (CHECK_IN > CHECK_OUT) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "La date de départ (CHECK_OUT) ne peut pas être antérieure à la date d'arrivée (CHECK_IN).");
        return false;
    }
    if (NUM_ENFANT < 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nombre d'enfants ne peut pas être négatif.");
        return false;
    }
    if (NUM_ADULT < 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nombre d'adultes ne peut pas être négatif.");
        return false;
    }
    if (NUM_CHAMBRE <= 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le numéro de chambre doit être un entier positif.");
        return false;
    }

    if (ETAGE < 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'étage ne peut pas être négatif.");
        return false;
    }
    if (OPTIONS.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Les options ne peuvent pas être vides.");
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO reservation (NUM_RES, CHECK_IN, CHECK_OUT, NUM_ENFANT, NUM_CHAMBRE, ETAGE, NUM_ADULT, OPTIONS,FEED_BACK) "
                  "VALUES (:NUM_RES, :CHECK_IN, :CHECK_OUT, :NUM_ENFANT, :NUM_CHAMBRE, :ETAGE, :NUM_ADULT, :OPTIONS,:FEED_BACK)");

    query.bindValue(":NUM_RES", NUM_RES);
    query.bindValue(":CHECK_IN", CHECK_IN);
    query.bindValue(":CHECK_OUT", CHECK_OUT);
    query.bindValue(":NUM_ENFANT", NUM_ENFANT);
    query.bindValue(":NUM_CHAMBRE", NUM_CHAMBRE);
    query.bindValue(":ETAGE", ETAGE);
    query.bindValue(":NUM_ADULT", NUM_ADULT);
    query.bindValue(":OPTIONS", OPTIONS);
    query.bindValue(":FEED_BACK", FEED_BACK);

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de la réservation:" << query.lastError().text();
        return false;
    }

    return true;
}

// Méthode pour afficher les réservations
QSqlQueryModel* Reservation::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT NUM_RES,CHECK_IN,CHECK_OUT,NUM_ENFANT,NUM_ADULT,ETAGE,NUM_CHAMBRE,OPTIONS,FEED_BACK FROM reservation");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_RES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CHECK_IN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CHECK_OUT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_ENFANT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_ADULT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAGE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUM_CHAMBRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("OPTIONS"));// Affichage du champ OPTIONS
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("FEED_BACK"));


    return model;
}
QSqlQueryModel* Reservation::afficher1() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT NUM_RES,FEED_BACK FROM reservation");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_RES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FEED_BACK"));


    return model;
}

// Méthode pour modifier une réservation
bool Reservation::modifier(int numRes, const QDate& checkIn, const QDate& checkOut,
                           int numEnfant, int numChambre, int etage, int numAdult, const QString& options, int feedBack) {
    if (numRes <= 0) {
        qDebug() << "Numéro de réservation non valide.";
        return false;
    }

    QStringList updateFields;

    if (checkIn.isValid()) { updateFields << "CHECK_IN = :CHECK_IN"; }
    if (checkOut.isValid()) { updateFields << "CHECK_OUT = :CHECK_OUT"; }
    if (numEnfant >= 0) { updateFields << "NUM_ENFANT = :NUM_ENFANT"; }
    if (numChambre > 0) { updateFields << "NUM_CHAMBRE = :NUM_CHAMBRE"; }
    if (etage >= 0) { updateFields << "ETAGE = :ETAGE"; }
    if (numAdult >= 0) { updateFields << "NUM_ADULT = :NUM_ADULT"; }
    if (!options.isEmpty()) { updateFields << "OPTIONS = :OPTIONS"; }
    if (feedBack >= -1) { updateFields << "FEED_BACK = :FEED_BACK"; }

    if (updateFields.isEmpty()) {
        qDebug() << "Aucun champ à mettre à jour.";
        return false;
    }

    QString queryString = "UPDATE reservation SET " + updateFields.join(", ") + " WHERE NUM_RES = :NUM_RES";

    QSqlQuery query;
    query.prepare(queryString);

    if (checkIn.isValid()) query.bindValue(":CHECK_IN", checkIn);
    if (checkOut.isValid()) query.bindValue(":CHECK_OUT", checkOut);
    if (numEnfant >= 0) query.bindValue(":NUM_ENFANT", numEnfant);
    if (numChambre > 0) query.bindValue(":NUM_CHAMBRE", numChambre);
    if (etage >= 0) query.bindValue(":ETAGE", etage);
    if (numAdult >= 0) query.bindValue(":NUM_ADULT", numAdult);
    if (!options.isEmpty()) query.bindValue(":OPTIONS", options);
    if (feedBack >= -1) query.bindValue(":FEED_BACK", feedBack);

    query.bindValue(":NUM_RES", numRes);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification de la réservation:" << query.lastError().text();
        return false;
    }
    return true;
}


bool Reservation::modifier1(int NUM_RES, int nouveauFeedBack) {
    QSqlQuery query;

    // Préparation de la requête SQL pour calculer la moyenne
    query.prepare(R"(
        UPDATE RESERVATION
        SET FEED_BACK = (FEED_BACK + :nouveauFeedBack) / 2
        WHERE NUM_RES = :NUM_RES
    )");

    // Liaison des valeurs
    query.bindValue(":nouveauFeedBack", nouveauFeedBack);
    query.bindValue(":NUM_RES", NUM_RES);

    // Exécution de la requête et gestion des erreurs
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du feedback :" << query.lastError().text();
        return false;
    }

    return true;
}



// Méthode pour supprimer une réservation
bool Reservation::supprimer(int numRes) {
    QSqlQuery query;
    query.prepare("DELETE FROM reservation WHERE NUM_RES = :NUM_RES");
    query.bindValue(":NUM_RES", numRes);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de la réservation:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Reservation::modifierFeedback(int numRes, int feedback) {
    QSqlQuery query;

    // Préparation de la requête SQL pour calculer la moyenne du feedback
    query.prepare(R"(
        UPDATE RESERVATION
        SET FEED_BACK = (FEED_BACK + :feedback) / 2
        WHERE NUM_RES = :numRes
    )");

    query.bindValue(":feedback", feedback);
    query.bindValue(":numRes", numRes);

    // Exécution de la requête et gestion des erreurs
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du feedback :" << query.lastError().text();
        return false;  // Retourner false en cas d'erreur
    }

    return true;  // Retourner true si la mise à jour a réussi
}

