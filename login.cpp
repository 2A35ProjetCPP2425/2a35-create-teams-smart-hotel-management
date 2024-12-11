#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}



void Login::on_login_clicked()
{
    QString email = ui->email->text().toLower().trimmed();
    QString password = ui->password->text().toLower().trimmed();

    // Vérification du format de l'email
    if (!email.contains("@smarthotel")) {
        QMessageBox::warning(this, "Authentification", "L'email n'est pas valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM admin WHERE email = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            // Authentification réussie
            QMessageBox::information(this, "Authentification", "Connexion réussie !");
            accept(); // Ferme la boîte de dialogue et passe à l'application principale
        } else {
            // Aucun résultat trouvé
            QMessageBox::warning(this, "Authentification", "Email ou mot de passe incorrect.");
        }
    } else {
        // Problème avec l'exécution de la requête
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification : " + query.lastError().text());
    }
    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;

    if (!query.exec()) {
        qDebug() << "SQL Error: " << query.lastError().text();
    }

}

