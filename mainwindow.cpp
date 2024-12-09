#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include "Chambre.h"
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QRegularExpression>


QSerialPort *serialPort; // Serial port for Arduino communication

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Vérifiez la connexion à la base de données ici avant de remplir le QComboBox
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "La connexion à la base de données a échoué!";
    }
    // Initialize the table with room data
    // Setup serial port connection for Arduino
    setupSerialPort();

    // Connect table selection signal to a slot
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::onRoomSelected);
}

MainWindow::~MainWindow() {
    if (serialPort->isOpen()) {
        serialPort->close();
    }
    delete ui;
}
bool MainWindow::validateInputs() {
    bool ok;
    int num = ui->lineEdit->text().toInt(&ok);
    if (!ok || num <= 0) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid room number.");
        return false;
    }
    // Additional validation for other fields can be added here
    return true;
}

void MainWindow::on_Ajouter_clicked()
{
    if (!validateInputs()) return;

    Chambre chambre(ui->lineEdit->text().toInt(),
                    ui->lineEdit_2->text(),
                    ui->lineEdit_3->text(),
                    ui->lineEdit_4->text(),
                    ui->lineEdit_5->text());

    if (chambre.ajouter()) {
        QMessageBox::information(this, "Succès", "Chambre ajoutée avec succès.");
        ui->tableView->setModel(chambre.afficher());  // Affichage sans tri par défaut
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la chambre.");
    }
}

void MainWindow::on_modifier_clicked()
{
    if (!validateInputs()) return;

    // Create a new Chambre object for modification
    Chambre chambreToUpdate(ui->lineEdit->text().toInt(),
                            ui->lineEdit_2->text(),
                            ui->lineEdit_3->text(),
                            ui->lineEdit_4->text(),
                            ui->lineEdit_5->text());

    if (chambreToUpdate.modifier(chambreToUpdate.getNum())) {
        QMessageBox::information(this, "Succès", "Chambre modifiée avec succès.");
        ui->tableView->setModel(chambre.afficher());  // Refresh the view
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la chambre.");
    }
}

void MainWindow::on_supprimer_clicked() {
    if (!validateInputs()) return;

    int num = ui->lineEdit->text().toInt();
    if (chambre.supprimer(num)) {
        QMessageBox::information(this, "Succès", "Chambre supprimée avec succès.");
        ui->tableView->setModel(chambre.afficher());  // Refresh the view
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la chambre.");
    }
}


// Ajouter un bouton pour trier par ETAGE
void MainWindow::on_trier_etage_clicked()
{
    ui->tableView->setModel(chambre.afficher("etage"));  // Affichage trié par ETAGE
}

// Ajouter un bouton pour trier par TARIF
void MainWindow::on_trier_tarif_clicked()
{
    ui->tableView->setModel(chambre.afficher("tarif"));  // Affichage trié par TARIF
}

void MainWindow::on_rechercherButton_clicked() {
    // Récupérer le numéro de la chambre depuis l'interface utilisateur
    int numRecherche = ui->lineEdit->text().toInt();

    // Créer une instance de la classe Chambre
    Chambre chambre;

    // Appeler la méthode rechercher
    QSqlQueryModel *model = chambre.rechercher(numRecherche);

    if (model != nullptr && model->rowCount() > 0) {
        // Si la chambre a été trouvée, afficher dans le QTableView
        ui->tableView->setModel(model);
        QMessageBox::information(this, "Recherche", "Chambre trouvée avec succès.");
    } else {
        // Si aucune chambre n'a été trouvée
        QMessageBox::warning(this, "Recherche", "Chambre introuvable.");
    }
}

void MainWindow::on_genererPDFButton_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "", tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) {
        return; // L'utilisateur a annulé l'enregistrement
    }

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&writer);

    // Définir la police et la taille
    QFont font("Arial", 12);
    painter.setFont(font);

    // Titre
    painter.drawText(3000, 0, "Liste des Chambres");
    painter.drawLine(100, 110, 500, 110); // Ligne sous le titre

    // Récupérer les données de la base de données
    QSqlQuery query("SELECT * FROM CHAMBRE");
    int y = 130; // Position de départ pour écrire les données
    int margin = 50; // Marges

    while (query.next()) {
        // Récupérer les valeurs
        QString NUM = query.value("NUM").toString();
        QString NETOYAGE = query.value("NETOYAGE").toString();
        QString ETAGE = query.value("ETAGE").toString();
        QString TARIF = query.value("TARIF").toString();
        QString TYPE = query.value("TYPE").toString();

        // Écrire chaque champ sur une nouvelle ligne
        painter.drawText(margin, y, QString("CHAMBRE NUM: %1").arg(NUM));
        y += 290; // Espacement entre les lignes

        painter.drawText(margin, y, QString("NETOYAGE: %1").arg(NETOYAGE));
        y += 290;

        painter.drawText(margin, y, QString("ETAGE: %1").arg(ETAGE));
        y += 290;

        painter.drawText(margin, y, QString("TARIF: %1").arg(TARIF));
        y += 290;

        painter.drawText(margin, y, QString("TYPE: %1").arg(TYPE));
        y += 290; // Espacement supplémentaire avant le prochain article

        painter.drawLine(margin, y, 500, y); // Ligne de séparation entre les chambres
        y += 290; // Espacement après la ligne de séparation

        // Vérifier si on dépasse la hauteur de la page
        if (y > writer.height() - 100) {
            painter.end();
            writer.newPage(); // Créer une nouvelle page si nécessaire
            painter.begin(&writer);
            painter.setFont(font); // Redéfinir la police
            y = 100; // Réinitialiser la position y
        }
    }

    painter.end();

    // Afficher un message de succès
    QMessageBox::information(this, tr("Succès"), tr("Les données ont été exportées vers le PDF avec succès."));
}






bool MainWindow::assignChambreToEmploye(const QString& numChambre, const QString& idEmploye) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Base de données non connectée.");
        return false;
    }

    QSqlQuery query;

    // Récupérer le nombre total d'employés
    query.exec("SELECT COUNT(*) FROM PERSONNEL");
    if (!query.next()) return false;
    int nombreEmployes = query.value(0).toInt();

    // Récupérer le nombre total de chambres
    query.exec("SELECT COUNT(*) FROM CHAMBRE");
    if (!query.next()) return false;
    int nombreChambres = query.value(0).toInt();

    // Calculer le nombre maximum de chambres par employé
    int maxChambresParEmploye = nombreChambres / nombreEmployes;

    // Vérifier combien de chambres cet employé organise déjà
    query.prepare("SELECT COUNT(*) FROM CHAMBRE WHERE ID_P = :idEmploye");
    query.bindValue(":idEmploye", idEmploye);
    query.exec();
    if (!query.next()) return false;
    int chambresAttribuees = query.value(0).toInt();

    if (chambresAttribuees >= maxChambresParEmploye) {
        QMessageBox::warning(this, "Limite atteinte", "Cet employé a atteint sa limite de chambres.");
        return false;
    }

    // Mettre à jour la chambre avec l'ID employé
    query.prepare("UPDATE CHAMBRE SET ID_P = :idEmploye WHERE NUM = :numChambre");
    query.bindValue(":idEmploye", idEmploye);
    query.bindValue(":numChambre", numChambre);
    return query.exec();
}
void MainWindow::on_afficher2_clicked()
{
    ui->tableView_2->setModel(chambre.afficher2());
}


void MainWindow::on_Affecter_clicked()
{
    QString numChambre = ui->lineEdit_numChambre->text();
    QString idEmploye = ui->lineEdit_idEmploye->text();

    if (numChambre.isEmpty() || idEmploye.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir les deux champs.");
        return;
    }

    qDebug() << "Num Chambre: " << numChambre << ", ID Employé: " << idEmploye;

    if (assignChambreToEmploye(numChambre, idEmploye)) {
        QMessageBox::information(this, "Succès", "Chambre attribuée à l'employé avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'attribution de la chambre.");
    }
}


#include <QMessageBox>  // Assurez-vous d'inclure cette ligne en haut de votre fichier

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;

    // Récupérer les valeurs des champs de texte
    int numChambre = ui->lineEdit_8->text().toInt();  // Le numéro de chambre
    int idp = ui->lineEdit_6->text().toInt();         // ID de l'employé
    int qte = ui->lineEdit_7->text().toInt();         // Quantité

    // Récupérer le nombre total d'articles (QTE) depuis la table UTILITEE
    query.prepare("SELECT QTE FROM UTILITEE WHERE ID_PROD = :idp");
    query.bindValue(":idp", idp); // Lier le paramètre idp à la requête
    if (!query.exec()) {
        qDebug() << "Erreur de requête SELECT : " << query.lastError();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération de la quantité.");
        return;
    }

    int QTE = 0; // Initialisation de QTE
    if (query.next()) {
        QTE = query.value(0).toInt();
    }

    // Calculer la nouvelle quantité
    int novqte = QTE - qte;

    // Mise à jour de la table UTILITEE
    query.prepare("UPDATE UTILITEE SET QTE = :novqte WHERE ID_PROD = :idp");
    query.bindValue(":novqte", novqte);
    query.bindValue(":idp", idp);

    // Exécuter la requête de mise à jour
    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour : " << query.lastError();
        QMessageBox::critical(this, "Erreur", "La mise à jour a échoué.");
        return;
    }

    // Si la quantité devient 0, effacer la ligne de la table UTILITEE
    if (novqte == 0) {
        query.prepare("DELETE FROM UTILITEE WHERE ID_PROD = :idp");
        query.bindValue(":idp", idp);
        if (!query.exec()) {
            qDebug() << "Erreur de suppression : " << query.lastError();
            QMessageBox::critical(this, "Erreur", "La suppression a échoué.");
            return;
        } else {
            QMessageBox::information(this, "Mise à jour réussie", "La ligne a été supprimée car la quantité est à zéro.");
        }
    } else {
        // Si la quantité n'est pas égale à zéro, mettre à jour la colonne NETOYAGE à '1' pour la chambre
        query.prepare("UPDATE CHAMBRE SET NETOYAGE = '1' WHERE NUM = :numChambre");
        query.bindValue(":numChambre", numChambre);
        if (!query.exec()) {
            qDebug() << "Erreur de mise à jour de NETOYAGE : " << query.lastError();
            QMessageBox::critical(this, "Erreur", "La mise à jour de NETOYAGE a échoué.");
            return;
        }
    }

    // Affichage de la nouvelle quantité dans un QMessageBox
    QString message = QString("La nouvelle quantité est : %1").arg(novqte);
    QMessageBox::information(this, "Mise à jour réussie", message);

}

void MainWindow::on_afficher2_2_clicked()
{
    ui->tableView_3->setModel(chambre.afficher3());
}


void MainWindow::on_genererPDFButton_2_clicked()
{
    // Créer une instance de Chambre
    Chambre chambre;

    // Appeler la méthode etatParEtage
    QMap<int, QList<QString>> etat = chambre.etatParEtage();

    // Afficher l'état de chaque étage
    foreach (int etage, etat.keys()) {
        QString infoEtage = "Étage " + QString::number(etage) + ":\n";
        foreach (const QString &chambreInfo, etat[etage]) {
            infoEtage += chambreInfo + "\n";
        }
        qDebug() << infoEtage;  // Afficher l'information dans la console, ou utilisez un autre moyen pour afficher dans l'UI
    }
}


void MainWindow::setupSerialPort() {
    serialPort = new QSerialPort(this);

    // Force using COM5
    serialPort->setPortName("COM5");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
        qDebug() << "Arduino connected on port COM5.";
    } else {
        QMessageBox::critical(this, "Connection Error", "Failed to open COM5. Please check your device connection.");
        qDebug() << "Error opening COM5:" << serialPort->errorString();
    }
}

void MainWindow::onRoomSelected(const QModelIndex &index) {
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView->model());
    if (!model) {
        QMessageBox::critical(this, "Error", "Failed to retrieve model from table view.");
        return;
    }

    int row = index.row();
    QString roomNum = model->data(model->index(row, 0)).toString();
    QString nettoyageStatus = model->data(model->index(row, 4)).toString();

    qDebug() << "Room Number:" << roomNum << ", Netoyage Status:" << nettoyageStatus;

    if (nettoyageStatus == "1") { // Room is clean
        sendCommandToArduino("CLEAN\n");       // Turn on red LED and buzzer for 2 seconds
        sendCommandToArduino("ROOM_CLEAN\n"); // Mark room as clean
        QMessageBox::information(this, "Room Status", "Room is clean.");
    } else if (nettoyageStatus == "0") { // Room is not clean
        sendCommandToArduino("ROOM_DIRTY\n"); // Mark room as dirty
        QMessageBox::information(this, "Room Status", "Room " + roomNum + " is not clean.");
    }
}

void MainWindow::sendCommandToArduino(const QString &command) {
    if (serialPort && serialPort->isOpen()) {
        serialPort->write(command.toUtf8());
        qDebug() << "Command sent to Arduino:" << command; // Debugging
    } else {
        QMessageBox::warning(this, "Error", "Serial port is not open.");
        qDebug() << "Serial port not open. Command not sent."; // Debugging
    }
}

void MainWindow::readSerialData() {
    static QByteArray buffer; // Buffer to store incoming data
    buffer.append(serialPort->readAll()); // Append the new data to the buffer

    // Check if we have a complete message (ending with '\n')
    while (buffer.contains('\n')) {
        int newlineIndex = buffer.indexOf('\n');
        QByteArray completeMessage = buffer.left(newlineIndex + 1); // Extract the complete message
        buffer.remove(0, newlineIndex + 1); // Remove the processed part from the buffer

        // Process the complete message
        QString receivedData = QString::fromUtf8(completeMessage).trimmed();
        qDebug() << "Received Complete Data:" << receivedData;

        // Use QRegularExpression to extract the number of passes
        QRegularExpression rx("Number of passes: (\\d+)");
        QRegularExpressionMatch match = rx.match(receivedData);
        if (match.hasMatch()) {
            QString numPassesStr = match.captured(1);
            int numPasses = numPassesStr.toInt();

            qDebug() << "Number of passes:" << numPasses;

            if (numPasses == 3) {
                QModelIndex currentIndex = ui->tableView->currentIndex();
                if (!currentIndex.isValid()) {
                    qDebug() << "No valid row selected.";
                    return;
                }

                QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView->model());
                QString roomNum = model->data(model->index(currentIndex.row(), 0)).toString();

                QSqlQuery query;
                query.prepare("UPDATE CHAMBRE SET NETOYAGE = '1' WHERE NUM = :num");
                query.bindValue(":num", roomNum);
                if (query.exec()) {
                    qDebug() << "Database updated successfully for room:" << roomNum;
                    model->setQuery(model->query().executedQuery()); // Refresh view
                    QMessageBox::information(this, "RFID Event", "Room marked as clean.");
                } else {
                    qDebug() << "Failed to update database: " << query.lastError();
                }
            }
        }
    }
}
