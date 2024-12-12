/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QTableView *tableView;
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *email;
    QLineEdit *password;
    QPushButton *login;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(1201, 679);
        tableView = new QTableView(Login);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(0, 0, 1201, 681));
        QFont font;
        font.setUnderline(false);
        tableView->setFont(font);
        tableView->setStyleSheet(QString::fromUtf8("background-color:#0096c7;"));
        label = new QLabel(Login);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 60, 531, 131));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("SimSun")});
        font1.setPointSize(24);
        font1.setUnderline(false);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("background-color:#90e0ef;\n"
"color:black;"));
        groupBox = new QGroupBox(Login);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(420, 250, 401, 301));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setUnderline(false);
        groupBox->setFont(font2);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 60, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 140, 91, 20));
        email = new QLineEdit(groupBox);
        email->setObjectName("email");
        email->setGeometry(QRect(40, 100, 211, 26));
        password = new QLineEdit(groupBox);
        password->setObjectName("password");
        password->setGeometry(QRect(40, 170, 211, 26));
        login = new QPushButton(groupBox);
        login->setObjectName("login");
        login->setGeometry(QRect(120, 230, 141, 51));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setUnderline(false);
        login->setFont(font3);
        login->setStyleSheet(QString::fromUtf8("color:black;\n"
"background-color:#90e0ef;\n"
""));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Login", "       AUTHENTIFICATION", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Login", "Welcome", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "Email :", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "Password :", nullptr));
        login->setText(QCoreApplication::translate("Login", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
