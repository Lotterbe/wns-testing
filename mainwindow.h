#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QCheckBox>
#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QRegExp>
#include <QSizePolicy>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QStringList>
#include <QTableView>
#include <QTabWidget>
#include <QTextStream>
#include <QToolButton>
#include <QValidator>


#include <fstream>
#include <iostream>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void renameTabs();

public slots:
    void actFunc(QAction* action);
    void addRow();
    void addTab(int i);
    void addTabButtonclicked(int i);
    void changeRow(int i);
    void clickAll(int i);
    void clickBox(QStandardItem *item);
    void fillTable(QString fileName);
    void loadFile(QString fName = "noFile");
    void removeRow();
    void removeTab(int i);
    void saveFile(QString fileName = "");
    void transmitData();


private:
    QString const lastSavePaths;

    Ui::MainWindow *ui;
    QTabWidget *tabWidget = new QTabWidget;




};

#endif // MAINWINDOW_H
