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

Employe e;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->aff->setModel(e.afficher());
    ui->aff_feed->setModel(e.afficherEmpFeedback());
    afficherStatistiques();

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

