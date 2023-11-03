#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <windows.h>
#include <filesystem>

namespace fs = std::filesystem;

class MainWindow;

class CustomListWidget : public QListWidget
{
public:
    CustomListWidget(QWidget *parent = nullptr);
    QListWidget(parent);

    void setW(MainWindow* w2){
        win = w2;
    }

    void updatePaths(fs::path path);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
            event->acceptProposedAction();
        }
    }

    void dropEvent(QDropEvent *event) override
    {
        QByteArray itemData = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        while (!dataStream.atEnd()) {
            int row, col;
            QMap<int, QVariant> roleDataMap;
            dataStream >> row >> col >> roleDataMap;

            if (col == 0) {
                // Ignore drops on the same list
                if (this != event->source()) {
                    // Create a new QListWidgetItem with the same text
                    //                    QListWidgetItem *item = new QListWidgetItem(roleDataMap[Qt::DisplayRole].toString());
                    //                    addItem(item);
                    fs::path path = roleDataMap[Qt::DisplayRole].toString().toStdString();
                    updatePaths(path);
                    event->setDropAction(Qt::CopyAction);
                    event->accept();
                }
            }
        }
    }

private:
    MainWindow* win;

signals:

};
#endif // CUSTOMLISTWIDGET_H
