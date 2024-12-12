#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "employe.h"
#include <QSqlQuery>
#include <QFileDialog>
#include <QSqlError>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QGraphicsScene>
#include <QMessageBox>

#include"facture.h"
#include"QMessageBox"
#include <QPdfWriter>
#include <QPainter>
#include<QVBoxLayout>
#include<QDialog>
#include<QCheckBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include <QMessageBox>
#include "utilitee.h"
#include <QDate>  // Inclure QDate pour pouvoir l'utiliser
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include "arduino.h"

#include "client.h"
#include "metier.h"
#include "reservation.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QPageLayout>
#include <QPageSize>
#include <QtSql/QSqlError>   // Pour QSqlError
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include "arduino.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->aff->setModel(e.afficher());
    ui->aff_feed->setModel(e.afficherEmpFeedback());
    afficherStatistiques();


    //facture

    ui->priceTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->priceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->priceTableView->viewport()->update();

    ui->tableView->setModel(f.afficher());
    ui->comboboxSort->addItem("trier par");    // Sort by name
    ui->comboboxSort->addItem("ref");    // Sort by name
    ui->comboboxSort->addItem("date");
    ui->comboboxSort->addItem("prix");




    connect(ui->tableView_2, &QTableView::clicked, this, &MainWindow::onRoomSelected);


    //utilitee
    ui->comboBox->addItem("Trier par");
    ui->comboBox->addItem("ID_PROD");
    ui->comboBox->addItem("PRIX_PROD");
    ui->comboBox->addItem("QTE");
    ui->tableView_5->setModel(util.afficher());


    //client
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    ui->tableView_6->setModel(client.afficher());

    // Afficher les réservations existantes
    Reservation reservation;
    ui->reservationTableView->setModel(reservation.afficher());
    ui->FEEDTableView->setModel(reservation.afficher1());
    //QSqlQueryModel* model = ; // Fetch the model from the database
    //proxyModel->setSourceModel(model); // Set the source model for the proxy
    ui->tableView_6->setModel(client.afficher()); // Attach the proxy model to the table view

        // Connect the lineEdit for dynamic searching
   // connect(ui->lineEditRecherche, &QLineEdit::textChanged, this, [this](const QString &text) {
   // proxyModel->setFilterKeyColumn(-1); // Enable search across all columns
   // proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption)); // Use case-insensitive search
//});



    //interface
    ui->interface_login->show();

    ui->menu->hide();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString role = ui->role->currentText();
    double salaire = ui->salaire->text().toDouble();

    if (nom.isEmpty() || prenom.isEmpty() || role.isEmpty() || salaire <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement !");
        return;
    }

    Employe e(0, nom, prenom, role, salaire);
    if (e.ajouter()) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès !");
        ui->aff->setModel(e.afficher());
        afficherStatistiques();

    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout de l'employé !");
    }}


void MainWindow::on_modifier_clicked()
{
    int id = ui->id_m->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString role = ui->role->currentText();
    double salaire = ui->salaire->text().toDouble();

    if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || role.isEmpty() || salaire <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement !");
        return;
    }

    Employe e(id, nom, prenom, role, salaire);
    if (e.modifier()) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès !");
        ui->aff->setModel(e.afficher());
        afficherStatistiques();

    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification de l'employé !");
    }}


void MainWindow::on_recuperer_clicked() {
    int id = ui->id_m->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
        return;
    }

    Employe e;
    if (!e.verifierId(id)) {
        QMessageBox::warning(this, "Erreur", "Aucun employé trouvé avec cet ID !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT nom, prenom, role, salaire FROM employe WHERE id_e = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        ui->nom->setText(query.value(0).toString());
        ui->prenom->setText(query.value(1).toString());
        ui->role->setCurrentText(query.value(2).toString());
        ui->salaire->setText(query.value(3).toString());
        QMessageBox::information(this, "Succès", "Données récupérées avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données !");
    }
}


void MainWindow::on_supprimer_clicked() {
    int id = ui->id_supp->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
        return;
    }

    Employe e;
    if (!e.verifierId(id)) {
        QMessageBox::warning(this, "Erreur", "Aucun employé trouvé avec cet ID !");
        return;
    }

    if (e.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès !");
        ui->aff->setModel(e.afficher());
        afficherStatistiques();

    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'employé !");
    }
}


void MainWindow::on_annuler_clicked() {
    ui->nom->clear();
    ui->prenom->clear();
    ui->salaire->clear();
    ui->role->setCurrentIndex(0);
    ui->id_m->clear();
    ui->id_supp->clear();

    QMessageBox::information(this, "Réinitialisé", "Tous les champs ont été vidés !");
}



void MainWindow::on_ajouter_f_clicked() {
    int id_employe = ui->id_em->text().toInt();
    QString feedback = ui->feedback->currentText(); // Assurez-vous que la ComboBox contient '+' et '-'

    if (id_employe <= 0 || (feedback != "+" && feedback != "-")) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir correctement les champs !");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO feedback (id_f, id_employe, feedback) "
                  "VALUES (seq_feedback.NEXTVAL, :id_employe, :feedback)");
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":feedback", feedback);

    if (query.exec()) {
        // Mise à jour des points dans `emp_f`
        int points_change = (feedback == "+") ? 10 : -10;

        QSqlQuery updateQuery;
        updateQuery.prepare("MERGE INTO emp_f USING DUAL "
                            "ON (id_employe = :id_employe) "
                            "WHEN MATCHED THEN "
                            "    UPDATE SET points = points + :points "
                            "WHEN NOT MATCHED THEN "
                            "    INSERT (id_employe, feedback, points) VALUES (:id_employe, :feedback, :points)");
        updateQuery.bindValue(":id_employe", id_employe);
        updateQuery.bindValue(":feedback", feedback);
        updateQuery.bindValue(":points", points_change);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Succès", "Feedback ajouté avec succès !");
            ui->aff_feed->setModel(e.afficherEmpFeedback());

        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la mise à jour des points !");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout du feedback !");
    }
}



void MainWindow::on_trie_clicked()
{
    QString critere = ui->tri->currentText();

    if (critere != "role" && critere != "salaire") {
        QMessageBox::warning(this, "Erreur", "Critère de tri invalide. Choisissez 'role' ou 'salaire'.");
        return;
    }

    QSqlQueryModel *model = e.trier(critere);
    ui->aff->setModel(model);
}


void MainWindow::on_rechercher_clicked()
{
    QString critere = ui->rech->currentText();
    QString valeur = ui->valeur->text();


    QSqlQueryModel *model = e.rechercher(critere, valeur);
    ui->aff->setModel(model);
}


void MainWindow::on_pdf_clicked()
{
    // Ouvrir une boîte de dialogue pour choisir l'emplacement du fichier PDF
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";  // Ajouter l'extension si elle n'est pas fournie
        }



        // Générer le PDF à l'emplacement choisi
        e.genererPDF(fichierPDF);

        // Informer l'utilisateur que le PDF a été généré avec succès
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        // Si l'utilisateur annule l'opération
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}


void MainWindow::afficherStatistiques() {

    // Récupérer la série de statistiques (pie chart)
    QPieSeries* series = e.statistiques();

    // Créer un objet QChart pour afficher le graphique
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employes par role");

    // Créer un QChartView pour intégrer le QChart
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Améliorer le rendu

    // Créer une QGraphicsScene et ajouter le QChartView
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addWidget(chartView);

    // Ajouter la scène dans le QGraphicsView (stat_e)
    ui->aff_stat->setScene(scene);

    // Redimensionner la scène pour s'adapter au QGraphicsView
    chartView->resize(ui->aff_stat->size());  // Ajuste la taille du chartView à celle de stat_e
}



void MainWindow::on_actualiser_clicked()
{
        Employe e; // Créez une instance de la classe Employe
        e.afficherRappelPoints(40); // Appelez la fonction avec un seuil de 40 points
    }


void MainWindow::on_pushButton_clicked()
{

    int ref=ui->lineEdit_5->text().toInt();
    QString nom =ui->lineEdit_4->text();
    QString mode=ui->lineEdit_3->text();
    double prix=ui->doubleSpinBox->value();
    QDate date=ui->dateEdit->date();
     f.fset( ref,mode,nom,date,prix);
    if(f.ajout()){

           QMessageBox::information(nullptr, "Ajout", "Ajout avec succès");
        ui->tableView->setModel(f.afficher());
     }
    else{
        QMessageBox::warning(nullptr, "erreur", "Ajout failed");
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int ref= ui->lineEdit_5->text().toInt();

    if (f.supprimer(ref)) {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Suppression avec succès"), QMessageBox::Ok);
        ui->tableView->setModel(f.afficher()); // Refresh the table view
    } else {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Suppression échou"), QMessageBox::Ok);
    }
}


void MainWindow::on_modifierButton_clicked()
{
    // Supposons que vous ayez un champ pour saisir la référence, le mode, le nom, et la date
    int ref = ui->lineEdit_5->text().toInt();
    QString mode = ui->lineEdit_3->text();
    QString nom = ui->lineEdit_4->text();
    double prix=ui->doubleSpinBox->value();
    QDate date = ui->dateEdit->date();

    // Créer une instance de facture et définir les nouveaux détails
    facture f;
    f.fset(ref, mode, nom, date,prix);

    // Appeler la fonction modifier
    if(f.modifier(ref)) {
        ui->tableView->setModel(f.afficher());
        QMessageBox::information(this, "Succès", "Facture modifiée avec succès");
    } else {
        QMessageBox::critical(this, "Erreur", "La modification a échoué");
    }
}

void MainWindow::updatePriceTab(int numRev, double prixFac) {
    // Requête SQL pour récupérer les prix des extras sélectionnés
    QSqlQuery query;
    query.prepare("SELECT EXTRA_NAME, PRICE FROM EXTRAS WHERE NUM_REV = :num_rev AND SELECTED = 1");
    query.bindValue(":num_rev", numRev);
    query.exec();

    double totalPrice = prixFac;  // Commencer avec le prix de la facture

    // Créer un modèle pour afficher les extras
    QStandardItemModel *totalModel = new QStandardItemModel();
    totalModel->setHorizontalHeaderLabels({"Extra", "Prix"});

    // Ajouter les lignes pour chaque extra sélectionné
    while (query.next()) {
        QString extraName = query.value(0).toString();
        double extraPrice = query.value(1).toDouble();

        // Ajouter chaque extra dans le modèle
        QStandardItem *extraNameItem = new QStandardItem(extraName);
        QStandardItem *extraPriceItem = new QStandardItem(QString::number(extraPrice));
        totalModel->appendRow({extraNameItem, extraPriceItem});

        // Ajouter le prix de l'extra au total
        totalPrice += extraPrice;
    }

    // Ajouter une ligne pour le total
    QStandardItem *totalItem = new QStandardItem("Total");
    QStandardItem *totalPriceItem = new QStandardItem(QString::number(totalPrice));
    totalModel->appendRow({totalItem, totalPriceItem});

    // Mettre à jour la vue avec le modèle qui contient les extras et le prix total
    ui->priceTableView->setModel(totalModel);

    // Mise à jour du PRIX_FAC dans la base de données avec le prix total
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE FACTURE SET PRIX_FAC = :totalPrice WHERE NUM_REV = :num_rev");
    updateQuery.bindValue(":totalPrice", totalPrice);  // Le total calculé
    updateQuery.bindValue(":num_rev", numRev);

    if (!updateQuery.exec()) {
        qDebug() << "Erreur lors de la mise à jour du prix dans la base de données : " << updateQuery.lastError().text();
    } else {
        qDebug() << "Prix total mis à jour dans la base de données pour NUM_REV =" << numRev << ": " << totalPrice;
    }
}

void MainWindow::recalculerPrixTotal(int numRev, double extraPrice)
{
    // Récupérer les prix de tous les NUM_REV dans la table FACTURE
    QSqlQuery query;
    query.prepare("SELECT NUM_REV, PRIX_FAC FROM FACTURE");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des factures : " << query.lastError().text();
        return;
    }

    while (query.next()) {
        int currentNumRev = query.value(0).toInt();  // Récupérer NUM_REV
        double prixFac = query.value(1).toDouble();  // Prix de la facture principale

        double totalPrix = prixFac;  // Commencer avec le prix de la facture principale

        // Soustraire le prix de l'extra réclamé pour le NUM_REV actuel
        if (currentNumRev == numRev) {
            totalPrix -= extraPrice;
        }

        // Récupérer les prix des extras non réclamés (RECLAME = 0) et sélectionnés pour ce NUM_REV
        query.prepare("SELECT PRICE FROM EXTRAS WHERE NUM_REV = :num_rev AND RECLAME = 0 AND SELECTED = 1");
        query.bindValue(":num_rev", currentNumRev);

        if (query.exec()) {
            while (query.next()) {
                totalPrix -= query.value(0).toDouble();  // Ajouter les prix des extras non réclamés
            }
        } else {
            qDebug() << "Erreur lors de la récupération des extras non réclamés : " << query.lastError().text();
        }

        // Mettre à jour le prix total dans la base de données pour ce NUM_REV
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE FACTURE SET PRIX_FAC = :totalPrix WHERE NUM_REV = :num_rev");
        updateQuery.bindValue(":totalPrix", totalPrix);
        updateQuery.bindValue(":num_rev", currentNumRev);

        if (!updateQuery.exec()) {
            qDebug() << "Erreur lors de la mise à jour du prix total : " << updateQuery.lastError().text();
            return;
        }

        // Mettre à jour le modèle dans priceTableView pour chaque NUM_REV
        QAbstractItemModel *model = ui->priceTableView->model();

        // Rechercher la ligne correspondant à chaque NUM_REV
        for (int row = 0; row < model->rowCount(); ++row) {
            QModelIndex index = model->index(row, 0);  // Colonne 0 : NUM_REV

            // Vérifier si cette ligne correspond à currentNumRev
            if (index.data().toInt() == currentNumRev) {
                // Mettre à jour la colonne qui contient le prix total (supposons que c'est la colonne 2)
                QModelIndex priceIndex = model->index(row, 2);  // Supposons que la colonne PRIX_FAC (total) est la colonne 2
                model->setData(priceIndex, totalPrix, Qt::EditRole);  // Mettre à jour la cellule avec le nouveau prix

                // Forcer la mise à jour visuelle
                ui->priceTableView->viewport()->update();  // Mettre à jour la vue
                qDebug() << "Prix total mis à jour pour NUM_REV" << currentNumRev << ": " << totalPrix;
                break;  // Sortir de la boucle après la mise à jour
            }
        }
    }
}

void MainWindow::afficherStatistiquesPaiements() {
    // Création de l'objet facture pour récupérer les statistiques
    facture f;

    // Récupérer les statistiques à partir de la classe facture
    QMap<QString, int> stats = f.statistiquesPaiements();

    // Création d'une série de type camembert (pie chart)
    QPieSeries *series = new QPieSeries();

    // Ajouter les statistiques au graphique
    series->append("Chèque", stats["cheque"]);
    series->append("Espèces", stats["espece"]);

    // Rendre les parts cliquables et visibles
    QPieSlice *chequeSlice = series->slices().at(0);
    chequeSlice->setLabelVisible();
    chequeSlice->setExploded();

    QPieSlice *especeSlice = series->slices().at(1);
    especeSlice->setLabelVisible();

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des paiements");

    // Création de la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Lisser le rendu graphique

    // Création d'une nouvelle boîte de dialogue pour afficher le graphique
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques des Paiements");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);

    dialog->setLayout(layout);
    dialog->resize(400, 300);  // Taille de la fenêtre du graphique
    dialog->exec();  // Afficher la fenêtre
}
void MainWindow::on_pushButton_generatePDF_clicked()
{
    // Access the tableView directly from the UI
    QTableView *tableView = ui->tableView;

    QString fileName = QFileDialog::getSaveFileName(this, "Save as PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);

    QAbstractItemModel *model = tableView->model();

    int x = 10;   // Starting x position
    int y = 30;   // Starting y position
    int rowHeight = 100;
    int columnWidth = 250;

    // Set up font for the PDF
    QFont font = painter.font();
    font.setPointSize(5);
    painter.setFont(font);

    // Draw column headers
    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString());
        painter.drawRect(rect);
    }

    // Draw rows
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + (row + 1) * rowHeight, columnWidth, rowHeight);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, column)).toString());
            painter.drawRect(rect);
        }
    }

    painter.end();
    QMessageBox::information(this, "Export Complete", "Data has been exported to PDF successfully.");
}

void MainWindow::on_pushButton_search_clicked()
{
    QString searchTerm = ui->lineEdit_search->text();  // Get the search term from the QLineEdit

    // Call the search method of the 'facture' class
    QSqlQueryModel *model = f.rechercher(searchTerm);

    if (model) {
        // Set the model to the table view to display the results
        ui->tableView->setModel(model);
    } else {
        QMessageBox::warning(this, "Search Error", "No results found or an error occurred during the search.");
    }
}

void MainWindow::on_comboboxSort_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;

    if (index == 1) {  // Trier par référence (ref)
        query = "SELECT * FROM Facture ORDER BY REF_FACTURE ASC";
    } else if (index == 2) {  // Trier par date
        query = "SELECT * FROM Facture ORDER BY DATE_FAC ASC";
    } else if (index == 3) {  // Trier par prix
        query = "SELECT * FROM Facture ORDER BY PRIX_FAC ASC";  // Assurez-vous que "PRIX" est le bon nom de colonne
    }

    model->setQuery(query);
    ui->tableView->setModel(model);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int numRev = index.sibling(index.row(), 0).data().toInt();  // NUM_REV
    double prixFac = index.sibling(index.row(), 1).data().toDouble();  // PRIX_FAC

    // Créer un dialogue pour la sélection des extras
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Sélectionner les extras pour NUM_REV : " + QString::number(numRev));

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Créer des cases à cocher pour les extras
    QCheckBox *plongee = new QCheckBox("Plongée", dialog);
    QCheckBox *quad = new QCheckBox("Quad", dialog);
    QCheckBox *sortie = new QCheckBox("Sortie", dialog);

    layout->addWidget(plongee);
    layout->addWidget(quad);
    layout->addWidget(sortie);

    // Créer un bouton "Sauvegarder"
    QPushButton *saveButton = new QPushButton("Sauvegarder", dialog);
    layout->addWidget(saveButton);

    dialog->setLayout(layout);

    // Charger les extras précédemment sauvegardés pour ce NUM_REV
    QSqlQuery query;
    query.prepare("SELECT EXTRA_NAME, SELECTED FROM EXTRAS WHERE NUM_REV = :num_rev");
    query.bindValue(":num_rev", numRev);
    query.exec();

    // Mettre à jour les cases à cocher en fonction des extras sauvegardés
    while (query.next()) {
        QString extraName = query.value(0).toString();
        int selected = query.value(1).toInt();

        if (extraName == "plongée") {
            plongee->setChecked(selected == 1);
        } else if (extraName == "quad") {
            quad->setChecked(selected == 1);
        } else if (extraName == "sortie") {
            sortie->setChecked(selected == 1);
        }
    }

    // Connecter le bouton "Sauvegarder"
        connect(saveButton, &QPushButton::clicked, [=]() {
        bool plongeeChecked = plongee->isChecked();
        bool quadChecked = quad->isChecked();
        bool sortieChecked = sortie->isChecked();

        // Sauvegarder les extras dans la base de données pour ce NUM_REV
        QSqlQuery saveQuery;

        // Exemple de prix fixes pour chaque extra
        double prixPlongee = 30.0;  // Exemple de prix pour Plongée
        double prixQuad = 50.0;     // Exemple de prix pour Quad
        double prixSortie = 40.0;   // Exemple de prix pour Sortie

        // Sauvegarder Plongée
        saveQuery.prepare("MERGE INTO EXTRAS e USING (SELECT :num_rev AS NUM_REV, 'plongée' AS EXTRA_NAME FROM dual) d "
                          "ON (e.NUM_REV = d.NUM_REV AND e.EXTRA_NAME = d.EXTRA_NAME) "
                          "WHEN MATCHED THEN UPDATE SET e.SELECTED = :selected, e.PRICE = :price "
                          "WHEN NOT MATCHED THEN INSERT (NUM_REV, EXTRA_NAME, SELECTED, PRICE) VALUES (:num_rev, 'plongée', :selected, :price)");
        saveQuery.bindValue(":num_rev", numRev);
        saveQuery.bindValue(":selected", plongeeChecked ? 1 : 0);
        saveQuery.bindValue(":price", plongeeChecked ? prixPlongee : 0.0);
        saveQuery.exec();

        // Sauvegarder Quad
        saveQuery.prepare("MERGE INTO EXTRAS e USING (SELECT :num_rev AS NUM_REV, 'quad' AS EXTRA_NAME FROM dual) d "
                          "ON (e.NUM_REV = d.NUM_REV AND e.EXTRA_NAME = d.EXTRA_NAME) "
                          "WHEN MATCHED THEN UPDATE SET e.SELECTED = :selected, e.PRICE = :price "
                          "WHEN NOT MATCHED THEN INSERT (NUM_REV, EXTRA_NAME, SELECTED, PRICE) VALUES (:num_rev, 'quad', :selected, :price)");
        saveQuery.bindValue(":num_rev", numRev);
        saveQuery.bindValue(":selected", quadChecked ? 1 : 0);
        saveQuery.bindValue(":price", quadChecked ? prixQuad : 0.0);
        saveQuery.exec();

        // Sauvegarder Sortie
        saveQuery.prepare("MERGE INTO EXTRAS e USING (SELECT :num_rev AS NUM_REV, 'sortie' AS EXTRA_NAME FROM dual) d "
                          "ON (e.NUM_REV = d.NUM_REV AND e.EXTRA_NAME = d.EXTRA_NAME) "
                          "WHEN MATCHED THEN UPDATE SET e.SELECTED = :selected, e.PRICE = :price "
                          "WHEN NOT MATCHED THEN INSERT (NUM_REV, EXTRA_NAME, SELECTED, PRICE) VALUES (:num_rev, 'sortie', :selected, :price)");
        saveQuery.bindValue(":num_rev", numRev);
        saveQuery.bindValue(":selected", sortieChecked ? 1 : 0);
        saveQuery.bindValue(":price", sortieChecked ? prixSortie : 0.0);
        saveQuery.exec();

        // Mettre à jour tableView3 pour afficher les extras sélectionnés avec prix
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT EXTRA_NAME, SELECTED, PRICE FROM EXTRAS WHERE NUM_REV = " + QString::number(numRev));
        ui->tableView3->setModel(model);

        // Mettre à jour le total des prix dans un nouveau tabView
        updatePriceTab(numRev, prixFac);

        dialog->accept();
    });

    // Exécuter le dialogue
    dialog->exec();
}


void MainWindow::on_pushButton_afficher_clicked()
{
    // Appeler la méthode afficher2() pour obtenir le modèle de données
    QSqlQueryModel* model = f.afficher2();

    // Utilisez ui->tableView2 si tableView2 est défini dans le fichier .ui
    ui->tableView2->setModel(model);
}

void MainWindow::on_reclamationButton_clicked()
{
    // Vérifier si une ligne est sélectionnée dans `priceTableView`
    QModelIndexList selectedRows = ui->priceTableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un extra à réclamer.");
        return;
    }

    // Récupérer les informations de la ligne sélectionnée
    int numRev = selectedRows.first().siblingAtColumn(0).data().toInt();  // Récupérer le NUM_REV de la colonne 0
    QString extraName = selectedRows.first().siblingAtColumn(1).data().toString();  // Nom de l'extra (colonne 1)

    // Vérifier si le nom de l'extra est vide
    if (extraName.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom de l'extra sélectionné est vide. Veuillez sélectionner une ligne valide.");
        return;
    }

    // Récupérer le prix de l'extra réclamé
    double extraPrice = selectedRows.first().siblingAtColumn(2).data().toDouble();  // Supposons que la colonne 2 contient le prix

    // Marquer l'extra comme "réclamé" en mettant à jour la colonne RECLAME à 1
    QSqlQuery query;
    query.prepare("UPDATE EXTRAS SET RECLAME = 1 WHERE NUM_REV = :num_rev AND EXTRA_NAME = :extra_name");
    query.bindValue(":num_rev", numRev);
    query.bindValue(":extra_name", extraName);

    // Exécuter la requête pour marquer l'extra comme réclamé
    if (query.exec()) {
        QMessageBox::information(this, "Réclamation", "La réclamation a été enregistrée.");
        // Recalculer le prix total après la réclamation en passant le prix de l'extra réclamé
        recalculerPrixTotal(numRev, extraPrice);
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'enregistrement de la réclamation.");
        qDebug() << "Erreur de réclamation : " << query.lastError();
    }
}

void MainWindow::on_statButton_clicked()
{
    // Création de l'objet facture pour récupérer les statistiques
    facture f;

    // Récupérer les statistiques à partir de la classe facture
    QMap<QString, int> stats = f.statistiquesPaiements();

    // Création d'une série de type camembert (pie chart)
    QPieSeries *series = new QPieSeries();

    // Ajouter les statistiques au graphique
    series->append("Chèque", stats["cheque"]);
    series->append("Espèces", stats["espece"]);

    // Rendre les parts cliquables et visibles
    QPieSlice *chequeSlice = series->slices().at(0);
    chequeSlice->setLabelVisible();
    chequeSlice->setExploded();

    QPieSlice *especeSlice = series->slices().at(1);
    especeSlice->setLabelVisible();

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des paiements");

    // Création de la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Lisser le rendu graphique

    // Création d'une nouvelle boîte de dialogue pour afficher le graphique
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques des Paiements");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);

    dialog->setLayout(layout);
    dialog->resize(400, 300);  // Taille de la fenêtre du graphique
    dialog->exec();  // Afficher la fenêtre
}



//

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
                    ui->lineEdit_6->text(),
                    ui->lineEdit_7->text(),
                    ui->lineEdit_8->text());

    if (chambre.ajouter()) {
        QMessageBox::information(this, "Succès", "Chambre ajoutée avec succès.");
        ui->tableView_2->setModel(chambre.afficher());  // Affichage sans tri par défaut
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la chambre.");
    }
}

void MainWindow::on_modifier_2_clicked()
{
    if (!validateInputs()) return;

    // Create a new Chambre object for modification
    Chambre chambreToUpdate(ui->lineEdit->text().toInt(),
                            ui->lineEdit_2->text(),
                            ui->lineEdit_6->text(),
                            ui->lineEdit_7->text(),
                            ui->lineEdit_8->text());

    if (chambreToUpdate.modifier(chambreToUpdate.getNum())) {
        QMessageBox::information(this, "Succès", "Chambre modifiée avec succès.");
        ui->tableView_2->setModel(chambre.afficher());  // Refresh the view
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la chambre.");
    }
}

void MainWindow::on_supprimer_2_clicked()
{
    if (!validateInputs()) return;

    int num = ui->lineEdit->text().toInt();
    if (chambre.supprimer(num)) {
        QMessageBox::information(this, "Succès", "Chambre supprimée avec succès.");
        ui->tableView_2->setModel(chambre.afficher());  // Refresh the view
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la chambre.");
    }
}

void MainWindow::on_trier_tarif_clicked()
{
    ui->tableView_2->setModel(chambre.afficher("tarif"));  // Affichage trié par TARIF

}

void MainWindow::on_rechercherButton_clicked()
{
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

void MainWindow::on_genererPDFButton_clicked()
{
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

   /* if (nettoyageStatus == "1") { // Room is clean
        sendCommandToArduino("CLEAN\n");       // Turn on red LED and buzzer for 2 seconds
        sendCommandToArduino("ROOM_CLEAN\n"); // Mark room as clean
        QMessageBox::information(this, "Room Status", "Room is clean.");
    } else if (nettoyageStatus == "0") { // Room is not clean
        sendCommandToArduino("ROOM_DIRTY\n"); // Mark room as dirty
        QMessageBox::information(this, "Room Status", "Room " + roomNum + " is not clean.");
    }*/
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

void MainWindow::on_afficher2_clicked()
{
    ui->tableView_3->setModel(chambre.afficher2());

}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;

    // Récupérer les valeurs des champs de texte
    int numChambre = ui->lineEdit_11->text().toInt();  // Le numéro de chambre
    int idp = ui->lineEdit_9->text().toInt();         // ID de l'employé
    int qte = ui->lineEdit_10->text().toInt();         // Quantité

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

void MainWindow::on_addButton_clicked()
{
    // Récupérer les données depuis l'interface
    int idProd = ui->lineEdit_idProd->text().toInt();
    double prixProd = ui->lineEdit_prixProd->text().toDouble();
    int qte = ui->lineEdit_qte->text().toInt();
    QString type = ui->comboBox_2->currentText(); // Récupère le type sélectionné

    // Créer un objet Utilitee avec les données récupérées
    Utilitee util(idProd, prixProd, qte, type);

    // Ajouter l'élément dans la base de données
    if (util.ajouter()) {
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès.");
        ui->tableView_5->setModel(util.afficher());
        QString msg = "on a ajouter: ";
        util.enregistrerAnnulationDansFichier(idProd, prixProd, qte, type, msg);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du produit.");
    }
}

void MainWindow::on_updateButton_clicked()
{
    // Récupérer les données depuis l'interface
    int idProd = ui->lineEdit_idProd->text().toInt();
    double prixProd = ui->lineEdit_prixProd->text().toDouble();
    int qte = ui->lineEdit_qte->text().toInt();
    QString type = ui->comboBox_2->currentText(); // Récupère le type sélectionné dans la liste déroulante

    // Créer un objet Utilitee avec les nouvelles valeurs
    Utilitee util(idProd, prixProd, qte, type);

    // Modifier l'élément dans la base de données
    if (util.modifier(idProd)) {
        QMessageBox::information(this, "Succès", "Produit modifié avec succès.");
        ui->tableView_5->setModel(util.afficher());
        QString msg = "on a modifié : ";
        util.enregistrerAnnulationDansFichier(idProd, prixProd, qte, type, msg);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du produit.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int idProd = ui->lineEdit_idProd->text().toInt();
     QSqlQuery query;
     query.prepare("select PRIX_PROD ,QTE,TYPE FROM UTILITEE WHERE ID_PROD=:idprod");
     query.bindValue(":idProd", idProd);
     double prix=query.value(0).toDouble();
     int qte=query.value(1).toInt();
     QString TYPE=query.value(2).toString();
     QString msg="on a supprimer:  ";
    // Supprimer l'élément de la base de données
    Utilitee util;
    if (util.supprimer(idProd)) {
        QMessageBox::information(this, "Succès", "Produit supprimé avec succès.");
        ui->tableView_5->setModel(util.afficher());
        util.enregistrerAnnulationDansFichier(idProd,  prix,qte, TYPE,msg);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression du produit.");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
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
    painter.drawText(3000, 0, "Liste des UTILITEE");
    painter.drawLine(100, 110, 500, 110); // Ligne sous le titre

    // Récupérer les données de la base de données
    QSqlQuery query("SELECT * FROM UTILITEE");
    int y = 130; // Position de départ pour écrire les données
    int margin = 50; // Marges

    while (query.next()) {
        // Récupérer les valeurs
        int NUM = query.value("ID_PROD").toInt();
        int NETOYAGE = query.value("PRIX_PROD").toInt();
        int ETAGE = query.value("QTE").toInt();
        QString TARIF = query.value("TYPE").toString();

        // Écrire chaque champ sur une nouvelle ligne
        painter.drawText(margin, y, QString("UTILITEE ID_PROD: %1").arg(NUM));
        y += 290; // Espacement entre les lignes

        painter.drawText(margin, y, QString("PRIX_PROD: %1").arg(NETOYAGE));
        y += 290;

        painter.drawText(margin, y, QString("QTE: %1").arg(ETAGE));
        y += 290;

        painter.drawText(margin, y, QString("TYPE: %1").arg(TARIF));
        y += 290;
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

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query;

    if (index == 1) {  // Trier par nom du service
             query = "SELECT "
                        "ID_PROD, "
                        "PRIX_PROD, "
                        "QTE, "
                        "TYPE "
                        "FROM UTILITEE "
                        "ORDER BY ID_PROD ASC";

    } else if (index == 2) {  // Trier par prix du service
             query = "SELECT "
                        "ID_PROD, "
                        "PRIX_PROD, "
                        "QTE, "
                        "TYPE "
                        "FROM UTILITEE "
                        "ORDER BY PRIX_PROD DESC";
    }
    else if (index == 3) {  // Trier par prix du service
             query = "SELECT "
                        "ID_PROD, "
                        "PRIX_PROD, "
                        "QTE, "
                        "TYPE "
                        "FROM UTILITEE "
                        "ORDER BY QTE DESC";
       }
    model->setQuery(query);
    ui->tableView_5->setModel(model);
}

void MainWindow::on_rechercheLineEdit_textChanged(const QString &input)
{
    // Préparez la requête pour rechercher les produits par référence ou nom.
    QSqlQueryModel *model = new QSqlQueryModel();  // Utilisation d'un pointeur pour le modèle
    QSqlQuery query;
    query.prepare("SELECT * FROM UTILITEE WHERE ID_PROD LIKE :input OR TYPE LIKE :input");
    query.bindValue(":input", "%" + input + "%");

    if (query.exec()) {
        model->setQuery(query);
        ui->tableView_5->setModel(model);
    } else {
        qDebug() << "Exécution de la requête échouée:" << query.lastError().text();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    // Créer un objet Utilitee pour obtenir les statistiques
    Utilitee util;

    // Récupérer les statistiques par type
    QSqlQueryModel* model = util.statistiquesParType();

    // Afficher les résultats dans une table
    ui->tableView_5->setModel(model);

}

void MainWindow::on_pushButton_6_clicked()
{
    // Obtenir les lignes sélectionnées dans le tableau
    QModelIndexList selectedIndexes = ui->tableView_5->selectionModel()->selectedRows();

    if (selectedIndexes.isEmpty()) {
        // Afficher un message si aucune ligne n'est sélectionnée
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une ligne à modifier.");
        return;
    }

    // Récupérer l'ID du produit depuis la première ligne sélectionnée
    QString id = selectedIndexes.first().data().toString();

    // Créer un objet Utilitee pour récupérer les détails depuis la base de données
    Utilitee util;
    QSqlQuery query;
    query.prepare("SELECT ID_PROD, PRIX_PROD, QTE, TYPE FROM UTILITEE WHERE ID_PROD = :idProd");
    query.bindValue(":idProd", id.toInt());

    if (query.exec() && query.next()) {
        // Récupérer les valeurs de la requête
        int idProd = query.value(0).toInt();
        double prixProd = query.value(1).toDouble();
        int qte = query.value(2).toInt();
        QString type = query.value(3).toString();

        // Remplir les champs de l'interface utilisateur avec les données récupérées
        ui->lineEdit_idProd->setText(QString::number(idProd));
        ui->lineEdit_prixProd->setText(QString::number(prixProd, 'f', 2));
        ui->lineEdit_qte->setText(QString::number(qte));
        ui->comboBox_2->setCurrentText(type); // Affecter le type au QComboBox

        // Enregistrer l'annulation dans un fichier
        QString msg="on supprimer: ";
        util.enregistrerAnnulationDansFichier(idProd, prixProd, qte, type,msg);
        QMessageBox::information(this, "Succès", "L'annulation a été enregistrée avec succès.");
    } else {
        // Afficher un message en cas d'erreur ou si l'ID n'existe pas
        QMessageBox::warning(this, "Erreur", "Aucun produit trouvé pour cet ID.");
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    // Début de la fonction pour la gestion des quantités dans la table UTILITEE
    QSqlQuery query;

    // Récupérer les valeurs des champs de texte
    int numChambre = ui->lineEdit_17->text().toInt();  // Le numéro de chambre
    int idp = ui->lineEdit_22->text().toInt();         // ID du produit
    int qteDemandee = ui->lineEdit_23->text().toInt();  // Quantité demandée

    // Récupérer la quantité actuelle en stock dans la table UTILITEE
    query.prepare("SELECT QTE FROM UTILITEE WHERE ID_PROD = :idp");
    query.bindValue(":idp", idp); // Lier le paramètre idp à la requête
    if (!query.exec()) {
        qDebug() << "Erreur de requête SELECT : " << query.lastError();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération de la quantité.");
        return;
    }

    int qteEnStock = 0; // Initialisation de qteEnStock
    if (query.next()) {
        qteEnStock = query.value(0).toInt();
    }

    // Vérifier si la quantité demandée dépasse la quantité en stock
    if (qteDemandee > qteEnStock) {
        // Afficher un message d'erreur si le stock est insuffisant
        QMessageBox::critical(this, "Stock insuffisant", "La quantité demandée dépasse le stock disponible.");
        return; // Ne pas continuer si la condition est vraie
    }

    // Calculer la nouvelle quantité après la demande
    int novQte = qteEnStock - qteDemandee;

    // Mise à jour de la table UTILITEE avec la nouvelle quantité
    query.prepare("UPDATE UTILITEE SET QTE = :novQte WHERE ID_PROD = :idp");
    query.bindValue(":novQte", novQte);
    query.bindValue(":idp", idp);

    // Exécuter la requête de mise à jour
    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour : " << query.lastError();
        QMessageBox::critical(this, "Erreur", "La mise à jour a échoué.");
        QString msg="on a modifier: ";
        double test=1.0;
       util.enregistrerAnnulationDansFichier(idp,  test,novQte, "type",msg);
        return;
    }

    // Ajouter l'action à l'historique
    QString actionDetails = QString("Quantité mise à jour pour le produit ID %1. Ancienne quantité : %2, Nouvelle quantité : %3")
                                .arg(idp).arg(qteEnStock).arg(novQte); // Appel de la fonction historique de Utilitee

    // Si la quantité devient 0, effacer la ligne de la table UTILITEE
    if (novQte == 0) {
        query.prepare("DELETE FROM UTILITEE WHERE ID_PROD = :idp");
        query.bindValue(":idp", idp);
        if (!query.exec()) {
            qDebug() << "Erreur de suppression : " << query.lastError();
            QMessageBox::critical(this, "Erreur", "La suppression a échoué.");
            return;
        } else {
            QMessageBox::information(this, "Mise à jour réussie", "La ligne a été supprimée car la quantité est à zéro.");
            // Ajouter cette suppression dans l'historique
             // Appel de la fonction historique de Utilitee
        }
    }


    //int remainingQTE = getRemainingStockFromDB(idp);
        // Send the remaining stock to Arduino
    //arduino->sendDataToArduino(remainingQTE);

    // Affichage de la nouvelle quantité dans un QMessageBox
    QString message = QString("La nouvelle quantité est : %1").arg(novQte);
    QMessageBox::information(this, "Mise à jour réussie", message);
}

void MainWindow::on_afficher2_6_clicked()
{
    ui->tableView_10->setModel(util.afficher());

}




//client
void MainWindow::displayReservationsPerMonthStatistics() {
    // Liste des mois pour l'axe X
    QStringList months = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
    QMap<QString, int> monthCounts;

    // Initialisation des compteurs pour chaque mois
    for (const QString &month : months) {
        monthCounts[month] = 0;
    }

    // Requête SQL pour compter les réservations par mois et année basées sur CHECK_IN
    QSqlQuery query;
    query.prepare(
        "SELECT TO_CHAR(CHECK_IN, 'MM') AS month, "
        "TO_CHAR(CHECK_IN, 'YYYY') AS year, "
        "COUNT(*) AS count "
        "FROM RESERVATION "
        "GROUP BY TO_CHAR(CHECK_IN, 'MM'), TO_CHAR(CHECK_IN, 'YYYY') "
        "ORDER BY TO_CHAR(CHECK_IN, 'YYYY'), TO_CHAR(CHECK_IN, 'MM')"
    );

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return;
    }

    // Préparation des données pour le graphique
    QBarSet *barSet = new QBarSet("Reservations");
    QStringList categories;
    QMap<QString, int> dataMap;

    while (query.next()) {
        QString month = query.value("month").toString();
        QString year = query.value("year").toString();
        int count = query.value("count").toInt();

        QString label = months[month.toInt() - 1] + " " + year; // Format "Month Year"
        dataMap[label] = count;
    }

    for (const QString &key : dataMap.keys()) {
        *barSet << dataMap[key]; // Ajouter les données au jeu de barres
        categories << key;       // Ajouter l'étiquette pour l'axe X
    }

    // Création de la série de données et du graphique
    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Reservations Per Month");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of Reservations");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    // Affichage du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(600, 400);

    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->addWidget(chartView);
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->scene()->update();
    ui->graphicsView->show();
    updateModel();
}


void MainWindow::displayClientGenderStatistics() {
    // Requête SQL pour compter les clients par genre
    QSqlQuery query;
    query.prepare(
        "SELECT GENRE, COUNT(*) as count "
        "FROM CLIENT "
        "GROUP BY GENRE"
    );

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return;
    }

    // Création de la série pour le graphique circulaire
    QPieSeries *pieSeries = new QPieSeries();
    int totalClients = 0;

    // Collecte des données et calcul du total
    while (query.next()) {
        QString genre = query.value("GENRE").toString();
        int count = query.value("count").toInt();
        totalClients += count;

        pieSeries->append(genre, count);
    }

    // Correction : mise à jour des étiquettes avec des pourcentages corrects
    for (QPieSlice *slice : pieSeries->slices()) {
        QString genre = slice->label(); // Récupérer le genre
        int count = slice->value();    // Nombre de clients
        double percentage = (count / static_cast<double>(totalClients)) * 100.0;

        // Utilisation de asprintf pour formater correctement la chaîne
        QString label = QString::asprintf("%s: %d clients (%.1f%%)",
                                          genre.toUtf8().constData(),
                                          count,
                                          percentage);

        slice->setLabelVisible(true);
        slice->setLabel(label);
    }

    // Création et affichage du graphique
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Client Gender Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(600, 400);

    ui->graphicsView1->setScene(new QGraphicsScene());
    ui->graphicsView1->scene()->addWidget(chartView);
    ui->graphicsView1->fitInView(ui->graphicsView1->scene()->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView1->scene()->update();
    ui->graphicsView1->show();
    updateModel();
}


void MainWindow::updateModel() {
  //  Client client; // Create an instance of Commande to fetch data
  //  QSqlQueryModel* model = client.afficher(); // Fetch the model from the database
   // proxyModel->setSourceModel(model); // Set the source model for the proxy
   // ui->tableView_6->setModel(proxyModel); // Attach the proxy model to the table view
    ui->tableView_6->setModel(client.afficher());
}

void MainWindow::on_ajouterButton_clicked()
{

    int CIN = ui->lineEdit_CIN->text().toInt();
    QString NOM = ui->lineEdit_NOM->text();
    QString PRENOM = ui->lineEdit_PRENOM->text();
    int NUM = ui->lineEdit_NUM->text().toInt();
    QString ADRESSE = ui->lineEdit_ADRESSE->text();

    QString GENRE = ui->comboBox_GENRE->currentText();  // Utilisation de ComboBox pour OPTIONS


    Client client(CIN, NOM, PRENOM, NUM, ADRESSE, GENRE);

    if (client.ajouter()) {
        QMessageBox::information(this, "Ajout réussi", "Le client a été ajouté avec succès.");
        ui->tableView_6->setModel(client.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client.");
    }
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    updateModel();
}

void MainWindow::on_supprimerButton_clicked()
{
    int CIN = ui->lineEdit_CIN1->text().toInt();

    Client client;

    if (client.supprimer(CIN)) {
        QMessageBox::information(this, "Suppression réussie", "Le client a été supprimé avec succès.");
        ui->tableView_6->setModel(client.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du client.");
    }
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    updateModel();
}

void MainWindow::on_modifierButton_2_clicked()
{
    int CIN = ui->lineEdit_CIN1->text().toInt();
    if (CIN == 0) {
        QMessageBox::warning(this, "Erreur d'entrée", "Le CIN pour modifier est vide ou invalide.");
        return;
    }

    QString NOM = ui->lineEdit_NOM->text();
    QString PRENOM = ui->lineEdit_PRENOM->text();
    int NUM = ui->lineEdit_NUM->text().toInt();
    QString ADRESSE = ui->lineEdit_ADRESSE->text();
    QString GENRE = ui->comboBox_GENRE->currentText();
    Client client;
    client.setCIN(CIN);

    if (client.CINExists(CIN)) {
        if (client.modifier(CIN, NOM, PRENOM, NUM, ADRESSE, GENRE)) {
            QMessageBox::information(this, "Succès", "Les informations du client ont été modifiées avec succès.");
            ui->tableView_6->setModel(client.afficher());
            ui->tableView_6->resizeColumnsToContents();
        } else {
            QMessageBox::warning(this, "Échec", "Échec de la modification des informations du client.");
        }
    } else {
        QMessageBox::information(this, "Échec", "Le CIN pour modification n'existe pas.");
    }
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    updateModel();
}

void MainWindow::on_triComboBoxclient_currentIndexChanged(int index)
{
    QSqlQueryModel* model = nullptr;

    if (index == 0) {
        model = metier.trierParNom();
    } else if (index == 1) {
        model = metier.trierParCIN();
    } else if (index == 2) {
        model = metier.trierParNumero();
    }

    if (model) {
        ui->tableView_6->setModel(model);
    }
}

void MainWindow::on_exportPDFButtonclient_clicked()
{
    exportTableViewToPDF(ui->tableView_6);

}
void MainWindow::exportTableViewToPDF(QTableView *tableView) {
    // Ouvrir une boîte de dialogue pour choisir où sauvegarder le fichier PDF
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save as PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    // Création du QPdfWriter pour écrire dans le fichier PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    // Création du QPainter pour dessiner dans le PDF
    QPainter painter(&pdfWriter);

    // Récupérer le modèle de données de la table
    QAbstractItemModel *model = tableView->model();

    int x = 10;   // Position de départ x
    int y = 30;   // Position de départ y
    int rowHeight = 100;
    int columnWidth = 250;

    // Définir la police pour le PDF
    QFont font = painter.font();
    font.setPointSize(5);
    painter.setFont(font);

    // Dessiner les en-têtes de colonne
    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString());
        painter.drawRect(rect);
    }

    // Dessiner les lignes de données
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + (row + 1) * rowHeight, columnWidth, rowHeight);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, column)).toString());
            painter.drawRect(rect);
        }
    }

    // Terminer l'écriture dans le PDF
    painter.end();

    // Afficher un message de confirmation une fois l'export terminé
    QMessageBox::information(nullptr, "Export Complete", "Data has been exported to PDF successfully.");
    updateModel();
}
void MainWindow::on_ajouterReservationButton_clicked()
{
    int NUM_RES = ui->lineEdit_NUM_RES->text().toInt();
    QDate CHECK_IN = ui->dateEdit_CHECK_IN->date();
    QDate CHECK_OUT = ui->dateEdit_CHECK_OUT->date();
    int NUM_ENFANT = ui->spinBox_NUM_ENFANT->value();  // Utilisation de QSpinBox pour NUM_ENFANT
    int NUM_CHAMBRE = ui->lineEdit_NUM_CHAMBRE->text().toInt();
    int ETAGE = ui->lineEdit_ETAGE->text().toInt();
    int NUM_ADULT = ui->spinBox_NUM_ADULT->value();  // Utilisation de QSpinBox pour NUM_ADULT
    QString OPTIONS = ui->comboBox_OPTIONS->currentText();  // Utilisation de ComboBox pour OPTIONS
    int FEED_BACK = ui->lineEdit_FEED_BACK->text().toInt();

    Reservation reservation(NUM_RES, CHECK_IN, CHECK_OUT, NUM_ENFANT, NUM_CHAMBRE, ETAGE, NUM_ADULT, OPTIONS, FEED_BACK);

    if (reservation.ajouter()) {
        QMessageBox::information(this, "Ajout réussi", "La réservation a été ajoutée avec succès.");
        ui->reservationTableView->setModel(reservation.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la réservation.");
    }
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    updateModel();
}

void MainWindow::on_modifierReservationButton_clicked()
{
    int NUM_RES = ui->lineEdit_NUM_RES1->text().toInt();
    if (NUM_RES == 0) {
        QMessageBox::warning(this, "Erreur d'entrée", "Le numéro de réservation est invalide.");
        return;
    }

    QDate CHECK_IN = ui->dateEdit_CHECK_IN->date();
    QDate CHECK_OUT = ui->dateEdit_CHECK_OUT->date();
    int NUM_ENFANT = ui->spinBox_NUM_ENFANT->value();
    int NUM_CHAMBRE = ui->lineEdit_NUM_CHAMBRE->text().toInt();
    int ETAGE = ui->lineEdit_ETAGE->text().toInt();
    int NUM_ADULT = ui->spinBox_NUM_ADULT->value();
    QString OPTIONS = ui->comboBox_OPTIONS->currentText();
    int FEED_BACK = ui->lineEdit_FEED_BACK->text().toInt();


    Reservation reservation;
    if (reservation.modifier(NUM_RES, CHECK_IN, CHECK_OUT, NUM_ENFANT, NUM_CHAMBRE, ETAGE, NUM_ADULT, OPTIONS,FEED_BACK)) {
        QMessageBox::information(this, "Modification réussie", "La réservation a été modifiée avec succès.");
        ui->reservationTableView->setModel(reservation.afficher());
    } else {
        QMessageBox::warning(this, "Échec", "Échec de la modification de la réservation.");
    }
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    updateModel();
}

void MainWindow::on_supprimerReservationButton_clicked()
{
    int NUM_RES = ui->lineEdit_NUM_RES1->text().toInt();
    Reservation reservation;

    if (reservation.supprimer(NUM_RES)) {
        QMessageBox::information(this, "Suppression réussie", "La réservation a été supprimée avec succès.");
        ui->reservationTableView->setModel(reservation.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la réservation.");
    }
    displayReservationsPerMonthStatistics();  // Statistiques des réservations par mois
    displayClientGenderStatistics();
    updateModel();
}

void MainWindow::on_modifierButtonfeedback_clicked()
{
    int numRes = ui->lineEdit_numRes->text().toInt(); // Récupérer l'ID de réservation
    int nouveauFeedback = ui->lineEdit_feed->text().toInt(); // Récupérer le nouveau feedback

    Reservation reservation;
    if (reservation.modifier1(numRes, nouveauFeedback)) {
        QMessageBox::information(this, "Succès", "Feedback mis à jour avec succès !");
        ui->FEEDTableView->setModel(reservation.afficher1());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du feedback.");
    }
    updateModel();
}

void MainWindow::on_menu_to_employe_clicked()
{
    ui->interface_login->hide();

    ui->menu->hide();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->show();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_menu_to_client_clicked()
{
    ui->interface_login->hide();

    ui->menu->hide();
    ui->gestion_chambre->hide();
    ui->gestion_client->show();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_menu_to_chambre_clicked()
{
    ui->interface_login->hide();

    ui->menu->hide();
    ui->gestion_chambre->show();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_menu_to_facture_clicked()
{
    ui->interface_login->hide();

    ui->menu->hide();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->show();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_menu_to_utiliter_clicked()
{
    ui->interface_login->hide();

    ui->menu->hide();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->show();
}


void MainWindow::on_annuler_2_clicked()
{
    ui->interface_login->hide();

    ui->menu->show();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_annuler_3_clicked()
{
    ui->interface_login->hide();

    ui->menu->show();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_annuler_4_clicked()
{
    ui->interface_login->hide();

    ui->menu->show();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_annuler_5_clicked()
{
    ui->interface_login->hide();

    ui->menu->show();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_annuler_6_clicked()
{
    ui->interface_login->hide();
    ui->menu->show();
    ui->gestion_chambre->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_facture->hide();
    ui->gestion_utilitee->hide();
}


void MainWindow::on_login_2_clicked()
{
    QString email = ui->email_2->text().toLower().trimmed();
    QString password = ui->password_2->text().toLower().trimmed();

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
            ui->interface_login->hide();

            ui->menu->show();
            ui->gestion_chambre->hide();
            ui->gestion_client->hide();
            ui->gestion_employe->hide();
            ui->gestion_facture->hide();
            ui->gestion_utilitee->hide();
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

