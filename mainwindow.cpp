#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AXI_Wrapper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastSavePaths("LAST_SAVE_PATHS.txt")
{

    // SETUP UI

    ui->setupUi(this);
    this->setCentralWidget(this->tabWidget);
    this->ui->mainToolBar->hide();


    QMenu *saveMenu = menuBar()->addMenu(tr("save"));
    saveMenu->addAction(tr("save tab"));
    saveMenu->addAction(tr("save all"));
    this->connect(saveMenu, SIGNAL(triggered(QAction*)), this, SLOT(actFunc(QAction*)));

    QMenu *loadMenu = menuBar()->addMenu(tr("load"));
    loadMenu->addAction(tr("load tab"));
    loadMenu->addAction(tr("load tabs"));
    this->connect(loadMenu, SIGNAL(triggered(QAction*)), this, SLOT(actFunc(QAction*)));

    QWidget* addwidget = new QWidget();
    this->tabWidget->addTab(addwidget, "+");

    QLabel *label = new QLabel(addwidget);
    label->setText("Please click the + to add a new tab.");

    QGridLayout *addLayout = new QGridLayout(addwidget);
    addLayout->addWidget(label);
    addwidget->setLayout(addLayout);

    this->addTab(0);
    this->tabWidget->setTabsClosable(1);
    tabWidget->tabBar()->tabButton(1, QTabBar::RightSide)->resize(0, 0);

    // Lädt zuletzt gespeicherte oder geöffnete Datei

    int i = 0;

    QString qS;
    QFile qF(this->lastSavePaths);
    if(qF.open(QIODevice::ReadOnly)){
        QTextStream qTS(&qF);
        while(!qTS.atEnd()) {
            qTS >> qS;
            if(qS != ""){
                if(i >  0){
                    this->addTab(i);
                }
                this->fillTable(qS);
                i = i+1;
            }
        }
    }
    qF.close();



    this->tabWidget->setCurrentIndex(0);



    // Signals and Slots

    this->connect(this->tabWidget, SIGNAL(tabBarClicked(int)),this, SLOT(addTabButtonclicked(int)));
    this->connect(this->tabWidget->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(removeTab(int)));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTabButtonclicked(int i){
    if(this->tabWidget->tabText(i) == "+"){
        this->addTab(i);
    }
}


void MainWindow::addTab(int i) {

    if(this->tabWidget->tabText(i) == "+"){
        int j = this->tabWidget->addTab(new QWidget, QString("NW-Stack")+ QString::number(i+1));

        this->tabWidget->tabBar()->moveTab(j,i);
        this->tabWidget->setCurrentIndex(i);
    }

    else{
        this->tabWidget->addTab(new QWidget, QString("NW-Stack")+ QString::number(i+1));
        this->tabWidget->setCurrentIndex(i);
    }

    QWidget* newwidget = this->tabWidget->currentWidget();

    QGridLayout* newgridlayout = new QGridLayout(newwidget);

    QLabel* newlabel = new QLabel(newwidget);
    newlabel->setText("Base adress:");

    QLineEdit* newbaseaddr = new QLineEdit(newwidget);
    newbaseaddr->setToolTip("write in hexadecimal representation");

    QLabel *rowlabel = new QLabel(newwidget);
    rowlabel->setText("row number");

    QSpinBox *rowspin = new QSpinBox(newwidget);
    rowspin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton* newconnectbutton = new QPushButton(newwidget);
    newconnectbutton->setText("transmit");
    newconnectbutton->setStyleSheet("background-color: grey; border-color: grey; color: white; font: 10px; ");
    newconnectbutton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    QWidget* spacew = new QWidget(newwidget);
    spacew->setFixedHeight(10);

    QCheckBox* checkbox = new QCheckBox(newwidget);
    checkbox->setText("(un-)click all");

    // Signals and Slots
    this->connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(clickAll(int)));
    this->connect(newconnectbutton, SIGNAL(clicked(bool)), this, SLOT(transmitData()));
    this->connect(rowspin, SIGNAL(valueChanged(int)), this, SLOT(changeRow(int)));



    // SETUP MODEL

    int row = 1;
    int col = 5;
    QStandardItemModel *newmodel = new QStandardItemModel(newwidget);

    newmodel->insertColumns(newmodel->columnCount(),col);
    newmodel->setHeaderData(0, Qt::Horizontal, tr("name"));
    newmodel->setHeaderData(1, Qt::Horizontal, tr("offset"));
    newmodel->setHeaderData(2, Qt::Horizontal, tr("value"));
    newmodel->setHeaderData(3, Qt::Horizontal, tr("read"));
    newmodel->setHeaderData(4, Qt::Horizontal, tr("write"));

    for(int i=0; i < row; i++){
        this->addRow();
        rowspin->setValue(i+1);
    }

    this->connect(newmodel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(clickBox(QStandardItem*)));


    // SETUP VIEW

    QTableView *newview = new QTableView(newwidget);
    newview->setModel(newmodel);
    newview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // tab Layout

    newgridlayout->addWidget(newlabel,0,0,1,1);
    newgridlayout->addWidget(newbaseaddr,0,1,1,1);
    newgridlayout->addWidget(checkbox,7,3,1,1);
    newgridlayout->addWidget(newview,3,0,4,4);
    newgridlayout->addWidget(rowlabel,7,0,1,1);
    newgridlayout->addWidget(rowspin, 7,1,1,1);
    newgridlayout->addWidget(newconnectbutton,0,2,1,1);

    newwidget->setLayout(newgridlayout);

    // Validators

    QRegExp rx("[0-9,a-f]{1,8}");
    QValidator *ipvalidator = new QRegExpValidator(rx, this);
    newbaseaddr->setValidator(ipvalidator);

}


void MainWindow::changeRow(int i){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    int diff = actualmodel->rowCount() - i;

    if(diff > 0){
        for(int k=0; k < diff; k++){
            this->removeRow();
        }
    }
    else if(diff < 0){
        for(int k=0; k > diff; k--){
            this->addRow();
        }
    }
}


void MainWindow::removeTab(int i){
    this->tabWidget->removeTab(i);
    if(i>0){
        this->tabWidget->setCurrentIndex(i-1);
    }
    this->renameTabs();
}


void MainWindow::renameTabs(){
    for(int i=0; i<this->tabWidget->count()-1; i++){
        this->tabWidget->setTabText(i, QString("NW-Stack")+ QString::number(i+1));
    }
}


void MainWindow::addRow(){
    QStandardItem* newitem = new QStandardItem;
    QStandardItem* newreaditem = new QStandardItem;
    QStandardItem* newwriteitem = new QStandardItem;
    QStandardItem* newoffitem = new QStandardItem;
    QStandardItem* newvalueitem = new QStandardItem;
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();

    int rownumber = actualmodel->rowCount();

    actualmodel->appendRow(newitem);
    actualmodel->setItem(rownumber,1,newoffitem);
    actualmodel->setItem(rownumber,2,newvalueitem);
    actualmodel->setItem(rownumber,3,newreaditem);
    actualmodel->setItem(rownumber,4,newwriteitem);


    newreaditem->setCheckable(2);
    newreaditem->setCheckState(Qt::Checked);
    newreaditem->setEditable(0);
    newwriteitem->setCheckable(2);
    newwriteitem->setEditable(0);

    newitem->setText("name" + QString::number(rownumber));
    newoffitem->setToolTip("write in hexadecimal representation");
}


void MainWindow::removeRow(){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    actualmodel->removeRow(actualmodel->rowCount()-1);
}


void MainWindow::clickAll(int i){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    int numrow = actualmodel->rowCount();


    if(i == 2){
        for (int i=0; i < numrow; i++){
            actualmodel->item(i, 3)->setCheckState(Qt::Checked);
            actualmodel->item(i, 4)->setCheckState(Qt::Unchecked);
        }
    }
    else{
        for (int i=0; i < numrow; i++){
            actualmodel->item(i, 3)->setCheckState(Qt::Unchecked);
            actualmodel->item(i, 4)->setCheckState(Qt::Checked);
        }
    }
}


void MainWindow::clickBox(QStandardItem *item){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();

    int col = item->column();
    int row = item->row();

    if(actualmodel->item(row, 4)!= nullptr){
        if(col == 3){
            if(item->checkState()==2){
                actualmodel->item(row, 4)->setCheckState(Qt::Unchecked);
            }
            else if(item->checkState()==0){

                actualmodel->item(row, 4)->setCheckState(Qt::Checked);
            }

        }
        else if(col == 4){
                if(item->checkState()==2){
                    actualmodel->item(row, 3)->setCheckState(Qt::Unchecked);
                }
                else if(item->checkState()==0){
                    actualmodel->item(row, 3)->setCheckState(Qt::Checked);
                }
        }
    }
}


void MainWindow::loadFile(QString fName){
    if(fName=="noFile"){
        fName = QFileDialog::getOpenFileName(this, tr("Load tab"), "", tr("Text files (*.txt)"));

        QFile qF(this->lastSavePaths);
            qF.open(QIODevice::WriteOnly);
            QTextStream qTS(&qF);
            qTS << fName;
            qF.close();
    }
    if (fName=="")
    {
        std::cout << "Could not open file - please check filename" << std::endl;
        return;
    }
    else
    {
        this->fillTable(fName);

    }

    this->renameTabs();
}


void MainWindow::fillTable(QString fileName){

    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    QLineEdit *baseadress = this->tabWidget->currentWidget()->findChild<QLineEdit*>();
    QSpinBox *rowspin = this->tabWidget->currentWidget()->findChild<QSpinBox*>();
    int numrow = actualmodel->rowCount();

    QFile dir(fileName);
    std::string base;
    std::vector<std::string> vw, vx, vy;
    std::vector<int> vz;
    int dz;
    std::string dw, dx, dy;

    if (dir.exists())
    {
        std::ifstream file(fileName.toStdString());
        file >> base;
        while (file >> dw >> dx >> dy >> dz)
        {
           vw.push_back(dw);
           vx.push_back(dx);
           vy.push_back(dy);
           vz.push_back(dz);
        }
        file.close();

        int num = vw.size();
        if(vw.size() >  numrow){
            int add = vw.size() - numrow;
            for(int j=0; j<add; j++){
                this->addRow();
            }

        rowspin->setValue(num);
        }
        baseadress->setText(QString::fromStdString(base));
        for(int i = 0; i < num; i++){
            actualmodel->item(i,0)->setText(QString::fromStdString(vw.at(i)));
            actualmodel->item(i,1)->setText(QString::fromStdString(vx.at(i)));
            actualmodel->item(i,2)->setText(QString::fromStdString(vy.at(i)));
            actualmodel->item(i,3)->setCheckState((Qt::CheckState)vz.at(i));
        }
    }
}


void MainWindow::saveFile(QString fileName){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    QLineEdit *baseadress = this->tabWidget->currentWidget()->findChild<QLineEdit*>();

    int numrow = actualmodel->rowCount();

    if(fileName ==""){
        fileName = QFileDialog::getSaveFileName(this, tr("Save table as *.txt"), "", tr("Text files (*.txt)"));
        QFile qF(this->lastSavePaths);
            qF.open(QIODevice::WriteOnly);
            QTextStream qTS(&qF);
            qTS << fileName;
            qF.close();
    }
    if(fileName != ""){
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream qTSfile(&file);
        qTSfile << baseadress->text() << "\r\n";
        for(int i=0; i < numrow; i+=1){
            if(actualmodel->item(i,1)->text()!="" && actualmodel->item(i,2)->text()!=""){
                qTSfile << actualmodel->item(i,0)->text() << "\t" << actualmodel->item(i,1)->text() << "\t" <<
                       actualmodel->item(i,2)->text() << "\t" << actualmodel->item(i,3)->checkState() << "\r\n";
            }
        }
        file.close();
    }
}



void MainWindow::actFunc(QAction *action){
    if(action->text()=="save tab"){
        this->saveFile();
    }
    if(action->text()=="load tab"){
        this->loadFile();
    }
    else{
        int tabcounter = this->tabWidget->count();
        if(action->text()=="save all"){
            QString dirName = QFileDialog::getExistingDirectory(this, tr("Save tabs in directory"));
            if(dirName != ""){
                QFile qF(this->lastSavePaths);
                qF.open(QIODevice::Truncate | QIODevice::WriteOnly);
                qF.close();

                for(int i=tabcounter-2; i>=0; i--){
                    QString name = dirName + QDir::toNativeSeparators("/") + this->tabWidget->tabText(i) + QString(".txt");
                    this->tabWidget->setCurrentIndex(i);
                    this->saveFile(name);

                    QFile qF(this->lastSavePaths);
                    qF.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream qTS(&qF);
                    qTS << name << endl;
                    qF.close();
                }
            }
        }
        else if(action->text()=="load tabs"){
            QString dirName = QFileDialog::getExistingDirectory(this, tr("Load tabs from directory"));
            if(dirName != ""){
                QDir dir = QDir(dirName);
                QFileInfoList infolist = dir.entryInfoList(QDir::Files);
                int listnumber = infolist.count();

                QFile qF(this->lastSavePaths);
                qF.open(QIODevice::Truncate | QIODevice::WriteOnly);
                qF.close();

                for(int i=0; i<listnumber; i++){
                    QString fileName = infolist.at(i).filePath();
                    this->addTab(tabcounter-1+i);
                    this->loadFile(fileName);

                    QFile qF(this->lastSavePaths);
                    qF.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream qTS(&qF);
                    qTS << endl << fileName;

                    qF.close();
                }
            }
        }
    }
}


void MainWindow::transmitData(){
    std::cout << std::endl;
    std::cout << "*******************************************************************" << std::endl;
    std::cout << "************************** transmit data **************************" << std::endl;
    std::cout << "*******************************************************************" << std::endl << std::endl;

    QLineEdit *baseadress = this->tabWidget->currentWidget()->findChild<QLineEdit*>();
    bool ok;
    uint32_t base = baseadress->text().toUInt(&ok, 16);
    AXI_Wrapper* wrapper = new AXI_Wrapper();
    std::cout << "initalized AXI_Wrapper" << std::endl;
    int map = wrapper->Init_Emu(base); //Emulator
    //int map = wrapper->Init(base); // sudo-Rechte

    if(map == 1){
        std::cout << "Could not initialize AXI_Wrapper object, because you are missing sudo rights" << std::endl;
    }
    else{
        QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
        int numrow = actualmodel->rowCount();


        for(int i=0; i<numrow; i++){
            uint32_t offset = actualmodel->item(i,1)->text().toUInt(&ok, 16);
            if(actualmodel->item(i,3)->checkState() == 0){
                uint32_t value = actualmodel->item(i,2)->text().toUInt(&ok, 16);
                wrapper->write(offset, value);
            }
            else{
                uint32_t value = wrapper->read(offset);
                actualmodel->item(i,2)->setText(QString("0x%1").arg(value,8, 16, QLatin1Char( '0' )));
            }
        }
    }
}
