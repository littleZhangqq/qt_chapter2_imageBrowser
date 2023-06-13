#ifndef PREVIEWITEM_H
#define PREVIEWITEM_H

#include <QListWidgetItem>
#include <QBoxLayout>
#include <QLabel>

class PreviewItem :public QListWidgetItem
{

private:

public:
    PreviewItem(QString str);
    ~PreviewItem();
    int index = 0;
    QString path;
};

#endif // PREVIEWITEM_H
