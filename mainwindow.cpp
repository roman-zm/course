#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileloader.h"

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loader = new fileLoader("components.txt", this);
    leftListWidget = new QListWidget(this);
    ui->tabWidget->addTab(leftListWidget, "Проектируемая модель");
    leftListWidget->addItem("Микроядро");

    QStringList keys = loader->getKeys();
    foreach (QString key, keys) {
        createTab(key);
    }

    connect(leftListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(removeComponentOnLeft(QListWidgetItem*)));
    mutatlyExcl = loader->getMutatlyExcl();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addComponentOnLeft(QListWidgetItem *inputItem)
{
    bool exists = false;
    QString inpName = inputItem->text();

    for(int i=0; i<leftListWidget->count(); i++){
        QString name = leftListWidget->item(i)->text();
        if(name == inpName) exists = true;
        foreach (auto excl, mutatlyExcl) {
            if(excl.contains(name) && excl.contains(inpName))
                exists = true;
        }
        if(exists) break;
    }

    if(!exists) leftListWidget->addItem(inpName);
}

void MainWindow::removeComponentOnLeft(QListWidgetItem *inputItem)
{
    QString inputName = inputItem->text();
    for(int i=0; i<leftListWidget->count(); i++){
        QString name = leftListWidget->item(i)->text();
        if(name == inputName) leftListWidget->takeItem(i);
    }
}

void MainWindow::createTab(QString tabName)
{
    widgetInTab[tabName] = new QListWidget(this);
    ui->tabWidget_2->addTab(widgetInTab[tabName], tabName);

    foreach(QString component, loader->getComponents(tabName)){
        addComponent(tabName, component);
    }
    connect(widgetInTab[tabName], SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(addComponentOnLeft(QListWidgetItem*)));
}

void MainWindow::addComponent(QString tabName, QString componentName)
{
    widgetInTab[tabName]->addItem(componentName);
}
