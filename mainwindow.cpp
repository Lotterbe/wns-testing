#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastSavePaths("LAST_SAVE_PATHS.txt")//,
    //tmpCfgFile("tmp.cfg")
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
    //tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);


    int i = 0;

    QString qS;
    QFile qF(this->lastSavePaths);
    if(qF.open(QIODevice::ReadOnly)){
        QTextStream qTS(&qF);
        while(!qTS.atEnd()) {
            qTS >> qS;
            std::cout << qS.toStdString() << std::endl;
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
        //QWidget* newwidget = this->tabWidget->widget(j);
        this->tabWidget->tabBar()->moveTab(j,i);
        this->tabWidget->setCurrentIndex(i);
    }

    else{
        this->tabWidget->addTab(new QWidget, QString("NW-Stack")+ QString::number(i+1));
        //QWidget* newwidget = this->tabWidget->widget(i);
        //this->tabWidget->tabBar()->moveTab(j,i);
        this->tabWidget->setCurrentIndex(i);
    }

    QWidget* newwidget = this->tabWidget->currentWidget();

    QGridLayout* newgridlayout = new QGridLayout(newwidget);

    QLabel* newlabel = new QLabel(newwidget);
    newlabel->setText("Base adress:");
    QLineEdit* newbaseaddr = new QLineEdit(newwidget);
    newbaseaddr->setToolTip("write in hexadecimal representation");

    QPushButton* newaddbutton = new QPushButton(newwidget);
    newaddbutton->setText("+ row");
    QPushButton* newremovebutton = new QPushButton(newwidget);
    newremovebutton->setText("- row");
    newremovebutton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    /*QPushButton* loadbutton = new QPushButton(newwidget);
    loadbutton->setText("load");
    loadbutton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton* savebutton = new QPushButton(newwidget);
    savebutton->setText("save");
    savebutton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);*/
    QPushButton* newconnectbutton = new QPushButton(newwidget);
    newconnectbutton->setText("transmit");
    newconnectbutton->setStyleSheet("background-color: grey; border-color: grey; color: white; font: 10px; ");
    newconnectbutton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    //newconnectbutton->setStyle(QStyleOptionButton::Flat);
    QWidget* spacew = new QWidget(newwidget);
    spacew->setFixedHeight(10);

    QCheckBox* checkbox = new QCheckBox(newwidget);
    checkbox->setText("(un-)click all");


    this->connect(newaddbutton, SIGNAL(clicked(bool)), this, SLOT(addRow()));
    this->connect(newremovebutton, SIGNAL(clicked(bool)), this, SLOT(removeRow()));
    //this->connect(loadbutton, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    //this->connect(savebutton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    this->connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(clickAll(int)));



    // SETUP MODEL
    int row = 1;
    int col = 4;
    QStandardItemModel *newmodel = new QStandardItemModel(newwidget);

    newmodel->insertColumns(newmodel->columnCount(),col);
    newmodel->setHeaderData(0, Qt::Horizontal, tr("name"));
    newmodel->setHeaderData(1, Qt::Horizontal, tr("offset"));
    newmodel->setHeaderData(2, Qt::Horizontal, tr("value"));
    newmodel->setHeaderData(3, Qt::Horizontal, tr("read/write"));
    for(int i=0; i < row; i++){
        this->addRow();
    }

    // FÜR READ WRITE !! unsigned int, wegen Compiler??
    u_int32_t par = 203888026;
    //unsigned int par =  203888026;
    QString hex = QString("0x%1").arg(par,8, 16, QLatin1Char( '0' ));
    //hex.setNum(par, 16);

    //std::cout << hex.toStdString() << std::endl;

    //4294967295
    //2863311530
    newmodel->item(0,1)->setText(hex);
    bool ok;
    uint32_t d = newmodel->item(0,1)->text().toUInt(&ok, 16);
    //unsigned int d = newmodel->item(0,1)->text().toUInt(&ok, 16);
    //std::cout << d << std::endl;
    /*QStandardItem* checkitem = new QStandardItem;
    newmodel->setItem(0,3,checkitem);
    checkitem->setCheckable(2);
    checkitem->setEditable(0);
    //checkitem->setTextAlignment(Qt::AlignRight);
    checkitem->setData(Qt::AlignRight, Qt::TextAlignmentRole);*/

    //pCheckBox->setStyleSheet("margin-left:50%; margin-right:50%;");




    // SETUP VIEW
    QTableView *newview = new QTableView(newwidget);
    newview->setModel(newmodel);
    newview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //newview->set


    // tab Layout
    newgridlayout->addWidget(newlabel,0,0,1,1);
    newgridlayout->addWidget(newbaseaddr,0,1,1,1);
    newgridlayout->addWidget(checkbox,7,3,1,1);
    newgridlayout->addWidget(newview,3,0,4,4);
    newgridlayout->addWidget(newaddbutton, 7,0,1,1);
    newgridlayout->addWidget(newremovebutton,8,0,1,1);
    //newgridlayout->addWidget(loadbutton,0,3,1,1);
    //newgridlayout->addWidget(savebutton,1,3,1,1);
    newgridlayout->addWidget(newconnectbutton,0,2,1,1);
    //newgridlayout->addWidget(spacew, 1,0,1,5);

    //newconnectbutton->setStyleSheet("font: bold 14px; min-width: 10em;padding: 6px");

    newwidget->setLayout(newgridlayout);

    // Validators

    //QRegExp rx("(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])");
    //QRegExp rx("?:1\d?\d?|2(?:[0-4]\d?|[6789]|5[0-5]?)?|[3-9]\d?|0)(?:\.(?:1\d?\d?|2(?:[0-4]\d?|[6789]|5[0-5]?)?|[3-9]\d?|0)){3}");
    QRegExp rx("[0-9,a-f]{1,8}");
    QValidator *ipvalidator = new QRegExpValidator(rx, this);
    newbaseaddr->setValidator(ipvalidator);

    //->setValidator(validator);
    //ValidIpAddressRegex = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";

    //ValidHostnameRegex = "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$";
    // found at https://stackoverflow.com/questions/106179/regular-expression-to-match-dns-hostname-or-ip-address


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
    QStandardItem* newcheckitem = new QStandardItem;
    QStandardItem* newoffitem = new QStandardItem;
    QStandardItem* newvalueitem = new QStandardItem;
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    int rownumber = actualmodel->rowCount();

    actualmodel->appendRow(newitem);
    actualmodel->setItem(rownumber,1,newoffitem);
    actualmodel->setItem(rownumber,2,newvalueitem);
    actualmodel->setItem(rownumber,3,newcheckitem);


    newcheckitem->setCheckable(2);
    newcheckitem->setEditable(0);
    newitem->setText("name"+QString::number(rownumber));

    newoffitem->setToolTip("write in hexadecimal representation");

}


void MainWindow::removeRow(){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    actualmodel->removeRow(actualmodel->rowCount()-1);
}


void MainWindow::clickAll(int i){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    int numrow = actualmodel->rowCount();
    /*bool checkallindex = false;

    for (int i=0; i < numrow; i++){
        if(actualmodel->item(i,3)->checkState() != Qt::Checked){
            checkallindex = true;
        }
    }*/

    if(i == 2){
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
    int numrow = actualmodel->rowCount();

    QFile dir(fileName);
    std::vector<std::string> vw;
    std::vector<uint32_t> vx,vy;
    std::vector<int> vz;
    uint32_t dx,dy;
    int dz;
    std::string dw;

    if (dir.exists())
    {
        std::ifstream file(fileName.toStdString());
        while (file >> dw >> dx >> dy >> dz)
        {
           vw.push_back(dw);
           vx.push_back(dx);
           vy.push_back(dy);
           vz.push_back(dz);
        }
        file.close();
    }
    int num = vw.size();
    if(vw.size() >  numrow){
        int add = vw.size() - numrow;
        for(int j=0; j<add; j++){
            this->addRow();
        }
    }

    for(int i = 0; i < num; i++){
        actualmodel->item(i,0)->setText(QString::fromStdString(vw.at(i)));
        actualmodel->item(i,1)->setText(QString::number(vx.at(i)));
        actualmodel->item(i,2)->setText(QString::number(vy.at(i)));
        actualmodel->item(i,3)->setCheckState((Qt::CheckState)vz.at(i));
    }
}

void MainWindow::saveFile(QString fileName){
    QStandardItemModel* actualmodel =  this->tabWidget->currentWidget()->findChild<QStandardItemModel*>();
    int numrow = actualmodel->rowCount();

    if(fileName ==""){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save table as *.txt"), "", tr("Text files (*.txt)"));

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
                    std::cout << name.toStdString() << std::endl;
                    this->tabWidget->setCurrentIndex(i);
                    this->saveFile(name);

                    QFile qF(this->lastSavePaths);
                    qF.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream qTS(&qF);
                    qTS << name + QString::fromStdString("\n");
                    qF.close();
                }

            }

        }
        if(action->text()=="load tabs"){
            QString dirName = QFileDialog::getExistingDirectory(this, tr("Load tabs from directory"));
            if(dirName != ""){
                QDir dir = QDir(dirName);
                //QStringList list = dir.entryList();
                QFileInfoList infolist = dir.entryInfoList(QDir::Files);
                int listnumber = infolist.count();
                std::cout << listnumber << std::endl;

                QFile qF(this->lastSavePaths);
                qF.open(QIODevice::Truncate | QIODevice::WriteOnly);
                qF.close();

                for(int i=0; i<listnumber; i++){
                    //QString fileName = list.at(i);
                    QString fileName = infolist.at(i).filePath();
                    this->addTab(tabcounter-1+i);
                    this->loadFile(fileName);
                    std::cout << fileName.toStdString() << std::endl;

                    QFile qF(this->lastSavePaths);
                    qF.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream qTS(&qF);
                    qTS << QString::fromStdString("\n") + fileName;

                    qF.close();
                }

            }
        }
    }

}
