#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QListWidget>
#include <previewitem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFileButtonClick();
    void onClickListItem(QListWidgetItem *item);
    void onClickPreviousImage();
    void onClickNextImage();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout;
    QWidget *openView;
    QWidget *scanView;
    QLabel *imageView;
    QListWidget *listWidget;
    QStackedLayout *stack;
    QStringList fileNames;
    int selectRow;
    void createMainView();
};
#endif // MAINWINDOW_H
