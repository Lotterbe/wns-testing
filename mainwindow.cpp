#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // SETUP UI

    ui->setupUi(this);

    QTabWidget* tabWidget = new QTabWidget(this);
    this->setCentralWidget(tabWidget);

    QWidget* widget = new QWidget();
    tabWidget->addTab(widget, "NW-Stack");

    QGridLayout* gridlayout = new QGridLayout(widget);

    QLabel* label = new QLabel(widget);
    label->setText("Base adress:");
    QLineEdit* baseaddr = new QLineEdit(widget);
    QWidget* viewwidget = new QWidget(widget);

    gridlayout->addWidget(viewwidget,1,0,1,4);
    gridlayout->addWidget(label,0,0,1,1);
    gridlayout->addWidget(baseaddr,0,1,1,1);
    widget->setLayout(gridlayout);

    // SETUP MODEL
    int row = 1;
    int col = 4;

    this->model.setParent(this);
    this->model.insertRows(model.rowCount(),row);
    this->model.insertColumns(model.columnCount(),col);


    // SETUP VIEW

    this->view.setParent(viewwidget);
    this->view.setModel(&this->model);

}

MainWindow::~MainWindow()
{
    delete ui;
}
