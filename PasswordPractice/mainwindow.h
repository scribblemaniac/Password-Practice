#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>

#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_password_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString secret;
    int total;
    int correct;
    QSound bing, bong;
    std::vector<qint64> submitTimes;
};

#endif // MAINWINDOW_H
