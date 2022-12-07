#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "my_canvas.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->canvas, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Mouse_Pressed()
{
    //ui->lblMouse_Current_Event->setText("Mouse Pressed");
    QPixmap pix(ui->canvas->size());
    pix.fill(Qt::transparent);
    QPainter paint(&pix);
    if(isSingleLine){
        if(ui->canvas->x_coords.length() == 1){
            paint.drawPoint(ui->canvas->x_coords[0], ui->canvas->y_coords[0]);
        } else if (ui->canvas->x_coords.length() > 1){
            paint.drawLine(ui->canvas->x_coords[0], ui->canvas->y_coords[0], ui->canvas->x_coords[1], ui->canvas->y_coords[1]);
        }
        ui->canvas->setPixmap(pix);
    } else {
        if(ui->canvas->x_coords.length() == 1){
            paint.drawPoint(ui->canvas->x_coords[0], ui->canvas->y_coords[0]);
            ui->canvas->setPixmap(pix);
        } else if (ui->canvas->x_coords.length() > 1){
            for(int i = 0; i < round(ui->canvas->x_coords.length()) - 1; i+=2){ //i++ kalo mau nyambung dari setiap ujungnya
                paint.drawLine(ui->canvas->x_coords[i], ui->canvas->y_coords[i], ui->canvas->x_coords[i+1], ui->canvas->y_coords[i+1]);
                if(ui->canvas->x_coords.length() % 2 == 0){
                    //int n_line = ui->canvas->x_coords.length() / 2;
                    for (int j = 0; j < ui->canvas->x_coords.length() / 2; j++){
                        for (int k = j; k < ui->canvas->x_coords.length() / 2; k++){
                            // int pos = j * 4;
                            if(k != j){
                                std::pdd A = std::make_pair(ui->canvas->x_coords[2*j], ui->canvas->y_coords[2*j]);
                                std::pdd B = std::make_pair(ui->canvas->x_coords[2*j + 1], ui->canvas->y_coords[2*j + 1]);
                                std::pdd C = std::make_pair(ui->canvas->x_coords[2*k], ui->canvas->y_coords[2*k]);
                                std::pdd D = std::make_pair(ui->canvas->x_coords[2*k + 1], ui->canvas->y_coords[2*k + 1]);
                                std::pdd intersection = lineIntersection(A, B, C, D);
                                if(intersection.first == INT_MAX && intersection.second == INT_MAX){
                                    QTextStream(stdout) << "Parallel" << Qt::endl;
                                } else {
                                    paint.setBrush(Qt::red);
                                    paint.drawEllipse(intersection.first-2, intersection.second-2, 4, 4);
                                    // QTextStream(stdout) << "(" << intersection.first << "," << intersection.second << ")" << Qt::endl;
                                    // QTextStream(stdout) << fact(n_line) / (fact(2) * fact(n_line - 2)) << Qt::endl;
                                }
                            }
                        }
                    }
//                    for (int j = 0; j < ui->canvas->x_coords.length() / 4; j++){
//                        int pos = j * 4;
//                        std::pdd A = std::make_pair(ui->canvas->x_coords[pos], ui->canvas->y_coords[pos]);
//                        std::pdd B = std::make_pair(ui->canvas->x_coords[pos + 1], ui->canvas->y_coords[pos + 1]);
//                        std::pdd C = std::make_pair(ui->canvas->x_coords[pos + 2], ui->canvas->y_coords[pos + 2]);
//                        std::pdd D = std::make_pair(ui->canvas->x_coords[pos + 3], ui->canvas->y_coords[pos + 3]);
//                        std::pdd intersection = lineLineIntersection(A, B, C, D);
//                        if(intersection.first == INT_MAX && intersection.second == INT_MAX){
//                            QTextStream(stdout) << "Parallel" << Qt::endl;
//                        } else {
//                            paint.setBrush(Qt::red);
//                            paint.drawEllipse(intersection.first-2, intersection.second-2, 4, 4);
//                        }
//                    }
                }
                ui->canvas->setPixmap(pix);
            }
        }
    }
}



void MainWindow::on_resetButton_clicked()
{
    QPixmap pix(ui->canvas->size());
    ui->canvas->x_coords.clear();
    ui->canvas->y_coords.clear();
    pix.fill(Qt::transparent);
    ui->canvas->setPixmap(pix);
}

void MainWindow::on_singleButton_clicked()
{
    this->isSingleLine = true;
    on_resetButton_clicked();
}


void MainWindow::on_multiButton_clicked()
{
    this->isSingleLine = false;
    on_resetButton_clicked();
}
