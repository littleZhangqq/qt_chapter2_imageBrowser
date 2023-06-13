#include "previewwidget.h"
#include "ui_previewwidget.h"
#include <QBoxLayout>

previewWidget::previewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::previewWidget)
{
    ui->setupUi(this);
}

void previewWidget::addItem(QString str,QImage image){
    QVBoxLayout *v = new QVBoxLayout();
    ui->titleLabel->setText(str);
    ui->titleLabel->setAlignment(Qt::AlignCenter);
    ui->titleLabel->setStyleSheet("background-color:#00000000");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setStyleSheet("background-color:#00000000");
    v->addWidget(ui->titleLabel);
    v->addWidget(ui->imageLabel);
    this->setLayout(v);
    v->setStretch(0,1);
    v->setStretch(1,4);
}

previewWidget::~previewWidget()
{
    delete ui;
}
