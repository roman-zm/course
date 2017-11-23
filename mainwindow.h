#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "fileloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadFile();
    ~MainWindow();

private slots:
    void addComponentOnLeft(QListWidgetItem *inputItem);
    void removeComponentOnLeft(QListWidgetItem *inputItem);

private:
    void createTab(QString tabName);
    void addComponent(QString tabName, QString componentName);

    QListWidget *leftListWidget;
    QList<QStringList> mutatlyExcl;
    QMap<QString, QListWidget*> widgetInTab;
    fileLoader *loader;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
