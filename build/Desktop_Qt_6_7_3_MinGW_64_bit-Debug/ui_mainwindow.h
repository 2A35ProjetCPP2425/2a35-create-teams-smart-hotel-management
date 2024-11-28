/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *facture;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_supprimer;
    QPushButton *modifierButton;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QDateEdit *dateEdit;
    QTableView *tableView;
    QPushButton *pushButton_generatePDF;
    QPushButton *pushButton_search;
    QLineEdit *lineEdit_search;
    QComboBox *comboboxSort;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *statButton;
    QWidget *calucleextras;
    QTableView *tableView2;
    QPushButton *pushButton_afficher;
    QTableView *tableView3;
    QTableView *priceTableView;
    QPushButton *reclamationButton;
    QLabel *label_7;
    QWidget *tab;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1196, 695);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(30, 0, 1161, 701));
        tabWidget->setStyleSheet(QString::fromUtf8("\n"
"/* Style des boutons \303\240 l'int\303\251rieur des onglets */\n"
"QPushButton {\n"
"    background-color: #007bff; /* Fond bleu vif pour les boutons */\n"
"    color: white; /* Texte en blanc */\n"
"    border: 1px solid #0056b3; /* Bordure bleue fonc\303\251e pour les boutons */\n"
"    border-radius: 8px; /* Coins arrondis pour les boutons */\n"
"    padding: 10px 20px; /* Espacement autour du texte du bouton */\n"
"    font-size: 16px; /* Taille du texte du bouton */\n"
"    transition: background-color 0.3s, border-color 0.3s, transform 0.3s; /* Effets de transition */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #0069d9; /* Fond bleu clair au survol */\n"
"    border-color: #004085; /* Bordure plus fonc\303\251e au survol */\n"
"    transform: scale(1.05); /* Effet d'agrandissement l\303\251ger au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #0056b3; /* Fond plus fonc\303\251 lorsque le bouton est press\303\251 */\n"
"    border-color: #003366; /* Bordure"
                        " encore plus fonc\303\251e quand press\303\251 */\n"
"}\n"
"/* Style g\303\251n\303\251ral du QTabWidget */\n"
"QTabWidget::pane {\n"
"    background-color: #add8e6; /* Bleu clair pour l'arri\303\250re-plan */\n"
"    border: 1px solid #007bff; /* Optionnel : bordure bleue autour du QTabWidget */\n"
"}\n"
"\n"
"/* Style pour les onglets dans la barre de tabulation (QTabBar) */\n"
"QTabBar::tab {\n"
"    background-color: #f0f0f0; /* Fond gris clair pour les onglets inactifs */\n"
"    color: #000000; /* Texte noir */\n"
"    border: 1px solid #ccc; /* Bordure grise autour des onglets */\n"
"    padding: 8px 16px;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"}\n"
"\n"
"/* Style pour l'onglet s\303\251lectionn\303\251 */\n"
"QTabBar::tab:selected {\n"
"    background-color: #ffffff; /* Fond blanc pour l'onglet actif */\n"
"    color: #000000; /* Texte noir pour l'onglet actif */\n"
"}\n"
"\n"
"/* Style pour l'onglet au survol */\n"
"QTabBar::tab:hover {\n"
"    background-color:"
                        " #e0e0e0; /* Fond gris plus clair au survol */\n"
"}\n"
""));
        facture = new QWidget();
        facture->setObjectName("facture");
        label = new QLabel(facture);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 251, 431));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #F0F0F0;    /* Light gray background */\n"
"    color: #333333;               /* Dark text color */\n"
"    border: 2px solid #0078D7;    /* Blue contour border */\n"
"    border-radius: 10px;          /* Rounded corners */\n"
"    padding: 5px;                 /* Padding inside the label */\n"
"    font-size: 16px;              /* Font size */\n"
"    font-weight: bold;            /* Bold text */\n"
"    text-align: center;           /* Center the text */\n"
"}\n"
""));
        lineEdit_3 = new QLineEdit(facture);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(130, 210, 141, 41));
        lineEdit_3->setStyleSheet(QString::fromUtf8("/* Style pour QLineEdit */\n"
"QLineEdit {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #333; /* Texte gris fonc\303\251 */\n"
"    border: 2px solid #007bff; /* Bordure bleu */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 8px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    transition: border-color 0.3s, box-shadow 0.3s; /* Effet fluide pour le survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est survol\303\251 */\n"
"QLineEdit:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"    box-shadow: 0 0 8px #0056b3; /* Ombre bleue autour de l'\303\251l\303\251ment au survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est en focus */\n"
"QLineEdit:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel lorsqu'il est s\303\251lectionn\303\251 */\n"
"    box-shadow: 0 0 12px #00bfff; /* Ombre plus intense lorsqu'il est s\303\251lectionn\303\251 */\n"
"}\n"
""));
        lineEdit_4 = new QLineEdit(facture);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(132, 150, 141, 41));
        lineEdit_4->setStyleSheet(QString::fromUtf8("/* Style pour QLineEdit */\n"
"QLineEdit {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #333; /* Texte gris fonc\303\251 */\n"
"    border: 2px solid #007bff; /* Bordure bleu */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 8px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    transition: border-color 0.3s, box-shadow 0.3s; /* Effet fluide pour le survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est survol\303\251 */\n"
"QLineEdit:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"    box-shadow: 0 0 8px #0056b3; /* Ombre bleue autour de l'\303\251l\303\251ment au survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est en focus */\n"
"QLineEdit:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel lorsqu'il est s\303\251lectionn\303\251 */\n"
"    box-shadow: 0 0 12px #00bfff; /* Ombre plus intense lorsqu'il est s\303\251lectionn\303\251 */\n"
"}\n"
""));
        lineEdit_5 = new QLineEdit(facture);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(132, 90, 141, 41));
        lineEdit_5->setStyleSheet(QString::fromUtf8("/* Style pour QLineEdit */\n"
"QLineEdit {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #333; /* Texte gris fonc\303\251 */\n"
"    border: 2px solid #007bff; /* Bordure bleu */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 8px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    transition: border-color 0.3s, box-shadow 0.3s; /* Effet fluide pour le survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est survol\303\251 */\n"
"QLineEdit:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"    box-shadow: 0 0 8px #0056b3; /* Ombre bleue autour de l'\303\251l\303\251ment au survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est en focus */\n"
"QLineEdit:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel lorsqu'il est s\303\251lectionn\303\251 */\n"
"    box-shadow: 0 0 12px #00bfff; /* Ombre plus intense lorsqu'il est s\303\251lectionn\303\251 */\n"
"}\n"
""));
        label_2 = new QLabel(facture);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 90, 71, 31));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #000000; /* Texte noir */\n"
"    font-weight: bold; /* Texte en gras */\n"
"    font-size: 25px; /* Taille de la police \303\240 35 */\n"
"}\n"
""));
        pushButton = new QPushButton(facture);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(110, 510, 111, 41));
        pushButton_supprimer = new QPushButton(facture);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(510, 420, 121, 41));
        pushButton_supprimer->setStyleSheet(QString::fromUtf8("color=rgb(0, 0, 255);\n"
"alternate-background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.33 rgba(0, 0, 0, 255), stop:0.34 rgba(255, 30, 30, 255), stop:0.66 rgba(255, 0, 0, 255), stop:0.67 rgba(255, 255, 0, 255), stop:1 rgba(255, 255, 0, 255));"));
        modifierButton = new QPushButton(facture);
        modifierButton->setObjectName("modifierButton");
        modifierButton->setGeometry(QRect(660, 420, 131, 41));
        label_3 = new QLabel(facture);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 150, 61, 31));
        label_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #000000; /* Texte noir */\n"
"    font-weight: bold; /* Texte en gras */\n"
"    font-size: 25px; /* Taille de la police \303\240 35 */\n"
"}\n"
""));
        label_4 = new QLabel(facture);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 210, 71, 31));
        label_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #000000; /* Texte noir */\n"
"    font-weight: bold; /* Texte en gras */\n"
"    font-size: 25px; /* Taille de la police \303\240 35 */\n"
"}\n"
""));
        label_5 = new QLabel(facture);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 340, 71, 41));
        label_5->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #000000; /* Texte noir */\n"
"    font-weight: bold; /* Texte en gras */\n"
"    font-size: 25px; /* Taille de la police \303\240 35 */\n"
"}\n"
""));
        dateEdit = new QDateEdit(facture);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(130, 290, 141, 41));
        dateEdit->setStyleSheet(QString::fromUtf8("/* Style pour QDateEdit */\n"
"QDateEdit {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #000000; /* Texte noir */\n"
"    border: 2px solid #007bff; /* Bordure bleue */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 6px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    min-width: 120px; /* Largeur minimale pour le champ de date */\n"
"}\n"
"\n"
"/* Style au survol de QDateEdit */\n"
"QDateEdit:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"}\n"
"\n"
"/* Style pour QDateEdit lorsqu'il est en focus */\n"
"QDateEdit:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel au focus */\n"
"    box-shadow: 0 0 8px #00bfff; /* Ombre bleue au focus */\n"
"}\n"
"\n"
"/* Style pour la fl\303\250che de descente du QDateEdit */\n"
"QDateEdit::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #007bff; /* S\303\251"
                        "paration entre le champ et le bouton de descente */\n"
"    background-color: #007bff; /* Fond bleu pour le bouton */\n"
"    border-top-right-radius: 5px; /* Coins arrondis en haut \303\240 droite */\n"
"    border-bottom-right-radius: 5px; /* Coins arrondis en bas \303\240 droite */\n"
"}\n"
"\n"
"/* Style pour l'ic\303\264ne de la fl\303\250che de descente */\n"
"QDateEdit::down-arrow {\n"
"    image: url(:/images/down-arrow.png); /* Remplacer par l'ic\303\264ne personnalis\303\251e de fl\303\250che vers le bas */\n"
"    width: 12px; /* Largeur de l'ic\303\264ne */\n"
"    height: 12px; /* Hauteur de l'ic\303\264ne */\n"
"}\n"
"\n"
"/* Optionnel: Style au survol du bouton de descente */\n"
"QDateEdit::drop-down:hover {\n"
"    background-color: #0056b3; /* Changement de couleur au survol */\n"
"}\n"
"\n"
"/* Optionnel: Style des boutons fl\303\251ch\303\251s dans l'affichage du calendrier */\n"
"QCalendarWidget QToolButton {\n"
"    color: #ffffff; /* Couleur du texte des boutons du calendrier */\n"
"    b"
                        "ackground-color: #007bff; /* Fond bleu pour les boutons du calendrier */\n"
"    border: none; /* Pas de bordure pour les boutons */\n"
"    border-radius: 4px; /* Coins l\303\251g\303\250rement arrondis */\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Style pour les boutons fl\303\251ch\303\251s (mois pr\303\251c\303\251dent/suivant) */\n"
"QCalendarWidget QToolButton::hover {\n"
"    background-color: #0056b3; /* Fond bleu fonc\303\251 au survol */\n"
"}\n"
"\n"
"/* Style des num\303\251ros dans le calendrier */\n"
"QCalendarWidget QAbstractItemView {\n"
"    background-color: #ffffff; /* Fond blanc pour les jours */\n"
"    selection-background-color: #007bff; /* Fond bleu pour le jour s\303\251lectionn\303\251 */\n"
"    selection-color: white; /* Texte blanc pour le jour s\303\251lectionn\303\251 */\n"
"    color: #000000; /* Texte noir pour les jours non s\303\251lectionn\303\251s */\n"
"}\n"
""));
        tableView = new QTableView(facture);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(330, 70, 731, 341));
        tableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    background-color: #add8e6; /* Arri\303\250re-plan bleu clair */\n"
"    alternate-background-color: #e0f7fa; /* Couleur alternative pour les lignes */\n"
"    border: 1px solid #007bff; /* Bordure bleu vif */\n"
"    gridline-color: #007bff; /* Lignes de grille en bleu */\n"
"    selection-background-color: #87cefa; /* Bleu clair pour la s\303\251lection */\n"
"    selection-color: #ffffff; /* Texte blanc pour les cellules s\303\251lectionn\303\251es */\n"
"    font-size: 14px; /* Taille de police par d\303\251faut */\n"
"}\n"
"\n"
"QTableView::item {\n"
"    background-color: transparent; /* Fond transparent pour les \303\251l\303\251ments */\n"
"    color: #000000; /* Texte noir */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #007bff; /* Fond bleu vif pour l'en-t\303\252te */\n"
"    color: white; /* Texte blanc dans les en-t\303\252tes */\n"
"    padding: 4px;\n"
"    border: 1px solid #0056b3; /* Bordure pour les en-t\303\252tes */\n"
"}\n"
"\n"
"\n"
"\n"
""));
        pushButton_generatePDF = new QPushButton(facture);
        pushButton_generatePDF->setObjectName("pushButton_generatePDF");
        pushButton_generatePDF->setGeometry(QRect(370, 420, 121, 41));
        pushButton_search = new QPushButton(facture);
        pushButton_search->setObjectName("pushButton_search");
        pushButton_search->setGeometry(QRect(810, 420, 111, 41));
        lineEdit_search = new QLineEdit(facture);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setGeometry(QRect(940, 420, 113, 41));
        lineEdit_search->setStyleSheet(QString::fromUtf8("/* Style pour QLineEdit */\n"
"QLineEdit {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #333; /* Texte gris fonc\303\251 */\n"
"    border: 2px solid #007bff; /* Bordure bleu */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 8px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    transition: border-color 0.3s, box-shadow 0.3s; /* Effet fluide pour le survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est survol\303\251 */\n"
"QLineEdit:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"    box-shadow: 0 0 8px #0056b3; /* Ombre bleue autour de l'\303\251l\303\251ment au survol */\n"
"}\n"
"\n"
"/* Style pour QLineEdit lorsqu'il est en focus */\n"
"QLineEdit:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel lorsqu'il est s\303\251lectionn\303\251 */\n"
"    box-shadow: 0 0 12px #00bfff; /* Ombre plus intense lorsqu'il est s\303\251lectionn\303\251 */\n"
"}\n"
""));
        comboboxSort = new QComboBox(facture);
        comboboxSort->setObjectName("comboboxSort");
        comboboxSort->setGeometry(QRect(930, 30, 131, 41));
        comboboxSort->setStyleSheet(QString::fromUtf8("/* Style pour QComboBox */\n"
"QComboBox {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #000000; /* Texte noir */\n"
"    border: 2px solid #007bff; /* Bordure bleu */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 6px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    combobox-popup: 0; /* Affichage standard du menu d\303\251roulant */\n"
"}\n"
"\n"
"/* Style pour les \303\251l\303\251ments dans le menu d\303\251roulant */\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #f8f8f0; /* Couleur du menu d\303\251roulant */\n"
"    border: 2px solid #007bff; /* Bordure bleue autour du menu d\303\251roulant */\n"
"    selection-background-color: #0056b3; /* Fond bleu fonc\303\251 lors de la s\303\251lection */\n"
"    selection-color: white; /* Texte blanc pour l'\303\251l\303\251ment s\303\251lectionn\303\251 */\n"
"    color: #000000; /* Texte noir pour les \303\251l\303\251ments non s\303\251lectionn\303\251s */\n"
"}\n"
""
                        "\n"
"/* Style pour QComboBox lorsqu'il est survol\303\251 */\n"
"QComboBox:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"}\n"
"\n"
"/* Style pour QComboBox lorsqu'il est en focus */\n"
"QComboBox:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel lorsqu'il est en focus */\n"
"    box-shadow: 0 0 8px #00bfff; /* Ombre bleue au focus */\n"
"}\n"
"\n"
"/* Style pour la fl\303\250che d\303\251roulante de QComboBox */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #007bff; /* Bordure \303\240 gauche de la fl\303\250che */\n"
"    background-color: #007bff; /* Fond bleu pour la fl\303\250che */\n"
"}\n"
"\n"
"/* Ic\303\264ne de la fl\303\250che dans le QComboBox */\n"
"QComboBox::down-arrow {\n"
"    image: url(:/images/down-arrow.png); /* Remplacer par l'ic\303\264ne de la fl\303\250che */\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
""));
        label_6 = new QLabel(facture);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 280, 71, 41));
        label_6->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #000000; /* Texte noir */\n"
"    font-weight: bold; /* Texte en gras */\n"
"    font-size: 25px; /* Taille de la police \303\240 35 */\n"
"}\n"
""));
        doubleSpinBox = new QDoubleSpinBox(facture);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(130, 350, 141, 41));
        doubleSpinBox->setStyleSheet(QString::fromUtf8("/* Style pour QDoubleSpinBox */\n"
"QDoubleSpinBox {\n"
"    background-color: #f8f8f0; /* Blanc cass\303\251 */\n"
"    color: #000000; /* Texte noir */\n"
"    border: 2px solid #007bff; /* Bordure bleue */\n"
"    border-radius: 5px; /* Coins arrondis */\n"
"    padding: 6px; /* Espacement interne */\n"
"    font-size: 14px; /* Taille de la police */\n"
"    min-width: 100px; /* Largeur minimale */\n"
"}\n"
"\n"
"/* Style au survol de QDoubleSpinBox */\n"
"QDoubleSpinBox:hover {\n"
"    border-color: #0056b3; /* Bordure bleu fonc\303\251 au survol */\n"
"}\n"
"\n"
"/* Style pour QDoubleSpinBox lorsqu'il est en focus */\n"
"QDoubleSpinBox:focus {\n"
"    border-color: #00bfff; /* Bordure bleu ciel au focus */\n"
"    box-shadow: 0 0 8px #00bfff; /* Ombre bleue au focus */\n"
"}\n"
"\n"
"/* Style pour les boutons fl\303\251ch\303\251s de QDoubleSpinBox */\n"
"QDoubleSpinBox::up-button, QDoubleSpinBox::down-button {\n"
"    background-color: #007bff; /* Fond bleu pour les boutons de fl\303\250ches */\n"
"    b"
                        "order: none; /* Pas de bordure */\n"
"    width: 16px; /* Largeur des boutons */\n"
"    height: 16px; /* Hauteur des boutons */\n"
"    border-radius: 3px; /* Coins l\303\251g\303\250rement arrondis */\n"
"}\n"
"\n"
"/* Changement de couleur des boutons au survol */\n"
"QDoubleSpinBox::up-button:hover, QDoubleSpinBox::down-button:hover {\n"
"    background-color: #0056b3; /* Bleu fonc\303\251 au survol */\n"
"}\n"
"\n"
"/* Style de la fl\303\250che haut */\n"
"QDoubleSpinBox::up-arrow {\n"
"    image: url(:/images/up-arrow.png); /* Remplacer par votre ic\303\264ne de fl\303\250che vers le haut */\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}\n"
"\n"
"/* Style de la fl\303\250che bas */\n"
"QDoubleSpinBox::down-arrow {\n"
"    image: url(:/images/down-arrow.png); /* Remplacer par votre ic\303\264ne de fl\303\250che vers le bas */\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}\n"
"\n"
"/* Style pour le bouton press\303\251 */\n"
"QDoubleSpinBox::up-button:pressed, QDoubleSpinBox::down-button:pressed {\n"
""
                        "    background-color: #0056b3; /* Fond plus sombre lorsque le bouton est press\303\251 */\n"
"}\n"
""));
        statButton = new QPushButton(facture);
        statButton->setObjectName("statButton");
        statButton->setGeometry(QRect(660, 480, 161, 41));
        tabWidget->addTab(facture, QString());
        calucleextras = new QWidget();
        calucleextras->setObjectName("calucleextras");
        tableView2 = new QTableView(calucleextras);
        tableView2->setObjectName("tableView2");
        tableView2->setGeometry(QRect(20, 80, 321, 291));
        pushButton_afficher = new QPushButton(calucleextras);
        pushButton_afficher->setObjectName("pushButton_afficher");
        pushButton_afficher->setGeometry(QRect(100, 380, 131, 51));
        tableView3 = new QTableView(calucleextras);
        tableView3->setObjectName("tableView3");
        tableView3->setGeometry(QRect(420, 90, 401, 281));
        priceTableView = new QTableView(calucleextras);
        priceTableView->setObjectName("priceTableView");
        priceTableView->setGeometry(QRect(870, 130, 256, 192));
        reclamationButton = new QPushButton(calucleextras);
        reclamationButton->setObjectName("reclamationButton");
        reclamationButton->setGeometry(QRect(920, 330, 161, 51));
        label_7 = new QLabel(calucleextras);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(490, -70, 271, 261));
        tabWidget->addTab(calucleextras, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "ref", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        modifierButton->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "mode", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "prix", nullptr));
        pushButton_generatePDF->setText(QCoreApplication::translate("MainWindow", "pdf", nullptr));
        pushButton_search->setText(QCoreApplication::translate("MainWindow", "chercher", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "date", nullptr));
        statButton->setText(QCoreApplication::translate("MainWindow", "statstique(mode)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(facture), QCoreApplication::translate("MainWindow", "facture", nullptr));
        pushButton_afficher->setText(QCoreApplication::translate("MainWindow", "afficher", nullptr));
        reclamationButton->setText(QCoreApplication::translate("MainWindow", "reclamtion", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:28pt;\">Notre extras:</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(calucleextras), QCoreApplication::translate("MainWindow", "calcule extras", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
