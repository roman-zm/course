#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QFile>
#include <QMap>
#include <QStringList>

class fileLoader : public QObject
{
    Q_OBJECT
public:
    explicit fileLoader(QString fileName, QObject *parent = nullptr);
    QStringList getKeys();
    QStringList getComponents(QString key);
    QList<QStringList> getMutatlyExcl();

private:
    void parse();
    QString getSectionName(QString str);

    QFile *file;
    QStringList keys;
    QList<QStringList> mutatlyExcl;
    QString currentKey;
    QMap<QString, QStringList> map;
};

#endif // FILELOADER_H
