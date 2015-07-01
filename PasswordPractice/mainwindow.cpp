#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    total(0),
    correct(0),
    bing(":/sound/correct.wav"),
    bong(":/sound/incorrect.wav")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_password_editingFinished()
{
    if(secret.isEmpty()) {
        secret = ui->password->text();
    }
    else {
        ++total;
        submitTimes.push_back(QDateTime::currentMSecsSinceEpoch());
        if(secret == ui->password->text()) {
            ++correct;
            if(bing.isFinished() && bong.isFinished() && ui->playSounds->isChecked()) {
                bing.play();
            }
        }
        else {
            if(bong.isFinished() && bong.isFinished() && ui->playSounds->isChecked()) {
                bong.play();
            }
        }
    }
    ui->password->setText("");
    if(total != 0) {
        ui->correct->setText(QString::number(correct) + "/" + QString::number(total) + " Correct");
        ui->accuracy->setText(QString::number(round(static_cast<double>(correct) / total * 1000) / 10) + "% Accuracy");

        while(!submitTimes.empty() && submitTimes.back() - submitTimes.front() > 60000) {
            submitTimes.erase(submitTimes.begin());
        }

        if(submitTimes.empty() || submitTimes.front() == submitTimes.back()) {
            ui->speed->setText("0 Passwords Per Minute");
        }
        else {
            ui->speed->setText(QString::number(round(static_cast<double>(submitTimes.size()) / (submitTimes.back() - submitTimes.front()) * 60000)) + " Passwords Per Minute");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    total = 0;
    correct = 0;
    submitTimes.erase(submitTimes.begin(), submitTimes.end());
    secret = "";
    ui->correct->setText("0/0 Correct");
    ui->accuracy->setText("0% Accuracy");
    ui->speed->setText("0 Passwords Per Minute");
}
