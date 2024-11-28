#include "mainwindow.h"
#include "ui_mainwindow.h"
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->priceTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->priceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->priceTableView->viewport()->update();


    connect(ui->tableView2, &QTableView::clicked, this, &MainWindow::on_tableView2_clicked);
    connect(ui->statButton, &QPushButton::clicked, this, &MainWindow::afficherStatistiquesPaiements);


    ui->tableView->setModel(f.afficher());
    ui->comboboxSort->addItem("trier par");    // Sort by name
    ui->comboboxSort->addItem("ref");    // Sort by name
    ui->comboboxSort->addItem("date");
    ui->comboboxSort->addItem("prix");


}


/*void MainWindow::on_pushButton_clicked()
{

}*/


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

void MainWindow::on_pushButton_generatePDF_clicked() {
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
void MainWindow::on_pushButton_search_clicked() {
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
void MainWindow::on_comboboxSort_currentIndexChanged(int index) {
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
void MainWindow::on_pushButton_afficher_clicked()
{
    // Appeler la méthode afficher2() pour obtenir le modèle de données
    QSqlQueryModel* model = f.afficher2();

    // Utilisez ui->tableView2 si tableView2 est défini dans le fichier .ui
    ui->tableView2->setModel(model);
}
void MainWindow::on_tableView2_clicked(const QModelIndex &index) {
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

MainWindow::~MainWindow()
{
    delete ui;
}




