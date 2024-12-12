#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();

    void initArduino();                  // Initialize the Arduino connection
    void sendDataToArduino(int qte);     // Send remaining stock quantity to Arduino

private:
    QSerialPort *serialPort;
};

#endif // ARDUINO_H
