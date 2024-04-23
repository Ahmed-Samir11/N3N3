/*
    FCAI - Structured Programming - 2024 - Assignment 3
    Program Name: N3N3 Photoshop
    Program Photoshop: A small implementation of 20 filters that used mainly by most of image manipulation programs.
    Last Modification Date: 04/17/2024
    Author1 and ID and Group: Ahmed Samir Nagy Mohammed - 20230541 - S24
    Author2 and ID and Group: Mohammed Hany Raafat Mahrous - 20230581 - S24
    Author3 and ID and Group: Loay Medhat Mohammed Rafiq - 20230583 - S24
    Teaching Assistant: Hend Gamal
    Who did What: Ahmed Samir (20230541) => Filters 13, 14, 15, 16, 17 and 18
                  Mohammed Hany (20230581) => Filters 2, 5, 8, 10, 11, 12 + 2 bonus filters: Color Balancer and Glitch + GUI + Whole Code Connection
                  Loay Medhat (20230583) => Filters 1, 3, 4, 7, 9
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QRubberBand>
#include <cstdlib>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentImage(QImage())
{
    ui->setupUi(this);
    imageItem = nullptr;
    ui->pushButton_19->setVisible(false);
    ui->pushButton_24->setVisible(false);
    ui->pushButton_25->setVisible(false);
    ui->pushButton_26->setVisible(false);
    ui->pushButton_27->setVisible(false);
    ui->pushButton_28->setVisible(false);
    ui->pushButton_29->setVisible(false);
    ui->pushButton_30->setVisible(false);
    ui->pushButton_31->setVisible(false);
    ui->pushButton_32->setVisible(false);
    ui->pushButton_33->setVisible(false);
    ui->pushButton_34->setVisible(false);
    ui->pushButton_35->setVisible(false);
    ui->pushButton_36->setVisible(false);
    ui->pushButton_37->setVisible(false);
    ui->pushButton_38->setVisible(false);
    ui->pushButton_39->setVisible(false);
    ui->pushButton_40->setVisible(false);
    ui->pushButton_41->setVisible(false);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_10->setVisible(true);
    ui->pushButton_9->setVisible(true);
    ui->pushButton_22->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->horizontalSlider->setVisible(false);
    ui->horizontalSlider_2->setVisible(false);
    ui->horizontalSlider_3->setVisible(false);
    ui->horizontalSlider_4->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);
    ui->label_16->setVisible(false);
    ui->label_17->setVisible(false);
    ui->label_18->setVisible(false);
    ui->label_19->setVisible(false);
    ui->label_20->setVisible(false);
    ui->label_21->setVisible(false);
    ui->label_22->setVisible(false);
    ui->label_23->setVisible(false);
    ui->label_24->setVisible(false);
    ui->label_25->setVisible(false);
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->spinBox_2->setVisible(false);
    ui->spinBox_3->setVisible(false);
    ui->spinBox_4->setVisible(false);
    ui->spinBox_5->setVisible(false);
    ui->spinBox_6->setVisible(false);
    ui->spinBox_7->setVisible(false);
    ui->spinBox_8->setVisible(false);
    ui->spinBox_9->setVisible(false);
    ui->doubleSpinBox->setVisible(false);
    ui->verticalSlider->setVisible(false);
    ui->verticalSlider_2->setVisible(false);
    ui->verticalSlider_3->setVisible(false);
    ui->comboBox_2->setVisible(false);
    setMouseTracking(true);
    ui->graphicsView->installEventFilter(this);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged);
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged2);
    connect(ui->horizontalSlider_3, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged3);
    connect(ui->horizontalSlider_4, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged4);
    connect(ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::onVSliderValueChanged);
    connect(ui->verticalSlider_2, &QSlider::valueChanged, this, &MainWindow::onVSliderValueChanged2);
    connect(ui->verticalSlider_3, &QSlider::valueChanged, this, &MainWindow::onVSliderValueChanged3);
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_5_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.jpg *.png *.bmp *.jpeg)");
    if (fileName.isEmpty()) {
        return;
    }

    QImage image;
    if (!image.load(fileName)) {
        QMessageBox::critical(this, "Error", "Failed to load image!");
        return;
    }

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QGraphicsScene *graphic = new QGraphicsScene(this);

    QPixmap pixmap = QPixmap::fromImage(image.scaled(w, h, Qt::KeepAspectRatio));
    imageItem = graphic->addPixmap(pixmap);
    ui->graphicsView->setScene(graphic);

    currentImage = image;
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage grayImage = currentImage.copy();
    grayImage = grayImage.convertToFormat(QImage::Format_Grayscale8);

    int threshold = 128;
    for (int y = 0; y < grayImage.height(); ++y) {
        for (int x = 0; x < grayImage.width(); ++x) {
            QRgb pixel = grayImage.pixel(x, y);
            int gray = qGray(pixel);
            grayImage.setPixel(x, y, qRgb(gray > threshold ? 255 : 0, gray > threshold ? 255 : 0, gray > threshold ? 255 : 0));
        }
    }

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(grayImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = grayImage;
}

void MainWindow::on_pushButton_17_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()){
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QString selectedFormat = ui->comboBox->currentText();
    if(selectedFormat.isEmpty()){
        selectedFormat = "jpg";
    }
    QString filename = ui->lineEdit->text();
    if(filename.isEmpty()){
        filename = QFileDialog::getSaveFileName(this, "Save Image", "", tr("Image Files (*.jpg *.png *.bmp *.jpeg)"));
        if (filename.isEmpty()){
            return;
        }
    }
    QString extension = QFileInfo(filename).suffix().toLower();
    if (selectedFormat != extension && QMessageBox::question(this, "Warning", "The selected format does not match the filename extension. Do you want to proceed?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;
    QString saveLocation = QFileDialog::getExistingDirectory(this, "Save Image", "");
    QString fullPath = saveLocation.isEmpty() ? filename : QDir(saveLocation).filePath(filename + "." + selectedFormat.toLower());

    bool success = false;
    if (selectedFormat == "jpg"){
        success = currentImage.save(fullPath, "jpg");
    } else if (selectedFormat == "png"){
        success = currentImage.save(fullPath, "png");
    } else if (selectedFormat == "jpeg"){
        success = currentImage.save(fullPath, "jpeg");
    } else if (selectedFormat == "bmp"){
        success = currentImage.save(fullPath, "bmp");
    }
    if (success){
        QMessageBox::information(this, "Success", "Image Saved");
    } else{
        QMessageBox::critical(this, "Error", "Failed to save!!");
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage invertedImage = currentImage.copy();
    for (int y = 0; y < invertedImage.height(); ++y) {
        for (int x = 0; x < invertedImage.width(); ++x) {
            QRgb pixel = invertedImage.pixel(x, y);
            int red = 255 - qRed(pixel);
            int green = 255 - qGreen(pixel);
            int blue = 255 - qBlue(pixel);
            invertedImage.setPixel(x, y, qRgb(red, green, blue));
        }
    }

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(invertedImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = invertedImage;
}


void MainWindow::on_pushButton_6_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    ui->pushButton_19->setVisible(true);
    ui->pushButton_24->setVisible(true);
    ui->pushButton_6->setVisible(false);
}


void MainWindow::on_pushButton_19_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage flippedHorizontally = currentImage.copy();
    for (int i = 0; i < flippedHorizontally.width()/2; i++){
        for (int j = 0; j < flippedHorizontally.height(); j++){
            QRgb pixel = flippedHorizontally.pixel(i, j);
            QRgb temp = flippedHorizontally.pixel(flippedHorizontally.width() - 1 - i, j);
            flippedHorizontally.setPixel(flippedHorizontally.width() - 1 - i, j, pixel);
            flippedHorizontally.setPixel(i, j, temp);
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(flippedHorizontally.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = flippedHorizontally;

    ui->pushButton_24->setVisible(false);
    ui->pushButton_19->setVisible(false);
    ui->pushButton_6->setVisible(true);
}

void MainWindow::on_pushButton_24_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage flippedVertically = currentImage.copy();
    for (int i = 0; i < flippedVertically.width(); i++){
        for (int j = 0; j < flippedVertically.height()/2; j++){
            QRgb pixel = flippedVertically.pixel(i, j);
            QRgb temp = flippedVertically.pixel(i, flippedVertically.height() - 1 - j);
            flippedVertically.setPixel(i, flippedVertically.height() - 1 - j, pixel);
            flippedVertically.setPixel(i, j, temp);
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(flippedVertically.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = flippedVertically;

    ui->pushButton_24->setVisible(false);
    ui->pushButton_19->setVisible(false);
    ui->pushButton_6->setVisible(true);
}

void MainWindow::on_pushButton_7_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_25->setVisible(true);
    ui->pushButton_26->setVisible(true);
    ui->pushButton_27->setVisible(true);
    ui->pushButton_7->setVisible(false);
}



void MainWindow::on_pushButton_25_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage rotated90(currentImage.height(), currentImage.width(), currentImage.format());
    for (int i = 0; i  < rotated90.width(); ++i ) {
        for (int j = 0; j < rotated90.height(); ++j){
            QRgb pixel = currentImage.pixel(j, i);
            rotated90.setPixel(rotated90.width() - 1 - i, j, pixel);
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(rotated90.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = rotated90;

    ui->pushButton_25->setVisible(false);
    ui->pushButton_26->setVisible(false);
    ui->pushButton_27->setVisible(false);
    ui->pushButton_7->setVisible(true);
}


void MainWindow::on_pushButton_26_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage rotated180(currentImage.width(), currentImage.height(), currentImage.format());
    for (int i = 0; i  < rotated180.width(); ++i ) {
        for (int j = 0; j < rotated180.height(); ++j){
            QRgb pixel = currentImage.pixel(i, j);
            rotated180.setPixel(rotated180.width() - 1 - i, rotated180.height() - 1 - j, pixel);
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(rotated180.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = rotated180;

    ui->pushButton_25->setVisible(false);
    ui->pushButton_26->setVisible(false);
    ui->pushButton_27->setVisible(false);
    ui->pushButton_7->setVisible(true);
}


void MainWindow::on_pushButton_27_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage rotated270(currentImage.height(), currentImage.width(), currentImage.format());
    for (int i = 0; i < rotated270.width(); ++i) {
        for (int j = 0; j < rotated270.height(); ++j){
            QRgb pixel = currentImage.pixel(j, i);
            rotated270.setPixel(i, rotated270.height() - 1 - j, pixel);
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(rotated270.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = rotated270;

    ui->pushButton_25->setVisible(false);
    ui->pushButton_26->setVisible(false);
    ui->pushButton_27->setVisible(false);
    ui->pushButton_7->setVisible(true);
}


void MainWindow::on_pushButton_11_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_11->setVisible(false);
    ui->pushButton_39->setVisible(true);
    ui->label_24->setVisible(true);
    ui->label_25->setVisible(true);
    ui->label_26->setVisible(true);
    ui->label_27->setVisible(true);
    ui->spinBox_6->setVisible(true);
    ui->spinBox_7->setVisible(true);
    ui->spinBox_8->setVisible(true);
    ui->spinBox_9->setVisible(true);
}

void MainWindow::on_pushButton_23_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage sunLighted = currentImage.copy();
    for (int i = 0; i  < sunLighted.width(); ++i ) {
        for (int j = 0; j < sunLighted.height(); ++j){
            QRgb pixel = currentImage.pixel(i, j);
            int red = std::min(255, qRed(pixel) + 25);
            int green = std::min(255, qGreen(pixel)+35);
            int blue = std::max(0, qBlue(pixel)-25);
            sunLighted.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(sunLighted.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = sunLighted;
}


void MainWindow::on_pushButton_14_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    QImage purplizer = currentImage.copy();
    for (int i = 0; i  < purplizer.width(); ++i ) {
        for (int j = 0; j < purplizer.height(); ++j){
            QRgb pixel = currentImage.pixel(i, j);
            int red = std::min(255, qRed(pixel) + 20);
            int green = std::max(0, qGreen(pixel) - 50);
            int blue = std::min(255, qBlue(pixel) + 20);
            purplizer.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(purplizer.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = purplizer;
}


void MainWindow::on_pushButton_10_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_28->setVisible(true);
    ui->pushButton_29->setVisible(true);
    ui->pushButton_10->setVisible(false);
    ui->horizontalSlider->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
}

void MainWindow::onSliderValueChanged(int value) {
    factor = value/100.0;
}

void MainWindow::on_pushButton_29_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QImage darkenImage = currentImage.copy();
    isDarkenEnabled = true;
    for (int i = 0; i  < darkenImage.width(); ++i ) {
        for (int j = 0; j < darkenImage.height(); ++j){
            QRgb pixel = currentImage.pixel(i, j);
            int red = factor * qRed(pixel);
            int green = factor * qGreen(pixel);
            int blue = factor * qBlue(pixel);
            darkenImage.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(darkenImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = darkenImage;
    ui->pushButton_28->setVisible(false);
    ui->pushButton_29->setVisible(false);
    ui->pushButton_10->setVisible(true);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->horizontalSlider->setVisible(false);
    isDarkenEnabled = false;
}

void MainWindow::on_pushButton_28_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QImage lightenImage = currentImage.copy();
    isDarkenEnabled = true;
    for (int i = 0; i  < lightenImage.width(); ++i ) {
        for (int j = 0; j < lightenImage.height(); ++j){
            QRgb pixel = currentImage.pixel(i, j);
            int red = std::min(255, (int)(qRed(pixel) + factor * (255 - qRed(pixel))));
            int green = std::min(255, (int)(qGreen(pixel) + factor * (255 - qGreen(pixel))));
            int blue = std::min(255, (int)(qBlue(pixel) + factor * (255 - qBlue(pixel))));
            lightenImage.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(lightenImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = lightenImage;
    ui->pushButton_28->setVisible(false);
    ui->pushButton_29->setVisible(false);
    ui->pushButton_10->setVisible(true);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->horizontalSlider->setVisible(false);
    isDarkenEnabled = false;
}

void MainWindow::on_pushButton_12_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QImage edges = currentImage.copy();
    int sobHor[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobVer[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 1; y < currentImage.height() - 1; ++y ) {
        for (int x = 1; x < currentImage.width() - 1; ++x) {
            int gx = 0, gy = 0;
            for (int dy = -1; dy  <= 1; ++dy ) {
                for (int dx = -1; dx  <= 1; ++dx ) {
                    gx += sobHor[dy + 1][dx + 1] * qGray(currentImage.pixel(x + dx, y + dy));
                    gy += sobVer[dy + 1][dx + 1] * qGray(currentImage.pixel(x + dx, y + dy));
                }
            }
            int mag = qBound(0, (int)qSqrt(gx*gx + gy*gy), 255);
            edges.setPixel(x, y, qRgb(mag, mag, mag));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(edges.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = edges;
}


void MainWindow::on_pushButton_8_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_30->setVisible(true);
    ui->horizontalSlider_2->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->pushButton_8->setVisible(false);
}

void MainWindow::onSliderValueChanged2(int value){
    kernelSize = value;
}

void MainWindow::onSliderValueChanged3(int value){
    glitchFactor = value;
}

void MainWindow::onVSliderValueChanged(int value){
    dRed = value;
}

void MainWindow::onVSliderValueChanged2(int value){
    dGreen = value;
}

void MainWindow::onVSliderValueChanged3(int value){
    dBlue = value;
}

void MainWindow::on_pushButton_30_clicked()
{
    int kernelRadius = kernelSize/2;
    QImage tempImage = currentImage.copy();
    for (int i = kernelRadius; i < currentImage.width() - kernelRadius; ++i) {
        for (int j = kernelRadius; j < currentImage.height() - kernelRadius; ++j){
            int rSum = 0, gSum = 0, bSum = 0, nNeighbors = 0;
            for (int x = -kernelRadius; x <= kernelRadius; ++x) {
                for (int y = -kernelRadius; y <= kernelRadius; ++y) {
                    int xNeighbor = x + i;
                    int yNeighbor = y + j;
                    if (xNeighbor >= 0 && xNeighbor < currentImage.width() && yNeighbor >= 0 && yNeighbor < currentImage.height()){
                        rSum += qRed(currentImage.pixel(xNeighbor, yNeighbor));
                        gSum += qGreen(currentImage.pixel(xNeighbor, yNeighbor));
                        bSum += qBlue(currentImage.pixel(xNeighbor, yNeighbor));
                        nNeighbors++;
                    }
                }
            }
            int rAvg, bAvg, gAvg;
            if (nNeighbors > 0){
                rAvg = rSum/nNeighbors;
                gAvg = gSum/nNeighbors;
                bAvg = bSum/nNeighbors;
            }
            else{
                rAvg = qRed(currentImage.pixel(i, j));
                gAvg = qGreen(currentImage.pixel(i, j));
                bAvg = qBlue(currentImage.pixel(i, j));
            }
            tempImage.setPixel(i, j, qRgb(rAvg, gAvg, bAvg));
        }
    }
    QImage blurredImage(tempImage.width() - kernelRadius * 2, tempImage.height() - kernelRadius * 2, tempImage.format());
    for (int i = 0; i < blurredImage.width(); ++i) {
        for (int j = 0; j < blurredImage.height(); ++j) {
            QRgb pixel = tempImage.pixel(i + kernelRadius, j + kernelRadius);
            blurredImage.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(blurredImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = blurredImage;
    ui->pushButton_30->setVisible(false);
    ui->horizontalSlider_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->pushButton_8->setVisible(true);
}

void MainWindow::on_pushButton_21_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QImage oilPainted = currentImage.copy();
    for (int j = 2; j < currentImage.height() - 2; ++j){
        for (int i = 2; i < currentImage.width() - 2; ++i) {
            long intensityCount[256] = {0}, SumR[256] = {0}, SumG[256] = {0}, SumB[256] = {0};
            for (int x = -2; x  <= 2; ++x ) {
                for (int y = -2; y <= 2; ++y) {
                    int r = qRed(currentImage.pixel(x + i, y +j));
                    int g = qGreen(currentImage.pixel(x + i, y + j));
                    int b = qBlue(currentImage.pixel(x + i, j + y));
                    int nCurrentIntensity = ( (r + g + b) / 3.0 * 10) / 255;
                    if (nCurrentIntensity > 255){
                        nCurrentIntensity = 255;
                    }
                    int k = nCurrentIntensity;
                    intensityCount[k]++;
                    SumR[k] = SumR[k] + r;
                    SumB[k] = SumB[k] + b;
                    SumG[k] = SumG[k] + g;
                }
            }
            int nCurMax = 0;
            int nMaxIndex = 0;
            for (int nI = 0; nI < 256; nI++) {
                if (intensityCount[nI] > nCurMax){
                    nCurMax = intensityCount[nI];
                    nMaxIndex = nI;
                }
            }
            if (nCurMax == 0){
                int redOriginal = qRed(currentImage.pixel(i, j));
                int greenOriginal = qGreen(currentImage.pixel(i, j));
                int blueOriginal = qBlue(currentImage.pixel(i, j));
                int avg = (redOriginal + greenOriginal + blueOriginal)/3;
                oilPainted.setPixel(i, j, qRgb(avg, avg, avg));
            }
            else{
                int reeed = SumR[nMaxIndex]/nCurMax;
                int greeeen = SumG[nMaxIndex]/nCurMax;
                int bluuee = SumB[nMaxIndex]/nCurMax;
                oilPainted.setPixel(i, j, qRgb(reeed, greeeen, bluuee));
            }
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(oilPainted.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = oilPainted;
}


void MainWindow::on_pushButton_9_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_9->setVisible(false);
    ui->pushButton_31->setVisible(true);
    ui->pushButton_32->setVisible(true);
}


void MainWindow::on_pushButton_31_clicked()
{
    ui->pushButton_33->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->spinBox->setVisible(true);
    ui->spinBox_2->setVisible(true);
    ui->pushButton_34->setVisible(false);
    ui->doubleSpinBox->setVisible(false);
}



void MainWindow::on_pushButton_32_clicked()
{
    ui->pushButton_33->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->spinBox_2->setVisible(false);
    ui->pushButton_34->setVisible(true);
    ui->doubleSpinBox->setVisible(true);
}


void MainWindow::on_pushButton_33_clicked()
{
    int width = ui->spinBox->text().toInt();
    int height = ui->spinBox->text().toInt();
    QImage resizedImage = currentImage.copy();
    resizedImage = resizedImage.scaled(width, height);

    QPixmap newPixmap = QPixmap::fromImage(resizedImage);

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = resizedImage;
    ui->pushButton_33->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->spinBox_2->setVisible(false);
    ui->pushButton_34->setVisible(false);
    ui->doubleSpinBox->setVisible(false);
    ui->pushButton_9->setVisible(true);
    ui->pushButton_31->setVisible(false);
    ui->pushButton_32->setVisible(false);
}


void MainWindow::on_pushButton_34_clicked()
{
    double ratio = ui->doubleSpinBox->text().toDouble();
    QImage resizedImage = currentImage.copy();
    int newHeight = qMax(1, (int)(ratio*currentImage.height()));
    int newWidth = qMax(1, (int)(ratio*currentImage.width()));
    resizedImage = resizedImage.scaled(newWidth, newHeight);

    QPixmap newPixmap = QPixmap::fromImage(resizedImage);

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = resizedImage;

    ui->pushButton_34->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->spinBox_2->setVisible(false);
    ui->pushButton_33->setVisible(false);
    ui->doubleSpinBox->setVisible(false);
    ui->pushButton_9->setVisible(true);
    ui->pushButton_31->setVisible(false);
    ui->pushButton_32->setVisible(false);
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QImage grayscaleImage = currentImage.copy();
    for (int x = 0; x < currentImage.width(); ++x) {
        for (int y = 0; y < currentImage.height(); ++y) {
            QRgb pixel = currentImage.pixel(x, y);
            int gray = (qRed(pixel) + qGreen(pixel) + qBlue(pixel))/3;
            grayscaleImage.setPixel(x, y, qRgb(gray, gray, gray));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(grayscaleImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = grayscaleImage;
}


void MainWindow::on_pushButton_20_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    QImage infraredImage = currentImage.copy();
    for (int x = 0; x < currentImage.width(); ++x) {
        for (int y = 0; y < currentImage.height(); ++y) {
            QRgb pixel = currentImage.pixel(x, y);
            int r = 255;
            int g = 255 - qGreen(pixel);
            int b = 255 - qBlue(pixel);
            infraredImage.setPixel(x, y, qRgb(r, g, b));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(infraredImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = infraredImage;
}


void MainWindow::on_pushButton_18_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_35->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_11->setVisible(true);
    ui->label_12->setVisible(true);
    ui->label_13->setVisible(true);
    ui->label_14->setVisible(true);
    ui->label_15->setVisible(true);
    ui->label_16->setVisible(true);
    ui->verticalSlider->setVisible(true);
    ui->verticalSlider_2->setVisible(true);
    ui->verticalSlider_3->setVisible(true);
}


void MainWindow::on_pushButton_35_clicked()
{
    QImage balancedImage = currentImage.copy();
    for (int i = 0; i < currentImage.width(); ++i) {
        for (int j = 0; j < currentImage.height(); ++j) {
            QRgb pixel = currentImage.pixel(i, j);
            int red = qMax(0, qMin(255, qRed(pixel) + dRed));
            int blue = qMax(0, qMin(255, qBlue(pixel) + dBlue));
            int green = qMax(0, qMin(255, qGreen(pixel) + dGreen));
            balancedImage.setPixel(i, j, qRgb(red, green, blue));
        }
    }

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(balancedImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = balancedImage;


    ui->pushButton_35->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);
    ui->label_16->setVisible(false);
    ui->verticalSlider->setVisible(false);
    ui->verticalSlider_2->setVisible(false);
    ui->verticalSlider_3->setVisible(false);
}


void MainWindow::on_pushButton_15_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_15->setVisible(false);
    ui->pushButton_36->setVisible(true);
    ui->label_17->setVisible(true);
    ui->label_18->setVisible(true);
    ui->horizontalSlider_3->setVisible(true);

}


void MainWindow::on_pushButton_36_clicked()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, currentImage.width() - 1);

    QImage glitchedImage = currentImage.copy();
    for (int i = 0; i < currentImage.width(); ++i) {
        for (int j = 0; j < currentImage.height(); ++j) {
            int shiftX = floor(glitchFactor/100.0 * distribution(generator));
            int newX = (i + shiftX)%currentImage.width();
            QRgb pixel = currentImage.pixel(newX, j);
            glitchedImage.setPixel(i , j, pixel);
        }
    }

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(glitchedImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = glitchedImage;

    ui->pushButton_15->setVisible(true);
    ui->pushButton_36->setVisible(false);
    ui->label_17->setVisible(false);
    ui->label_18->setVisible(false);
    ui->horizontalSlider_3->setVisible(false);
}


void MainWindow::on_pushButton_13_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_13->setVisible(false);
    ui->pushButton_37->setVisible(true);
    ui->label_19->setVisible(true);
    ui->label_20->setVisible(true);
    ui->label_21->setVisible(true);
    ui->spinBox_3->setVisible(true);
    ui->spinBox_4->setVisible(true);
    ui->spinBox_5->setVisible(true);
    ui->comboBox_2->setVisible(true);
}


void MainWindow::on_pushButton_37_clicked()
{
    int red = ui->spinBox_3->text().toInt();
    int green = ui->spinBox_4->text().toInt();
    int blue = ui->spinBox_5->text().toInt();
    QString type = ui->comboBox_2->currentText();
    int frame_size = 0.03*qMax(currentImage.width(), currentImage.height());
    int width = currentImage.width()+2*frame_size;
    int height = currentImage.height()+2*frame_size;
    QImage framed(width, height, QImage::Format_RGB32);
    if (type == "Basic"){
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                if (i < frame_size || j < frame_size || i >= currentImage.width() + frame_size ||
                    j >= currentImage.width() + frame_size){
                    framed.setPixel(i, j, qRgb(red, green, blue));
                }
                else{
                    QRgb pixel = currentImage.pixel(i - frame_size, j - frame_size);
                    framed.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
                }
            }
        }
    }
    if (type == "Gradient"){
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                if (i < frame_size || j < frame_size || i >= currentImage.width() + frame_size || j >= currentImage.height() + frame_size) {
                    int dist = qMin(qMin(i, framed.width()-i), qMin(j,framed.height()-j));
                    int r = red - (red * dist)/frame_size;
                    int g = green - (green * dist)/frame_size;
                    int b = blue - (blue * dist)/frame_size;
                    framed.setPixel(i, j, qRgb(r, g, b));
                }else{
                    QRgb pixel = currentImage.pixel(i - frame_size, j - frame_size);
                    framed.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
                }
            }
        }
    }
    if (type == "Checkerboard"){
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                int distToFrameX = qMin(i, framed.width() - 1 - i);
                int distToFrameY = qMin(j, framed.height() - 1 - j);

                bool insideFrame = (distToFrameX < frame_size || distToFrameY < frame_size);
                bool isCheckerboard = ((distToFrameX / frame_size) % 2 == 0 && (distToFrameY / frame_size) % 2 == 0) ||
                                      ((distToFrameX / frame_size) % 2 != 0 && (distToFrameY / frame_size) % 2 != 0);

                if (insideFrame && isCheckerboard){
                    framed.setPixel(i, j, qRgb(255, 255, 255));
                }else if (insideFrame && !isCheckerboard){
                    framed.setPixel(i, j, qRgb(0, 0, 0));
                }else{
                    int x0 = i - frame_size;
                    int y0 = j - frame_size;
                    if(x0 >= 0 && x0 < currentImage.width() && y0 >= 0 && y0 < currentImage.height()){
                        QRgb pixel = currentImage.pixel(x0, y0);
                        framed.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
                    }
                }
            }
        }
    }
    if (type == "Lines"){
        int lineSize = 5;
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                if(i < frame_size || j < frame_size || i >= currentImage.width() + frame_size || j >= currentImage.height() + frame_size){
                    if((i+j)%(2 * lineSize) < lineSize){
                        framed.setPixel(i, j, qRgb(red, green, blue));
                    }
                    else{
                        framed.setPixel(i, j, qRgb(128, 128, 128));
                    }
                }else{
                    int x0 = i - frame_size;
                    int y0 = j - frame_size;
                    QRgb pixel = currentImage.pixel(x0, y0);
                    int r = qRed(pixel);
                    int g = qGreen(pixel);
                    int b = qBlue(pixel);
                    framed.setPixel(i, j, qRgb(r, g, b));
                }
            }
        }
    }
    if(type == "Loops"){
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                if (i < frame_size || j < frame_size || i >= currentImage.width() + frame_size || j >= currentImage.width() + frame_size){
                    int centerX = frame_size + currentImage.width()/2;
                    int centerY = frame_size + currentImage.height()/2;
                    double distance = std::sqrt(std::pow(i-centerX, 2)+ std::pow(j - centerY, 2));
                    double ang = distance/frame_size * 10.0;
                    double brightness = 1.0-std::abs(std::sin(ang));
                    int r = red * brightness;
                    int g = green * brightness;
                    int b = blue * brightness;
                    framed.setPixel(i, j, qRgb(r, g, b));
                }
                else{
                    QRgb pixel = currentImage.pixel(i - frame_size, j - frame_size);
                    framed.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
                }
            }
        }
    }
    if (type == "Circles"){
        int centerX = framed.width()/2;
        int centerY = framed.height()/2;
        int circleSpacing = 30;
        int circleThickness = 5;
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                bool insideFrame = (i >= frame_size && i < framed.width() - frame_size &&
                                    j >= frame_size && j < framed.height() - frame_size);
                if (!insideFrame) {
                    int distToCenter = sqrt((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY));
                    bool isPattern = (distToCenter % circleSpacing < circleThickness);
                    if (isPattern){
                        framed.setPixel(i, j, qRgb(red, green, blue));
                    }
                    else{
                        framed.setPixel(i, j, qRgb(255, 255, 255));
                    }
                }
                else{
                    int x0 = i - frame_size;
                    int y0 = j - frame_size;
                    if (x0 >= 0 && x0 < currentImage.width() && y0 >= 0 && y0 < currentImage.height()) {
                        QRgb pixel = currentImage.pixel(x0, y0);
                        framed.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
                    }
                }
            }
        }
    }
    if(type == "Diagonals"){
        for (int i = 0; i < framed.width(); ++i) {
            for (int j = 0; j < framed.height(); ++j) {
                int distToFrameX = qMin(i, framed.width() - 1 - i);
                int distToFrameY = qMin(j, framed.height() - 1 - j);

                bool insideFrame = (distToFrameX < frame_size || distToFrameY < frame_size);

                int rbrightness = red - ((distToFrameX + distToFrameY) * red) / (2 * frame_size);
                int gbrightness = green - ((distToFrameX + distToFrameY) * green) / (2 * frame_size);
                int bbrightness = blue - ((distToFrameX + distToFrameY) * blue) / (2 * frame_size);

                if (insideFrame) {
                    framed.setPixel(i, j, qRgb(rbrightness, gbrightness, bbrightness));
                }else{
                    int x0 = qAbs(i - frame_size);
                    int y0 = qAbs(j - frame_size);
                    QRgb pixel = currentImage.pixel(x0, y0);
                    framed.setPixel(i, j, qRgb(qRed(pixel), qGreen(pixel), qBlue(pixel)));
                }
            }
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(framed.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = framed;

    ui->pushButton_13->setVisible(true);
    ui->pushButton_37->setVisible(false);
    ui->label_19->setVisible(false);
    ui->label_20->setVisible(false);
    ui->label_21->setVisible(false);
    ui->spinBox_3->setVisible(false);
    ui->spinBox_4->setVisible(false);
    ui->spinBox_5->setVisible(false);
    ui->comboBox_2->setVisible(false);
}

void MainWindow::on_pushButton_16_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    for (int y = 0; y < currentImage.height(); ++y) {
        for (int x = 0; x < currentImage.width(); ++x) {
            if (y%2 == 0){
                int offset = std::rand()%30;
                int red = qMin(255, qRed(currentImage.pixel(x, y)) + offset);
                int green = qMin(255, qGreen(currentImage.pixel(x, y)) + offset);
                int blue = qMin(255, qBlue(currentImage.pixel(x, y)) + offset);
                currentImage.setPixel(x, y, qRgb(red, green, blue));
            }
        }
    }
    QImage noisedImage = currentImage.copy();
    std::srand(static_cast<unsigned int>(time(nullptr)));
    int noiseLevel = 20;
    for (int i = 0; i < currentImage.width(); ++i) {
        for (int j = 0; j < currentImage.height(); ++j) {
            int randomNoise = std::rand()%(noiseLevel * 2 + 1) - noiseLevel;
            QRgb pixel = currentImage.pixel(i, j);
            int RnewValue = qMax(0, qMin(255, static_cast<int>(qRed(pixel)) + randomNoise));
            int GnewValue = qMax(0, qMin(255, static_cast<int>(qGreen(pixel)) + randomNoise));
            int BnewValue = qMax(0, qMin(255, static_cast<int>(qBlue(pixel)) + randomNoise));
            noisedImage.setPixel(i, j, qRgb(RnewValue, GnewValue, BnewValue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(noisedImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = noisedImage;
}


void MainWindow::onSliderValueChanged4(int value){
    angle = value;
}

void MainWindow::on_pushButton_22_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }

    ui->label_22->setVisible(true);
    ui->label_23->setVisible(true);
    ui->pushButton_38->setVisible(true);
    ui->pushButton_22->setVisible(false);
    ui->horizontalSlider_4->setVisible(true);
}


void MainWindow::on_pushButton_38_clicked()
{
    if(angle == 0){
        return;
    }
    double radians = angle * M_PI/180.0;
    double max_required_width = currentImage.width() + std::abs(currentImage.height() * tan(radians));
    int newWidth = static_cast<int>(qMin(currentImage.width() + std::abs(currentImage.height() * tan(radians)), max_required_width));
    int newHeight = currentImage.height();
    QImage skewedImage(newWidth, newHeight, QImage::Format_RGB32);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            double srcX = 0;
            if (angle > 0){
                srcX = x - (newWidth)/2.0;
            }
            else if (angle < 0){
                srcX = x - (newWidth - 2*currentImage.height())/2.0;
            }
            double srcY = y;
            double srcXimage = srcX - srcY * tan(-radians);
            double srcYimage = srcY;
            if(srcXimage >= 0 && srcXimage < currentImage.width() && srcYimage >= 0 && srcYimage < currentImage.height()){
                int x0 = static_cast<int>(srcXimage);
                int y0 = static_cast<int>(srcYimage);
                double dx = srcXimage - x0;
                double dy = srcYimage - y0;
                QRgb pixel00 = currentImage.pixel(x0, y0);
                QRgb pixel01 = currentImage.pixel(x0, y0+1);
                QRgb pixel10 = currentImage.pixel(x0+1, y0);
                QRgb pixel11 = currentImage.pixel(x0+1, y0+1);
                unsigned char Rv00 = qRed(pixel00), Gv00 = qGreen(pixel00), Bv00 = qBlue(pixel00);
                unsigned char Rv01 = qRed(pixel01), Gv01 = qGreen(pixel01), Bv01 = qBlue(pixel01);
                unsigned char Rv10 = qRed(pixel10), Gv10 = qGreen(pixel10), Bv10 = qBlue(pixel10);
                unsigned char Rv11 = qRed(pixel11), Gv11 = qGreen(pixel11), Bv11 = qBlue(pixel11);

                unsigned char RinterpolatedValue = static_cast<unsigned char>((1-dx) * (1-dy) * Rv00 + dx * (1-dy) * Rv10 + (1-dx) * dy * Rv01 + dx * dy * Rv11);
                unsigned char GinterpolatedValue = static_cast<unsigned char>((1-dx) * (1-dy) * Gv00 + dx * (1-dy) * Gv10 + (1-dx) * dy * Gv01 + dx * dy * Gv11);
                unsigned char BinterpolatedValue = static_cast<unsigned char>((1-dx) * (1-dy) * Bv00 + dx * (1-dy) * Bv10 + (1-dx) * dy * Bv01 + dx * dy * Bv11);

                skewedImage.setPixel(x, y, qRgb(RinterpolatedValue, GinterpolatedValue, BinterpolatedValue));
            }
            else{
                skewedImage.setPixel(x, y, qRgb(255, 255, 255));
            }
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(skewedImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = skewedImage;
    ui->label_22->setVisible(false);
    ui->label_23->setVisible(false);
    ui->pushButton_38->setVisible(false);
    ui->pushButton_22->setVisible(true);
    ui->horizontalSlider_4->setVisible(false);
}



void MainWindow::on_pushButton_39_clicked()
{
    int x = ui->spinBox_6->text().toInt();
    int y = ui->spinBox_7->text().toInt();
    int width = ui->spinBox_8->text().toInt();
    int height = ui->spinBox_9->text().toInt();

    if(x < 0 || y < 0 || x >= currentImage.width() || y >= currentImage.height() || width <= 0 || height <= 0 || width + x > currentImage.width() || height + y > currentImage.height()){
        QMessageBox::information(this, "Information", "Please select valid area to crop.");
        return;
    }
    QImage croppedImage = currentImage.copy(x, y, width, height);
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(croppedImage.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = croppedImage;

    ui->pushButton_11->setVisible(true);
    ui->pushButton_39->setVisible(false);
    ui->label_24->setVisible(false);
    ui->label_25->setVisible(false);
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    ui->spinBox_6->setVisible(false);
    ui->spinBox_7->setVisible(false);
    ui->spinBox_8->setVisible(false);
    ui->spinBox_9->setVisible(false);
}


void MainWindow::on_pushButton_5_clicked()
{
    if (!ui->graphicsView || ui->graphicsView->items().isEmpty()) {
        QMessageBox::information(this, "Information", "Please load an image first.");
        return;
    }
    ui->pushButton_40->setVisible(true);
    ui->pushButton_41->setVisible(true);
    ui->pushButton_5->setVisible(false);

    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.jpg *.png *.bmp *.jpeg)");
    if(fileName.isEmpty()){
        return;
    }

    QImage loadedImage;
    if (!loadedImage.load(fileName)) {
        QMessageBox::critical(this, "Error", "Failed to load image!");
        return;
    }
    image2 = loadedImage;
}


void MainWindow::on_pushButton_40_clicked()
{
    int max_width = qMax(currentImage.width(), image2.width());
    int max_height = qMax(currentImage.height(), image2.height());
    currentImage = currentImage.scaled(max_width, max_height, Qt::KeepAspectRatio);
    image2 = image2.scaled(max_width, max_height, Qt::KeepAspectRatio);
    QImage merged(max_width, max_height, QImage::Format_RGB32);

    for (int i = 0; i < max_width; ++i) {
        for (int j = 0; j < max_height; ++j) {
            QRgb pixel1 = currentImage.pixel(i, j);
            QRgb pixel2 = image2.pixel(i, j);
            int red = (qRed(pixel1) + qRed(pixel2))/2;
            int green = (qGreen(pixel1) + qGreen(pixel2))/2;
            int blue = (qBlue(pixel1) + qBlue(pixel2))/2;
            merged.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(merged.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = merged;
    ui->pushButton_40->setVisible(false);
    ui->pushButton_41->setVisible(false);
    ui->pushButton_5->setVisible(true);
}

void MainWindow::on_pushButton_41_clicked()
{
    int common_width = qMin(currentImage.width(), image2.width());
    int common_height = qMin(currentImage.height(), image2.height());
    QImage merged(common_width, common_height, QImage::Format_RGB32);
    for (int i = 0; i < common_width; ++i) {
        for (int j = 0; j < common_height; ++j) {
            QRgb pixel1 = currentImage.pixel((currentImage.width()/2)-(common_width/2)+i, (currentImage.height()/2)-(common_height/2)+j);
            QRgb pixel2 = image2.pixel((image2.width()/2)-(common_width/2)+i, (image2.height()/2)-(common_height/2)+j);
            int red = (qRed(pixel1)+qRed(pixel2))/2;
            int green = (qGreen(pixel1)+qGreen(pixel2))/2;
            int blue = (qBlue(pixel1)+qBlue(pixel2))/2;
            merged.setPixel(i, j, qRgb(red, green, blue));
        }
    }
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    QPixmap newPixmap = QPixmap::fromImage(merged.scaled(w, h, Qt::KeepAspectRatio));

    imageItem->setPixmap(newPixmap);

    QGraphicsScene *graphic = ui->graphicsView->scene();
    graphic->setSceneRect(newPixmap.rect());
    currentImage = merged;
    ui->pushButton_40->setVisible(false);
    ui->pushButton_41->setVisible(false);
    ui->pushButton_5->setVisible(true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
