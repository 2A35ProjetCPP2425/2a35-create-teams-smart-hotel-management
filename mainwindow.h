#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"facture.h"
#include <QFileDialog>
#include <QTableView>// Include the QTableView class
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCheckBox>
#include "employe.h"


#include <QAbstractItemModel>
#include <QString>
#include <QSerialPort>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include "chambre.h"
#include "arduino.h"
#include "utilitee.h"

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

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *roomModel;          // Model for the room table

private slots:
    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_recuperer_clicked();

    void on_supprimer_clicked();

    void on_annuler_clicked();

    void on_ajouter_f_clicked();

    void on_trie_clicked();

    void on_rechercher_clicked();

    void on_pdf_clicked();

    void   afficherStatistiques();



    void on_actualiser_clicked();

    void on_pushButton_clicked();

    void on_pushButton_supprimer_clicked();

    void on_modifierButton_clicked();

    void updatePriceTab(int numRev, double prixFac) ;
    void recalculerPrixTotal(int numRev, double extraPrice);

    void on_pushButton_generatePDF_clicked();

    void on_pushButton_search_clicked();

    void on_comboboxSort_currentIndexChanged(int index);


    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_afficher_clicked();

    void on_reclamationButton_clicked();

    void on_statButton_clicked();

    void on_Ajouter_clicked();

    void on_modifier_2_clicked();

    void on_supprimer_2_clicked();

    void on_trier_tarif_clicked();

    void on_rechercherButton_clicked();

    void on_genererPDFButton_clicked();
    void onRoomSelected(const QModelIndex &index) ;

    void on_Affecter_clicked();

    void on_afficher2_clicked();

    void on_pushButton_2_clicked();

//    int getRemainingStockFromDB(int idProd);
  //  void sendQteToArduino(int remainingQTE);

    void on_addButton_clicked();

    void on_updateButton_clicked();

    void on_deleteButton_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_rechercheLineEdit_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_afficher2_6_clicked();
    void afficherStatistiquesPaiements() ;

    //client

    void displayReservationsPerMonthStatistics() ;

    void displayClientGenderStatistics() ;

    void updateModel() ;

    void on_ajouterButton_clicked();

    void on_supprimerButton_clicked();

    void on_modifierButton_2_clicked();

    void on_triComboBoxclient_currentIndexChanged(int index);

    void on_exportPDFButtonclient_clicked();
    void exportTableViewToPDF(QTableView *tableView) ;

    void on_ajouterReservationButton_clicked();

    void on_modifierReservationButton_clicked();

    void on_supprimerReservationButton_clicked();

    void on_modifierButtonfeedback_clicked();

    void on_menu_to_employe_clicked();

    void on_menu_to_client_clicked();

    void on_menu_to_chambre_clicked();

    void on_menu_to_facture_clicked();

    void on_menu_to_utiliter_clicked();

    void on_annuler_2_clicked();

    void on_annuler_3_clicked();

    void on_annuler_4_clicked();

    void on_annuler_5_clicked();

    void on_annuler_6_clicked();

    void on_login_2_clicked();

private:
    Ui::MainWindow *ui;
    facture f;
    QTableView* tableView2;  // Table pour afficher NUM_REV et PRIX
    QPushButton* buttonAfficher;
    QTableView *tableView3;    // Table des extras
    Employe e;


    //chambre
    bool assignChambreToEmploye(const QString &numChambre, const QString &idEmploye);
    bool validateInputs();                  // Validate inputs for other operations
    Chambre chambre;                        // Instance of the Chambre class
    QString selectedEmployeeId;             // ID of the selected employee
    QAbstractItemModel *model;              // Data model
    int maxOrganization;


    //utititee
    Utilitee util;
    Arduino *arduino;
    QTimer *timer;           // Timer to poll the database
    int lastQTE;


    //client / reservation
    Metier metier;
    //Arduino* arduino;
   // QSortFilterProxyModel *proxyModel; // Add this line
    Client client;
};
#endif // MAINWINDOW_H
