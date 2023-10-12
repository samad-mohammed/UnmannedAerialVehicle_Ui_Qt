#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <QTimer>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MyQQuickWidget : public QQuickWidget {
    Q_OBJECT
public:
    MyQQuickWidget(QWidget *parent = nullptr) : QQuickWidget(parent) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onLoadFinished(bool ok);

private:
    Ui::MainWindow *ui;

    int timerId;
    QSerialPort *serialPort;
    void checkForData();
    void readData();

    double gyroX;
    double gyroY;
    double gyroZ;

    double pitch;
    double roll;
    double yaw;

    double accX;
    double accY;
    double accZ;

    signed int accelerationX;
    signed int accelerationY;
    signed int accelerationZ;

private slots:
    void on_PitchSpinBox_valueChanged(double arg1);
    void on_RollSpinBox_valueChanged(double arg1);

};
#endif // MAINWINDOW_H
