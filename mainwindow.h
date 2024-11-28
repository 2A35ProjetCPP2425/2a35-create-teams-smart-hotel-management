#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"facture.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QTableView>// Include the QTableView class
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCheckBox>
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
    void on_tableView2_clicked(const QModelIndex &index);





/*private slots:
    void on_pushButton_clicked();*/

private slots:
    void on_pushButton_clicked();
    void on_pushButton_supprimer_clicked();
    void on_modifierButton_clicked();
    void on_pushButton_generatePDF_clicked();
    void on_pushButton_search_clicked();    // Declare search function
    void on_comboboxSort_currentIndexChanged(int index);
    void on_pushButton_afficher_clicked();
    void updatePriceTab(int numRev, double prixFac);
    void on_reclamationButton_clicked();
    void recalculerPrixTotal(int numRev, double extraPrice);
    void afficherStatistiquesPaiements() ;




private:
    Ui::MainWindow *ui;
    facture f;
    QTableView* tableView2;  // Table pour afficher NUM_REV et PRIX
    QPushButton* buttonAfficher;
    QTableView *tableView3;    // Table des extras
   // Modèle pour tableView3


};
#endif // MAINWINDOW_H
