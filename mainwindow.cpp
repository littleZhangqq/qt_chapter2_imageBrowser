#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <previewitem.h>
#include "previewwidget.h"
#include <QScrollArea>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QMessageBox>

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
    openView = new QWidget(this);
    openView->setStyleSheet("background-color:#999999");
    QVBoxLayout *v1 = new QVBoxLayout();
    openView->setLayout(v1);

    QVBoxLayout *centerBox = new QVBoxLayout();
    centerBox->setAlignment(Qt::AlignCenter);

    ui->pushButton->setIcon(QPixmap(":/images/openfile.png"));
    ui->pushButton->setStyleSheet("background-color:#BA7373");
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(openFileButtonClick()));
    centerBox->addWidget(ui->pushButton);
    v1->addLayout(centerBox);

    layout = new QVBoxLayout();
    scanView = new QWidget(this);
    scanView->setStyleSheet("background-color:#33333333");
    scanView->setLayout(layout);

    imageView = new QLabel();
    imageView->setAlignment(Qt::AlignCenter);
    QVBoxLayout *imageLayout = new QVBoxLayout();
    imageLayout->addWidget(imageView);

    QVBoxLayout *hlayout = new QVBoxLayout();

    QScrollArea *area = new QScrollArea();
    area->setFrameShape(QFrame::NoFrame);
    area->setWidgetResizable(true);
    hlayout->addWidget(area);

    listWidget = new QListWidget();
    listWidget->setStyleSheet("QListWidget { background-color: #B497FF; }""QListWidget::item:selected { background-color: yellow; }");
    area->setWidget(listWidget);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignBottom);

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

    QHBoxLayout *l1 = new QHBoxLayout();
    l1->addLayout(imageLayout);
    l1->addLayout(hlayout);
    l1->setStretch(0,4);
    l1->setStretch(1,1);

    layout->addLayout(l1);
    layout->addLayout(bottomLayout);

    layout->setStretch(0,16);
    layout->setStretch(1,1);

    stack = new QStackedLayout();
    stack->addWidget(openView);
    stack->addWidget(scanView);
    stack->setCurrentIndex(0);

    QWidget *window = new QWidget(this);
    window->setLayout(stack);
    setCentralWidget(window);

    connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onClickListItem(QListWidgetItem*)));
    connect(ui->previous,SIGNAL(clicked(bool)),this,SLOT(onClickPreviousImage()));
    connect(ui->next,SIGNAL(clicked(bool)),this,SLOT(onClickNextImage()));
}

void MainWindow::openFileButtonClick(){
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QStringList fileName = QFileDialog::getOpenFileNames(this, "选择文件", desktop, "All Files (*.png *.jpg)");
    if (!fileName.isEmpty()) {
        // 处理选择的文件
        // 可以使用 fileName 变量来获取选择的文件路径
        stack->setCurrentIndex(1);
        listWidget->clear();
        fileNames = fileName;
        for (int i = 0; i < fileName.length(); ++i) {
            QString path = fileName.at(i);
            QImage image = QImage(path);

            PreviewItem *item = new PreviewItem("");
            item->setSizeHint(QSize(60,100));
            item->index = i;
            item->path = path;
            previewWidget *wid = new previewWidget(this);
            wid->addItem("测试数据"+QString::number(i+1),image);
            listWidget->addItem(item);
            listWidget->setItemWidget(item,wid);
        }
    }
}

void MainWindow::onClickListItem(QListWidgetItem *item){
    int index = listWidget->row(item);
    selectRow = index;
    QImage image = QImage(fileNames.at(index));
    imageView->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::onClickPreviousImage(){
    if(selectRow > 0){
        QListWidgetItem *item = listWidget->item(selectRow-1);
        onClickListItem(item);
        listWidget->setCurrentItem(item);
    }else{
        QMessageBox::information(this,"提示","已经是第一张了","OK");
    }

}

void MainWindow::onClickNextImage(){
    if(selectRow < fileNames.length()-1){
        QListWidgetItem *item = listWidget->item(selectRow+1);
        onClickListItem(item);
        listWidget->setCurrentItem(item);
    }else{
        QMessageBox::information(this,"提示","已经是最后一张了","OK");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

