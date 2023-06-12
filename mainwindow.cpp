#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("小强图片浏览器");
    this->resize(600,400);
    createMainView();
}

void MainWindow::createMainView(){
    layout = new QVBoxLayout();
    QWidget *view = new QWidget(this);
    view->setLayout(layout);
    setCentralWidget(view);
    view->setStyleSheet("background-color:#6F48FF");

    QVBoxLayout *centerBox = new QVBoxLayout();
    centerBox->setAlignment(Qt::AlignCenter);

    ui->pushButton->setIcon(QPixmap(":/images/openfile.png"));
    ui->pushButton->setStyleSheet("background-color:#BA7373");
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(openFileButtonClick()));
    centerBox->addWidget(ui->pushButton);
    layout->addLayout(centerBox);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignBottom);
    layout->addLayout(bottomLayout);

    ui->holder1->setStyleSheet("background-color:#00FFFFFF");
    bottomLayout->addWidget(ui->holder1);

    ui->previous->setIcon(QPixmap(":/images/previous.png"));
    bottomLayout->addWidget(ui->previous);

    ui->holder2->setStyleSheet("background-color:#00FFFFFF");
    bottomLayout->addWidget(ui->holder2);

    ui->next->setIcon(QPixmap(":/images/next.png"));
    bottomLayout->addWidget(ui->next);

    ui->holder3->setStyleSheet("background-color:#00FFFFFF");
    bottomLayout->addWidget(ui->holder3);

    layout->setStretch(0,4);
    layout->setStretch(1,1);

}

void MainWindow::openFileButtonClick(){

}

MainWindow::~MainWindow()
{
    delete ui;
}

