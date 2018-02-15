#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRegExp>
#include <QSizePolicy>
#include <QStandardItemModel>
#include <QTableView>
#include <QTabWidget>
#include <QValidator>

#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addRow();
    void addTab(int i);
    void removeRow();
    void removeTab(int i);
    void clickAll();

private:
    Ui::MainWindow *ui;
    //QStandardItemModel *model = new QStandardItemModel;
    //QTableView *view = new QTableView;
    QTabWidget *tabWidget = new QTabWidget;
   // QPushButton *addbutton;




};

#endif // MAINWINDOW_H
