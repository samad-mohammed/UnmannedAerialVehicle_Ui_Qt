

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QSerialPort>
#include<QSerialPortInfo>
#include<QMessageBox>


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->UiQmlWidget->setSource(QUrl(QStringLiteral("qrc:/mapQml.qml")));
    ui->UiQmlWidget->show();

    // Connect the button's clicked signal to the slot
    connect(ui->startCameraButton, &QPushButton::clicked, this, &MainWindow::startCamera);


    // Create a QWebEngineView
    QWebEngineView* mapOverviewView = new QWebEngineView(ui->mapOverviewWidget);

    mapOverviewView->setFixedWidth(190);
     mapOverviewView->setFixedHeight(190);

    // Load the HTML file into the view
    mapOverviewView->setUrl(QUrl("qrc:/mapOverview.html"));

    /*   QWebEngineView* camView = new QWebEngineView(ui->cameraView);

    camView->setFixedWidth(315);
    camView->setFixedHeight(200);

    // Load the HTML file into the view
    camView->setUrl(QUrl("qrc:/cameraViewHTML.html"));*/

     serialPort = new QSerialPort(this);


     //     Find the correct serial port name for your Arduino Mega
     foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
         qDebug() <<  port.description();
         if (port.description().contains("Arduino Mega 2560")) {

             serialPort->setPort(port);
             serialPort->setBaudRate(QSerialPort::Baud57600);
             break;
         }
     }


     if (serialPort->open(QIODevice::ReadOnly)) {
         qDebug() << "Serial port opened successfully.";
     } else {
         qDebug() << "Failed to open serial port: " << serialPort->errorString();

     }


     // Create a timer to check for data every 1000 milliseconds (1 second)
     QTimer *timer = new QTimer(this);
     connect(timer, &QTimer::timeout, this, &MainWindow::checkForData);
     timer->start(200); // Start the timer


}



MainWindow::~MainWindow()
{
    delete ui;
}
//-------------------------------------------------------------------------------------


void MainWindow::startCamera()
{
    QProcess process;
    process.start("python3", QStringList() << "cameraFeed.py");
    process.waitForFinished();
}

//--------------------------------------------------------------------------------------

void MainWindow::on_loadPushButton_clicked()
{
    /* QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Load Image"),
                                                    mResourceDir,
                                                    tr("Images (*.png *.jpg)"));*/
    QString filename = "../marker-icons/flight-icon.png";

    if (filename.isEmpty())  {
         return;
    }

    QPixmap p(filename);

    /*
#ifdef DEBUG
    qDebug() << "File: " << filename;
    qDebug() << "Depth: " << p.depth();
    qDebug() << "Width: " << p.width();
    qDebug() << "Height: " << p.height();
    qDebug() << "alpha: " << p.hasAlphaChannel();
#endif
*/
    if (! ui->graphicsView->scene()) {
         //qDebug() << "No Scene!";

         QGraphicsScene *scene = new QGraphicsScene(this);
         ui->graphicsView->setScene(scene);
    }
    QGraphicsScene *scene = ui->graphicsView->scene();
    QGraphicsPixmapItem *pixmapItem = scene->addPixmap(p);

    // Calculate the scale factors to fit the image within the view
    qreal viewWidth = ui->graphicsView->width();
    qreal viewHeight = ui->graphicsView->height();
    qreal imageWidth = p.width();
    qreal imageHeight = p.height();

    qreal scaleX = viewWidth / imageWidth;
    qreal scaleY = viewHeight / imageHeight;

    // Set the scale factors to fit the image within the view
    qreal scaleFactor = qMin(scaleX, scaleY);
    pixmapItem->setScale(scaleFactor);

    // Center the image in the view
    ui->graphicsView->centerOn(pixmapItem);
    // Set the background color to dark gray
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(5, 2, 36))); // RGB values for dark gray
}



//--------------------------------------------------------------------------------------
void MainWindow::onLoadFinished(bool ok)
{
    if (!ok) {
        QMessageBox::critical(this, "Error", "Failed to load the map HTML file.");
        // Handle the error as needed.
    }
}



void MainWindow::on_PitchSpinBox_valueChanged(double arg1)
{
    ui->gyro_EADI->setPitch(arg1);
    ui->gyro_EADI->redraw();

}


void MainWindow::on_RollSpinBox_valueChanged(double arg1)
{
    ui->gyro_EADI->setRoll(arg1);
    ui->gyro_EADI->redraw();
}


void MainWindow::checkForData()
{
    if (serialPort->bytesAvailable() > 0) {
        // Data is available to be read, so call readData to process it
        readData();
    }
}

void MainWindow::readData()
{

    QByteArray data = serialPort->readLine();
    QString dataString = QString::fromUtf8(data);

    qDebug() << dataString;

    QList<QByteArray> values = data.split(',');

    if (values.size() == 6) {
        gyroX = values[0].toDouble();
        gyroY = values[1].toDouble();
        gyroZ = values[2].toDouble();

        accX = values[3].toDouble();
        accY = values[4].toDouble();
        accZ = values[5].toDouble();

        accelerationX = (signed int)(((signed int)accX) * 3.9);
        accelerationY = (signed int)(((signed int)accY) * 3.9);
        accelerationZ = (signed int)(((signed int)accZ) * 3.9);


        //        Note: M_PI = 3.14159265358979323846 it is constant defined in math.h
        pitch = 180 * atan (accelerationX/sqrt(accelerationY*accelerationY + accelerationZ*accelerationZ))/M_PI;

        roll = atan2(accelerationY, accelerationZ) * 180.0 / M_PI;

        yaw = atan2(accelerationZ, accelerationX)*180.0 / M_PI - 90.0;

//        double gyro_sensitivity_x = 250;
//        double gyro_bias_x = 0.5;
//        yaw = (gyroX+gyroY+gyroZ)*0.2;
//        currYaw = prevYaw + yaw;
//        turnRate = yaw/0.2;
//        prevYaw = currYaw;


        // turnRate = (gyroZ/gyro_sensitivity_x) - gyro_bias_x;
        // Update UI elements here with the received data

        ui->PitchSpinBox->setValue(pitch);
        ui->RollSpinBox->setValue(roll);
        /*
        ui->doubleSpinBoxHeading->setValue(yaw);
        ui->doubleSpinBoxTR->setValue(gyroX);
        ui->doubleSpinBoxHeadingSpeed->setValue(accelerationX);
        */
        //            ui->doubleSpinBoxTR->setValue(turnRate);



    }
}


void MainWindow::on_clearPushButton_clicked()
{
    if (ui->graphicsView->scene()) {
        ui->graphicsView->scene()->clear();
    }
}



