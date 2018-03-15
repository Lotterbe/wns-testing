#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // SETUP UI

    ui->setupUi(this);


    this->setCentralWidget(this->tabWidget);


    //QWidget* widget = new QWidget();
    QWidget* addwidget = new QWidget();
    this->tabWidget->addTab(addwidget, "+");
    //this->tabWidget->addTab(widget, tr("NW-Stack ") + tr("1"));

    this->addTab(0);

    this->tabWidget->setTabsClosable(1);
    tabWidget->tabBar()->tabButton(1, QTabBar::RightSide)->resize(0, 0);
    tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);






    /*QGridLayout* gridlayout = new QGridLayout(widget);

    QLabel* label = new QLabel(widget);
    label->setText("Base adress:");
    QLineEdit* baseaddr = new QLineEdit(widget);

    QPushButton* addbutton = new QPushButton(widget);
    addbutton->setText("+ add row");



    gridlayout->addWidget(label,0,0,1,1);
    gridlayout->addWidget(baseaddr,0,1,1,1);
    gridlayout->addWidget(addbutton, 2,0,1,1);
    gridlayout->addWidget(this->view,1,0,1,4);

    widget->setLayout(gridlayout);



    // SETUP MODEL
    int row = 1;
    int col = 4;

    this->model->setParent(widget);
    this->model->insertRows(model->rowCount(),row);
    this->model->insertColumns(model->columnCount(),col);
    this->model->setHeaderData(0, Qt::Horizontal, tr("name"));
    this->model->setHeaderData(1, Qt::Horizontal, tr("Ip"));
    this->model->setHeaderData(2, Qt::Horizontal, tr("value"));
    this->model->setHeaderData(3, Qt::Horizontal, tr("read/write"));



    // SETUP VIEW

    this->view->setParent(widget);
    this->view->setModel(this->model);*/


    // Signals and Slots
    this->connect(this->tabWidget, SIGNAL(tabBarClicked(int)),this, SLOT(addTab(int)));
    this->connect(this->tabWidget->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(removeTab(int)));

    //QPushButton* actualbutton = this->tabWidget->currentWidget()->findChild<QPushButton*>();
    //this->connect(addbutton, SIGNAL(clicked(bool)), this, SLOT(addRow()));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addTab(int i) {
    if(this->tabWidget->tabText(i) == "+"){
        int j = this->tabWidget->addTab(new QWidget, QString("NW-Stack")+ QString::number(i+1));
        QWidget *newwidget = this->tabWidget->widget(j);
        this->tabWidget->tabBar()->moveTab(j,i);
        this->tabWidget->setCurrentIndex(i);


        QGridLayout* newgridlayout = new QGridLayout(newwidget);

        QLabel* newlabel = new QLabel(newwidget);
        newlabel->setText("Base adress:");
        QLineEdit* newbaseaddr = new QLineEdit(newwidget);

        QPushButton* newaddbutton = new QPushButton(newwidget);
        newaddbutton->setText("+ add row");
        QPushButton* newremovebutton = new QPushButton(newwidget);
        newremovebutton->setText("- remove row");
        QPushButton* clickbutton = new QPushButton(newwidget);
        clickbutton->setText("(un-)/click all");

        this->connect(newaddbutton, SIGNAL(clicked(bool)), this, SLOT(addRow()));
        this->connect(newremovebutton, SIGNAL(clicked(bool)), this, SLOT(removeRow()));
        this->connect(clickbutton, SIGNAL(clicked(bool)), this, SLOT(clickAll()));



        // SETUP MODEL
        int row = 1;
        int col = 4;
        QStandardItemModel *newmodel = new QStandardItemModel(newwidget);

        newmodel->insertRows(newmodel->rowCount(),row);
        newmodel->insertColumns(newmodel->columnCount(),col);
        newmodel->setHeaderData(0, Qt::Horizontal, tr("name"));
        newmodel->setHeaderData(1, Qt::Horizontal, tr("Ip"));
        newmodel->setHeaderData(2, Qt::Horizontal, tr("value"));
        newmodel->setHeaderData(3, Qt::Horizontal, tr("read/write"));

        QStandardItem* checkitem = new QStandardItem;
        newmodel->setItem(0,3,checkitem);
        checkitem->setCheckable(2);
        checkitem->setEditable(0);
        //checkitem->setTextAlignment(Qt::AlignRight);
        checkitem->setData(Qt::AlignRight, Qt::TextAlignmentRole);

        //pCheckBox->setStyleSheet("margin-left:50%; margin-right:50%;");




        // SETUP VIEW
        QTableView *newview = new QTableView(newwidget);
        newview->setModel(newmodel);
        newview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //newview->set



        newgridlayout->addWidget(newlabel,0,0,1,1);
        newgridlayout->addWidget(newbaseaddr,0,1,1,1);
        newgridlayout->addWidget(clickbutton,1,3,1,1);
        newgridlayout->addWidget(newview,2,0,1,4);
        newgridlayout->addWidget(newaddbutton, 3,0,1,1);
        newgridlayout->addWidget(newremovebutton,4,0,1,1);

        newwidget->setLayout(newgridlayout);

        // Validators

        QRegExp rx("(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])");
        QValidator *ipvalidator = new QRegExpValidator(rx, this);
        newbaseaddr->setValidator(ipvalidator);

        //->setValidator(validator);
        //ValidIpAddressRegex = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";

        //ValidHostnameRegex = "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$";
        // found at https://stackoverflow.com/questions/106179/regular-expression-to-match-dns-hostname-or-ip-address

    }
}

void MainWindow::removeTab(int i){
    this->tabWidget->removeTab(i);
    if(i>0){
        this->tabWidget->setCurrentIndex(i-1);
    }

}

void MainWindow::addRow(){
    QStandardItem* newitem = new QStandardItem;
    QStandardItem* newcheckitem = new QStandardItem;
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();

    actualmodel->appendRow(newitem);

    actualmodel->setItem(actualmodel->rowCount()-1,3,newcheckitem);
    newcheckitem->setCheckable(2);
    newcheckitem->setEditable(0);
}


void MainWindow::removeRow(){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    actualmodel->removeRow(actualmodel->rowCount()-1);
}


void MainWindow::clickAll(){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    int numrow = actualmodel->rowCount();
    bool checkallindex = false;

    for (int i=0; i < numrow; i++){
        if(actualmodel->item(i,3)->checkState() != Qt::Checked){
            checkallindex = true;
        }
    }

    if(checkallindex == true){
        for (int i=0; i < numrow; i++){
            actualmodel->item(i, 3)->setCheckState(Qt::Checked);
        }
    }
    else{
        for (int i=0; i < numrow; i++){
            actualmodel->item(i, 3)->setCheckState(Qt::Unchecked);
        }
    }

}
