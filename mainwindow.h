#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QString>
#include <QSerialPort>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include "chambre.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;                 // Serial port for Arduino communication
    QStandardItemModel *roomModel;          // Model for the room table

    void setupSerialPort();                 // Initialize the serial connection

private slots:
    void onRoomSelected(const QModelIndex &index);  // Slot triggered when a room is selected
    void sendCommandToArduino(const QString &command);  // Send command to Arduino
    void readSerialData();                   // Read data from Arduino

    // Other slots for your application logic
    void on_afficher2_clicked();
    void on_Ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_trier_etage_clicked();
    void on_trier_tarif_clicked();
    void on_rechercherButton_clicked();
    void on_genererPDFButton_clicked();
    void on_Affecter_clicked();
    void on_pushButton_clicked();
    void on_afficher2_2_clicked();
    void on_genererPDFButton_2_clicked();

private:
    bool assignChambreToEmploye(const QString &numChambre, const QString &idEmploye);
    bool validateInputs();                  // Validate inputs for other operations
    Chambre chambre;                        // Instance of the Chambre class
    QString selectedEmployeeId;             // ID of the selected employee
    QAbstractItemModel *model;              // Data model
    int maxOrganization;                    // Maximum organizational capacity
};

#endif // MAINWINDOW_H
