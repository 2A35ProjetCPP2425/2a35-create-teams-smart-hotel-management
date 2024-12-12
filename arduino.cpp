#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent) : QObject(parent), serialPort(new QSerialPort(this)) {}

Arduino::~Arduino() {
    if (serialPort->isOpen()) {
        serialPort->close();
    }
}

void Arduino::initArduino() {
    serialPort->setPortName("COM6"); // Adjust the port name to your Arduino's COM port
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Arduino connected successfully.";
    } else {
        qDebug() << "Failed to connect to Arduino.";
    }
}

void Arduino::sendDataToArduino(int qte) {
    if (serialPort->isOpen()) {
        QString message = QString("QTE:%1\n").arg(qte); // Format message as "QTE:<remaining>"
        serialPort->write(message.toUtf8());           // Send to Arduino
        qDebug() << "Data sent to Arduino:" << message;
    } else {
        qDebug() << "Arduino is not connected.";
    }
}
