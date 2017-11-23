#include "fileloader.h"
#include <QFile>
#include <QApplication>
#include <QDir>
#include <QMessageBox>

fileLoader::fileLoader(QString fileName, QObject *parent) : QObject(parent)
{
    QString buffFileName = qApp->applicationDirPath() + QDir::separator() + fileName;
    file = new QFile(buffFileName, this);
    if(!file->open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",file->errorString());
        qApp->quit();
    }
    this->parse();
}

void fileLoader::parse()
{
    QString buffer;
    do {
        buffer = file->readLine();

        if(getSectionName(buffer) != ""){
            currentKey = getSectionName(buffer);
            if(currentKey != "MutatlyExclusive")
                keys.append(currentKey);
        } else {
            if(currentKey == "MutatlyExclusive"){
                if(buffer != "\n"){
                    buffer.chop(1);
                    mutatlyExcl.append(buffer.split(", "));
                }
            } else if(buffer != "" && buffer != "\n"){
                map[currentKey].append(buffer.left(buffer.size()-1));
            }
        }
    } while(buffer != "");
}

QString fileLoader::getSectionName(QString str)
{
    if(str[0] == '[' && str[str.size()-2] == ']'){
        return str.mid(1, str.size()-3);
    } else {
        return "";
    }
}

QStringList fileLoader::getKeys()
{
    return keys;
}

QStringList fileLoader::getComponents(QString key)
{
    return map[key];
}

QList<QStringList> fileLoader::getMutatlyExcl()
{
    return mutatlyExcl;
}
